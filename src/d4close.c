/* d4close.c   (c)Copyright Sequiter Software Inc., 1988-1998.  All rights reserved. */

#include "d4all.h"
#ifndef S4UNIX
   #ifdef __TURBOC__
      #pragma hdrstop
   #endif  /* __TUROBC__ */
#endif  /* S4UNIX */

#ifndef S4MEMO_OFF
   extern char f4memoNullChar ;
#endif  /* not S4MEMO_OFF */

#ifndef S4CLIENT
/* closes the given datafile if it's user count is zero */
int dfile4closeLow( DATA4FILE *data )
{
   int finalRc ;
   CODE4 *c4 ;
   #ifndef S4OFF_INDEX
      #ifdef N4OTHER
         TAG4FILE *t4 ;
      #else
         INDEX4FILE *i4 ;
      #endif
   #endif

   #ifdef E4PARM_LOW
      if ( data == 0 )
         return error4( 0, e4parm_null, E91102 ) ;
   #endif

   c4 = data->c4 ;

   if ( data->userCount > 0 )
      return 0 ;

   if ( data->info != 0 )
   {
      u4free( data->info ) ;
      data->info = 0 ;
   }

   finalRc = error4set( c4, 0 ) ;

   if ( file4openTest( &data->file ) )
   {
      if ( c4getDoRemove( c4 ) == 1 )
         data->file.isTemp = 1 ;

      #ifndef S4OFF_WRITE
         if ( data->fileChanged && data->file.isTemp != 1 && data->file.isReadOnly == 0 )
         {
            u4yymmdd( &data->yy ) ;
            #ifdef S4OFF_MULTI
               dfile4updateHeader( data, 1, 1 ) ;
            #else
               if ( data->file.lowAccessMode == OPEN4DENY_RW )
                  dfile4updateHeader( data, 1, 1 ) ;
               else /* only date stamp required */
                  dfile4updateHeader( data, 1, 0 ) ;
            #endif
         }
      #endif
   }

   #ifndef S4MEMO_OFF
      if ( file4openTest( &data->memoFile.file ) )
      {
         if ( c4getDoRemove( c4 ) == 1 )
            data->memoFile.file.isTemp = 1 ;
         if ( file4close( &data->memoFile.file ) < 0 )
            finalRc = error4set( c4, 0 ) ;
      }
   #endif

   #ifndef S4OFF_INDEX
      for ( ;; )
      {
         #ifdef N4OTHER
            t4 = (TAG4FILE *)l4first( &data->tagfiles ) ;
            if ( t4 == 0 )
               break ;
            tfile4close( t4, data ) ;
         #else
            i4 = (INDEX4FILE *)l4first( &data->indexes ) ;
            if ( i4 == 0 )
               break ;
            index4close( i4 ) ;
         #endif
      }
   #endif

   if ( data->link.n != 0 )
      l4remove( &c4->dataFileList, data ) ;

   if ( file4openTest( &data->file ) )
      if ( file4close( &data->file ) < 0 )
         finalRc = error4set( c4, 0 ) ;

   data->record = 0 ;

   mem4free( c4->data4fileMemory, data ) ;
   error4set( c4, (short)finalRc ) ;
   return finalRc ;
}

/* closes all datafiles for which the user count is zero */
int code4dataFileCloseAll( CODE4 *c4 )
{
   DATA4FILE *data ;
   int rc ;

   #ifdef E4PARM_LOW
      if ( c4 == 0 )
         return error4( 0, e4parm_null, E91304 ) ;
   #endif

   for( ;; )
   {
      for ( data = (DATA4FILE *)l4first( &c4->dataFileList ) ;; )
      {
         if ( data == 0 )
            break ;
         if ( data->userCount > 0 )
            data = (DATA4FILE *)l4next( &c4->dataFileList, data ) ;
         else
            break ;
      }
      if ( data == 0 )
         break ;
      rc = dfile4closeLow( data ) ;
      if ( rc < 0 )  /* need to return in order to avoid endless loop */
         return error4stack( c4, (short)rc, E91304 ) ;
   }

   return 0 ;
}
#endif

