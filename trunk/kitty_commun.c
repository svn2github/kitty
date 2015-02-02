/*
 * Fichier contenant les procedures communes à tous les programmes putty, pscp, psftp, plink, pageant
 */

#include "kitty_commun.h"
#include "kitty_tools.h"

#ifdef PERSOPORT

#ifndef SAVEMODE_REG
#define SAVEMODE_REG 0
#endif
#ifndef SAVEMODE_FILE
#define SAVEMODE_FILE 1
#endif
#ifndef SAVEMODE_DIR
#define SAVEMODE_DIR 2
#endif

// Flag pour le fonctionnement en mode "portable" (gestion par fichiers)
#ifdef PORTABLE
int IniFileFlag = SAVEMODE_DIR ;
#else
int IniFileFlag = SAVEMODE_REG ;
#endif

// Flag permettant la gestion de l'arborscence (dossier=folder) dans le cas d'un savemode=dir
#ifdef PORTABLE
int DirectoryBrowseFlag = 1 ;
#else
int DirectoryBrowseFlag = 0 ;
#endif

// Flag permettant de sauvegarder automatique les cles SSH des serveurs
int AutoStoreSSHKeyFlag = 0 ;

// Répertoire de sauvegarde de la configuration (savemode=dir)
char * ConfigDirectory = NULL ;

char * GetConfigDirectory( void ) { return ConfigDirectory ; }

int stricmp(const char *s1, const char *s2) ;
int readINI( const char * filename, const char * section, const char * key, char * pStr) ;
char * SetSessPath( const char * dec ) ;

// Nettoie les noms de folder en remplaçant les "/" par des "\" et les " \ " par des " \"
void CleanFolderName( char * folder ) {
	int i, j ;
	if( folder == NULL ) return ;
	if( strlen( folder ) == 0 ) return ;
	for( i=0 ; i<strlen(folder) ; i++ ) if( folder[i]=='/' ) folder[i]='\\' ;
	for( i=0 ; i<(strlen(folder)-1) ; i++ ) 
		if( folder[i]=='\\' ) 
			while( folder[i+1]==' ' ) for( j=i+1 ; j<strlen(folder) ; j++ ) folder[j]=folder[j+1] ;
	for( i=(strlen(folder)-1) ; i>0 ; i-- )
		if( folder[i]=='\\' )
			while( folder[i-1]==' ' ) {
				for( j=i-1 ; j<strlen(folder) ; j++ ) folder[j]=folder[j+1] ;
				i-- ;
				}
	}

#include <sys/types.h>
#include <dirent.h>
#define MAX_VALUE_NAME 16383
// Supprime une arborescence
void DelDir( const char * directory ) {
	DIR * dir ;
	struct dirent * de ;
	char fullpath[MAX_VALUE_NAME] ;

	if( (dir=opendir(directory)) != NULL ) {
		while( (de=readdir( dir ) ) != NULL ) 
		if( strcmp(de->d_name,".") && strcmp(de->d_name,"..") ) {
			sprintf( fullpath, "%s\\%s", directory, de->d_name ) ;
			if( GetFileAttributes( fullpath ) & FILE_ATTRIBUTE_DIRECTORY ) { DelDir( fullpath ) ; }
			else if( !(GetFileAttributes( fullpath ) & FILE_ATTRIBUTE_DIRECTORY) ) { unlink( fullpath ) ; }
			}
		closedir( dir ) ;
		_rmdir( directory ) ;
		}
	}


