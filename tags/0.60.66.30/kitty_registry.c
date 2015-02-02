#include "kitty_registry.h"

//static const int cstMaxRegLength = 1024;
#define cstMaxRegLength 1024

char * itoa (int __val, char *__s, int __radix) ;
char * GetValueData(HKEY hkTopKey, char * lpSubKey, const char * lpValueName, char * rValue){
    HKEY hkKey;
    DWORD lpType, dwDataSize = cstMaxRegLength;
  
  //Receptionne la valeur de réception lecture clé registre
    //unsigned char * lpData = new unsigned char[cstMaxRegLength];
	unsigned char * lpData = (unsigned char*) malloc( cstMaxRegLength );
    
  //Receptionne la valeur de réception lecture clé registre
    //char * rValue = (char*) malloc( cstMaxRegLength );
    rValue[0] = '\0';
  //Lecture de la clé registre si ok passe à la suite...
    if (RegOpenKeyEx(hkTopKey,lpSubKey,0,KEY_READ,&hkKey) == ERROR_SUCCESS){
  
      if (RegQueryValueEx(hkKey,lpValueName,NULL,&lpType,lpData,&dwDataSize) == ERROR_SUCCESS){
      //déchiffrage des différents type de clé dans registry
        switch ((int)lpType){
  
          case REG_BINARY:
               itoa((u_int)(lpData[0]),rValue, 10);
               strcat(rValue,".");
               itoa((u_int)(lpData[1]),(char*)(rValue+strlen(rValue)),10);
               strcat(rValue,".");
               itoa((u_int)(lpData[2]),(char*)(rValue+strlen(rValue)),10);
               strcat(rValue,".");
               itoa((u_int)(lpData[3]),(char*)(rValue+strlen(rValue)),10);
               break;
  
          case REG_DWORD:
               itoa(*(int*)(lpData),rValue,10);
               break;
  
          case REG_EXPAND_SZ:
               //rValue=(char *)lpData;
               strcpy( rValue, (char*)lpData ) ;
               break;
  
          case REG_MULTI_SZ:
               //rValue=(char *)lpData;
               strcpy( rValue, (char*)lpData ) ;
               break;
  
          case REG_SZ:
               //rValue=(char *)lpData;
               strcpy( rValue, (char*)lpData ) ;
               break;
        }//end switch
      }//end if
      else { RegCloseKey(hkKey); free(lpData); return NULL ; }
       free(lpData); // libère la mémoire
       RegCloseKey(hkKey); 
      
    }//end if
    else { return NULL ; }
    return rValue;
  }//end function

// Teste l'existance d'une clé
int RegTestKey( HKEY hMainKey, LPCTSTR lpSubKey ) {
	HKEY hKey ;
	if( lpSubKey == NULL ) return 1 ;
	if( strlen( lpSubKey ) == 0 ) return 1 ;
	if( RegOpenKeyEx( hMainKey, TEXT(lpSubKey), 0, KEY_WRITE, &hKey) != ERROR_SUCCESS ) return 0 ;
	RegCloseKey( hKey ) ;
	return 1 ;
	}

// Retourne le nombre de sous-keys
int RegCountKey( HKEY hMainKey, LPCTSTR lpSubKey ) {
	HKEY hKey ;
	TCHAR    achClass[MAX_PATH] = TEXT("");
	DWORD    cchClassName = MAX_PATH, cSubKeys=0, cbMaxSubKey, cchMaxClass, cValues, cchMaxValue, cbMaxValueData, cbSecurityDescriptor ;
	FILETIME ftLastWriteTime;

	int nb = 0 ;
	if( RegOpenKeyEx( hMainKey, TEXT(lpSubKey), 0, KEY_READ, &hKey) != ERROR_SUCCESS ) return 0 ;
	
	RegQueryInfoKey( hKey, achClass, &cchClassName, NULL, &cSubKeys, &cbMaxSubKey, &cchMaxClass
		, &cValues, &cchMaxValue, &cbMaxValueData, &cbSecurityDescriptor, &ftLastWriteTime) ;
	nb = cSubKeys ;
	RegCloseKey( hKey ) ;
	return nb ;
	}

	// Teste l'existance d'une clé ou bien d'une valeur et la crée sinon
