#include "d4all.h"


#ifdef __TURBOC__
   extern unsigned _stklen = 10000;
#endif

void openAFile( CODE4 *cb )
{
   DATA4 *d ;

   /* 'd' falls out of scope.  Data file is still open*/
   d = d4open( cb, "INFO" ) ;
}

void main( void )
{
   CODE4 cb ;
   DATA4 *d ;

   code4init( &cb ) ;
   cb.autoOpen = 0 ;
   openAFile( &cb ) ;

   d = d4open( &cb, "DATA" ) ;   /* open a second file */
   printf("Number of records in DATA: %d \n",d4recCount( d ) ) ;

   code4close( &cb ) ; /* INFO and DATAFILE are both closed*/
   code4initUndo( &cb ) ;
}

