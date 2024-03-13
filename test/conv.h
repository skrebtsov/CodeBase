#ifndef CONV_H
#define CONV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include <iconv.h>
#include <wchar.h>
//#include <locale.h>

#include "math.h"

#define MAX_CONV 2048
//#define MAX_CONV 8196

#define SRC_SIZE 1024

#define E_SIZE  -1
#define E_ILSEQ -2
#define E_INVAL -3
#define E_BIG   -4

char *conv_open( const char *to, const char *from);
void conv_close( iconv_t cd);
int conv( iconv_t cd, char **str, int *size, char **outbuf, int *outsize);
void conv_reset( iconv_t cd);

int conv_init( void);
void conv_free( void);
char *conv_utf8( char *str, int *size);
char *conv_cp866( char *str, int *size);
char *str866( char *str);
char conv_cp866_wchar( wchar_t wchar);
char char866( wchar_t wchar);
int conv_source( char *src, int *size);
char *conv_fgets( char *buf, int size, FILE *fp);

int conv_test( char *str, int len);

#endif
