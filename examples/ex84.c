/*ex84.c*/
#include "d4all.h"

#ifdef __TURBOC__
   extern unsigned _stklen = 10000;
#endif

void main( )
{
   char time[9] ;

   date4timeNow( time ) ;
   time[9] = 0 ;  /* Add the null for the printf() */
   printf( "\nThe current time is %s.", time ) ;
}
