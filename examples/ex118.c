/*ex118.c*/
#include "d4all.h"  

#ifdef __TURBOC__
   extern unsigned _stklen = 10000;
#endif

int addLotsOfRecords( DATA4 *d ) 
{
	INDEX4 *production ;
	int i ;

	production = d4index( d, d4alias( d ) ) ; /* get the production index file*/
    								
	if( production != NULL )
       i4close( production ) ;
 
    d4top( d ) ;
    for( i = 200 ; i ; i -- )
    {
       d4appendStart( d, 0 ) ;
       d4append( d ) ; /* make 200 copies of record 1*/
    }

    /* open the index file and update it*/
    production = i4open( d, d4alias( d ) ) ;
    return i4reindex( production ) ;
}
void main()
{
	CODE4 cb ;
	DATA4 *data ;

	code4init( &cb ) ;
	data = d4open( &cb, "DATA") ;
	addLotsOfRecords( data ) ;
	code4initUndo( &cb ) ;
}

