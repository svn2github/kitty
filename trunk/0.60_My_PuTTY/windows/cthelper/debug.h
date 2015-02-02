/*
-- putty-0.59/windows/cthelper/debug.h	1969-12-31 17:00:00.000000000 -0700
++ putty-0.59-cygterm/windows/cthelper/debug.h	2005-12-14 12:26:27.000000000 -0700
@ -0,0 +1,26 @@
*/
#ifndef DEBUG_H
#define DEBUG_H

#include "dbug.h"
#include "mm.h"

#ifndef __attribute__
#define __attribute__(x)
#endif

#if !defined(DBUG_OFF) && !defined(_lint)

/* allow GCC to check format strings against their arguments */
extern void _dbug_doprnt_(const char *format, ...)
	__attribute__((format(printf, 1, 2)));

extern void debug_memdump(const void *buf, int len, int L);

#else

#define debug_memdump(buf,len,L)

#endif

#endif /* DEBUG_H */
/* ex:set sw=4: */
