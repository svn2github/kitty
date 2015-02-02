/*
-- putty-0.59/windows/cygcfg.c	1969-12-31 17:00:00.000000000 -0700
++ putty-0.59-cygterm/windows/cygcfg.c	2007-02-06 16:16:15.000000000 -0700
@ -0,0 +1,33 @@
*/

#include "putty.h"
#include "dialog.h"

extern void config_protocolbuttons_handler(union control *, void *, void *, int);

static int CygTermFlag = 0 ;

void cygterm_set_flag( int flag ) {
	if( flag >= 1 ) CygTermFlag = 1 ;
	else CygTermFlag = 0 ;
	}

int cygterm_get_flag( void ) {
	return CygTermFlag ;
	}

void cygterm_setup_config_box(struct controlbox *b, int midsession)
{
	union control *c;
	int i;
	
	if( !CygTermFlag ) return ;
	
	struct controlset *s = ctrl_getset(b, "Session", "hostport",
		"Specify the destination you want to connect to");
	for (i = 0; i < s->ncontrols; i++) {
		c = s->ctrls[i];
		if (c->generic.type == CTRL_RADIO &&
			c->generic.handler == config_protocolbuttons_handler) {
			c->radio.nbuttons++;
			// c->radio.ncolumns++; 
			c->radio.buttons =
				sresize(c->radio.buttons, c->radio.nbuttons, char *);
			c->radio.buttons[c->radio.nbuttons-1] = dupstr("Cygterm");
			c->radio.buttondata =
				sresize(c->radio.buttondata, c->radio.nbuttons, intorptr);
			c->radio.buttondata[c->radio.nbuttons-1] = I(PROT_CYGTERM);
			if (c->radio.shortcuts) {
				c->radio.shortcuts =
					sresize(c->radio.shortcuts, c->radio.nbuttons, char);
				c->radio.shortcuts[c->radio.nbuttons-1] = NO_SHORTCUT;
			}
		}
	}
}
