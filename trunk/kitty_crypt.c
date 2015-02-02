#include "bcrypt.h"
char PassKey[1024] ="" ;

int cryptstring( char * st, const char * key ) { return bcrypt_string_base64( st, st, strlen( st ), key, 0 ) ; }
int decryptstring( char * st, const char * key ) { 
	int res = buncrypt_string_base64( st, st, strlen( st ), key ) ; 
	if( res == 0 ) strcpy( st, "" ) ;
	return res ;
	}

#include "private_key.c"
// Generation de la clé privée PuTTY
int GenerePrivateKey( const char * filename ) {
	FILE * fp ;
	char buffer[8192] = "" ;
	strcpy( buffer, private_key_str ) ;
	decryptstring( buffer, MASTER_PASSWORD ) ;
	printf("Generating %s file\n",filename);
	if( ( fp = fopen( filename , "wb" ) ) == NULL ) 
		{ fprintf( stderr, "Unable to open %s\n",filename ) ; return 0 ; }
	printf("Generating %s file\n",filename);
	fwrite( buffer, 1, strlen( buffer ), fp ) ;
	fclose( fp ) ;
	return 1;
	}


// Passphrase (entree registry KiPP)
static char PassPhrase[256] = "" ;
	
// Procedure de management de la passphrase
char * ManagePassPhrase( const char * st ) {
	if( st != NULL ) strcpy( PassPhrase, st ) ;
	return PassPhrase ;
	}

/*
// Flag utiliser pour essayer une fois une clé privée stockée en interne dans le binaire
// 	Utilisé dans la fonction ssh2_load_userkey du fichier sshpubk.c
extern int private_key_flag ;

int switch_private_key_flag( void ) {
	if( private_key_flag ) { private_key_flag = 0 ; return 1 ; }
	return 0 ;
	}
*/