int dfile4close( DATA4FILE *data )
{
   #ifndef S4STAND_ALONE
      CODE4 *c4 ;
   #endif
   #ifdef S4CLIENT
      int finalRc, saveRc ;
      INDEX4FILE *i4 ;
      CONNECTION4 *connection ;
   #endif

   #ifdef E4PARM_LOW
      if ( data == 0 )
         return error4( 0, e4parm_null, E91102 ) ;
   #endif

   #ifdef E4ANALYZE
      if ( data->userCount <= 0 )
         return error4( 0, e4struct, E91102 ) ;
   #endif

   #ifndef S4STAND_ALONE
      c4 = data->c4 ;
   #endif

   #ifdef S4CLIENT
      saveRc = error4set( c4, 0 ) ;
      finalRc = 0 ;
   #endif

   data->userCount-- ;
   if ( data->userCount == 0 )
   {
      #ifdef S4CLIENT
         if ( data->info != 0 )
         {
            u4free( data->info ) ;
            data->info = 0 ;
         }

         connection = data->connection ;
         if ( connection == 0 )
            finalRc = e4connection ;
         else
         {
            connection4assign( connection, CON4CLOSE, 0, data->serverId ) ;
            connection4sendMessage( connection ) ;
            finalRc = connection4receiveMessage( connection ) ;
            if ( finalRc >= 0 )
               finalRc = connection4status( connection ) ;
         }
         #ifndef S4OFF_INDEX
            for ( ;; )
            {
               i4 = (INDEX4FILE *)l4first( &data->indexes ) ;
               if ( i4 == 0 )
                  break ;
               index4close( i4 ) ;
            }
         #endif

         l4remove( &c4->dataFileList, data ) ;
         mem4free( c4->data4fileMemory, data ) ;
         if ( saveRc != 0 )
         {
            error4set( c4, saveRc ) ;
            return saveRc ;
         }
         else
         {
            error4set( c4, finalRc ) ;
            return finalRc ;
         }
      #else
         #ifdef S4SERVER
            if ( c4->server->keepOpen == 0 || data->valid != 1 )    /* not a valid datafile (failure in dfile4open) so close */
               return dfile4closeLow( data ) ;
            if ( data->file.isTemp && c4->server->keepOpen != 2 )  /* cannot leave temp files open or they will never close */
               return dfile4closeLow( data ) ;
            data->singleClient = 0 ;
            time( &data->nullTime ) ;
         #else
            return dfile4closeLow( data ) ;
         #endif
      #endif  /* S4CLIENT */
   }

   return 0 ;
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
/* clears all locks for a given DATA4 from the list (useful when closing a file) */
void code4lockClearData( CODE4 *c4, DATA4 *data )
{
   #ifndef S4SINGLE
      LOCK4 *lock ;
      SINGLE4DISTANT lockList ;
      TRAN4 *trans ;

      #ifdef S4SERVER
         trans = &c4->currentClient->trans ;
      #else
         trans = &c4->c4trans.trans ;
      #endif

      single4distantInitIterate( &lockList, &trans->locks ) ;

      for (  ;; )
      {
         lock = (LOCK4 *)single4distantToItem( &lockList ) ;
         if ( lock == 0 )
            break ;
         #ifdef S4SERVER
            if ( lock->id.clientId != data4clientId( data ) || lock->id.serverId != data4serverId( data ) )
            {
               single4distantNext( &lockList ) ;
               continue ;
            }
         #else
            #ifdef S4CLIENT
               if ( lock->data != data )
            #else
               if ( lock->data != data->dataFile )
            #endif
               {
                  single4distantNext( &lockList ) ;
                  continue ;
               }
         #endif
         single4distantPop( &lockList ) ;
         mem4free( c4->lockMemory, lock ) ;
      }
   #endif /* S4SINGLE */
   return ;
}

int S4FUNCTION d4close( DATA4 *data )
{
   int rc, saveRc, saveRc2 ;
   CODE4 *c4 ;
   #ifndef S4CLIENT
      #ifndef S4OFF_WRITE
         #ifndef S4OFF_TRAN
            long connectionId ;
            TRAN4 *trans = 0 ;
         #endif
      #endif
   #endif
   #ifndef S4INDEX_OFF
      INDEX4 *indexNext, *indexOn ;
   #endif
   #ifdef E4ANALYZE
      LINK4 compareLink ;
   #endif
   #ifndef S4MEMO_OFF
      int i ;
   #endif
   #ifndef S4SINGLE
      /* 11/11/96 AS stopped waiting forever on locks when closing.
         Change more closely follows documentation, and CodeControls
         works better */
      /* int saveAttempts ; */
   #endif

   #ifdef E4PARM_HIGH
      if ( data == 0 )
         return error4( 0, e4parm_null, E91302 ) ;
   #endif

   c4 = data->codeBase ;
   saveRc = 0 ;

   #ifndef S4SINGLE
      /* 11/11/96 AS as above */
      /* saveAttempts = c4->lockAttempts ; */
      /* c4->lockAttempts = WAIT4EVER ; */
   #endif
   if ( error4code( c4 ) == e4unique )
      data->recordChanged = 0 ;

   if ( error4code( c4 ) < 0 )
      saveRc2 = error4set( c4, 0 ) ;
   else
      saveRc2 = 0 ;

   if ( data->dataFile != 0 )
   {
      /* need to remove any references to any code4lock() calls */
      code4lockClearData( c4, data ) ;

      #ifndef S4OFF_WRITE
         saveRc = d4update( data ) ;
         if ( saveRc == e4unique )
            data->recordChanged = 0 ;
      #endif

      #ifndef S4OFF_TRAN
         #ifndef S4OFF_WRITE
            #ifndef S4CLIENT
               #ifdef S4SERVER
                  if ( c4->currentClient != 0 )
               #endif
               if ( code4transEnabled( c4 ) )
               {
                  trans = code4trans( c4 ) ;
                  #ifdef S4STAND_ALONE
                     connectionId = 0L ;
                  #else
                     connectionId = c4->currentClient->id ;
                  #endif

                  if ( trans->currentTranStatus != r4active )
                  {
                     rc = tran4set( trans, trans->currentTranStatus, -1L, connectionId, TRAN4CLOSE,
                          0, data4clientId( data ), data4serverId( data ) ) ;
                     if ( rc < 0 )
                        saveRc = rc ;
                     if ( tran4lowAppend( trans, "\0", 0 ) != 0 )
                        saveRc = e4transAppend ;
                  }
               }
               else
                  trans = 0 ;
            #endif
         #endif /* S4OFF_WRITE */
      #endif /* S4OFF_TRAN */

      #ifndef S4OFF_TRAN
         #ifndef S4OFF_WRITE
            #ifdef S4CLIENT
               if ( code4transEnabled( c4 ) )   /* can't unlock in this instance */
                  if ( code4tranStatus( c4 ) == r4active )
            #else
               if ( trans != 0 )   /* just add to list */
                  if ( trans->currentTranStatus == r4active )
            #endif
               {
                  l4remove( tran4dataList( data->trans ), data ) ;
                  l4add( &(code4trans( c4 )->closedDataFiles), data ) ;
                  #ifndef S4SINGLE
                       /* 11/11/96 AS as above */
 /*                    c4->lockAttempts = saveAttempts ; */
                  #endif
                  return 0 ;
               }
         #endif
      #endif

      #ifndef S4SINGLE
         if ( d4unlockLow( data, data4clientId( data ), 0 ) < 0 )
            saveRc = error4set( c4, 0 ) ;
      #endif  /* S4SINGLE */

      #ifndef S4INDEX_OFF
         for( indexNext = (INDEX4 *)l4first( &data->indexes );; )
         {
            indexOn = indexNext ;
            indexNext = (INDEX4 *)l4next( &data->indexes, indexOn ) ;
            if ( !indexOn )
               break ;

            rc = i4closeLow( indexOn ) ;
            if ( rc < 0 )
            {
               saveRc = rc ;
               error4set( c4, 0 ) ;
            }
         }
      #endif

      #ifndef S4MEMO_OFF
         if ( data->fieldsMemo != 0 )
         {
            for ( i = 0; i < data->dataFile->nFieldsMemo ; i++ )
               if ( data->fieldsMemo[i].contents != &f4memoNullChar )
               {
                  u4free( data->fieldsMemo[i].contents ) ;
                  data->fieldsMemo[i].contents = &f4memoNullChar ;
               }
            u4free( data->fieldsMemo ) ;
            data->fieldsMemo = 0 ;
         }
      #endif  /* S4MEMO_OFF */

      #ifdef S4SERVER
         /* 05/31/96 AS exclusive open not getting cleared with KEEPOPEN (t4code4.c) */
         if ( data->dataFile->exclusiveOpen == data )
            data->dataFile->exclusiveOpen = 0 ;
      #endif

      #ifdef S4CLIENT
         if ( c4getDoRemove( c4 ) == 1 )
            rc = dfile4remove( data->dataFile ) ;
         else
      #endif
         rc = dfile4close( data->dataFile ) ;
      if ( rc < 0 )
         saveRc = rc ;
      data->dataFile = 0 ;

      if ( data->groupRecordAlloc != 0 )
      {
         u4free( data->groupRecordAlloc ) ;
         data->record = 0 ;
         data->recordOld = 0 ;
         data->fields = 0 ;
         data->recordBlank = 0 ;
      }
      else
      {
         u4free( data->record ) ;
         u4free( data->recordOld ) ;
         u4free( data->fields )  ;
         u4free( data->recordBlank ) ;
      }

      if ( data->trans != 0 )
         l4remove( tran4dataList( data->trans ), data ) ;
      #ifdef E4ANALYZE
         else
         {
            memset( &compareLink, 0, sizeof( LINK4 ) ) ;
            if ( c4memcmp( &data->link, &compareLink, sizeof( LINK4 ) ) != 0 )
               saveRc = error4( c4, e4struct, E81305 ) ;
         }
      #endif
   }
   else
      if ( data->trans != 0 )
         l4remove( tran4dataList( data->trans ), data ) ;

   mem4free( c4->dataMemory, data ) ;

   if ( saveRc != 0 )
      error4set( c4, (short)saveRc ) ;

   #ifndef S4SINGLE
      /* 11/11/96 AS as above */
/*      c4->lockAttempts = saveAttempts ; */
   #endif
   if ( saveRc2 < 0 )
   {
      error4set( c4, (short)saveRc2 ) ;
      return saveRc2 ;
   }
   return saveRc ;
}
