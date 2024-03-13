#include "conv.h"

#ifdef DEBUG
    extern FILE *Debug ;
#endif

iconv_t Conv_utf8, Conv_cp866, Conv_cp866_wchar;
static char Conv [MAX_CONV];

char *conv_open( const char *to, const char *from)
{
    iconv_t cd;

    cd = iconv_open( to, from);

    return cd;
}

void conv_close( iconv_t cd)
{
    iconv_close( cd);
}

/*
 * Возвращает сконвертированую строку, а в size ее длина.
 * ВНИМАНИЕ: сконвертированую строку я не терминировал NULL(ём),
 * т.к. для двух- (и более)- байтовых кодировок это не принесёт
 * большой пользы.
 */
int conv( iconv_t cd, char **str, int *len, char **outbuf, int *outsize)
{
    int rc;
    char *buf;
    size_t size, bufsize;

    if( !outsize || *outsize < 0)
        return E_SIZE;

    if( *len == 0) {
        *outbuf = *str;
        *outsize = 0;

        return 0;
    }

    if( *outbuf == NULL) {
        *outbuf = Conv;
        buf = Conv;
        bufsize = MAX_CONV;
    } else if( *outsize == 0) {
        return E_SIZE;
    } else {
        buf = *outbuf;
        bufsize = *outsize;
    }
/*
#ifdef DEBUG
        fprintf( Debug, "conv: bufsize=%d, len=%d, str=<%*.*s>\n", (int)bufsize, *len, *len, *len, *str) ;
        fflush( Debug) ;
#endif
*/
    size = *len;
    rc = iconv( cd, str, &size, &buf, &bufsize);
    *len = size;
    *outsize = MAX_CONV - bufsize;

    if( rc == -1) {
#ifdef DEBUG
        fprintf( Debug, "conv: errno=%d (EILSEQ=%d, EINVAL=%d, E2BIG=%d)\n", errno, EILSEQ, EINVAL, E2BIG);
        fflush( Debug);
#endif
        switch( errno) {
        case EILSEQ:	/* Invalid multibyte sequence */
            return E_ILSEQ;
        case EINVAL:	/* Incomplete multibyte sequence */
            return E_INVAL;
        case E2BIG:	/* Not sufficient room in buf */
            return E_BIG;
        }
    }

    return rc;
}

int conv_init( void)
{
//    if( setlocale( LC_CTYPE, "ru_RU.UTF-8") == NULL) {
//        return -1;
//    }

    if(( Conv_utf8 = conv_open( "UTF-8", "CP866")) == (iconv_t)-1) {
        return -1;
    }

    if(( Conv_cp866 = conv_open( "CP866", "UTF-8")) == (iconv_t)-1) {
        return -1;
    }
#ifdef __GNUC__
    if(( Conv_cp866_wchar = conv_open( "CP866", "WCHAR_T")) == (iconv_t)-1) {
        return -1;
    }
#endif
    return 0;
}

void conv_free( void)
{
    conv_close( Conv_cp866_wchar);
    conv_close( Conv_cp866);
    conv_close( Conv_utf8);
}

void conv_reset( iconv_t cd)
{
    size_t inlen = 0, outlen = 0;

    iconv( cd, NULL, &inlen, NULL, &outlen);
}

char *conv_utf8( char *str, int *size)
{
    int rc, outsize = 0;
    char *outbuf = NULL;

    if( !str)
        return NULL;

#ifdef DEBUG
    fprintf( Debug, "conv_utf8[%p]: str=<%*.*s>\n", Conv_utf8, *size, *size, str) ;
    fflush( Debug) ;
#endif
    if(( rc = conv( Conv_utf8, &str, size, &outbuf, &outsize)) < 0)
        return NULL;

    *size = outsize;

    return outbuf;
}

char *conv_cp866( char *str, int *size)
{
    int rc, outsize = 0;
    char *outbuf = NULL;

    if( !str)
        return NULL;

    if(( rc = conv( Conv_cp866, &str, size, &outbuf, &outsize)) < 0)
        return NULL;

    *size = outsize;

    return outbuf;
}

char *str866( char *str)
{
//#ifdef UTF8
    int len;

    if( !str)
        return NULL;

    len = strlen( str);

    if( !( str = conv_cp866( str, &len)))
        return NULL;

    str [len] = '\0';

#ifdef DEBUG
    fprintf( Debug, "str866: len=%d, str=<%s>\n", len, str);
    fflush( Debug);
#endif
//#endif

    return str;
}

