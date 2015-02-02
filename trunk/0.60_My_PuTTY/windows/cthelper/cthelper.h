/*
-- putty-0.59/windows/cthelper/cthelper.h	1969-12-31 17:00:00.000000000 -0700
++ putty-0.59-cygterm/windows/cthelper/cthelper.h	2007-02-02 16:52:54.000000000 -0700
@ -0,0 +1,8 @@
*/
enum cthelper_exitcode {
	CthelperSuccess = 0,
	CthelperInvalidUsage,
	CthelperInvalidPort,
	CthelperConnectFailed,
	CthelperPtyforkFailure,
	CthelperExecFailure,
};
