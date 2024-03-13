/* r4reindx.c   (c)Copyright Sequiter Software Inc., 1988-1998.  All rights reserved. */

#include "d4all.h"

#ifndef S4OFF_WRITE
#ifndef S4INDEX_OFF
#ifdef S4CLIPPER

#ifndef S4UNIX
   #ifdef __TURBOC__
      #pragma hdrstop
   #endif  /* __TURBOC__ */
#endif  /* S4UNIX */

#include "r4reinde.h"

#ifdef P4ARGS_USED
   #pragma argsused
#endif
B4KEY_DATA   *r4key( R4BLOCK_DATA *r4, int i, int keylen)
{
   return (B4KEY_DATA *)( (char *)&r4->nKeys + r4->blockIndex[i] ) ;
}

int S4FUNCTION i4reindex( INDEX4 *i4 )
{
   int rc ;
   TAG4 *tagOn ;
   DATA4 *data ;
   #ifndef S4OPTIMIZE_OFF
      #ifdef S4LOW_MEMORY
         int hasOpt ;
      #endif
   #endif

   #ifdef S4VBASIC
      if ( c4parm_check( i4, 0, E92101 ) )
         return -1 ;
   #endif

   #ifdef E4PARM_HIGH
      if ( i4 == 0  )
         return error4( 0, e4parm_null, E92101 ) ;
   #endif

   if ( error4code( i4->codeBase ) < 0 )
      return -1 ;

   data = i4->data ;

   #ifndef S4OPTIMIZE_OFF
      #ifdef S4LOW_MEMORY
         hasOpt = i4->codeBase->hasOpt && i4->codeBase->opt.numBuffers ;
         if ( hasOpt )
            code4optSuspend( i4->codeBase ) ;
      #endif
   #endif

   #ifndef S4SINGLE
      rc = d4lockAll( data ) ;
      if ( rc )
         return rc ;
   #endif

   #ifndef S4OFF_TRAN
      /* reindex is allowed, but need to fix-up any unique settings */
      i4deleteRemoveKeys( i4 ) ;
   #endif

   for( tagOn = 0 ;; )
   {
      tagOn = (TAG4 *)l4next( &i4->tags, tagOn ) ;
      if ( tagOn == 0 )
         break ;

      rc = expr4context( tagOn->tagFile->expr, data ) ;
      if ( rc < 0 )
         return rc ;
      if ( tagOn->tagFile->filter != 0 )
      {
         rc = expr4context( tagOn->tagFile->filter, data ) ;
         if ( rc < 0 )
            return rc ;
      }

      rc = t4reindex( tagOn ) ;
      if ( rc )
         return rc ;
   }
   #ifndef S4OPTIMIZE_OFF
      #ifdef S4LOW_MEMORY
         if ( hasOpt )
            code4optRestart( i4->codeBase ) ;
      #endif
   #endif
   data->recNum = -1 ;
   data->recNumOld = -1 ;
   d4blankLow( data, data->record ) ;
   return 0 ;
}

