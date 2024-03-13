#include "d4all.h"


#ifdef __TURBOC__
   extern unsigned _stklen = 10000;
#endif

void disp( char *ptr )
{
	char buf[80] ;
	strncpy( buf, ptr, sizeof(buf) ) ;

	/* A null will be placed in the 80th byte of 'buf' to guarantee that it is null terminated */

	c4trimN( ptr, sizeof(buf) ) ;
	printf( "Display Result: %structure", ptr) ;
}
