/*
-- putty-0.59/windows/cthelper/ptyfork.h	1969-12-31 17:00:00.000000000 -0700
++ putty-0.59-cygterm/windows/cthelper/ptyfork.h	2007-02-02 16:53:35.000000000 -0700
@ -0,0 +1,5 @@
*/
#include <sys/types.h>
#include <termios.h>
pid_t pty_fork(int *ptrfdm, char *slave_name,
               const struct termios *slave_termios,
               const struct winsize *slave_winsize);