int t4reindex( TAG4 *t4 )
{
   R4REINDEX reindex ;
   INDEX4 *i4 ;
   int rc ;
   #ifndef S4OPTIMIZE_OFF
      #ifdef S4LOW_MEMORY
         int hasOpt ;
      #endif
   #endif
   B4KEY_DATA *bdata ;
   int i ;

   if ( error4code( t4->tagFile->codeBase ) < 0 )
      return -1 ;

   i4 = t4->index ;

   #ifndef S4OPTIMIZE_OFF
      #ifdef S4LOW_MEMORY
         hasOpt = i4->codeBase->hasOpt && i4->codeBase->opt.numBuffers ;
         if ( hasOpt )
            code4optSuspend( i4->codeBase ) ;
      #endif
   #endif

   #ifndef S4SINGLE
      {
         rc = d4lockIndex( i4->data ) ;
         if ( rc )
            return rc  ;
      }
   #endif

   if ( r4reindexInit( &reindex, t4 ) < 0 )
      return -1 ;
   if ( r4reindexTagHeadersCalc( &reindex, t4->tagFile ) < 0 )
      return -1 ;
   if ( r4reindexBlocksAlloc( &reindex ) < 0 )
      return -1 ;

   reindex.nBlocksUsed = 0 ;

   rc = r4reindexSupplyKeys( &reindex, t4->tagFile ) ;
   if ( rc < 0 )
   {
      r4reindexFree( &reindex ) ;
      return rc ;
   }

   rc = r4reindexWriteKeys( &reindex, t4->tagFile, t4unique( t4 ) ) ;
   if ( rc )
   {
      r4reindexFree( &reindex ) ;
      return rc ;
   }

   rc = r4reindexTagHeadersWrite( &reindex, t4->tagFile ) ;

   if ( rc )
      return rc ;

   #ifdef E4MISC
      t4->tagFile->checkEof = file4longGetLo( file4lenLow( &t4->tagFile->file ) ) - B4BLOCK_SIZE ;  /* reset verify eof variable */
   #endif

   t4->index->codeBase->doIndexVerify = 0 ;  /* avoid verify errors due to our partial removal */
   tfile4bottom( t4->tagFile ) ;
   tfile4balance( t4->tagFile, tfile4block( t4->tagFile ), 1 ) ;
   t4->index->codeBase->doIndexVerify = 1 ;

   if ( reindex.stranded )   /* add stranded entry */
      tfile4add( t4->tagFile, (unsigned char *)reindex.stranded->value, reindex.stranded->num, t4unique( t4 ) ) ;

   /* and also add any extra block members */
   if ( reindex.startBlock->nKeys < t4->tagFile->header.keysHalf && reindex.nBlocksUsed > 1 )
   {
      for ( i = 0 ; i < reindex.startBlock->nKeys ; i++ )
      {
         bdata = r4key( reindex.startBlock, i, t4->tagFile->header.keyLen ) ;
         tfile4add( t4->tagFile, (unsigned char *)bdata->value, bdata->num, t4unique( t4 ) ) ;
      }
   }

   tfile4update( t4->tagFile ) ;

   r4reindexFree( &reindex ) ;
   #ifndef S4OPTIMIZE_OFF
      #ifdef S4LOW_MEMORY
         if ( hasOpt )
            code4optRestart( i4->codeBase ) ;
      #endif
   #endif
   return rc ;
}

int r4reindexInit( R4REINDEX *r4, TAG4 *t4 )
{
   INDEX4 *i4 ;

   i4 = t4->index ;

   memset( r4, 0, sizeof( R4REINDEX ) ) ;

   r4->data = t4->index->data ;
   r4->codeBase = t4->tagFile->codeBase ;

   r4->minKeysmax = INT_MAX ;
   r4->startBlock = 0 ;
   r4->sort.file.hand = INVALID4HANDLE ;

   r4->bufferLen = i4->codeBase->memSizeSortBuffer ;
   if ( r4->bufferLen < 1024 )
      r4->bufferLen = 1024 ;

   r4->buffer = (char *)u4allocEr( r4->codeBase, r4->bufferLen ) ;
   if ( r4->buffer == 0 )
      return e4memory ;

   r4->tag = t4->tagFile ;

   return 0 ;
}

void r4reindexFree( R4REINDEX *r4 )
{
   u4free( r4->buffer ) ;
   u4free( r4->startBlock ) ;
   sort4free( &r4->sort ) ;
}

int r4reindexBlocksAlloc( R4REINDEX *r4 )
{
   long onCount ;
   long numSub ;

   #ifdef E4ANALYZE
      if ( (unsigned) r4->minKeysmax > INT_MAX )
         return error4( 0, e4struct, E92102 ) ;
   #endif

   /* Calculate the block stack height */
   onCount = d4recCount( r4->data ) ;

   #ifdef E4MISC
      if ( onCount < 0 )
         return error4( r4->codeBase, (short int)onCount, E92102 ) ;
   #endif

   numSub = r4->minKeysmax ;
   for ( r4->nBlocks = 0 ; onCount > 0L ; r4->nBlocks++ )
   {
      onCount -= numSub ;
      numSub *= r4->minKeysmax ;
   }
   r4->nBlocks ++ ;
   if( r4->nBlocks < 2 )
      r4->nBlocks = 2 ;
   r4->startBlock = (R4BLOCK_DATA *) u4alloc( (long) ( B4BLOCK_SIZE + 2 * sizeof( void *) ) * r4->nBlocks ) ;

   if ( r4->startBlock == 0 )
      return error4( r4->codeBase, e4memory, E82105 ) ;

   return 0 ;
}