void RegTestOrCreate( HKEY hMainKey, LPCTSTR lpSubKey, LPCTSTR name, LPCTSTR value ) {
	HKEY hKey ;
	if( lpSubKey == NULL ) return ;
	if( strlen( lpSubKey ) == 0 ) return ;
	if( RegOpenKeyEx( hMainKey, TEXT(lpSubKey), 0, KEY_WRITE, &hKey) != ERROR_SUCCESS ) {
		RegCreateKey( hMainKey, lpSubKey, &hKey ) ;
		}
	if( name != NULL ) {
		RegSetValueEx( hKey, TEXT( name ), 0, REG_SZ, (const BYTE *)value, strlen(value)+1 ) ;
		}
	RegCloseKey( hKey ) ;
	}
	
// Test l'existance d'une clé ou bien d'une valeur DWORD et la crée sinon
void RegTestOrCreateDWORD( HKEY hMainKey, LPCTSTR lpSubKey, LPCTSTR name, DWORD value ) {
	HKEY hKey ;
	if( lpSubKey == NULL ) return ;
	if( strlen( lpSubKey ) == 0 ) return ;
	if( RegOpenKeyEx( hMainKey, TEXT(lpSubKey), 0, KEY_WRITE, &hKey) != ERROR_SUCCESS ) {
		RegCreateKey( hMainKey, lpSubKey, &hKey ) ;
		}
	if( name != NULL ) {
		RegSetValueEx( hKey, TEXT( name ), 0, REG_DWORD, (LPBYTE)&value, sizeof(DWORD) ) ;
		}
	RegCloseKey( hKey ) ;
	}
	
// Initialise toutes les sessions avec une valeur
void QuerySubKey( HKEY hMainKey, LPCTSTR lpSubKey, FILE * fp_out, char * text  ) { 
	HKEY hKey ;
    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string 
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
    DWORD    cchClassName = MAX_PATH;  // size of class string 
    DWORD    cSubKeys=0;               // number of subkeys 
    DWORD    cbMaxSubKey;              // longest subkey size 
    DWORD    cchMaxClass;              // longest class string 
    DWORD    cValues;              // number of values for key 
    DWORD    cchMaxValue;          // longest value name 
    DWORD    cbMaxValueData;       // longest value data 
    DWORD    cbSecurityDescriptor; // size of security descriptor 
    FILETIME ftLastWriteTime;      // last write time 
    DWORD i, retCode; 
	
	char * buffer = NULL ;

	// On ouvre la clé
	if( RegOpenKeyEx( hMainKey, TEXT(lpSubKey), 0, KEY_READ, &hKey) != ERROR_SUCCESS ) return ;

    // Get the class name and the value count. 
    retCode = RegQueryInfoKey(
        hKey,                    // key handle 
        achClass,                // buffer for class name 
        &cchClassName,           // size of class string 
        NULL,                    // reserved 
        &cSubKeys,               // number of subkeys 
        &cbMaxSubKey,            // longest subkey size 
        &cchMaxClass,            // longest class string 
        &cValues,                // number of values for this key 
        &cchMaxValue,            // longest value name 
        &cbMaxValueData,         // longest value data 
        &cbSecurityDescriptor,   // security descriptor 
        &ftLastWriteTime);       // last write time 
 
	// Enumerate the subkeys, until RegEnumKeyEx fails.
	if (cSubKeys) {
		for (i=0; i<cSubKeys; i++) { 
			cbName = MAX_KEY_LENGTH;
			retCode = RegEnumKeyEx(hKey, i, achKey, &cbName, NULL, NULL, NULL, &ftLastWriteTime); 
			if (retCode == ERROR_SUCCESS) {
				buffer = (char*) malloc( strlen( TEXT(lpSubKey) ) + strlen( achKey ) + 100 ) ;
				sprintf( buffer, "[HKEY_CURRENT_USER\\%s\\%s]", TEXT(lpSubKey), achKey ) ;
				fprintf( fp_out, "\r\n%s\r\n", buffer ) ;
				if( text!=NULL ) 
					if( strlen( text ) > 0 ) fprintf( fp_out, "%s\r\n", text ) ;
				free( buffer );				
				}
			}
		} 
	RegCloseKey( hKey ) ;
	}