/* test if we are in portable mode by looking for putty.ini or kitty.ini in running directory */
int IsPortableMode( void ) {
	FILE * fp = NULL ;
	int ret = 0 ;
	char buffer[256] ;

	if( (fp = fopen( "putty.ini", "r" )) != NULL ) {
		fclose(fp ) ;
		if( readINI( "putty.ini", "PuTTY", "savemode", buffer ) ) {
			while( (buffer[strlen(buffer)-1]=='\n')||(buffer[strlen(buffer)-1]=='\r')
				||(buffer[strlen(buffer)-1]==' ')
				||(buffer[strlen(buffer)-1]=='\t') ) buffer[strlen(buffer)-1]='\0';
			if( !stricmp( buffer, "registry" ) ) IniFileFlag = SAVEMODE_REG ;
			else if( !stricmp( buffer, "file" ) ) IniFileFlag = SAVEMODE_FILE ;
			else if( !stricmp( buffer, "dir" ) ) { IniFileFlag = SAVEMODE_DIR ; DirectoryBrowseFlag = 1 ; ret = 1 ; }
			}
		if(  IniFileFlag == SAVEMODE_DIR ) {
			if( readINI( "putty.ini", "PuTTY", "browsedirectory", buffer ) ) {
				if( !stricmp( buffer, "NO" )&&(IniFileFlag==SAVEMODE_DIR) ) DirectoryBrowseFlag = 0 ; 
				else DirectoryBrowseFlag = 1 ;
				}
			if( readINI( "putty.ini", "PuTTY", "configdir", buffer ) ) { 
				if( strlen( buffer ) > 0 ) { 
					ConfigDirectory = (char*)malloc( strlen(buffer) + 1 ) ;
					strcpy( ConfigDirectory, buffer ) ;
					}
				}
			}
		else  DirectoryBrowseFlag = 0 ;
		}
	else if( (fp = fopen( "kitty.ini", "r" )) != NULL ) {
		fclose(fp ) ;
		if( readINI( "kitty.ini", "KiTTY", "savemode", buffer ) ) {
			while( (buffer[strlen(buffer)-1]=='\n')||(buffer[strlen(buffer)-1]=='\r')
				||(buffer[strlen(buffer)-1]==' ')
				||(buffer[strlen(buffer)-1]=='\t') ) buffer[strlen(buffer)-1]='\0';
			if( !stricmp( buffer, "registry" ) ) IniFileFlag = SAVEMODE_REG ;
			else if( !stricmp( buffer, "file" ) ) IniFileFlag = SAVEMODE_FILE ;
			else if( !stricmp( buffer, "dir" ) ) { IniFileFlag = SAVEMODE_DIR ; ret = 1 ; }
			}
		if(  IniFileFlag == SAVEMODE_DIR ) {
			if( readINI( "kitty.ini", "KiTTY", "browsedirectory", buffer ) ) { 
				if( !stricmp( buffer, "NO" )&&(IniFileFlag==SAVEMODE_DIR) ) DirectoryBrowseFlag = 0 ; 
				else DirectoryBrowseFlag = 1 ;
				}
			if( readINI( "kitty.ini", "KiTTY", "configdir", buffer ) ) { 
				if( strlen( buffer ) > 0 ) { 
					ConfigDirectory = (char*)malloc( strlen(buffer) + 1 ) ;
					strcpy( ConfigDirectory, buffer ) ;
					}
				}
			}
		else  DirectoryBrowseFlag = 0 ;
		}
	else { printf( "No ini file\n" ) ; }
	return ret ;
	}

// Positionne un flag permettant de determiner si on est connecte
int backend_connected = 0 ;

void SetSSHConnected( void ) { backend_connected = 1 ; }

char *dupvprintf(const char *fmt, va_list ap) ;
void logevent(void *frontend, const char *string);

// Affichage d'un message dans l'event log
void debug_logevent( const char *fmt, ... ) {
	va_list ap;
	char *buf;

	if( debug_flag ) {
		va_start(ap, fmt);
		buf = dupvprintf(fmt, ap) ;
		va_end(ap);
		logevent(NULL,buf);
		free(buf);
		}
	}

PVOID SecureZeroMemory( PVOID ptr, SIZE_T cnt) { return memset( ptr, 0, cnt ) ; }

// Fonction permettant de changer le statut du stockage automatique des ssh host keys
void SetAutoStoreSSHKey( void ) {
	AutoStoreSSHKeyFlag = 1 ;
	}

// Gestion de la fenetre d'affichage des portforward
char*PortForwardMsg=NULL ;
void AddNewPortForwardMsg( char * st) {
	if( st!=NULL ){
		if( PortForwardMsg==NULL ) { PortForwardMsg=(char*)malloc(1); PortForwardMsg[0]='\0'; }
		PortForwardMsg=realloc(PortForwardMsg,strlen(PortForwardMsg)+strlen(st)+2);
		strcat(PortForwardMsg,st);
		}
	}