int r4reindexSupplyKeys( R4REINDEX *r4, TAG4FILE *t4 )
{
   FILE4SEQ_READ seqRead ;
   EXPR4 *filter ;
   char *keyResult ;
   int rc, *filterResult ;
   long count, iRec ;
   DATA4 *d4 ;
   DATA4FILE *d4file ;
   #ifndef S4MEMO_OFF
      int i ;
   #endif

   d4 = r4->data ;
   d4file = d4->dataFile ;
   #ifdef E4MISC
      r4->keyCount = 0L ;
   #endif

   if ( sort4init( &r4->sort, r4->codeBase, t4->header.keyLen, 0 ) < 0 )
      return -1 ;
   r4->sort.cmp = t4->cmp ;

   rc = expr4context( r4->tag->expr, d4 ) ;
   if ( rc < 0 )
      return rc ;
   if ( r4->tag->filter != 0 )
   {
      rc = expr4context( r4->tag->filter, d4 ) ;
      if ( rc < 0 )
         return rc ;
   }

   filter = t4->filter ;
   count = dfile4recCount( d4file, -2L ) ;
   if ( count < 0 )
      return error4stack( r4->codeBase, (short)rc, E92102 ) ;

   file4seqReadInitDo( &seqRead, &d4file->file, dfile4recordPosition( d4file, 1L ), r4->buffer, r4->bufferLen, 1 ) ;

   for ( iRec = 1L; iRec <= count; iRec++ )
   {
      if ( file4seqReadAll( &seqRead, d4->record, dfile4recWidth( d4file ) ) < 0 )
         return -1 ;
      d4->recNum = iRec ;

      #ifndef S4MEMO_OFF
         for ( i = 0; i < d4file->nFieldsMemo; i++ )
            f4memoReset( d4->fieldsMemo[i].field ) ;
      #endif

      if ( filter )
      {
         rc = expr4vary( filter, (char **)&filterResult ) ;
         if ( rc < 0 )
         {
            #ifdef S4ADVANCE_READ
               file4seqReadInitUndo( &seqRead ) ;
            #endif
            return error4stack( r4->codeBase, (short)rc, E92102 ) ;
         }
         #ifdef E4MISC
            if ( expr4type( filter ) != r4log )
            {
               #ifdef S4ADVANCE_READ
                  file4seqReadInitUndo( &seqRead ) ;
               #endif
               return error4( r4->codeBase, e4result, E92102 ) ;
            }
         #endif  /* E4MISC */
         if ( ! *filterResult )
            continue ;
         t4->hasKeys = 1 ;
         #ifdef S4MDX
            t4->hadKeys = 0 ;
         #endif
      }

      tfile4exprKey( t4, (unsigned char **)&keyResult ) ;

      if ( sort4put( &r4->sort, iRec, keyResult, "" ) < 0)
      {
         #ifdef S4ADVANCE_READ
            file4seqReadInitUndo( &seqRead ) ;
         #endif
         return -1 ;
      }
      #ifdef E4MISC
         r4->keyCount++ ;
      #endif
   }

   #ifdef S4ADVANCE_READ
      file4seqReadInitUndo( &seqRead ) ;
   #endif

   return 0 ;
}

int  r4reindexTagHeadersCalc( R4REINDEX *r4, TAG4FILE *t4 )
{
   int exprType ;

   if ( tfile4freeAll( t4 ) < 0 )
      return -1 ;

   t4->header.keyLen = t4->expr->keyLen = expr4keyLen( t4->expr ) ;
   t4->expr->keyDec = t4->header.keyDec ;
   if( t4->header.keyLen < 0 )
      return -1 ;


   exprType = expr4type( t4->expr ) ;
   if ( exprType < 0 )
      return exprType ;
   tfile4initSeekConv( t4, exprType ) ;
   t4->header.groupLen = t4->header.keyLen+8 ;
   r4->keysHalf = t4->header.keysHalf = (1020/ (t4->header.groupLen+2) - 1)/ 2;
   t4->header.sign   = 6 ;
   t4->header.keysMax = t4->header.keysHalf * 2 ;
   if ( t4->header.keysMax < 2 )
      return error4( t4->codeBase, e4info, E81601 ) ;

   if ( t4->header.keysMax < r4->minKeysmax )
      r4->minKeysmax = t4->header.keysMax ;

   r4->lastblockInc = B4BLOCK_SIZE / 512 ;
   r4->lastblock = 0 ;

   return 0 ;
}