void InitRegistryAllSessions( HKEY hMainKey, LPCTSTR lpSubKey, char * SubKeyName, char * filename, char * text ) {
	FILE * fp;
	char buf[1024] = "" ;
	if( (fp=fopen( filename, "wb" )) != NULL ) {
		fprintf( fp, "Windows Registry Editor Version 5.00\r\n" ) ;
		sprintf( buf, "%s\\%s", lpSubKey, SubKeyName ); 
		QuerySubKey( hMainKey, (LPCTSTR)buf, fp, text ) ;
		fclose( fp ) ;
		}
	}
	
void InitAllSessions( HKEY hMainKey, LPCTSTR lpSubKey, char * SubKeyName, char * filename ) {
	char text[4096], f[1024] ;
	FILE * fp ;
	int len ;
	if( (fp=fopen(filename, "rb")) != NULL ) {
		len = fread( text, 1, 4096, fp ) ;
		fclose( fp ) ;
		text[4095]='\0'; text[len] = '\0' ;
		while( (text[strlen(text)-1]=='\n')||(text[strlen(text)-1]=='\r') ) text[strlen(text)-1]='\0' ;
		sprintf( f, "%s.reg", filename ) ;
		InitRegistryAllSessions( hMainKey, lpSubKey, SubKeyName, f, text ) ;
		unlink(filename);
		}
	}
	
// Détruit une valeur de clé de registre 
BOOL RegDelValue (HKEY hKeyRoot, LPTSTR lpSubKey, LPTSTR lpValue ) {
	HKEY hKey;
	LONG lResult;
	if( (lResult = RegOpenKeyEx (hKeyRoot, lpSubKey, 0, KEY_WRITE, &hKey)) == ERROR_SUCCESS ) {
		RegDeleteValue( hKey, lpValue ) ;
		RegCloseKey(hKey) ;
		}
	return TRUE;   
	}

// Detruit une clé de registre et ses sous-clé
BOOL RegDelTree (HKEY hKeyRoot, LPCTSTR lpSubKey) {
    TCHAR lpEnd[MAX_PATH];
    LONG lResult;
    DWORD dwSize;
    TCHAR szName[MAX_PATH];
    HKEY hKey;
    FILETIME ftWrite;

    // First, see if we can delete the key without having
    // to recurse.
    lResult = RegDeleteKey(hKeyRoot, lpSubKey);
    if (lResult == ERROR_SUCCESS) return TRUE;

    lResult = RegOpenKeyEx (hKeyRoot, lpSubKey, 0, KEY_READ, &hKey) ;

    if (lResult != ERROR_SUCCESS) {
        if (lResult == ERROR_FILE_NOT_FOUND) { printf("Key not found.\n"); return TRUE; } 
        else {printf("Error opening key.\n");return FALSE;}
    	}

    // Enumerate the keys
    dwSize = MAX_PATH;
    lResult = RegEnumKeyEx(hKey, 0, szName, &dwSize, NULL, NULL, NULL, &ftWrite) ;

    if (lResult == ERROR_SUCCESS) 
    {
        do {
            //StringCchCopy (lpEnd, MAX_PATH*2, szName);
            sprintf(lpEnd, "%s\\%s", lpSubKey, szName);

            //if( !RegDelTree( hKeyRoot, lpSubKey ) ) { break ; }
            if( !RegDelTree( hKeyRoot, lpEnd ) ) { break ; }
            dwSize = MAX_PATH;
            lResult = RegEnumKeyEx(hKey, 0, szName, &dwSize, NULL, NULL, NULL, &ftWrite) ;
        } while ( lResult == ERROR_SUCCESS ) ;
    }

	RegCloseKey(hKey) ;

	// Try again to delete the key.
	lResult = RegDeleteKey(hKeyRoot, lpSubKey);

	if (lResult == ERROR_SUCCESS) return TRUE;
	return FALSE;
	}

