#include "char.h"

char chrupr866( char c)
{
    if(( c >= 'a' && c <= 'z') || ( c >= CHAR_a && c <= CHAR_pe))
        return( c & 0xDF);

    if( c >= CHAR_re && c <= CHAR_ya)
        return( (c & 0x0F) | 0x90);

    if( c == CHAR_jo)
        return CHAR_Jo;

    return c;
}

char chrlwr866( char c)
{
    if(( c >= 'A' && c <= 'Z') || ( c >= CHAR_A && c <= CHAR_Pe))
        return( c | 0x20);

    if( c >= CHAR_Re && c <= CHAR_Ya)
        return(( c & 0x0F) | 0xE0);

    if( c == CHAR_Jo)
        return CHAR_jo;

    return c;
}