int r4reindexTagHeadersWrite( R4REINDEX *r4, TAG4FILE *t4 )
{
   int len ;
   const char *ptr ;
   FILE4LONG pos ;
   #ifdef S4BYTE_SWAP
      I4IND_HEAD_WRITE *swap ;
   #endif

   /* Now write the headers */
   file4longAssign( pos, 0, 0 ) ;
   file4seqWriteInitLow( &r4->seqwrite, &t4->file, pos, r4->buffer, r4->bufferLen ) ;

   t4->header.eof = 0 ;

   #ifdef S4BYTE_SWAP
      /* swap = (I4IND_HEAD_WRITE *) t4->codeBase, u4allocEr( sizeof(I4IND_HEAD_WRITE ) ) ;*/
      swap = (I4IND_HEAD_WRITE *)u4allocEr( t4->codeBase, sizeof(I4IND_HEAD_WRITE ) ) ;
      if ( swap == 0 )
         return -1 ;
      swap->sign = x4reverseShort( (void *)&t4->header.sign ) ;
      swap->version = x4reverseShort( (void *)&t4->header.version ) ;
      swap->root = x4reverseLong( (void *)&t4->header.root ) ;
      swap->eof = x4reverseLong( (void *)&t4->header.eof ) ;
      swap->groupLen = x4reverseShort( (void *)&t4->header.groupLen ) ;
      swap->keyLen = x4reverseShort( (void *)&t4->header.keyLen ) ;
      swap->keyDec = x4reverseShort( (void *)&t4->header.keyDec ) ;
      swap->keysMax = x4reverseShort( (void *)&t4->header.keysMax ) ;
      swap->keysHalf = x4reverseShort( (void *)&t4->header.keysHalf ) ;

      #ifdef S4STRUCT_PAD
         file4seqWrite( &r4->seqwrite, swap, sizeof(I4IND_HEAD_WRITE) - 2 ) ;
      #else
         file4seqWrite( &r4->seqwrite, swap, sizeof(I4IND_HEAD_WRITE) ) ;
      #endif
      u4free( swap ) ;
   #else
      #ifdef S4STRUCT_PAD
         file4seqWrite( &r4->seqwrite, &t4->header.sign, sizeof(I4IND_HEAD_WRITE) - 2 ) ;
      #else
         file4seqWrite( &r4->seqwrite, &t4->header.sign, sizeof(I4IND_HEAD_WRITE) ) ;
      #endif
   #endif

   ptr = t4->expr->source ;
   len = strlen(ptr) ;
   if ( len > I4MAX_EXPR_SIZE )
      return error4( r4->codeBase, e4index, E82106 ) ;

   file4seqWrite( &r4->seqwrite, ptr, len) ;
   file4seqWriteRepeat( &r4->seqwrite, I4MAX_EXPR_SIZE - len + 1, 0 ) ;
   #ifdef S4BYTE_SWAP
      t4->header.unique = x4reverseLong( (void *)&t4->header.unique ) ;
      file4seqWrite( &r4->seqwrite, &t4->header.unique, sizeof( t4->header.unique ) ) ;
      t4->header.unique = x4reverseLong( (void *)&t4->header.unique ) ;
   #else
      file4seqWrite( &r4->seqwrite, &t4->header.unique, sizeof( t4->header.unique ) ) ;
   #endif

   file4seqWriteRepeat( &r4->seqwrite, 1, (char)0 ) ;

   #ifdef S4BYTE_SWAP
      t4->header.descending = x4reverseLong( (void *)&t4->header.descending ) ;
      file4seqWrite( &r4->seqwrite, &t4->header.descending, sizeof( t4->header.descending ) ) ;
      t4->header.descending = x4reverseLong( (void *)&t4->header.descending ) ;
   #else
      file4seqWrite( &r4->seqwrite, &t4->header.descending, sizeof( t4->header.descending ) ) ;
   #endif

   if ( t4->filter != 0 )
   {
      ptr = t4->filter->source ;
      len = strlen(ptr) ;

      file4seqWrite( &r4->seqwrite, ptr, len ) ;
      file4seqWriteRepeat( &r4->seqwrite, I4MAX_EXPR_SIZE - len + 1, 0 ) ;
   }
   else
      file4seqWriteRepeat( &r4->seqwrite, I4MAX_EXPR_SIZE + 1, 0 ) ;

   #ifdef E4ANALYZE
      if ( B4BLOCK_SIZE - (r4->seqwrite.working - r4->seqwrite.avail ) < 0 )
         return error4( r4->codeBase, e4index, E82103 ) ;
   #endif
   file4seqWriteRepeat( &r4->seqwrite, B4BLOCK_SIZE - (r4->seqwrite.working - r4->seqwrite.avail) , 0 ) ;

   if ( file4seqWriteFlush(&r4->seqwrite) < 0 )
      return -1 ;

   file4longAssign( pos, (r4->lastblock + r4->lastblockInc) * 512, 0 ) ;
   file4lenSetLow( &t4->file, pos ) ;
   return 0 ;
}