// Copie une clé de registre vers une autre
void RegCopyTree( HKEY hMainKey, LPCTSTR lpSubKey, LPCTSTR lpDestKey ) { 
	HKEY hKey, hDestKey ;
    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string 
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
    DWORD    cchClassName = MAX_PATH;  // size of class string 
    DWORD    cSubKeys=0;               // number of subkeys 
    DWORD    cbMaxSubKey;              // longest subkey size 
    DWORD    cchMaxClass;              // longest class string 
    DWORD    cValues;              // number of values for key 
    DWORD    cchMaxValue;          // longest value name 
    DWORD    cbMaxValueData;       // longest value data 
    DWORD    cbSecurityDescriptor; // size of security descriptor 
    FILETIME ftLastWriteTime;      // last write time 
 
    DWORD i, retCode; 
 
    TCHAR  achValue[MAX_VALUE_NAME]; 
    DWORD cchValue = MAX_VALUE_NAME; 
	
	DWORD lpType, dwDataSize = 1024 ;
	char * buffer = NULL, * destbuffer = NULL ;
	
	// On ouvre la clé
	if( RegOpenKeyEx( hMainKey, TEXT(lpSubKey), 0, KEY_READ, &hKey) != ERROR_SUCCESS ) return ;
	if( RegCreateKey( hMainKey, TEXT(lpDestKey), &hDestKey ) == ERROR_SUCCESS )
					RegCloseKey( hDestKey ) ;

    // Get the class name and the value count. 
    retCode = RegQueryInfoKey(
        hKey,                    // key handle 
        achClass,                // buffer for class name 
        &cchClassName,           // size of class string 
        NULL,                    // reserved 
        &cSubKeys,               // number of subkeys 
        &cbMaxSubKey,            // longest subkey size 
        &cchMaxClass,            // longest class string 
        &cValues,                // number of values for this key 
        &cchMaxValue,            // longest value name 
        &cbMaxValueData,         // longest value data 
        &cbSecurityDescriptor,   // security descriptor 
        &ftLastWriteTime);       // last write time 
 
    // Enumerate the key values. 
    if (cValues) 
    {
        //printf( "\nNumber of values: %d\n", cValues);

        for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++) 
        { 
            cchValue = MAX_VALUE_NAME; 
            achValue[0] = '\0'; 
            retCode = RegEnumValue(hKey, i, 
                achValue, 
                &cchValue, 
                NULL, 
                NULL,
                NULL,
                NULL);
 
            if (retCode == ERROR_SUCCESS ) 
            { 
				unsigned char lpData[1024] ;
				dwDataSize = 1024 ;
				RegQueryValueEx( hKey, TEXT( achValue ), 0, &lpType, lpData, &dwDataSize ) ;
				
				if( RegOpenKeyEx( hMainKey, TEXT(lpDestKey), 0, KEY_WRITE, &hDestKey) != ERROR_SUCCESS ) return ;
				
				RegSetValueEx( hDestKey, TEXT( achValue ), 0, lpType, lpData, dwDataSize );
					
				RegCloseKey( hDestKey ) ;
            } 
        }
    }
	
    // Enumerate the subkeys, until RegEnumKeyEx fails.
    if (cSubKeys)
    {
        //printf( "\nNumber of subkeys: %d\n", cSubKeys);

        for (i=0; i<cSubKeys; i++) 
        { 
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(hKey, i,
                     achKey, 
                     &cbName, 
                     NULL, 
                     NULL, 
                     NULL, 
                     &ftLastWriteTime); 
            if (retCode == ERROR_SUCCESS) 
            {
				buffer = (char*) malloc( strlen( TEXT(lpSubKey) ) + strlen( achKey ) + 3 ) ;
				sprintf( buffer, "%s\\%s", TEXT(lpSubKey), achKey ) ;
				destbuffer = (char*) malloc( strlen( TEXT(lpDestKey) ) + strlen( achKey ) + 3 ) ;
				sprintf( destbuffer, "%s\\%s", TEXT(lpDestKey), achKey ) ;
				if( RegCreateKey( hMainKey, destbuffer, &hDestKey ) == ERROR_SUCCESS )
					RegCloseKey( hDestKey ) ;
					
				RegCopyTree( hMainKey, buffer, destbuffer ) ;
				free( buffer );
				free( destbuffer );
            }
        }
    } 
 
	RegCloseKey( hKey ) ;
}
