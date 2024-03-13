#include <stdio.h>

#include "d4all.h"
#include "conv.h"

#ifdef DEBUG
    FILE *Debug = NULL;
#endif

FIELD4INFO fields [] =
{
    { "NAME", 'C', 20, 0 },
    { "AGE", 'N', 3, 0 },
    NULL
};

TAG4INFO tags [] =
{
    { "name", "NAME", 0, 0, 0},
    NULL
};

TAG4INFO bank_tags [] =
{
    { "mfo", "MFO", 0, 0, 0},
    { "ks", "KS", 0, 0, 0},
    { "adr", "ADR", 0, 0, 0},
    NULL
};

int main( void)
{
    int i, n, rc;
    int size, len_utf8 = 0;
    char *str_utf8 = NULL, *str_cp866;

    CODE4 cb ;
    DATA4 *data, *bank ;
    FIELD4 *field = NULL;
    TAG4 *tag_mfo, *tag_ks, *tag_adr;
    INDEX4 *index, *ind_mfo, *ind_ks, *ind_adr;

    printf( "sizeof( int)=%d\n", sizeof( int));
    printf( "sizeof( long)=%d\n", sizeof( long));

#ifdef DEBUG
    if(( Debug = fopen( "debug.log", "w")) == NULL) {
        perror( "fopen:debug.log");
        return -1;
    }
    fflush( Debug);
#endif

    if( conv_init() == -1) {
        printf( "Error: Can't init conv!\n");
        return -1;
    }

    code4init( &cb) ;
    cb.safety = 0 ;
#ifdef N4OTHER
    cb.autoOpen = 0;
#endif

    data = d4create( &cb, "test", fields, tags) ;
    if( !data ) {
        printf( "Can't create <test.dbf>\n");
        return -1;
    }
    printf( "<test.dbf> successfully created\n") ;
    d4close( data);

    bank = d4open( &cb, "bank");
    if( !bank ) {
        printf( "Can't create <bank.dbf>\n");
        return -1;
    }
    printf( "<bank.dbf> successfully opened\n") ;

    if( cb.errorCode < 0) {
        printf( "ERROR! %d\n", cb.errorCode);
        return -1;
    }

    index = i4create( bank, "bank", bank_tags);
    i4close( index);

    printf( "bank: reccount=%d, recno=%d\n", d4recCount( bank), d4recNo( bank));
    d4bottom( bank);
    printf( "bank: bottom: recno=%d\n", d4recNo( bank));
    d4top( bank);
    printf( "bank: top: recno=%d\n", d4recNo( bank));
    d4go( bank, 100);
    printf( "bank: recno=%d\n", d4recNo( bank));

    ind_mfo = d4index( bank, "MFO");
    ind_ks = d4index( bank, "KS");
    ind_adr = d4index( bank, "ADR");

#ifdef S4CLIPPER
    tag_mfo = t4open( bank, ind_mfo, "MFO");
    tag_ks = t4open( bank, ind_ks, "KS");
    tag_adr = t4open( bank, ind_adr, "ADR");

    if( cb.errorCode < 0) {
        printf( "ERROR! %d\n", cb.errorCode);
        return -1;
    }

//    d4tagSelect( bank, tag_mfo);
    d4tagSelect( bank, tag_adr);
#endif

    n = d4numFields( bank);
//    for( rc = d4top( bank); rc == r4success; rc = d4skip( bank, 1L)) {
    for( rc = d4bottom( bank); rc == r4success; rc = d4skip( bank, -1L)) {
        printf( "%d:\t", d4recNo( bank));
        for( i = 1; i <= n; i++) {
            field = d4fieldJ( bank, i);
//            printf( "%d: %s ", d4recNo( bank), f4memoStr( field));

            str_cp866 = (char *)f4memoStr( field);
            size = strlen( str_cp866);

            str_utf8 = NULL;
            len_utf8 = 0;

            str_utf8 = conv_utf8( str_cp866, &size);
            len_utf8 = size;
            rc = str_utf8 ? 0 : -1;

            if( rc >= 0) {
//                printf( "rc=%d, len_utf8=<%d>\n", rc, len_utf8);
                printf( "%*.*s; ", len_utf8, len_utf8, str_utf8);
            } else {
                printf( "Error: rc=%d, Can't convert!\n", rc);
            }
        }
        printf("\n");
    }

    str_utf8 = "АБАТСКИЙ";
    size = strlen( str_utf8);
    str_cp866 = conv_cp866( str_utf8, &size);
    str_cp866[ size] = '\0';
    printf( "bank.seek: size=%d, str_utf8=<%s>, str_cp866=<%s>\n", size, str_utf8, str_cp866);
    if( str_cp866) {
        if( d4seek( bank, str_cp866) == 0)
            printf( "bank.seek: Ok! size=%d, recno=%d\n", size, d4recNo( bank));
        else
            printf( "bank.seek: No! not found\n");
    } else {
        printf( "Can't convert!\n");
    }

//    i4close( ind_ks);
//    i4close( ind_mfo);
    d4close( bank);

    code4close( &cb) ;
    code4initUndo( &cb) ;

    conv_free();

#ifdef DEBUG
    fclose( Debug);
#endif

    return 0;
}