int r4reindexWriteKeys( R4REINDEX *r4, TAG4FILE *t4, short int errUnique )
{
   char  lastKey[I4MAX_KEY_SIZE] ;
   unsigned char *keyData ;
   int   isUnique, rc, isFirst ;
   void *dummyPtr ;
   long  keyRec ;
   FILE4LONG pos ;

   r4->grouplen = t4->header.groupLen ;
   r4->valuelen = t4->header.keyLen ;
   r4->keysmax  = t4->header.keysMax ;

   memset( r4->startBlock, 0, (int)(( (long)B4BLOCK_SIZE + 2 * sizeof( void *) ) * r4->nBlocks) ) ;

   if ( sort4getInit( &r4->sort ) < 0 )
      return -1 ;

   file4longAssign( pos, ( r4->lastblock + r4->lastblockInc ) * 512, 0 ) ;
   file4seqWriteInitLow( &r4->seqwrite, &t4->file, pos, r4->buffer, r4->bufferLen ) ;

   #ifdef E4MISC
      if ( I4MAX_KEY_SIZE < r4->sort.sortLen )
         return error4( r4->codeBase, e4info, E82102 ) ;
   #endif

   memset( lastKey, 0, sizeof(lastKey) ) ;
   isUnique = t4->header.unique ;

   isFirst = 1 ;

   for(;;)  /* For each key to write */
   {
      if ( (rc = sort4get( &r4->sort, &keyRec, (void **) &keyData, &dummyPtr)) < 0)
         return -1 ;

      #ifdef E4MISC
         if ( r4->keyCount < 0L  ||  r4->keyCount == 0L && rc != r4done ||  r4->keyCount > 0L && rc == r4done )
            return error4( r4->codeBase, e4info, E92102 ) ;
         r4->keyCount-- ;
      #endif

      if ( rc == r4done )  /* No more keys */
      {
         if ( r4reindexFinish( r4 ) < 0 )
            return -1 ;
         if ( file4seqWriteFlush( &r4->seqwrite ) < 0 )
            return -1 ;
         break ;
      }

      if ( isUnique )
      {
         if( isFirst )
            isFirst = 0 ;
         else
            if ( (*t4->cmp)( keyData, lastKey, r4->sort.sortLen) == 0 )
            {
               switch( errUnique )
               {
                  case e4unique:
                     return error4describe( r4->codeBase, e4unique, E82103, t4->alias, (char *)0, 0 ) ;

                  case r4unique:
                     return r4unique ;

                  default:
                     continue ;
               }
            }

         memcpy( lastKey, keyData, r4->sort.sortLen ) ;
      }

      /* Add the key */
      if ( r4reindexAdd( r4, keyRec, keyData) < 0 )
         return -1 ;
   }

   /* Now complete the tag header info. */
   t4->header.root = r4->lastblock * 512 ;

   return 0 ;
}

