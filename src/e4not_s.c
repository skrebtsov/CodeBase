/* e4not_s.c   (c)Copyright Sequiter Software Inc., 1988-1998.  All rights reserved. */

/* contains error stubs for functions not supported under various compile
   switches */

#include "d4all.h"

#ifdef S4OS2DLL
   #ifndef S4DLL_DEF
      #define S4DLL_DEF
   #endif
#endif

#ifdef S4OFF_WRITE
   #ifndef ON_N4OTHER_OFF_WRITE_INDEX
      #define ON_N4OTHER_OFF_WRITE_INDEX
   #endif
   #ifndef S4OFF_INDEX_WRITE_ON_MDX_FOX
      #define S4OFF_INDEX_WRITE_ON_MDX_FOX
   #endif
   #ifndef S4OFF_WRITE_MEMO
      #define S4OFF_WRITE_MEMO
   #endif
   #ifndef S4OFF_WRITE_INDEX
      #define S4OFF_WRITE_INDEX
   #endif
   #ifndef S4OFF_STAND_WRITE_TRAN
      #define S4OFF_STAND_WRITE_TRAN
   #endif
   #ifndef S4OFF_WRITE_TRAN
      #define S4OFF_WRITE_TRAN
   #endif
   #ifndef S4OFF_N4OTHER_INDEX_WRITE
      #define S4OFF_N4OTHER_INDEX_WRITE
   #endif
   #ifndef S4OFF_WRITE_REPORT
      #define S4OFF_WRITE_REPORT
   #endif
   #ifndef S4OFF_CLIENT_OR_FOX_OR_WRITE
      #define S4OFF_CLIENT_OR_FOX_OR_WRITE
   #endif
   #ifndef S4OFF_INDEX_WRITE_OR_CLIENT
      #define S4OFF_INDEX_WRITE_OR_CLIENT
   #endif
#endif

#ifndef S4CLIENT_OR_FOX
   #ifndef S4OFF_CLIENT_OR_FOX_OR_WRITE
      #define S4OFF_CLIENT_OR_FOX_OR_WRITE
   #endif
#endif

#ifdef S4OFF_REPORT
   #ifndef S4OFF_WRITE_REPORT
      #define S4OFF_WRITE_REPORT
   #endif
#endif

#ifdef S4OFF_MEMO
   #ifndef S4OFF_WRITE_MEMO
      #define S4OFF_WRITE_MEMO
   #endif
   #ifndef S4OFF_MEMO_S4MDX
      #define S4OFF_MEMO_S4MDX
   #endif
#endif

#ifndef S4MDX
   #ifndef S4OFF_MEMO_S4MDX
      #define S4OFF_MEMO_S4MDX
   #endif
#endif

#ifdef S4OFF_INDEX
   #ifndef S4OFF_INDEX_OR_NOT_MDX
      #define S4OFF_INDEX_OR_NOT_MDX
   #endif
   #ifndef ON_N4OTHER_OFF_WRITE_INDEX
      #define ON_N4OTHER_OFF_WRITE_INDEX
   #endif
   #ifndef S4OFF_N4OTHER_INDEX
      #define S4OFF_N4OTHER_INDEX
   #endif
   #ifndef S4OFF_INDEX_WRITE_ON_MDX_FOX
      #define S4OFF_INDEX_WRITE_ON_MDX_FOX
   #endif
   #ifndef S4OFF_INDEX_ON_MDX_FOX
      #define S4OFF_INDEX_ON_MDX_FOX
   #endif
   #ifndef S4OFF_WRITE_INDEX
      #define S4OFF_WRITE_INDEX
   #endif
   #ifndef S4OFF_N4OTHER_INDEX_WRITE
      #define S4OFF_N4OTHER_INDEX_WRITE
   #endif
   #ifndef S4OFF_INDEX_ON_CB51
      #define S4OFF_INDEX_ON_CB51
   #endif
   #ifndef S4OFF_INDEX_WRITE_OR_CLIENT
      #define S4OFF_INDEX_WRITE_OR_CLIENT
   #endif
#endif

#ifdef S4MDX
   #ifndef S4OFF_INDEX_OR_NOT_MDX
      #define S4OFF_INDEX_OR_NOT_MDX
   #endif
   #ifndef S4OFF_INDEX_WRITE_ON_MDX_FOX
      #define S4OFF_INDEX_WRITE_ON_MDX_FOX
   #endif
   #ifndef S4OFF_INDEX_ON_MDX_FOX
      #define S4OFF_INDEX_ON_MDX_FOX
   #endif
#endif

#ifdef S4FOX
   #ifndef S4OFF_INDEX_WRITE_ON_MDX_FOX
      #define S4OFF_INDEX_WRITE_ON_MDX_FOX
   #endif
   #ifndef S4OFF_INDEX_ON_MDX_FOX
      #define S4OFF_INDEX_ON_MDX_FOX
   #endif
#endif

#ifdef N4OTHER
   #ifndef ON_N4OTHER_OFF_WRITE_INDEX
      #define ON_N4OTHER_OFF_WRITE_INDEX
   #endif
#else
   #ifndef S4OFF_N4OTHER_INDEX
      #define S4OFF_N4OTHER_INDEX
   #endif
   #ifndef S4OFF_N4OTHER_INDEX_WRITE
      #define S4OFF_N4OTHER_INDEX_WRITE
   #endif
#endif

#ifdef S4CLIENT
   #ifndef ON_CLIENT_OFF_TRAN
      #define ON_CLIENT_OFF_TRAN
   #endif
   #ifndef S4OFF_INDEX_WRITE_OR_CLIENT
      #define S4OFF_INDEX_WRITE_OR_CLIENT
   #endif
#endif

#ifdef S4OFF_TRAN
   #ifndef ON_CLIENT_OFF_TRAN
      #define ON_CLIENT_OFF_TRAN
   #endif
   #ifndef S4OFF_STAND_WRITE_TRAN
      #define S4OFF_STAND_WRITE_TRAN
   #endif
   #ifndef S4OFF_WRITE_TRAN
      #define S4OFF_STAND_WRITE_TRAN
   #endif
