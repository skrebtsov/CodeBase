/*ex81.c*/
#include "d4all.h"

#ifdef __TURBOC__
   extern unsigned _stklen = 10000;
#endif

void main( )
{
   char day[8] ;
   /*date4init puts the given date in CCYYMMDD format */
   date4init( day, "Oct 07/90", "MMM DD/YY" ) ;
   printf( "Oct 07/90 becomes %s\n", day ) ;
   date4init( day, "08/07/1989", "MM/DD/CCYY") ;
   printf( "08/07/1989 becomes %s \n", day );
}