static int r4reindexToDisk( R4REINDEX *r4, long rec, const char *keyValue )
{
   R4BLOCK_DATA *block ;
   int tnUsed, iBlock, i ;
   B4KEY_DATA *keyTo ;
   short offset ;
   #ifdef E4MISC
      long dif ;
      B4KEY_DATA *keyOn ;
   #endif
   #ifdef S4BYTE_SWAP
      char *swap, *swapPtr ;
      int j ;
      long longVal ;
      short shortVal ;
   #endif

   tnUsed = 1 ;

   /* Writes out the current block and adds references to higher blocks */
   block  = r4->startBlock ;
   iBlock= 0 ;

   #ifdef E4MISC
      keyOn = r4key( block, block->nKeys, r4->grouplen ) ;
      dif = (char *) keyOn -  (char *) &block->nKeys ;
      if ( dif+ r4->grouplen > B4BLOCK_SIZE || dif < 0 )
         return error4( r4->codeBase, e4result, E92102 ) ;
   #endif

   for(;;)
   {
      tnUsed++ ;
      #ifdef S4BYTE_SWAP
         swap = (char *)u4allocEr( r4->codeBase, B4BLOCK_SIZE ) ;
         if ( swap == 0 )
            return -1 ;

         memcpy( (void *)swap, (void *)&block->nKeys, B4BLOCK_SIZE ) ;

         index4swapBlockClipper( swap, r4->keysmax, r4->grouplen) ;

         if ( file4seqWrite( &r4->seqwrite, swap, B4BLOCK_SIZE) < 0 )
            return -1 ;
         u4free( swap ) ;
      #else
         if ( file4seqWrite( &r4->seqwrite, &block->nKeys, B4BLOCK_SIZE) < 0 )
            return -1 ;
      #endif
      if ( iBlock )
         memset( block, 0, B4BLOCK_SIZE ) ;
      r4->lastblock += r4->lastblockInc ;

      block = (R4BLOCK_DATA *) ((char *)block + B4BLOCK_SIZE + 2*sizeof(void *) ) ;
      iBlock++ ;
      #ifdef E4MISC
         if ( iBlock >= r4->nBlocks )
            return error4( r4->codeBase, e4info, E92102 ) ;
      #endif

      if ( block->nKeys == 0 )   /* set up the branch block... */
      {
         offset = ( r4->keysmax + 2 + ( ( r4->keysmax / 2 ) * 2 != r4->keysmax ) ) * sizeof(short) ;
         block->blockIndex = &block->nKeys + 1 ;
         for ( i = 0 ; i <= r4->keysmax ; i++ )
            block->blockIndex[i] = r4->grouplen * i + offset ;
         block->data = (char *) &block->nKeys + block->blockIndex[ 0 ] ;
      }

      keyTo = r4key( block, block->nKeys, r4->grouplen ) ;
      #ifdef E4MISC
         dif = (char *) keyTo -  (char *) block  ;
         if ( dif+sizeof(long) > B4BLOCK_SIZE || dif < 0 )
            return error4( r4->codeBase, e4result, E92102 ) ;
      #endif
      keyTo->pointer = r4->lastblock * 512 ;

      if ( block->nKeys < r4->keysmax )
      {
         if ( tnUsed > r4->nBlocksUsed )
            r4->nBlocksUsed = tnUsed ;
         #ifdef E4MISC
            if ( dif+r4->grouplen > B4BLOCK_SIZE )
               return error4( r4->codeBase, e4result, E92102 ) ;
         #endif
         keyTo->num = rec ;
         memcpy( keyTo->value, keyValue, r4->valuelen ) ;
         block->nKeys++ ;
         return 0 ;
      }
      #ifdef E4MISC
         if ( block->nKeys > r4->keysmax )
             return error4( r4->codeBase, e4info, E82104 ) ;
      #endif
   }
}

int r4reindexAdd( R4REINDEX *r4, const long rec, const unsigned char *keyValue )
{
   B4KEY_DATA *keyTo ;
   R4BLOCK_DATA *startBlock ;
   #ifdef E4MISC
      long  dif ;
   #endif
   short offset ;
   int i ;

   startBlock = r4->startBlock ;

   /* for NTX, if keysmax, then todisk() with the latest value... */

   if ( startBlock->nKeys == 0 )   /* first, so add references */
   {
      offset = ( r4->keysmax + 2 + ( ( r4->keysmax / 2 ) * 2 != r4->keysmax ) ) * sizeof(short) ;
      startBlock->blockIndex = &startBlock->nKeys + 1 ;  /* 1 short off of nKeys */
      for ( i = 0 ; i <= r4->keysmax ; i++ )
          startBlock->blockIndex[i] = r4->grouplen * i + offset ;
      startBlock->data = (char *)&startBlock->nKeys + startBlock->blockIndex[0] ;  /* first entry */
   }
   if ( startBlock->nKeys >= r4->keysmax )
   {
      if ( r4reindexToDisk( r4, rec, (const char*)keyValue ) < 0 )
         return -1 ;
      memset( startBlock, 0, B4BLOCK_SIZE + 2 * sizeof( void *) ) ;
      return 0 ;
   }

   keyTo = r4key( startBlock, startBlock->nKeys++, r4->grouplen ) ;

   #ifdef E4MISC
      dif = (char *)keyTo -  (char *)startBlock ;
      if ( dif + r4->grouplen > B4BLOCK_SIZE || dif < 0 )
         return error4( r4->codeBase, e4result, E92102 ) ;
   #endif
   keyTo->num = rec ;
   memcpy( keyTo->value, keyValue, r4->valuelen ) ;

   return 0 ;
}