#endif

#ifdef S4OFF_OPTIMIZE
   #ifndef S4OFF_STAND_OPT
      #define S4OFF_STAND_OPT
   #endif
#endif

#ifndef S4STAND_ALONE
   #ifndef S4OFF_STAND_OPT
      #define S4OFF_STAND_OPT
   #endif
   #ifndef S4OFF_STAND_WRITE_TRAN
      #define S4OFF_STAND_WRITE_TRAN
   #endif
#endif

#ifdef S4CB51
   #ifndef S4OFF_INDEX_ON_CB51
      #define S4OFF_INDEX_ON_CB51
   #endif
#endif

#ifndef S4UNIX
   #ifdef __TURBOC__
      #pragma hdrstop
   #endif
#endif

#ifdef S4SERVER
/* for index-independence of OLE-DB dll, need to export some functions... */

#ifndef S4FOX
#ifdef P4ARGS_USED
   #pragma argsused
#endif
void S4FUNCTION f4assignNull( FIELD4 *field )
{
   return ;
}
#endif /* S4FOX */

#else

#ifndef E4MISC
   int S4FUNCTION mem4checkMemory()
   {
      return error4( 0, e4notSupported, E95903 ) ;
   }

   #ifdef P4ARGS_USED
   #pragma argsused
#endif
   int S4FUNCTION mem4freeCheck( const int maxLeft )
   {
      return error4( 0, e4notSupported, E95904 ) ;
   }
#endif /* ifndef S4DEBUG */

#ifndef E4HOOK
#ifdef P4ARGS_USED
   #pragma argsused
#endif
void S4FUNCTION error4hook( CODE4 *c4, int errCode, long errCode2, const char *desc1, const char *desc2, const char *desc3 )
{
   error4( c4, e4notSupported, E96602 ) ;
}
#endif

#ifdef S4OFF_INDEX_WRITE_OR_CLIENT
#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION t4uniqueModify( TAG4 *tag, int newUnique )
{
   return error4( 0, e4notSupported, E91716 ) ;
}
#endif

#ifdef S4OFF_MULTI
#ifdef P4ARGS_USED
   #pragma argsused
#endif
long S4FUNCTION d4recCountDo( DATA4 *data )
{
   return 0L ;
}
#endif

