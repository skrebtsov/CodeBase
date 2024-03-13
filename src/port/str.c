#include <string.h>

#include "char.h"
#include "str.h"

char *strupr866( char *s)
{
    char *str = s;

    while( *str) {
        *str = chrupr866( *str);
        str++;
    }

    return s;
}

char *strlwr866( char *s)
{
    char *str = s;

    while( *str) {
        *str = chrlwr866( *str);
        str++;
    }

    return s;
}

char *strupr( char *s)
{
    return strupr866( s);
}

char *strlwr( char *s)
{
    return strlwr866( s);
}

int stricmp( char *s1, char *s2)
{
    return strcasecmp( s1, s2);
}

int strnicmp( char *s1, char *s2, size_t n)
{
    return strncasecmp( s1, s2, n);
}