char conv_cp866_wchar( wchar_t wchar)
{
    int rc, size = sizeof( wchar), outsize = 0;
    char *str = (char *)&wchar;
    char *outbuf = NULL;

    if(( rc = conv( Conv_cp866_wchar, &str, &size, &outbuf, &outsize)) < 0)
        return '\0';

#ifdef DEBUG
    fprintf( Debug, "conv_cp866_wchar: size=%d, outsize=%d\n", size, outsize);
    fflush( Debug);
#endif

    return *outbuf;
}

char char866( wchar_t wchar)
{
    return( conv_cp866_wchar( wchar));
}

int conv_source( char *src, int *size)
{
#ifdef DEBUG
    int size866 = 0;
#endif
    int rc, len, len_utf8 = 0, len_cp866;
    char *pb, *str_utf8 = src, *str_cp866;

#ifdef DEBUG
    fprintf( Debug, "conv_source: size=%d, src=<%*.*s>\n", *size, *size, *size, src);
    fflush( Debug);
#endif
    for( len = 0, pb = src; len <= *size; len += SRC_SIZE, pb += len_cp866) {
        len_utf8 += min( *size - len, SRC_SIZE);
        len_cp866 = 0;
        str_cp866 = NULL;
#ifdef DEBUG
        fprintf( Debug, "conv_source: len=%d, len_utf8=%d, str_utf8=<%*.*s>\n", len, len_utf8, len_utf8, len_utf8, str_utf8);
        fflush( Debug);
#endif
        rc = conv( Conv_cp866, &str_utf8, &len_utf8, &str_cp866, &len_cp866);
#ifdef DEBUG
        size866 += len_cp866;
        fprintf( Debug, "conv_source: rc=%d, len_utf8=%d, len_cp866=%d, size866=%d\n", rc, len_utf8, len_cp866, size866);
        fflush( Debug);
#endif
        if( rc >= 0 || rc == E_INVAL) {
            if( str_utf8 >= pb + len_cp866) {
                memcpy( pb, str_cp866, len_cp866);
                continue;
            }
        } else {
#ifdef DEBUG
            fprintf( Debug, "conv_source: rc=%d, Can't convert UTF8 to CP866\n", rc);
            fflush( Debug);
#endif
            return -1;
        }
    }

    *size = pb - src;

#ifdef DEBUG
    fprintf( Debug, "conv_source: Ok! rc=%d, size=%d\n", rc, *size);
    fflush( Debug);
#endif
    return 0;
}

char *conv_fgets( char *buf, int size, FILE *fp)
{
    if( !fgets( buf, size, fp))
        return NULL;

#ifdef VIEW_UTF8
    char *outbuf;

    size = strlen( buf);
    if( !( outbuf = conv_cp866( buf, &size)))
        return NULL;

    memcpy( buf, outbuf, size);
    buf [size] = '\0';
#endif

    return buf;
}

int conv_test( char *str, int len)
{
    int rc = 0, size, len_utf8 = 0;
    char *str_utf8 = NULL, *str_cp866;

    printf( "conv_test: str=<%*.*s>\n", len, len, str);

    conv_reset( Conv_utf8);

    str_cp866 = "����饭�� ������� �� �⪠�� �ਣ���";
    size = strlen( str_cp866);
    rc = conv( Conv_utf8, &str_cp866, &size, &str_utf8, &len_utf8);
    if( rc >= 0) {
        printf( "conv_test: rc=%d, len_utf8=<%d>\n", rc, len_utf8);
        printf( "conv_test [Ok!]: str_utf8=<%*.*s>\n", len_utf8, len_utf8, str_utf8);
    } else {
        printf( "conv_test [Error]: rc=%d, Can't convert!\n", rc);
    }

    str_utf8 = NULL;
    len_utf8 = 0;
    rc = conv( Conv_utf8, &str, &len, &str_utf8, &len_utf8);
    if( rc >= 0) {
        printf( "conv_test: rc=%d, len_utf8=<%d>\n", rc, len_utf8);
        printf( "conv_test [Ok!]: str_utf8=<%*.*s>\n", len_utf8, len_utf8, str_utf8);
    } else {
        printf( "conv_test [Error]: rc=%d, Can't convert!\n", rc);
    }

    return rc;
}
