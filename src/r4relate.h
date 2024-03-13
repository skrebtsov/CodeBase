/* r4relate.h   (c)Copyright Sequiter Software Inc., 1988-1998.  All rights reserved. */

#define relate4filterRecord 101
#define relate4doRemove 102
#define relate4skipped 104
#define relate4blank 105
#define relate4skipRec 106
#define relate4terminate 107
#define relate4exact 108
#define relate4scan 109
#define relate4approx 110
#define relate4sortSkip 120
#define relate4sortDone 121
#define relate4continue 200
/* backward compatibility redefinitions */
#define relate4skip_rec relate4skipRec

struct DATA4LISTSt ;
struct RELATE4St ;
struct RELATION4St ;

typedef struct
{
   struct DATA4LISTSt *relateDataList ;
   TAG4FILE S4PTR *tag ;  /* The tag whose expression could replace the sub-expression */
} E4INFO_REPORT ;

typedef struct
{
   EXPR4 S4PTR *expr ;
   E4INFO_REPORT S4PTR *infoReport ;  /* One per E4INFO entry */
   struct RELATION4St S4PTR *relation ;
   CODE4 S4PTR *codeBase ;
   char  S4PTR *buf ;
   unsigned bufPos, bufLen ;
} L4LOGICAL ;

typedef struct DATA4LISTSt
{
    struct RELATE4St S4PTR * S4PTR *pointers ;
    unsigned memAllocated ;
    int pointersTot ;
    int pointersUsed ;
} DATA4LIST ;

typedef struct RELATE4St
{
   LINK4 link ;

   S4CONV( short relationType, short relation_type ) ;  /* relate4exact, relate4scan, relate4approx */
   S4CONV( int sortType, int sort_type ) ;
   S4CONV( short errorAction, short error_action ) ;   /* relate4blank, relate4skipRec, relate4terminate */
   S4CONV( short matchLen, short match_len ) ;      /* Number of characters to match */

   unsigned short int id ;

   char S4PTR *scanValue ;      /* Allocated Memory */

   struct RELATE4St S4PTR *master ;
   struct RELATION4St S4PTR *relation ;

   S4CONV( CODE4 S4PTR *codeBase, CODE4 S4PTR *code_base ) ;
   S4CONV( EXPR4 S4PTR *masterExpr, EXPR4 S4PTR *master_expr ) ; /* master expression */
   S4CONV( TAG4 S4PTR *dataTag, TAG4 S4PTR *data_tag ) ;        /* Null means record # lookup */
   DATA4 S4PTR *data ;   /* This is the master for 'slaves' (if any) and */
                         /* possibly the slave for another data file. */

   LIST4 slaves ;
   LIST4 relateList ;  /* A list of scan Relate pointers; */

   #ifndef S4CLIENT
      int scanValueLen ;
      int isRead ;
      F4FLAG  set ;  /* Specify records for bitmap optimizable sub-expression. */
      #ifndef S4STAND_ALONE
         DATA4 S4PTR *dataOld ; /* the DATA4 that originally derived the relation */
         int freeData ;         /* did the relate create the data structure */
      #endif
   #endif

   #ifdef S4SERVER
      long dataId ;    /* used for client identification purposes (locking) */
   #else
      S4CONV( char S4PTR *oldRecord, char S4PTR *old_record ) ;
   #endif

   #ifdef S4WINDOWS
      HWND hWnd;
      S4CONV( int totalChildren, int total_children ) ;
   #endif
} RELATE4 ;

typedef struct
{
   LINK4 link ;
   RELATE4 S4PTR *ptr ;
} RELATE4LIST ;

typedef struct
{
   LINK4 link ;
   DATA4 S4PTR *data ;
   RELATE4 S4PTR *relate ;
} R4DATA_LIST ;

