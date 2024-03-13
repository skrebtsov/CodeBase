/* d4top.c   (c)Copyright Sequiter Software Inc., 1988-1998.  All rights reserved. */

#include "d4all.h"
#ifndef S4UNIX
   #ifdef __TURBOC__
      #pragma hdrstop
   #endif  /* __TUROBC__ */
#endif  /* S4UNIX */

#ifdef S4CLIENT
int S4FUNCTION d4top( DATA4 *data )
{
   #ifndef S4OFF_INDEX
      TAG4 *tag ;
   #endif
   int rc ;
   CONNECTION4 *connection ;
   CONNECTION4TOP_INFO_IN *info ;
   CONNECTION4TOP_INFO_OUT *out ;
   CODE4 *c4 ;

   #ifdef S4VBASIC
      if ( c4parm_check( data, 2, E92301 ) )
         return -1 ;
   #endif

   #ifdef E4PARM_HIGH
      if ( data == 0 )
         return error4( 0, e4parm_null, E92301 ) ;
   #endif

   c4 = data->codeBase ;
   if ( error4code( c4 ) < 0 )
      return e4codeBase ;

   #ifndef S4OFF_WRITE
      rc = d4updateRecord( data, 0 ) ;
      if ( rc )
         return rc ;
   #endif

   connection = data->dataFile->connection ;
   if ( connection == 0 )
      return e4connection ;

   data->recNum = -1 ;
   connection4assign( connection, CON4TOP, data4clientId( data ), data4serverId( data ) ) ;
   connection4addData( connection, NULL, sizeof( CONNECTION4TOP_INFO_IN ), (void **)&info ) ;
   #ifdef S4OFF_INDEX
      info->usesTag = 0 ;
   #else
      tag = data->tagSelected ;
      if ( tag == 0 )
         info->usesTag = 0 ;
      else
      {
         info->usesTag = 1 ;
         memcpy( info->tagName, tag->tagFile->alias, LEN4TAG_ALIAS  ) ;
         info->tagName[LEN4TAG_ALIAS] = 0 ;
      }
   #endif

   rc = connection4repeat( connection ) ;
   switch( rc )
   {
      case r4eof:
         data->bofFlag = 1 ;
         return d4goEof( data ) ;
      case r4success:
         break ;
      default:
         if ( rc < 0 )
            connection4error( connection, c4, rc, E92301 ) ;
         return rc ;
   }

   if ( connection4len( connection ) != (long)sizeof( CONNECTION4TOP_INFO_OUT ) + (long)dfile4recWidth( data->dataFile ) )
      return error4( c4, e4packetLen, E92301 ) ;

   out = (CONNECTION4TOP_INFO_OUT *)connection4data( connection ) ;

   /* now copy the data into the record */
   memcpy( data->record, ((char *)out) + sizeof( CONNECTION4TOP_INFO_OUT ), dfile4recWidth( data->dataFile ) ) ;

   data->bofFlag = out->bofFlag ;
   data->eofFlag = out->eofFlag ;

   data->recNum = ntohl(out->recNo) ;
   if ( out->recordLocked )
   {
      d4localLockSet( data, data->recNum ) ;
      memcpy( data->recordOld, data->record, dfile4recWidth( data->dataFile ) ) ;
      data->recNumOld = data->recNum ;
      data->memoValidated = 1 ;
   }

   return 0 ;
}

#else

int S4FUNCTION d4top( DATA4 *data )
{
   int rc ;
   CODE4 *c4 ;
   #ifndef S4OFF_INDEX
      long recno ;
      TAG4 *tag ;
      TAG4FILE *tagFile ;
   #endif
   #ifndef S4SERVER
      int saveFlag ;
   #endif

   #ifdef S4VBASIC
      if ( c4parm_check( data, 2, E92301 ) )
         return -1;
   #endif  /* S4VBASIC */

   #ifdef E4PARM_HIGH
      if ( data == 0 )
         return error4( 0, e4parm_null, E92301 ) ;
   #endif

   c4 = data->codeBase ;
   if ( error4code( c4 ) < 0 )
      return -1 ;

   #ifndef S4OFF_INDEX
      tag = data->tagSelected ;

      if ( tag == 0 )
      {
   #endif
      if ( d4recCount( data ) > 0L )
      {
         #ifndef S4SERVER
            saveFlag = c4->errGo ;
            c4->errGo = 0 ;
         #endif
         rc = d4go( data, 1L ) ;
         #ifndef S4SERVER
            c4->errGo = saveFlag ;
         #endif
         return rc ;
      }
   #ifndef S4OFF_INDEX
      }
      else
      {
         tagFile = tag->tagFile ;
         #ifndef S4OFF_WRITE
            /* AS 04/22/97 causes problems with t4seek, unlock reset to 0 */
            rc = d4updateRecord( data, 0 ) ;
            if ( rc )
               return rc ;
         #endif
         t4versionCheck( tag, 0, 0 ) ;
         rc = tfile4top( tagFile ) ;
         if ( rc )
            return rc ;
         if ( !tfile4eof( tagFile ) )
         {
            recno = tfile4recNo( tagFile ) ;
            if ( recno < 0 )
               return (int)recno ;
            rc = d4go( data, recno ) ;
            #ifndef S4OFF_MULTI
               #ifndef S4OFF_TRAN
                  if ( rc == 0 )
                     if ( code4transEnabled( c4 ) )
                        if ( t4unique( tag ) != 0 )
                           #ifdef S4SERVER
                              if ( !dfile4lockTestFile( data->dataFile, data4clientId( data ), data4serverId( data ) ) )
                           #else
                              if ( !d4lockTestFile( data ) )
                           #endif
                              rc = d4tagSyncDo( data, tag, 1 ) ;
               #endif
            #endif
            return rc ;
         }
      }
   #endif

   data->bofFlag = 1 ;
   return d4goEof( data ) ;
}

#endif /* S4CLIENT */

int S4FUNCTION d4goBof( DATA4 *data )
{
   int rc ;

   #ifdef E4PARM_HIGH
      if ( data == 0 )
         return error4( 0, e4parm_null, E93104 ) ;
   #endif

   if ( error4code( data->codeBase ) < 0 )
      return e4codeBase ;

   #ifndef S4OFF_WRITE
      /* AS 04/22/97 causes problems with t4seek, unlock reset to 0 */
      rc = d4updateRecord( data, 0 ) ;
      if ( rc )
         return rc ;
   #endif

   rc = d4top( data ) ;
   data->bofFlag = 1 ;
   if ( rc < 0 )
      return rc ;

   return r4bof ;
}