int r4reindexFinish( R4REINDEX *r4 )
{
   B4KEY_DATA *keyTo ;
   #ifdef E4MISC
      long dif ;
   #endif
   int iBlock = 0, tBlock ;

   #ifdef S4BYTE_SWAP
      char *swap, *swapPtr ;
      int j ;
      long longVal ;
      short shortVal ;
   #endif

   R4BLOCK_DATA *block = r4->startBlock, *temp_block ;

   short offset ;
   int i ;
   long pointer ;

   if ( r4->nBlocksUsed <= 1 )  /* empty database if nKeys = 0 */
   {
      if ( r4->startBlock->nKeys == 0 )   /* first, so add references */
      {
         offset = ( r4->keysmax + 2 + ( (r4->keysmax/2)*2 != r4->keysmax ) ) * sizeof(short) ;
         r4->startBlock->blockIndex = &r4->startBlock->nKeys + 1 ;  /* 1 short off of nKeys */
         for ( i = 0 ; i <= r4->keysmax ; i++ )
             r4->startBlock->blockIndex[i] = r4->grouplen * i + offset ;
         r4->startBlock->data = (char *) &r4->startBlock->nKeys + r4->startBlock->blockIndex[0] ;
      }
      iBlock ++ ;
      r4->stranded = 0 ;
      pointer = 0 ;

      #ifdef S4BYTE_SWAP
         swap = (char *)u4allocEr( r4->codeBase, B4BLOCK_SIZE ) ;
         if ( swap == 0 )
            return error4describe( r4->codeBase, e4memory, 0, 0, 0, 0 ) ;

         memcpy( (void *)swap, (void *)&r4->startBlock->nKeys, B4BLOCK_SIZE ) ;
                          /* position swapPtr at beginning of pointers */

         index4swapBlockClipper(swap, r4->keysmax, r4->grouplen) ;

         if ( file4seqWrite( &r4->seqwrite, swap, B4BLOCK_SIZE) < 0 )
            return -1 ;
         u4free( swap ) ;
      #else
         if ( file4seqWrite( &r4->seqwrite, &r4->startBlock->nKeys, B4BLOCK_SIZE) < 0 )
            return -1 ;
      #endif

      r4->lastblock += r4->lastblockInc ;
   }
   else if ( r4->startBlock->nKeys >= r4->keysHalf )
   {
      /* just grab the pointer for upward placement where belongs */
      r4->stranded = 0 ;

      #ifdef S4BYTE_SWAP
         swap = (char *) u4allocEr( r4->codeBase, B4BLOCK_SIZE ) ;
         if ( swap == 0 )
            return -1 ;

         memcpy( (void *)swap, (void *)&r4->startBlock->nKeys, B4BLOCK_SIZE ) ;

         index4swapBlockClipper(swap, r4->keysmax, r4->grouplen) ;

         if ( file4seqWrite( &r4->seqwrite, swap, B4BLOCK_SIZE) < 0 )
            return -1 ;
         u4free( swap ) ;
      #else
         if ( file4seqWrite( &r4->seqwrite, &r4->startBlock->nKeys, B4BLOCK_SIZE) < 0 )
            return -1 ;
      #endif

      r4->lastblock += r4->lastblockInc ;
      pointer = r4->lastblock*512 ;
      block = (R4BLOCK_DATA *) ((char *)block + B4BLOCK_SIZE + 2*sizeof(void *) ) ;
      iBlock++ ;
   }
   else       /* stranded entry, so add after */
   {
      /* if less than 1/2 entries, will re-add the required keys later... */
      block = (R4BLOCK_DATA *) ((char *)block + B4BLOCK_SIZE + 2*sizeof(void *) ) ;
      iBlock++ ;
      while( block->nKeys == 0 && iBlock < r4->nBlocksUsed )
      {
         block = (R4BLOCK_DATA *) ((char *)block + B4BLOCK_SIZE + 2*sizeof(void *) ) ;
         iBlock++ ;
      }

      r4->stranded = r4key( block, block->nKeys - 1, 0 ) ;
      block->nKeys -- ;
      if( block->nKeys > 0 )
      {
         #ifdef S4BYTE_SWAP
            swap = (char *)u4allocEr( r4->codeBase, B4BLOCK_SIZE ) ;
            if ( swap == 0 )
               return -1 ;

            memcpy( (void *)swap, (void *)&block->nKeys, B4BLOCK_SIZE ) ;

            index4swapBlockClipper(swap, r4->keysmax, r4->grouplen ) ;

            if ( file4seqWrite( &r4->seqwrite, swap, B4BLOCK_SIZE) < 0 )
               return -1 ;
            u4free( swap ) ;
         #else
            if ( file4seqWrite( &r4->seqwrite, &block->nKeys, B4BLOCK_SIZE) < 0 )
               return -1 ;
         #endif

         r4->lastblock += r4->lastblockInc ;
         pointer = 0 ;
      }
      else
         pointer = r4key( block, block->nKeys, 0 )->pointer ;
      block = (R4BLOCK_DATA *) ((char *)block + B4BLOCK_SIZE + 2*sizeof(void *) ) ;
      iBlock++ ;
   }

   /* now position to the last spot, and place the branch */
   if( iBlock < r4->nBlocksUsed )
   {
      if( block->nKeys <= r4->keysmax && pointer != 0 )
      {
         temp_block = block ;
         tBlock = iBlock ;
         while ( temp_block->nKeys == 0 && tBlock < r4->nBlocksUsed )
         {
            offset = ( r4->keysmax + 2 + ( ( r4->keysmax / 2 ) * 2 != r4->keysmax ) ) * sizeof(short) ;
            temp_block->blockIndex = &temp_block->nKeys + 1 ;  /* 1 short off of nKeys */
            for ( i = 0 ; i <= r4->keysmax ; i++ )
               temp_block->blockIndex[i] = r4->grouplen * i + offset ;
            temp_block->data = (char *)&temp_block->nKeys + temp_block->blockIndex[0] ;
            temp_block = (R4BLOCK_DATA *)((char *)temp_block + B4BLOCK_SIZE + 2 * sizeof(void *) ) ;
            tBlock++ ;
         }

         /* now place the pointer for data that goes rightward */
         keyTo = r4key( block, block->nKeys, 0 ) ;
         keyTo->pointer = pointer ;
         pointer = 0 ;

         #ifdef S4BYTE_SWAP
            swap = (char *) u4allocEr( r4->codeBase, B4BLOCK_SIZE ) ;
            if ( swap == 0 )
               return -1 ;

            memcpy( (void *)swap, (void *)&block->nKeys, B4BLOCK_SIZE ) ;

            index4swapBlockClipper(swap, r4->keysmax, r4->grouplen) ;

            if ( file4seqWrite( &r4->seqwrite, swap, B4BLOCK_SIZE) < 0 )
               return -1 ;
            u4free( swap ) ;
         #else
            if ( file4seqWrite( &r4->seqwrite, &block->nKeys, B4BLOCK_SIZE) < 0 ) return -1 ;
         #endif

         r4->lastblock += r4->lastblockInc ;
         block = (R4BLOCK_DATA *) ((char *)block + B4BLOCK_SIZE + 2*sizeof(void *) ) ;
         iBlock++ ;
      }
   }
   for(; iBlock < r4->nBlocksUsed; iBlock++ )
   {
      if ( block->nKeys == 0 )
      {
         offset = ( r4->keysmax + 2 + ( ( r4->keysmax / 2 ) * 2 != r4->keysmax ) ) * sizeof(short) ;
         block->blockIndex = &block->nKeys + 1 ;  /* 1 short off of nKeys */
         for ( i = 0 ; i <= r4->keysmax ; i++ )
            block->blockIndex[i] = r4->grouplen * i + offset ;
         block->data = (char *)&block->nKeys + block->blockIndex[0] ;
      }
      keyTo = r4key( block, block->nKeys, r4->grouplen ) ;
      #ifdef E4MISC
         dif = (char *)keyTo  -  (char *) block ;
         if ( dif + sizeof( long ) > B4BLOCK_SIZE  ||  dif < 0 )
            return error4( r4->codeBase, e4result, E92102 ) ;
      #endif
      keyTo->pointer = r4->lastblock * 512 ;

      #ifdef S4BYTE_SWAP
         swap = (char *)u4allocEr( r4->codeBase, B4BLOCK_SIZE ) ;
         if ( swap == 0 )
            return -1 ;

         memcpy( (void *)swap, (void *)&block->nKeys, B4BLOCK_SIZE ) ;

         index4swapBlockClipper(swap, r4->keysmax, r4->grouplen) ;

         if ( file4seqWrite( &r4->seqwrite, swap, B4BLOCK_SIZE) < 0 )
            return -1 ;
         u4free( swap ) ;
      #else
         if ( file4seqWrite( &r4->seqwrite, &block->nKeys, B4BLOCK_SIZE) < 0)
            return -1;
      #endif

      r4->lastblock += r4->lastblockInc ;
      block = (R4BLOCK_DATA *)( (char *)block + B4BLOCK_SIZE + 2 * sizeof(void *) ) ;
   }

   return 0 ;
}

#endif  /* S4CLIPPER */
#endif  /* S4INDEX_OFF */
#endif  /* S4WRITE_OFF */
