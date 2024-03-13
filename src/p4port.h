#ifndef P4PORT_INC
#define P4PORT_INC

#ifdef S4UNIX

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/stat.h>

#ifdef WINDIR
    #define S4NO_FCVT
#endif

#include "port/str.h"

#define S4NO_FILELENGTH
#define S4NO_CHSIZE

//#define S464BIT

#define S4CMP_PARM  const void *

typedef unsigned HANDLE;

#endif
#endif
