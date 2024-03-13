#include "d4all.h"
int display( CODE4 *cb, char *p )
{
	if( p == NULL )
		return error4describe( cb, e4parm, 0, "Null display string", 0, 0 ) ;
	printf( "%s\n", p ) ;
	return 0 ;
}
