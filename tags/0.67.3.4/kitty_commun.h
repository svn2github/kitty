#ifndef KITTY_COMMUN
#define KITTY_COMMUN

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#include "winstuff.h"

// Flag permettant d'activer l'acces a du code particulier permettant d'avoir plus d'info dans le kitty.dmp
extern int debug_flag ;

// Flag permettant de sauvegarder automatique les cles SSH des serveurs
// extern int AutoStoreSSHKeyFlag  ;
int GetAutoStoreSSHKeyFlag(void) ;
void SetAutoStoreSSHKeyFlag( const int flag ) ;

// Flag permettant de desactiver la sauvegarde automatique des informations de connexion (user/password) à la connexion SSH
// extern int UserPassSSHNoSave ;
int GetUserPassSSHNoSave(void) ;
void SetUserPassSSHNoSave( const int flag ) ;

#ifdef ADBPORT
// Flag pour inhiber le support d'ADB
int GetADBFlag(void) ;
void SetADBFlag( const int flag ) ;
#endif

// Répertoire de sauvegarde de la configuration (savemode=dir)
extern char * ConfigDirectory ;

char * GetConfigDirectory( void ) ;

int stricmp(const char *s1, const char *s2) ;
char * GetValueData(HKEY hkTopKey, char * lpSubKey, const char * lpValueName, char * rValue) ;
int readINI( const char * filename, const char * section, const char * key, char * pStr) ;
char * SetSessPath( const char * dec ) ;

// Nettoie les noms de folder en remplaçant les "/" par des "\" et les " \ " par des " \"
void CleanFolderName( char * folder ) ;

// Supprime une arborescence
void DelDir( const char * directory ) ;

// Lit un parametre soit dans le fichier de configuration, soit dans le registre
int ReadParameterLight( const char * key, const char * name, char * value ) ;

/* test if we are in portable mode by looking for putty.ini or kitty.ini in running directory */
int LoadParametersLight( void ) ;

// Positionne un flag permettant de determiner si on est connecte
extern int backend_connected ;
extern int backend_first_connected ;

void SetSSHConnected( int flag ) ;

PVOID SecureZeroMemory( PVOID ptr, SIZE_T cnt) ;

// Fonction permettant de changer le statut du stockage automatique des ssh host keys
void SetAutoStoreSSHKey( void ) ;

#endif
