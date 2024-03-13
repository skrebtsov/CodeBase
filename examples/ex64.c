#include "d4all.h"

#ifdef __TURBOC__
   extern unsigned _stklen = 10000;
#endif

void main( void )
{
   CODE4 cb ;
   DATA4 *people ;
   FIELD4 *age, *birth ;
   int rc ;
   char result[12] ;

   code4init( &cb ) ;
   people = d4open( &cb, "people.dbf" ) ;
    /* Assume 'PEOPLE.DBF' has a production index file with tags
       NAME_TAG, AGE_TAG, BIRTH_TAG */

   d4tagSelect( people, d4tag( people, "NAME_TAG" ) ) ;

   if( d4seek( people,  "fred" ) == r4success )
       printf("fred is in record # %d\n",d4recNo( people )) ;

   if( d4seek( people, "HANK STEVENS" ) == r4success )
       printf( "HANK STEVENS is in record # %d\n",d4recNo( people )) ;

   d4tagSelect( people, d4tag( people, "AGE_TAG" ) ) ;
   age = d4field( people, "AGE" ) ;

   rc = d4seekDouble( people, 0.0 ) ;

   if( rc == r4success || rc == r4after )
       printf( "The youngest age is: %d\n", f4int( age )) ;

    /* Seek using the char * version */
   rc = d4seek( people, "0" ) ;

   if( rc == r4success || rc == r4after )
       printf( "The youngest age is: %d\n", f4int( age )) ;

   /* Assume BIRTH_TAG is a Date key expression */

   d4tagSelect( people, d4tag( people, "BIRTH_TAG" )) ;
   birth = d4field( people, "BIRTH" ) ;
   date4format( "19600415", result, "MMM DD, CCYY" );

   if( d4seek( people, "19600415") == r4success)
                     /* Char. array in CCYYMMDD format*/
      printf( "Found: %s\n", result ) ;

   if( d4seekDouble( people, date4long( "19600415" )) == r4success )
      printf( "Found: %s\n", result ) ;

   d4close( people ) ;
   code4initUndo( &cb ) ;
}
