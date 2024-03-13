/* 'f4int()' uses 'c4atoi' because database field data is not null terminated */
#include "d4all.h"


#ifdef __TURBOC__
   extern unsigned _stklen = 10000;
#endif

int f4int( FIELD4 *field )
{
	/*convert the field data into an 'int' */
	return c4atoi(f4ptr(field), (int) f4len(field)) ;
}
