#include "d4all.h"

FIELD4INFO fields[ ] =
{
    { "NAME", 'C', 20, 0 },
    { "AGE", 'N', 3, 0 },
    NULL
} ;

void main( )
{
    CODE4 cb ;
    DATA4 *data ;

    code4init( &cb ) ;
    cb.safety = 0 ;

    data = d4create( &cb, "test", fields, 0 ) ;
    if( data )
        printf( "<test.dbf> successfully created\n" ) ;

    code4close( &cb ) ;
    code4initUndo( &cb ) ;
}