typedef struct RELATION4St
{
   LINK4 link ;     /* for server version, the list of relations */
   RELATE4 relate ;

   S4CONV( char S4PTR *exprSource, char S4PTR *expr_source ) ;

   char locked ;

   S4CONV( char S4PTR *sortSource, char S4PTR *sort_source ) ;
   char sortEofFlag ;
   BOOL4 bitmapDisable ;     /* used for testing purposes to test disabled bitmaps */

   #ifndef S4CLIENT
      char inSort ;       /* are we skipping for sorting purposes? */
      LIST4 sortDataList ;  /* data list for the sort */
      L4LOGICAL log ;
      char S4PTR *otherData, bitmapsFreed, sortDoneFlag ;
      SORT4 sort ;
      FILE4 sortedFile ;
      int  sortOtherLen ;
      long sortRecTo, sortRecOn, sortFilePos, sortRecCount ;
   #endif
   int isInitialized ;
   char skipBackwards ;   /* is backwards skipping enabled? */

   #ifdef S4CLIENT
      int needsFreeing ;
   #endif

   unsigned long relationId ;

   RELATE4 *currentRelateLevel ;   /* current pos for scans */
   #ifdef S4SERVER
      LIST4 localDataList ;
      unsigned short int relateIdCount ;
   #endif

/*   MEM4 S4PTR *relateMemory ;                  */
/*   MEM4 S4PTR *relateListMemory ;              */
/*   MEM4 S4PTR *relateDataListMemory ; */
} RELATION4 ;

#define BITMAP4LEAF 0x40
#define BITMAP4AND  0x20

typedef struct CONST4St
{
   LINK4  link ;
   int    offset ;
   int    len ;
} CONST4 ;

typedef struct BITMAP4St
{
   LINK4 link ;
   LINK4 eval ;

   /* flags */
   char  branch ;
   char  andOr ;    /* 1 = and, 2 = or, 0 means neither */
   char  evaluated ;
   char  finished;
   char  saveCount ;
   char  flipBase ;
   char  noMatch ;    /* no records match an and case */

   L4LOGICAL  S4PTR *log ;
   RELATE4    S4PTR *relate ;
   struct BITMAP4St S4PTR *base ;
   int type ;   /* r4num, etc. */

   /* Branch only */
   LIST4 children ;
   TAG4FILE S4PTR *tag ;

   CONST4 lt ;
   CONST4 le ;
   CONST4 gt ;
   CONST4 ge ;
   CONST4 eq ;
   LIST4 ne ;
} BITMAP4 ;

