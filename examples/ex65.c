#include "d4all.h"

#ifdef __TURBOC__
   extern unsigned _stklen = 10000;
#endif

int SeekSeries( DATA4 *d, const char *s )
{
   int rc ;

   rc = d4seekNext( d, s ) ;

   if( rc == r4noTag || rc == r4entry || rc == r4locked || rc < 0 )
      return rc ;

   if( rc == r4after || rc == r4eof )
      rc = d4seek( d, s ) ;
   printf( " the found record %s \n", d4record( d ) ) ;
   return rc ;
}

void main()
{
   CODE4 cb ;
   DATA4 *data ;
   TAG4 *nameTag ;
   int rc ;

   code4init( &cb ) ;
   data = d4open( &cb, "PEOPLE" ) ;
   nameTag = d4tag( data, "NAME_TAG") ;
   d4tagSelect( data, nameTag ) ;
   d4seek( data, "mickey" ) ;
   rc = SeekSeries( data, "mickey" ) ;
   code4initUndo( &cb ) ;
}
