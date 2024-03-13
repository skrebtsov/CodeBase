/*ex101.c*/
#include "d4all.h"  

#ifdef __TURBOC__
   extern unsigned _stklen = 10000;
#endif

void main()
{
	CODE4 cb ;
	DATA4 *data ;
	FIELD4 *field ;

	code4init( &cb ); 
	data = d4open( &cb, "INFO" ) ;
	field = d4fieldJ( data, 1 ); 
	printf( "the first field is called %s\n", f4name( field ) ) ;
	code4initUndo( &cb ) ;
}