#ifdef S4OFF_TRAN
#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION code4tranCommit( CODE4 *c4 )
{
   return error4( c4, e4notSupported, E93828 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION code4tranRollback( CODE4 *c4 )
{
   return error4( c4, e4notSupported, E93830 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION code4tranStart( CODE4 *c4 )
{
   return error4( c4, e4notSupported, E93829 ) ;
}
#endif /* S4OFF_TRAN */

#ifdef S4OFF_CLIENT_OR_FOX_OR_WRITE
#ifdef P4ARGS_USED
   #pragma argsused
#endif
void S4FUNCTION f4assignNotNull( FIELD4 *field )
{
   error4( field->data->codeBase, e4notSupported, E90539 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
void S4FUNCTION f4assignNull( FIELD4 *field )
{
   error4( field->data->codeBase, e4notSupported, E90539 ) ;
}
#endif /* S4OFF_CLIENT_OR_FOX_OR_WRITE */

#ifndef S4CLIENT_OR_FOX
#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION f4null( const FIELD4 *field )
{
   return error4( field->data->codeBase, e4notSupported, E90540 ) ;
}
#endif /* S4CLIENT_OR_FOX */

#ifdef S4WINDOWS
#ifdef S4OFF_REPORT
#include "r4report.h"
#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
void S4FUNCTION area4add_object( AREA4 *area, OBJ4 *obj_add )
{
   return ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
AREA4 * S4FUNCTION area4create( GROUP4 *group, long height, short is_header, char *expression )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
void S4FUNCTION area4free( AREA4 *area )
{
   return ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION area4numObjects( PAREA4 area )
{
   return e4notSupported ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
POBJ4 S4FUNCTION area4objFirst( PAREA4 area )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
POBJ4 S4FUNCTION area4objLast( PAREA4 area )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
POBJ4 S4FUNCTION area4objNext( PAREA4 area, POBJ4 aobj )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
POBJ4 S4FUNCTION area4objPrev( PAREA4 area, POBJ4 aobj )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION area4pageBreak( PAREA4 area, int breaks )
{
   return e4notSupported ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
void S4FUNCTION area4sort_obj_tree( PAREA4 area )
{
   return ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
LPSTR S4FUNCTION bmp4FindDIBBits( LPSTR lpbi )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
HANDLE S4FUNCTION bmp4GetDIB( LPSTR fname, CODE4 *codeBase )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
WORD S4FUNCTION bmp4PaletteSize( LPSTR lpbi )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
BOOL S4FUNCTION bmp4WriteDIB (LPSTR szFile, HANDLE hdib)
{
   return FALSE ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
GROUP4 * S4FUNCTION group4create( REPORT4 *r4, char *name, char *resetExpression )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
PAREA4 S4FUNCTION group4footerFirst( PGROUP4 group )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
PAREA4 S4FUNCTION group4footerNext( PGROUP4 group, PAREA4 area )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
PAREA4 S4FUNCTION group4footerPrev( PGROUP4 group, PAREA4 area )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
void S4FUNCTION group4free( GROUP4 *group )
{
   return ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
PAREA4 S4FUNCTION group4headerFirst( PGROUP4 group )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
PAREA4 S4FUNCTION group4headerNext( PGROUP4 group, PAREA4 area )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
PAREA4 S4FUNCTION group4headerPrev( PGROUP4 group, PAREA4 area )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION group4numFooters( PGROUP4 group )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION group4numHeaders( PGROUP4 group )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
void S4FUNCTION group4positionSet( GROUP4 *group, int position )
{
   return ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION group4repeatHeader( PGROUP4 group, int repeat_header )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION group4resetExprSet( PGROUP4 group, char *expr_src )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION group4resetPage( PGROUP4 group, int reset_page )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION group4resetPageNum( PGROUP4 group, int reset_pagenum )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION group4swapFooter( PGROUP4 group, int swap_footer )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION group4swapHeader( PGROUP4 group, int swap_header )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
POBJ4 S4FUNCTION obj4bitmapFieldCreate( AREA4 *area, FIELD4 *field, long x, long y, long w, long h )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
void S4FUNCTION obj4bitmapFieldFree( POBJ4 obj )
{
   return ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
POBJ4 S4FUNCTION obj4bitmapFileCreate( AREA4 *area, char *filename, long x, long y, long w, long h )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
void S4FUNCTION obj4bitmapFileFree( POBJ4 obj )
{
   return ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
POBJ4 S4FUNCTION obj4bitmapStaticCreate( AREA4 *area, HANDLE hDIB, long x, long y, long w, long h )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
void S4FUNCTION obj4bitmapStaticFree( POBJ4 obj )
{
   return ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION obj4brackets( POBJ4 obj, int use_brackets )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
POBJ4 S4FUNCTION obj4calcCreate( AREA4 *area, EXPR4CALC *calcPtr, long x, long y, long w, long h )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
void S4FUNCTION obj4calcFree( OBJ4 *obj )
{
   return ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION obj4dataFieldSet( POBJ4 obj, char *fname, char ftype, int flength, int fdec )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION obj4dateFormat( POBJ4 obj, char S4PTR *date_format )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION obj4decimals( POBJ4 obj, int decimals )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
void S4FUNCTION obj4delete( OBJ4 *obj )
{
   return ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION obj4displayOnce( POBJ4 obj, char S4PTR *expr_string )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION obj4displayZero( POBJ4 obj, int display_zero )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
POBJ4 S4FUNCTION obj4exprCreate( AREA4 *area, EXPR4 *expr_ptr, long x, long y, long w, long h )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
void S4FUNCTION obj4exprFree( OBJ4 *obj )
{
   return ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
POBJ4 S4FUNCTION obj4fieldCreate( AREA4 *area, FIELD4 *field_ptr, long x, long y, long w, long h )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
void S4FUNCTION obj4fieldFree( OBJ4 *obj )
{
   return ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION obj4frameCorners( POBJ4 obj, int rounded )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
POBJ4 S4FUNCTION obj4frameCreate( AREA4 *area, long x, long y, long w, long h )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION obj4frameFill( POBJ4 obj, int fill )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
void S4FUNCTION obj4frameFree( OBJ4 *obj )
{
   return ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION obj4justify( POBJ4 obj, int alignment )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION obj4leadingZero( POBJ4 obj, int leading_zero )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
POBJ4 S4FUNCTION obj4lineCreate( AREA4 *area, int vertical, long x, long y, long length )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
void S4FUNCTION obj4lineFree( OBJ4 *obj )
{
   return ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION obj4lineWidth( POBJ4 obj, long width )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION obj4lookAhead( POBJ4 obj, int lookahead )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION obj4numericType( POBJ4 obj, int numeric_type )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
void S4FUNCTION obj4remove( POBJ4 obj )
{
   return ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION obj4style( POBJ4 obj, PSTYLE4 style )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
POBJ4 S4FUNCTION obj4textCreate( AREA4 *area, char *str_ptr, long x, long y, long w, long h )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
void S4FUNCTION obj4textFree( OBJ4 *obj )
{
   return ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
POBJ4 S4FUNCTION obj4totalCreate( AREA4 *area, TOTAL4 *total_ptr, long x, long y, long w, long h )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
void S4FUNCTION obj4totalFree( OBJ4 *obj )
{
   return ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
DATA4 S4PTR* S4FUNCTION relate4lookup_data( RELATE4 *relate, char *dname )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
RELATE4 * S4FUNCTION relate4retrieve(CODE4 *c4, char *file_name, int open_files, char *pathname )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
RELATE4 *S4FUNCTION relate4retrieve2( CODE4 *c4, char *file_name, int open_files, char *pathname, char *buf, char *name_buf )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION relate4save2( RELATE4 *relate, char *file_name, int save_paths, char *buf, char *name_buf )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION relate4save(RELATE4 *relate, char *file_name, int save_paths )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4index_type()
{
   return -1 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4caption( PREPORT4 report, char S4PTR *caption )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4currency( PREPORT4 report, char *currency )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4dataFileSet( PREPORT4 report, char *fname )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4dataGroup( PREPORT4 report, PGROUP4 group )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4dateFormat( PREPORT4 report, char *date_format  )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4decimal( PREPORT4 report, char decimal )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4do( REPORT4 *report )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
void S4FUNCTION report4freeLow( REPORT4 *r4, int free_relate, int close_files, int doPrinterFree )
{
   return ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
void S4FUNCTION report4free_styles( REPORT4 *report )
{
   return ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4generatePage(PREPORT4 report, HDC hDC )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
HDC S4FUNCTION report4get_printerIC ( REPORT4 *report )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
PGROUP4 S4FUNCTION report4groupFirst( PREPORT4 report )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4groupHardResets( PREPORT4 report, int reset_flag )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
PGROUP4 S4FUNCTION report4groupLast( PREPORT4 report )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
PGROUP4 S4FUNCTION report4groupLookup( PREPORT4 report, char *group_name )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
PGROUP4 S4FUNCTION report4groupNext( PREPORT4 report, PGROUP4 group )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
PGROUP4 S4FUNCTION report4groupPrev( PREPORT4 report, PGROUP4 group )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
PREPORT4 S4FUNCTION report4init( RELATE4 *relate )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4margins( PREPORT4 report, long left, long right, long top, long bottom, int unit_type )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4numGroups( PREPORT4 report )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4numStyles( PREPORT4 report )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4off_write()
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4output( PREPORT4 report, int output_handle, int use_styles )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4pageFree( PREPORT4 report )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
PGROUP4 S4FUNCTION report4pageHeaderFooter( PREPORT4 report )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4pageInit( PREPORT4 report )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4pageMarginsGet( PREPORT4 report, long S4PTR *margin_left,long S4PTR *margin_right, long S4PTR *margin_top, long S4PTR *margin_bottom )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
POBJECT4 S4FUNCTION report4pageObjFirst( PREPORT4 report )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
POBJECT4 S4FUNCTION report4pageObjNext( PREPORT4 report )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4pageSize( PREPORT4 report, long pg_height, long pg_width, int unit_type )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4pageSizeGet( PREPORT4 report, long *page_width, long *page_height )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4parent( PREPORT4 report, HWND parent )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
HDC S4FUNCTION report4printerDC( PREPORT4 report, HDC hDC )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
void S4FUNCTION report4printerSelect( PREPORT4 report )
{
   return ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4querySet( PREPORT4 report, char S4PTR *expr )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
REPORT4 * S4FUNCTION report4retrieve(CODE4 *c4, char *file_name, int open_files, char *pathname )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
REPORT4 * S4FUNCTION report4retrieve2(CODE4 *c4, char *file_name, int open_files, char *pathname, char *buf, char *name_buf )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4save( REPORT4 *report, char *file_name, int path )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4separator( PREPORT4 report, char separator )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4sortSet( PREPORT4 report, char S4PTR *expr )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
PSTYLE4 S4FUNCTION report4styleFirst( PREPORT4 report )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
PSTYLE4 S4FUNCTION report4styleLast( PREPORT4 report )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
PSTYLE4 S4FUNCTION report4styleNext( PREPORT4 report, PSTYLE4 style )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4styleSelect( PREPORT4 report, PSTYLE4 style )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
PSTYLE4 S4FUNCTION report4styleSelected( PREPORT4 report )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4styleSheetLoad( REPORT4 *report, char *file_name, int override )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4styleSheetSave( REPORT4 *report, char *file_name )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4titlePage( PREPORT4 report, int title_page )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
PGROUP4 S4FUNCTION report4titleSummary( PREPORT4 report )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION report4toScreen( PREPORT4 report, int to_screen )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION style4color( PSTYLE4 style, R4COLORREF color )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
STYLE4 FAR* S4FUNCTION style4create( REPORT4 *report, PR4LOGFONT lfont, char *name, R4COLORREF color, int point_size )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
BOOL S4FUNCTION style4delete( REPORT4 *report, char *style_name )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
BOOL S4FUNCTION style4free( REPORT4 *report, STYLE4 *style )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
PSTYLE4 S4FUNCTION style4index( PREPORT4 report, int index )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
PSTYLE4 S4FUNCTION style4lookup( REPORT4 *report, char *style_name )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
int S4FUNCTION total4addCondition( PTOTAL4 total, char *addCondition_src, int logcon )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
TOTAL4 * S4FUNCTION total4create( REPORT4 *r4, char *name, char *expr_src, int totalType, char *reset_expr_src )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
void S4FUNCTION total4free( TOTAL4 *total )
{
   return ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT */
TOTAL4 * S4FUNCTION total4lookup( REPORT4 *report, char *name )
{
   return 0 ;
}
#endif /* S4OFF_REPORT */

#ifdef S4OFF_WRITE_REPORT
#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* S4WINDOWS and S4OFF_REPORT or S4OFF_WRITE */
int S4FUNCTION report4dataDo( PREPORT4 report )
{
   return 0 ;
}
#endif /* S4OFF_WRITE_REPORT */

#endif /* S4WINDOWS */

#ifndef S4CLIENT
#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION d4lockTestFileLow( DATA4 *data )
{
   return error4( 0, e4notSupported, E92705 ) ;
}

#ifdef S4OFF_N4OTHER_INDEX
#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION t4close( TAG4 *t4 )
{
   return error4( 0, e4notSupported, E91637 ) ;
}
#endif
#endif /* S4CLIENT */

#ifndef S4CB51
#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION relate4lock( RELATE4 *relate )
{
   return error4( 0, e4notSupported, E94411 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION file4temp( FILE4 *file, CODE4 *codeBase, char *buf, const int auto_remove )
{
   return error4( 0, e4notSupported, E90623 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION d4lock_group( DATA4 *data, const long *recs, const int n_recs )
{
   return error4( 0, e4notSupported, E92724 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION relate4unlock( RELATE4 *relate )
{
   return error4( 0, e4notSupported, E94424 ) ;
}
#endif /* S4CB51 */

#ifndef S4CLIENT
int S4FUNCTION code4serverRestart( CODE4 S4PTR *c4 )
{
   return error4( c4, e4notSupported, E91110 ) ;
}
#endif

#ifdef S4OFF_WRITE_MEMO
#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION f4memoSetLen( FIELD4 *field, const unsigned len )
{
   return error4( field->data->codeBase, e4notSupported, E90528 ) ;
}
#endif /* S4OFF_WRITE_MEMO */

#ifndef S4CLIENT
#ifdef S4OFF_N4OTHER_INDEX
#ifdef P4ARGS_USED
   #pragma argsused
#endif
TAG4 *S4FUNCTION t4openLow( DATA4 *d4, INDEX4 *i4ndx, const char *fileName, const char *indexName )
{
   error4( d4->codeBase, e4notSupported, E94903 ) ;

   return 0 ;
}
#endif /* S4OFF_N4OTHER_INDEX_WRITE */
#endif /* S4STAND_ALONE */

#ifdef S4OFF_STAND_WRITE_TRAN
#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION code4logCreate( CODE4 *c4, const char *fileName, const char *userId )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION code4logOpen( CODE4 *c4, const char *fileName, const char *userId )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
void S4FUNCTION code4logOpenOff( CODE4 *c4 )
{
   return ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
const char *S4FUNCTION code4logFileName( CODE4 *c4 )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION d4log( DATA4 *data, const int logging )
{
   return 0 ;
}
#endif

#ifdef S4OFF_COMMUNICATIONS
#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION code4connect( CODE4 *c4, const char *serverId, const char *processId, const char *userName, const char *password, const char *protocol )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
CODE4 * S4FUNCTION socket4codeBase( void *socket )
{
   return 0 ;
}
#endif

#ifdef S4OFF_STAND_OPT
#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION code4optAll( CODE4 *codeBase )
{
   return 0 ;
}
#endif

#ifdef S4STAND_ALONE
int S4FUNCTION d4lockTestAppendLow( DATA4 *data )
{
   return error4( data->codeBase, e4notSupported, E92704 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
S4CONST char *S4FUNCTION t4exprLow( TAG4 *t4 )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
S4CONST char *S4FUNCTION t4filterLow( TAG4 *t4 )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION code4info( CODE4 *c4 )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
const char *S4FUNCTION code4serverName( CODE4 *c4 )
{
   return 0 ;
}
#endif

#ifdef S4DLL_DEF
   #ifndef S4LOCK_HOOK
      #ifdef P4ARGS_USED
         #pragma argsused
      #endif
         int code4lockHook( CODE4 *c4, const char *fileName, const char *userId, const char *netId, long lockItem, int numAttempts )
         {
            #ifdef E4PARM_HIGH
               if ( c4 == 0 )
                  return error4( 0, e4parm_null, E90620 ) ;
            #endif

            return error4( c4, e4notLock, E90620 ) ;
         }
   #endif

   #ifndef E4HOOK
      #ifdef P4ARGS_USED
         #pragma argsused
      #endif
      void S4FUNCTION e4hook( CODE4 *c4, int err_code, const char *desc1, const char *desc2, const char *desc3 )
      {
         #ifdef E4PARM_HIGH
            if ( c4 == 0 )
               error4( 0, e4parm_null, E95001 ) ;
         #endif
      }
   #endif
#endif

#ifdef ON_N4OTHER_OFF_WRITE_INDEX
#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION i4tagAdd( INDEX4 *i4, const TAG4INFO *tagData )
{
   #ifdef E4PARM_HIGH
      if ( i4 == 0 )
         return error4( 0, e4parm_null, E91717 ) ;
   #endif

   return error4( i4->codeBase, e4notSupported, E91717 ) ;
}
#endif

#ifdef S4OFF_WRITE_MEMO
#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION d4memoCompress( DATA4 *data )
{
   #ifdef S4VBASIC
      if ( c4parm_check( data, 2, E95201 ) )
         return -1 ;
   #endif

   #ifdef E4PARM_HIGH
      if ( data == 0 )
         return error4( 0, e4parm_null, E95201 ) ;
   #endif
   return error4( data->codeBase, e4notSupported, E95201 ) ;
}
#endif

#ifdef S4OFF_WRITE
#ifdef P4ARGS_USED
   #pragma argsused
#endif
DATA4 *S4FUNCTION d4createTemp( CODE4 *c4, const FIELD4INFO *fieldData, const TAG4INFO *tagInfo )
{
   error4( c4, e4notWrite, E91401 ) ;
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION d4changed( DATA4 *data, int flag )
{
   #ifdef E4PARM_HIGH
      if ( data == 0 )
         return error4( 0, e4parm_null, E94101 ) ;
   #endif
   return error4( data->codeBase, e4notWrite, E94101 ) ;
}

int S4FUNCTION d4append( DATA4 *data )
{
   #ifdef S4VBASIC
      if ( c4parm_check( data, 2, E91103 ) )
         return -1 ;
   #endif  /* S4VBASIC */

   #ifdef E4PARM_HIGH
      if ( data == 0 )
         return error4( 0, e4parm_null, E91103 ) ;
   #endif

   return error4( data->codeBase, e4notWrite, E91103 ) ;
}

int S4FUNCTION d4appendBlank( DATA4 *data )
{
   #ifdef S4VBASIC
      if ( c4parm_check( data, 2, E91104 ) )
         return -1 ;
   #endif  /* S4VBASIC */

   #ifdef E4PARM_HIGH
      if ( data == 0 )
         return error4( 0, e4parm_null, E91104 ) ;
   #endif

   return error4( data->codeBase, e4notWrite, E91104 ) ;
}
#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION d4appendStart( DATA4 *data, int useMemoEntries )
{
   #ifdef S4VBASIC
      if ( c4parm_check( data, 2, E91107 ) )
         return -1 ;
   #endif  /* S4VBASIC */

   #ifdef E4PARM_HIGH
      if ( data == 0 )
         return error4( 0, e4parm_null, E91107 ) ;
   #endif

   return error4( data->codeBase, e4notWrite, E91107 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
DATA4 *S4FUNCTION d4create( CODE4 *c4, const char *name, const FIELD4INFO *fieldData, const TAG4INFO *tagInfo )
{
   #ifdef S4VBASIC
      if ( c4parm_check( c4, 1, E91401 ) )
         return 0 ;
   #endif  /* S4VBASIC */

   #ifdef E4PARM_HIGH
      if ( c4 == 0 )
      {
         error4( 0, e4parm_null, E91401 ) ;
         return 0 ;
      }
   #endif

   error4( c4, e4notWrite, E91401 ) ;
   return 0 ;
}

void S4FUNCTION d4delete( DATA4 *data )
{
   #ifdef S4VBASIC
      if ( c4parm_check( data, 2, E93305 ) )
         return ;
   #endif  /* S4VBASIC */

   #ifdef E4PARM_HIGH
      if ( data == 0 )
      {
         error4( 0, e4parm_null, E93305 ) ;
         return ;
      }
   #endif

   error4( data->codeBase, e4notWrite, E93305 ) ;
}

int S4FUNCTION d4pack( DATA4 *d4 )
{
   #ifdef S4VBASIC
      if ( c4parm_check( d4, 2, E94601 ) )
         return 0 ;
   #endif

   #ifdef E4PARM_HIGH
      if ( d4 == 0 )
         return error4( 0, e4parm_null, E94601 ) ;
   #endif

   return error4( d4->codeBase, e4notWrite, E94601 ) ;
}

void S4FUNCTION d4recall( DATA4 *data )
{
   #ifdef E4PARM_HIGH
      if ( data == 0 )
      {
         error4( 0, e4parm_null, E93311 ) ;
         return ;
      }
   #endif

   error4( data->codeBase, e4notWrite, E93311 ) ;
}

int S4FUNCTION d4reindex( DATA4 *data )
{
   #ifdef S4VBASIC
      if ( c4parm_check( data, 2, E93004 ) )
         return -1 ;
   #endif  /* S4VBASIC */

   #ifdef E4PARM_HIGH
      if ( data == 0 )
         return error4( 0, e4parm_null, E93004 ) ;
   #endif

   return error4( data->codeBase, e4notWrite, E93004 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION d4writeLow( DATA4 *d4, const long rec, const int unlock )
{
   #ifdef S4VBASIC
      if ( c4parm_check( d4, 2, E92601 ) )
         return 0 ;
   #endif  /* S4VBASIC */

   #ifdef E4PARM_HIGH
      if ( d4 == 0 )
         return error4( 0, e4parm_null, E92601 ) ;
   #endif

   return error4( d4->codeBase, e4notWrite, E92601 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION d4zap( DATA4 *d4, const long r1, const long r2 )
{
   #ifdef S4VBASIC
      if ( c4parm_check( d4, 2, E94604 ) )
         return -1 ;
   #endif

   #ifdef E4PARM_HIGH
      if ( d4 == 0 )
         return error4( 0, e4parm_null, E94604 ) ;
   #endif

   return error4( d4->codeBase, e4notWrite, E94604 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
void S4FUNCTION f4assign( FIELD4 *field, const char *str )
{
   #ifdef S4VBASIC
      if ( c4parm_check( field, 3, E90533 ) )
         return ;
   #endif

   #ifdef E4PARM_HIGH
      if ( field == 0 )
      {
         error4( 0, e4parm_null, E90533 ) ;
         return ;
      }
   #endif

   error4( field->data->codeBase, e4notWrite, E90533 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
void S4FUNCTION f4assignChar( FIELD4 *field, const int chr )
{
   #ifdef S4VBASIC
      if ( c4parm_check( field, 3, E90502 ) )
         return ;
   #endif

   #ifdef E4PARM_HIGH
      if ( field == 0 )
      {
         error4( 0, e4parm_null, E90502 ) ;
         return ;
      }
   #endif

   error4( field->data->codeBase, e4notWrite, E90502 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
void S4FUNCTION f4assignDouble( FIELD4 *field, const double dValue )
{
   #ifdef S4VBASIC
      if ( c4parm_check ( field, 3, E90504 ) )
         return ;
   #endif

   #ifdef E4PARM_HIGH
      if ( field == 0 )
      {
         error4( 0, e4parm_null, E90504 ) ;
         return ;
      }
   #endif

   error4( field->data->codeBase, e4notWrite, E90504 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
void S4FUNCTION f4assignField( FIELD4 *fieldTo, const FIELD4 *fieldFrom )
{
   #ifdef E4PARM_HIGH
      if ( fieldTo == 0 )
      {
         error4( 0, e4parm_null, E90501 ) ;
         return ;
      }
   #endif

   error4( fieldTo->data->codeBase, e4notWrite, E90501 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
void S4FUNCTION f4assignInt( FIELD4 *field, const int iValue )
{
   #ifdef S4VBASIC
      if ( c4parm_check( field, 3, E90514 ) )
         return ;
   #endif

   #ifdef E4PARM_HIGH
      if ( field == 0 )
      {
         error4( 0, e4parm_null, E90514 ) ;
         return ;
      }
   #endif

   error4( field->data->codeBase, e4notWrite, E90514 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
void S4FUNCTION f4assignLong( FIELD4 *field, const long lValue )
{
   #ifdef S4VBASIC
      if ( c4parm_check( field, 3, E90516 ) )
         return ;
   #endif

   #ifdef E4PARM_HIGH
      if ( field == 0 )
      {
         error4( 0, e4parm, E90516 ) ;
         return ;
      }
   #endif

   error4( field->data->codeBase, e4notWrite, E90516 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
void S4FUNCTION f4assignN( FIELD4 *field, const char *ptr, const unsigned ptrLen )
{
   #ifdef E4PARM_HIGH
      if ( field == 0 )
      {
         error4( 0, e4parm_null, E90534 ) ;
         return ;
      }
   #endif

   error4( field->data->codeBase, e4notWrite, E90534) ;
}

char *S4FUNCTION f4assignPtr( FIELD4 *field )
{
   #ifdef E4PARM_HIGH
      if ( field == 0 )
      {
         error4( 0, e4parm_null, E90507 ) ;
         return 0 ;
      }
   #endif

   error4( field->data->codeBase, e4notWrite, E90507 ) ;
   return 0 ;
}

void S4FUNCTION f4blank( FIELD4 *field )
{
   #ifdef S4VBASIC
      if ( c4parm_check( field, 3, E90508 ) )
         return ;
   #endif

   #ifdef E4PARM_HIGH
      if ( field == 0 )
      {
         error4( 0, e4parm_null, E90508 ) ;
         return ;
      }
   #endif

   error4( field->data->codeBase, e4notWrite, E90508 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION f4memoAssign( FIELD4 *field, const char *ptr )
{
   #ifdef E4PARM_HIGH
      if ( field == 0 )
         return error4( 0, e4parm_null, E90518 ) ;
   #endif

   return error4( field->data->codeBase, e4notWrite, E90518 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION f4memoAssignN( FIELD4 *field, const char *ptr, const unsigned ptrLen )
{
   #ifdef S4VBASIC
      if ( c4parm_check( field, 3, E90519 ) )
         return -1 ;
   #endif

   #ifdef E4PARM_HIGH
      if ( field == 0 )
         return error4( 0, e4parm_null, E90519 ) ;
   #endif

   return error4( field->data->codeBase, e4notWrite, E90519 ) ;
}
#endif

#ifdef S4OFF_WRITE_INDEX
#ifdef P4ARGS_USED
   #pragma argsused
#endif
INDEX4 *S4FUNCTION i4create( DATA4 *d4, const char *fileName, const TAG4INFO *tagData )
{
   #ifdef S4VBASIC
      if ( c4parm_check( d4, 2, E95301 ) )
         return 0 ;
   #endif

   #ifdef E4PARM_HIGH
      if ( d4 == 0 )
      {
         error4( 0, e4parm_null, E95301 ) ;
         return 0 ;
      }
   #endif

   error4( d4->codeBase, e4notSupported, E95301 ) ;
   return 0 ;
}

int S4FUNCTION i4reindex( INDEX4 *i4 )
{
   #ifdef S4VBASIC
      if ( c4parm_check( i4, 0, E92101 ) )
         return -1 ;
   #endif  /* S4VBASIC */

   #ifdef E4PARM_LOW
      if ( i4 == 0  )
         return error4( 0, e4parm_null, E92101 ) ;
   #endif

   return error4( i4->codeBase, e4notSupported, E92101 ) ;
}
#endif

#ifdef S4OFF_INDEX

const char *S4FUNCTION i4fileName( INDEX4 *i4 )
{
   #ifdef E4PARM_HIGH
      if ( i4 == 0 )
      {
         error4( 0, e4parm_null, E91720 ) ;
         return 0 ;
      }
   #endif

   error4( i4->codeBase, e4notIndex, E91720 ) ;
   return 0 ;
}

char *S4FUNCTION t4alias( TAG4 *t4 )
{
   #ifdef S4VBASIC
   #ifdef S4CB51
      if ( c4parm_check( t4, 4, E40146 ) ) return 0 ;
   #else
      if ( c4parm_check( t4, 4, E91640 ) ) return 0 ;
   #endif
   #endif

   #ifdef E4PARM_HIGH
      if ( t4 == 0 )
      {
         error4( 0, e4parm_null, E91640 ) ;
         return 0 ;
      }
   #endif

   error4( t4->index->codeBase, e4notIndex, E91640 ) ;
   return 0 ;
}

short int S4FUNCTION t4unique( const TAG4 *tag )
{
   #ifdef S4VBASIC
      #ifdef S4CB51
         if ( c4parm_check ( tag, 4, E40150 ) ) return 0 ;
      #else
         if ( c4parm_check ( tag, 4, E91639 ) ) return 0 ;
      #endif
   #endif

   #ifdef E4PARM_HIGH
      if ( tag == 0 )
         return error4( 0, e4parm_null, E91639 ) ;
      if ( tag->tagFile == 0 )
         return error4( 0, e4parm, E91639 ) ;
   #endif

   return error4( tag->index->codeBase, e4notIndex, E91639 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION t4uniqueSet( TAG4 S4PTR *t4, const short uniqueCode )
{

   #ifdef S4VBASIC
      if ( c4parm_check ( t4, 4, E91601 ) ) return 0 ;
   #endif

   #ifdef E4PARM_HIGH
      if ( t4 == 0 )
         return error4( 0, e4parm_null, E91601 ) ;
   #endif

   return error4( t4->index->codeBase, e4notIndex, E91601 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION d4seek( DATA4 *d4, const char *str )
{
   #ifdef S4VBASIC
      if ( c4parm_check( d4, 2, E92907 ) )
         return 0 ;
   #endif

   #ifdef E4PARM_HIGH
      if ( d4 == 0 )
         return error4( 0, e4parm_null, E92907 ) ;
   #endif

   return error4( d4->codeBase, e4notIndex, E92907 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION d4seekN( DATA4 S4PTR *d4, const char *str, const short len )
{
   #ifdef S4VBASIC
      if ( c4parm_check( d4, 2, E92903 ) )
         return 0 ;
   #endif

   #ifdef E4PARM_HIGH
      if ( d4 == 0 )
         return error4( 0, e4parm_null, E92903 ) ;
   #endif

   return error4( d4->codeBase, e4notIndex, E92903 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION d4seekDouble( DATA4 *d4, const double dkey )
{
   #ifdef S4VBASIC
      if ( c4parm_check( d4, 2, E92904 ) )
         return 0 ;
   #endif

   #ifdef E4PARM_HIGH
      if ( d4 == 0 )
         return error4( 0, e4parm_null, E92904 ) ;
   #endif

   return error4( d4->codeBase, e4notIndex, E92904 ) ;
}

int S4FUNCTION i4close( INDEX4 *i4 )
{
   #ifdef S4VBASIC
      if ( c4parm_check( i4, 0, E91701 ) )
         return -1 ;
   #endif

   #ifdef E4PARM_HIGH
      if ( i4 == 0 )
         return error4( 0, e4parm_null, E91701 ) ;
   #endif

   return error4( i4->codeBase, e4notIndex, E91701 ) ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
INDEX4 *S4FUNCTION i4open( DATA4 *d4, const char *fileName )
{
   #ifdef E4PARM_HIGH
      if ( d4 == 0 )
      {
         error4( 0, e4parm_null, E91706 ) ;
         return 0 ;
      }
   #endif

   error4( d4->codeBase, e4notIndex, E91706 ) ;
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
TAG4 *S4FUNCTION i4tag( INDEX4 *i4, const char *tagName )
{
   #ifdef S4VBASIC
      if ( c4parm_check( i4, 0, E91709 ) )
         return 0 ;
   #endif

   #ifdef E4PARM_LOW
      if ( i4 == 0 )
      {
         error4( 0, e4parm_null, E91709 ) ;
         return 0 ;
      }
   #endif

   error4( i4->codeBase, e4notIndex, E91709 ) ;
   return 0 ;
}

TAG4INFO *S4FUNCTION i4tagInfo( INDEX4 *index )
{
   #ifdef E4PARM_LOW
      if ( index == 0 )
      {
         error4( 0, e4parm_null, E95501 ) ;
         return 0 ;
      }
   #endif

   error4( index->codeBase, e4notIndex, E95501 ) ;
   return 0 ;
}
#endif /* S4OFF_INDEX */

#ifdef S4OFF_INDEX_ON_CB51
#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION d4seekNext( DATA4 *d4, const char *str )
{
   #ifdef S4VBASIC
      if ( c4parm_check( d4, 2, E92908 ) )
         return 0 ;
   #endif

   #ifdef E4PARM_HIGH
      if ( d4 == 0 )
         return error4( 0, e4parm_null, E92908 ) ;
   #endif

   #ifdef S4CB51
      return error4( d4->codeBase, e4notSupported, E92908 ) ;
   #else
      return error4( d4->codeBase, e4notIndex, E92908 ) ;
   #endif
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION d4seekNextDouble( DATA4 *data, const double dkey )
{
   #ifdef S4VBASIC
      if ( c4parm_check( data, 2, E92909 ) )
         return 0 ;
   #endif

   #ifdef E4PARM_HIGH
      if ( data == 0 )
         return error4( 0, e4parm_null, E92909 ) ;
   #endif

   #ifdef S4CB51
      return error4( data->codeBase, e4notSupported, E92909 ) ;
   #else
      return error4( data->codeBase, e4notIndex, E92909 ) ;
   #endif
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION d4seekNextN( DATA4 S4PTR *d4, const char *str, const short len )
{
   #ifdef S4VBASIC
      if ( c4parm_check( d4, 2, E92905 ) )
         return 0 ;
   #endif

   #ifdef E4PARM_HIGH
      if ( d4 == 0 )
         return error4( 0, e4parm_null, E92905 ) ;
   #endif

   #ifdef S4CB51
      return error4( d4->codeBase, e4notSupported, E92905 ) ;
   #else
      return error4( d4->codeBase, e4notIndex, E92905 ) ;
   #endif
}
#endif  /* S4OFF_INDEX_ON_CB51 */

#ifndef S4TESTING
#ifdef P4ARGS_USED
   #pragma argsused
#endif
void S4FUNCTION u4writeErr( const char *errStr, int val )
{
   error4( 0, e4notSupported, E94511 ) ;
}
#endif

#ifdef S4OFF_MEMO_S4MDX
#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION f4memoCheck( void *f4memo, void *data )
{
   return error4( 0, e4notSupported, E95206 ) ;
}
#endif

#ifndef E4FILE_LINE
   int  S4FUNCTION code4lineNo( void )
   {
      return 0 ;
   }
   const char *S4FUNCTION code4fileName( void )
   {
      return 0 ;
   }

#ifdef P4ARGS_USED
   #pragma argsused
#endif
   void S4FUNCTION code4lineNoSet( int val )
   {
      return ;
   }

#ifdef P4ARGS_USED
   #pragma argsused
#endif
   void S4FUNCTION code4fileNameSet( const char *ptr )
   {
      return ;
   }
#endif  /* E4FILE_LINE */

#ifndef E4LINK
#ifdef P4ARGS_USED
   #pragma argsused
#endif
void *S4FUNCTION l4firstLow( const LIST4 *list )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
void *S4FUNCTION l4lastLow( const LIST4 *list )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
void *S4FUNCTION l4nextLow( const LIST4 *list, const void *link )
{
   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
void S4FUNCTION l4addLow( LIST4 *list, void *item )
{
   return ;
}
#endif /* E4LINK */

#ifndef S4WRITE_DELAY
#ifdef P4ARGS_USED
   #pragma argsused
#endif
int S4FUNCTION file4seqWriteDelay( FILE4SEQ_WRITE *seqWrite )
{
   return error4( 0, e4notSupported, E90704 ) ;
}

#endif

#endif /* S4SERVER */

#ifdef S4DLL_DEF
   #undef S4DLL_DEF
#endif

#ifdef S4OFF_INDEX_ON_MDX
   #undef S4OFF_INDEX_OR_NOT_MDX
#endif

#ifdef ON_N4OTHER_OFF_WRITE_INDEX
   #undef ON_N4OTHER_OFF_WRITE_INDEX
#endif

#ifdef S4OFF_INDEX_ON_MDX_FOX
   #undef S4OFF_INDEX_ON_MDX_FOX
#endif

#ifdef S4OFF_INDEX_WRITE_ON_MDX_FOX
   #undef S4OFF_INDEX_WRITE_ON_MDX_FOX
#endif

#ifdef S4OFF_WRITE_MEMO
   #undef S4OFF_WRITE_MEMO
#endif

#ifdef S4OFF_WRITE_INDEX
   #undef S4OFF_WRITE_INDEX
#endif

#ifdef S4OFF_MEMO_S4MDX
   #undef S4OFF_MEMO_S4MDX
#endif

#ifdef S4OFF_STAND_OPT
   #undef S4OFF_STAND_OPT
#endif

#ifdef ON_CLIENT_OFF_TRAN
   #undef ON_CLIENT_OFF_TRAN
#endif

#ifdef S4OFF_STAND_WRITE_TRAN
   #undef S4OFF_STAND_WRITE_TRAN
#endif

#ifdef S4OFF_WRITE_TRAN
   #undef S4OFF_STAND_WRITE_TRAN
#endif

#ifdef S4OFF_N4OTHER_INDEX
   #undef S4OFF_N4OTHER_INDEX
#endif

#ifdef S4OFF_N4OTHER_INDEX_WRITE
   #undef S4OFF_N4OTHER_INDEX_WRITE
#endif

#ifdef S4OFF_INDEX_ON_CB51
   #undef S4OFF_INDEX_ON_CB51
#endif

#ifdef S4OFF_WRITE_REPORT
   #undef S4OFF_WRITE_REPORT
#endif

#ifdef S4OFF_CLIENT_OR_FOX_OR_WRITE
   #undef S4OFF_CLIENT_OR_FOX_OR_WRITE
#endif

#ifdef S4OFF_INDEX_WRITE_OR_CLIENT
   #undef S4OFF_INDEX_WRITE_OR_CLIENT
#endif
