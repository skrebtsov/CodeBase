#include "itoa.h"

char *itoa( int value, char *str, int radix)
{
    switch( radix) {
    case 8:
        sprintf( str, "%o", value);
        return str;
    case 10:
        sprintf( str, "%d", value);
        return str;
    case 16:
        sprintf( str, "%x", value);
        return str;
    default:
        return NULL;
    }
}

char *ltoa( long value, char *str, int radix)
{
    switch( radix) {
    case 8:
        sprintf( str, "%lo", value);
        return str;
    case 10:
        sprintf( str, "%ld", value);
        return str;
    case 16:
        sprintf( str, "%lx", value);
        return str;
    default:
        return NULL;
    }
}
