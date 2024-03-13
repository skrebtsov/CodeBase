#include "d4all.h"

#ifdef __TURBOC__
   extern unsigned _stklen = 10000;
#endif

CODE4 cb ;
DATA4 *data ;
FIELD4 *name ;

FIELD4INFO fieldInfo[] =
{
   { "NAME", 'C', 20, 0 },
   { 0,0,0,0 },
} ;

char *records[5] =
{
   "MARY",
   "SALLY",
   "DICK",
   "GERRY",
   "BOB",
} ;


void main(void)
{
   int i ;

   code4init( &cb ) ;

   data = d4create( &cb, "FROM_DBF", fieldInfo, 0 ) ;
   if ( data )
   {
      name = d4field( data, "name" ) ;

      for ( i = 0 ; i < 5 ; i++ )
      {
         d4appendStart( data, 0 ) ;
         f4assign( name, records[i] ) ;
         if ( d4append( data ) )
            printf( "ERROR: Could not append record to database\n" ) ;
      }
      printf( "The FROM_DBF has been created.\n" ) ;
   }
   else
      printf( "ERROR: Could not create database\n" ) ;

   code4initUndo( &cb ) ;
}