#ifdef __cplusplus
   extern "C" {
#endif

/* exported functions */
S4EXPORT int S4FUNCTION relate4bottom( RELATE4 S4PTR * ) ;
S4EXPORT int S4FUNCTION relate4changed( RELATE4 S4PTR * ) ;  /* Slave has been added or freed */
S4EXPORT RELATE4 S4PTR * S4FUNCTION relate4createSlave( RELATE4 S4PTR *, DATA4 S4PTR *, const char S4PTR *, TAG4 S4PTR * ) ;
S4EXPORT int S4FUNCTION relate4doAll( RELATE4 S4PTR * ) ;
S4EXPORT int S4FUNCTION relate4doOne( RELATE4 S4PTR * ) ;
S4EXPORT int S4FUNCTION relate4eof( RELATE4 S4PTR * ) ;
S4EXPORT int S4FUNCTION relate4errorAction( RELATE4 S4PTR *, const int ) ;  /* Set the error action */
S4EXPORT int S4FUNCTION relate4free( RELATE4 S4PTR *, const int ) ;
#ifdef S4SERVER
S4EXPORT RELATE4 S4PTR * S4FUNCTION relate4init( DATA4 S4PTR *, char S4PTR * ) ;
#else
S4EXPORT RELATE4 S4PTR * S4FUNCTION relate4init( DATA4 S4PTR * ) ;
#endif
S4EXPORT int S4FUNCTION relate4matchLen( RELATE4 S4PTR *, const int ) ;
S4EXPORT int S4FUNCTION relate4next( RELATE4 S4PTR * S4PTR * ) ;
S4EXPORT int S4FUNCTION relate4querySet( RELATE4 S4PTR *, const char S4PTR * ) ;
S4EXPORT int S4FUNCTION relate4skip( RELATE4 S4PTR *, const long ) ;        /* Extended record skip */
S4EXPORT int S4FUNCTION relate4skipEnable( RELATE4 S4PTR *, const int ) ;
S4EXPORT int S4FUNCTION relate4sortSet( RELATE4 S4PTR *, const char S4PTR * ) ;
S4EXPORT int S4FUNCTION relate4top( RELATE4 S4PTR * ) ;
S4EXPORT int S4FUNCTION relate4type( RELATE4 S4PTR *, int ) ;          /* Set the relate type */
/* used by codeReporter */
S4EXPORT int S4FUNCTION relate4freeRelate( RELATE4 S4PTR *, const int ) ;
S4EXPORT int   S4FUNCTION relate4lock( RELATE4 S4PTR * ) ;
S4EXPORT int   S4FUNCTION relate4unlock( RELATE4 S4PTR * ) ;
#ifndef S4CB51
   #define relate4data( r4 ) ( (r4)->data )
   #define relate4dataTag( r4 ) ( (r4)->dataTag )
   #define relate4master( r4 ) ( (r4)->master )
   #define relate4masterExpr( r4 ) ( ( (r4)->masterExpr == 0 ) ? ( 0 ) : ( (r4)->masterExpr->source ) )
#endif
#ifdef S4COMPILE_TEST
   #ifndef S4OFF_MULTI
      S4EXPORT int S4FUNCTION relate4lockAdd( RELATE4 S4PTR * ) ;
   #endif
#else
   S4EXPORT int S4FUNCTION relate4lockAdd( RELATE4 S4PTR * ) ;
#endif
S4EXPORT int S4FUNCTION relate4optimizeable( RELATE4 S4PTR * ) ;

/* internally used functions */
int bitmap4evaluate( L4LOGICAL *, const int ) ;
BITMAP4 * bitmap4redistribute( BITMAP4 *, BITMAP4 *, const char ) ;
BITMAP4 * bitmap4redistributeLeaf( BITMAP4 *, BITMAP4 *, BITMAP4 * ) ;
BITMAP4 * bitmap4redistributeBranch( BITMAP4 *, BITMAP4 * ) ;
BITMAP4 * bitmap4create( L4LOGICAL *, RELATE4 *, const char, const char ) ;
int  bitmap4destroy( BITMAP4 * ) ;
BITMAP4 * bitmap4combineLeafs( BITMAP4 *, BITMAP4 *, BITMAP4 * ) ;
long bitmap4seek( BITMAP4 *, const CONST4 *, const char, const long, const int ) ;
int  bitmap4copy( BITMAP4 *, const BITMAP4 * ) ;

void * const4return( L4LOGICAL *, const CONST4 * ) ;
int const4memAlloc( L4LOGICAL *, const unsigned ) ;
int const4duplicate( CONST4 *, const CONST4 *, L4LOGICAL * ) ;
int const4get( CONST4 *, BITMAP4 *, L4LOGICAL *, const int ) ;
int const4less( CONST4 *, CONST4 *, BITMAP4 * ) ;
int const4eq( CONST4 *, CONST4 *, BITMAP4 * ) ;
int const4lessEq( CONST4 *, CONST4 *, BITMAP4 * ) ;
void const4addNe( BITMAP4 *, CONST4 * ) ;
void const4deleteNe( LIST4 *, CONST4 * ) ;

int e4isConstant( E4INFO * ) ;
int e4isTag( E4INFO_REPORT *, EXPR4 *, E4INFO *, DATA4 * ) ;

int log4buildDatabaseLists( L4LOGICAL * ) ;
int log4true( L4LOGICAL * ) ;
int log4bitmapDo( L4LOGICAL * ) ; /* Do everything regarding bitmaps */
int log4determineEvaluationOrder( L4LOGICAL * ) ;

/* functions used to build the sort data list */
int r4dataListAdd( LIST4 *, DATA4 *, RELATE4 * ) ;
int r4dataListFind( LIST4 *, RELATE4 * ) ;
void r4dataListFree( LIST4 * ) ;
int r4dataListBuild( LIST4 *, RELATE4 *, EXPR4 *, int ) ;

void relate4freeBitmaps( RELATE4 * ) ;
RELATE4 *relate4lookupRelate( RELATE4 *, const DATA4 * ) ;
int relate4readIn( RELATE4 * ) ;   /* Read a record for this specific data file. */
#ifndef S4STAND_ALONE
   int relate4unpack( RELATION4 *, CONNECTION4 * ) ;
#endif

#ifdef S4CLIENT
   int relate4clientInit( RELATE4 * ) ;
#endif

#ifdef __cplusplus
   }
#endif
