/*ex79.c*/
#include "d4all.h"

#ifdef __TURBOC__
   extern unsigned _stklen = 10000;
#endif

void main( )
{
   char date[8] ;
   int tillEnd ;

   date4today( date ) ;
   tillEnd = 7 - date4dow( date ) ;
   printf( "%d days left till end of the week", tillEnd ) ;
}