#endif

#ifdef PORTKNOCKINGPORT
void vprint(char *fmt, ...)
{	char buf[1024];
	va_list args;
	va_start(args, fmt);
	vsprintf(buf,fmt, args);
	if( buf[strlen(buf)-1]=='\n' ) buf[strlen(buf)-1]='\0';
	logevent(NULL,buf);
	va_end(args);
}
int knock( char *hostname, unsigned short port, unsigned short proto) {
	SOCKET sd;
	struct hostent* host;
	struct sockaddr_in addr;

	host = gethostbyname(hostname);
	if(host == NULL) { fprintf(stderr, "Cannot resolve hostname\n") ; return 1 ; }

	if(proto == PROTO_UDP) { 
		sd = socket(PF_INET, SOCK_DGRAM, 0); 
		if(sd == -1) { fprintf(stderr, "Cannot open socket\n") ; return 2 ; } 
	} else {
		unsigned long arg = !0;
		sd = socket(PF_INET, SOCK_STREAM, 0); 
		if(sd == -1) { fprintf(stderr, "Cannot open socket\n") ; return 3 ; }
		ioctlsocket(sd, FIONBIO, &arg);
	}
	
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = *((long*)host->h_addr_list[0]);
	addr.sin_port = htons(port);
	
	if( proto == PROTO_UDP) {
		vprint("hitting udp %s:%u\n", inet_ntoa(addr.sin_addr), port);
		connect(sd, (struct sockaddr*)&addr, sizeof(struct sockaddr));
		send(sd, NULL, 0, 0);
	} else {
		vprint("hitting tcp %s:%u\n", inet_ntoa(addr.sin_addr), port);
		connect(sd, (struct sockaddr*)&addr, sizeof(struct sockaddr));
	}

	shutdown(sd, 2);
	closesocket(sd);
		
	return 0;
	}
	
int ManagePortKnocking( char* host, char *portknockseq ) {
	char portstr[256], protostr[256];
	short port, proto ;
	int i,j;
	if( (host==NULL) || (portknockseq==NULL) ) return 0 ;
	if( (strlen(host)==0) || (strlen(portknockseq)==0) ) return 0 ;
	
	for(i=0;i<strlen(portknockseq);i++) 
		{ if( (portknockseq[i]==' ')||(portknockseq[i]=='	')||(portknockseq[i]==';')||(portknockseq[i]=='-') ) portknockseq[i]=','; }
	while( portknockseq[0]==',' ) del(portknockseq,1,1);
	while( portknockseq[strlen(portknockseq)-1]==',' ) portknockseq[strlen(portknockseq)-1]='\0';
	while( (i=poss(",:",portknockseq)) ) { del(portknockseq,i,1); }
	while( (i=poss(":,",portknockseq)) ) { del(portknockseq,i+1,1); }
	while( (i=poss(",,",portknockseq)) ) { del(portknockseq,i,1); }
	
	while( strlen(portknockseq)>0 ) {
		while( (portknockseq[0]==' ')||(portknockseq[0]=='	')||(portknockseq[0]==',')||(portknockseq[0]==';') ) del(portknockseq,1,1);
		if( strlen(portknockseq)>0 ) {
			i=poss(":",portknockseq) ; if(i==0) i=strlen(portknockseq)+1;
			j=poss(",",portknockseq) ; if(j==0) j=strlen(portknockseq)+1; if(j<i) i=j;
			strcpy(portstr,portknockseq); 
			if( portstr[i-1]!=':' ) { 
				portstr[i-1]='\0'; del(portknockseq,1,i);
				strcpy(protostr,"tcp");
				}
			else {
				portstr[i-1]='\0'; del(portknockseq,1,i);
				i=poss(",",portknockseq) ; if(i==0) i=strlen(portknockseq)+1;
				strcpy(protostr,portknockseq); protostr[i-1]='\0'; del(portknockseq,1,i);
				}
			port=atoi(portstr);
			if( !stricmp(protostr,"udp") ) proto=PROTO_UDP ; else proto=PROTO_TCP ;
			
			if( knock(host,port,proto) ) logevent( NULL, "Unable to knock port" );
			}
		}
	
	return 1;
	}
#endif
