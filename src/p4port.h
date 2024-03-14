#ifndef P4PORT_INC
#define P4PORT_INC

#ifdef S4UNIX

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/stat.h>

#ifndef S4STAND_ALONE
    #include <netinet/in.h>
    #include <netinet/tcp.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <sys/ioctl.h>

    extern int h_errno;
#endif

#ifdef WINDIR
    #define S4NO_FCVT
#endif

#include "port/str.h"
#include "port/itoa.h"

#define S4NO_FILELENGTH
#define S4NO_CHSIZE

//#define S464BIT

#define S4CMP_PARM  const void *

typedef unsigned HANDLE;

#endif
#endif
