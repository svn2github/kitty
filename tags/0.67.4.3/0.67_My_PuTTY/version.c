/*
 * PuTTY version numbering
 */

/*
 * The difficult part of deciding what goes in these version strings
 * is done in Buildscr, and then written into version.h. All we have
 * to do here is to drop it into variables of the right names.
 */

#include "version.h"

#ifdef PERSOPORT
#include <string.h>
const char ver[] = "Custom build" ;
char sshver[] = "PuTTY-KiTTY\0                           " ;
void set_sshver( char * vers ) { 
	if(strlen(vers)<40 ) {
		strcpy( sshver, vers ) ; 
	} else {
		vers[40]='\0';
		memcpy( sshver,vers, 40 ) ;
	}
}
#else
const char ver[] = TEXTVER;
const char sshver[] = SSHVER;
#endif

/*
 * SSH local version string MUST be under 40 characters. Here's a
 * compile time assertion to verify this.
 */
enum { vorpal_sword = 1 / (sizeof(sshver) <= 40) };
