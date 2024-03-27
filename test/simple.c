#include <stdio.h>

#include "d4all.h"

static FIELD4INFO fields[] =
{
   { "COMMENT", 'C', 40, 0 },
   { "A_VALUE", 'N',  8, 2 },
   { "B_VALUE", 'N',  8, 2 },
   { "SUM",     'N',  8, 2 },
   NULL
} ;

int main( void)
{
    CODE4 cb;
    DATA4 *data;
    TAG4INFO tag;

    code4init( &cb) ;

    data = d4create( &cb, "simple", fields, NULL) ;
    printf( "<%p>\n", data);

    return 0;
}
