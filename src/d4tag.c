/* d4tag.c   (c)Copyright Sequiter Software Inc., 1988-1998.  All rights reserved. */

#include "d4all.h"
#ifndef S4UNIX
   #ifdef __TURBOC__
      #pragma hdrstop
   #endif
#endif

#ifdef P4ARGS_USED
   #pragma argsused
#endif
TAG4 *S4FUNCTION d4tag( DATA4 *d4, const char* const tagName )
{
   #ifndef S4INDEX_OFF
      char tagLookup[LEN4TAG_ALIAS+1] ;
      TAG4 *tagOn ;

      #ifdef S4VBASIC
         if ( c4parm_check( d4, 2, E92401 ) )
            return 0 ;
      #endif

      #ifdef E4PARM_HIGH
         if ( d4 == 0 || tagName == 0 )
         {
            error4( 0, e4parm_null, E92401 ) ;
            return 0 ;
         }
      #endif

      u4ncpy( tagLookup, tagName, sizeof( tagLookup ) ) ;
      c4upper( tagLookup ) ;

      for( tagOn = 0 ;; )
      {
         tagOn = d4tagNext( d4, tagOn ) ;
         if ( tagOn == 0 )
            break ;
         if ( strcmp( tagOn->tagFile->alias, tagLookup ) == 0 )
            return tagOn ;
         #ifdef S4CLIENT
            if ( code4indexFormat( d4->codeBase ) == r4ntx )  /* also check index file access name */
               if ( strcmp( tagOn->tagFile->indexFile->accessName, tagLookup ) == 0 )
                  return tagOn ;
         #endif
      }

      if ( d4->codeBase->errTagName )
         error4describe( d4->codeBase, e4tagName, E92401, tagName, 0, 0 ) ;
   #endif
   return 0 ;
}

#ifndef S4CLIENT
/* for N4OTHER should compare full name, adding extension if required */
#ifdef P4ARGS_USED
   #pragma argsused
#endif
TAG4FILE *dfile4tag( DATA4FILE *d4, const char * const tagName )
{
   #ifndef S4INDEX_OFF
      char tagLookup[LEN4TAG_ALIAS+1] ;
      TAG4FILE *tagOn ;
      #ifdef N4OTHER
         #ifndef S4CLIENT
            char tagLookup2[258], ext1[3], ext2[3] ;
            int l1, l2 ;
         #endif
      #endif

      #ifdef E4PARM_LOW
         if ( d4 == 0 || tagName == 0 )
         {
            error4( 0, e4parm_null, E91102 ) ;
            return 0 ;
         }
      #endif

      #ifdef N4OTHER
         #ifndef S4CLIENT
            u4nameCurrent( tagLookup2, sizeof( tagLookup2 ), tagName ) ;
            u4nameExt( tagLookup2, sizeof( tagLookup2 ), code4indexExtension( d4->c4 ), 0 ) ;
            c4upper( tagLookup2 ) ;
         #endif
      #endif

      u4namePiece( tagLookup, sizeof( tagLookup ), tagName, 0, 0 ) ;
      #ifndef S4CASE_SEN
         c4upper( tagLookup ) ;
      #endif

      for( tagOn = 0 ;; )
      {
         tagOn = dfile4tagNext( d4, tagOn ) ;
         if ( tagOn == 0 )
            break ;
         #ifdef N4OTHER
            #ifndef S4CLIENT
               if ( strcmp( tagOn->file.name, tagLookup2 ) == 0 )
                  return tagOn ;
            #endif
            if ( strcmp( tagOn->alias, tagLookup ) == 0 )  /* also need to verify extension*/
            {
               #ifndef S4CLIENT
                  l1 = u4nameRetExt( ext1, sizeof( ext1 ), tagOn->file.name ) ;
                  l2 = u4nameRetExt( ext2, sizeof( ext1 ), tagName ) ;
                  if ( ( l2 == 0 ) || ( ( l1 == l2 ) && ( memcmp( ext1, ext2, l1 ) == 0 ) ) )
               #endif
                  return tagOn ;
            }
         #else
            if ( strcmp( tagOn->alias, tagLookup ) == 0 )
               return tagOn ;
         #endif
      }

      if ( d4->c4->errTagName )
         error4describe( d4->c4, e4tagName, E91102, tagName, 0, 0 ) ;
   #endif
   return 0 ;
}
#endif

#ifdef P4ARGS_USED
   #pragma argsused
#endif
TAG4 *S4FUNCTION d4tagDefault( DATA4 *d4 )
{
   #ifndef S4INDEX_OFF
      TAG4 *tag ;
      INDEX4 *index ;

      #ifdef S4VBASIC
         if ( c4parm_check( d4, 2, E92403 ) )
            return 0 ;
      #endif

      #ifdef E4PARM_HIGH
         if ( d4 == 0 )
         {
            error4( 0, e4parm_null, E92403 ) ;
            return 0 ;
         }
      #endif

      tag = d4->tagSelected ;
      if ( tag )
         return tag ;

      index = (INDEX4 *)l4first( &d4->indexes ) ;
      if ( index )
      {
         tag = (TAG4 *)l4first( &index->tags ) ;
         if ( tag )
            return tag ;
      }
   #endif
   return 0 ;
}

#ifndef S4CLIENT
#ifdef P4ARGS_USED
   #pragma argsused
#endif
TAG4FILE *dfile4tagDefault( DATA4FILE *d4 )
{
   #ifndef S4INDEX_OFF
      TAG4FILE *tag ;

      #ifdef E4PARM_LOW
         if ( d4 == 0 )
         {
            error4( 0, e4parm_null, E91102 ) ;
            return 0 ;
         }
      #endif

      tag = dfile4tagSelected( d4 ) ;
      if ( tag )
         return tag ;

      tag = dfile4tagNext( d4, 0 ) ;
      return tag ;
   #else
      return 0 ;
   #endif
}
#endif

#ifdef P4ARGS_USED
   #pragma argsused
#endif
TAG4 *S4FUNCTION d4tagNext( DATA4 *d4, TAG4 * tag )
{
   #ifdef S4INDEX_OFF
      return 0 ;
   #else
      INDEX4 *i4 ;
      TAG4 * tagOn ;

      tagOn = tag ;

      #ifdef S4VBASIC
         if ( c4parm_check( d4, 2, E92405 ) )
            return 0 ;
      #endif

      #ifdef E4PARM_HIGH
         if ( d4 == 0 )
         {
            error4( 0, e4parm_null, E92405 ) ;
            return 0 ;
         }
      #endif

      if ( tagOn == 0 )
      {
         i4 = (INDEX4 *)l4first( &d4->indexes ) ;
         if ( i4 == 0 )
            return 0 ;
      }
      else
      {
         for ( i4 = 0 ;; )
         {
            i4 = (INDEX4 *)l4next( &d4->indexes, i4 ) ;
            if ( i4 == 0 )
               return 0 ;
            if ( i4 == tagOn->index )
               break ;
         }
      }

      tagOn = (TAG4 *)l4next( &i4->tags, tagOn ) ;
      if ( tagOn == 0 )
      {
         i4 = (INDEX4 *)l4next( &d4->indexes, i4 )  ;
         if ( i4 == 0 )
            return 0 ;
         return (TAG4 *)l4first( &i4->tags ) ;
      }
      return tagOn ;
   #endif
}

#ifndef S4CLIENT
#ifdef P4ARGS_USED
   #pragma argsused
#endif
TAG4FILE *dfile4tagNext( DATA4FILE *d4, TAG4FILE *tagOn )
{
   #ifdef S4INDEX_OFF
      return 0 ;
   #else
      #ifndef N4OTHER
         INDEX4FILE *i4 ;
      #endif

      #ifdef E4PARM_LOW
         if ( d4 == 0 )
         {
            error4( 0, e4parm_null, E91102 ) ;
            return 0 ;
         }
      #endif

      #ifdef N4OTHER
         return (TAG4FILE *)l4next( &d4->tagfiles, tagOn ) ;
      #else
         if ( tagOn == 0 )
         {
            i4 = (INDEX4FILE *)l4first( &d4->indexes ) ;
            if ( i4 == 0 )
               return 0 ;
         }
         else
            i4 = tagOn->indexFile ;

         tagOn = (TAG4FILE *)l4next( &i4->tags, tagOn ) ;
         if ( tagOn )
            return tagOn ;

         i4 = (INDEX4FILE *)l4next( &d4->indexes, i4 ) ;
         if ( i4 == 0 )
            return 0 ;

         return (TAG4FILE *)l4first( &i4->tags ) ;
      #endif /* N4OTHER */
   #endif
}
#endif

#ifdef P4ARGS_USED
   #pragma argsused
#endif
TAG4 *S4FUNCTION d4tagPrev( DATA4 *d4, TAG4 *tag )
{
   #ifdef S4INDEX_OFF
      return 0 ;
   #else
      INDEX4 *i4 ;
      TAG4 * tagOn ;

      tagOn = tag ;

      #ifdef S4VBASIC
         if ( c4parm_check( d4, 2, E92407 ) )
            return 0 ;
      #endif

      #ifdef E4PARM_HIGH
         if ( d4 == 0 )
         {
            error4( 0, e4parm_null, E92407 ) ;
            return 0 ;
         }
      #endif

      if ( tagOn == 0 )
      {
         i4 = (INDEX4 *)l4last( &d4->indexes ) ;
         if ( i4 == 0 )
            return 0 ;
      }
      else
      {
         for ( i4 = 0 ;; )
         {
            i4 = (INDEX4 *)l4prev( &d4->indexes, i4 ) ;
            if ( i4 == 0 )
               return 0 ;
            if ( i4 == tagOn->index )
               break ;
         }
      }

      tagOn = (TAG4 *)l4prev( &i4->tags, tagOn ) ;
      if ( tagOn == 0 )
      {
         i4 = (INDEX4 *)l4prev( &d4->indexes, i4 )  ;
         if ( i4 == 0 )
            return 0 ;
         return (TAG4 *)l4last( &i4->tags ) ;
      }
      return tagOn ;
   #endif
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
TAG4FILE *dfile4tagPrev( DATA4FILE *d4, TAG4FILE *tagOn )
{
   #ifdef S4INDEX_OFF
      return 0 ;
   #else
      #ifndef N4OTHER
         INDEX4FILE *i4 ;
      #endif

      #ifdef E4PARM_LOW
         if ( d4 == 0 )
         {
            error4( 0, e4parm_null, E91102 ) ;
            return 0 ;
         }
      #endif

      #ifdef N4OTHER
         return (TAG4FILE *)l4prev( &d4->tagfiles, tagOn ) ;
      #else
         if ( tagOn == 0 )
         {
            i4 = (INDEX4FILE *)l4last( &d4->indexes ) ;
            if ( i4 == 0 )
               return 0 ;
         }
         else
            i4 = tagOn->indexFile ;

         tagOn = (TAG4FILE *)l4prev( &i4->tags, tagOn ) ;
         if ( tagOn )
            return tagOn ;

         i4 = (INDEX4FILE *)l4prev( &d4->indexes, i4 ) ;
         if ( i4 == 0 )
            return 0 ;

         return (TAG4FILE *)l4last( &i4->tags ) ;
      #endif
   #endif
}

#ifdef P4ARGS_USED
   #pragma argsused
#endif
void S4FUNCTION d4tagSelect( DATA4 *d4, TAG4 *t4 )
{
   #ifdef S4VBASIC
      if ( c4parm_check( d4, 2, E92409 ) )
         return ;
   #endif

   #ifdef E4PARM_HIGH
      if ( d4 == 0 )
      {
         error4( 0, e4parm_null, E92409 ) ;
         return ;
      }
   #endif

   #ifdef S4INDEX_OFF
      if ( t4 != 0 )
      {
         error4( d4->codeBase, e4notIndex, E92409 ) ;
         return ;
      }
   #else
      d4->tagSelected = t4 ;
   #endif

   return ;
}

#ifndef S4CLIENT
int dfile4tagSelect( DATA4FILE *d4, TAG4FILE *t4 )
{
   #ifdef E4PARM_LOW
      if ( d4 == 0 )
         return error4( 0, e4parm_null, E91102 ) ;
   #endif

   #ifdef S4INDEX_OFF
      if ( t4 != 0 )
         error4( d4->c4, e4notIndex, E91102 ) ;
   #else
      #ifdef N4OTHER
         d4->tagfiles.selected = (LINK4 *)t4 ;
      #else
         #ifdef E4ANALYZE
            if ( t4 )
               if ( t4->indexFile->dataFile != d4 )
                  return error4( t4->codeBase, e4struct, E91102 ) ;
         #endif

         if ( t4 == 0 )
            d4->indexes.selected = 0 ;
         else
         {
            d4->indexes.selected = (LINK4 *)t4->indexFile ;
            t4->indexFile->tags.selected = (LINK4 *)t4 ;
         }
      #endif
   #endif

   return 0 ;
}
#endif

#ifdef P4ARGS_USED
   #pragma argsused
#endif
TAG4 *S4FUNCTION d4tagSelected( DATA4 *d4 )
{
   #ifndef S4INDEX_OFF
      #ifdef E4PARM_HIGH
         if ( d4 == 0 )
         {
            error4( 0, e4parm_null, E92411 ) ;
            return 0 ;
         }
      #endif

      return d4->tagSelected ;
   #else
      return 0 ;
   #endif
}

#ifndef S4CLIENT
#ifdef P4ARGS_USED
   #pragma argsused
#endif
TAG4FILE *dfile4tagSelected( DATA4FILE *d4 )
{
   #ifndef S4INDEX_OFF
      #ifndef N4OTHER
         INDEX4FILE *index ;
         TAG4FILE *tag ;
      #endif

      #ifdef E4PARM_LOW
         if ( d4 == 0 )
         {
            error4( 0, e4parm_null, E91102 ) ;
            return 0 ;
         }
      #endif

      #ifdef N4OTHER
         return (TAG4FILE *)d4->tagfiles.selected ;
      #else
         index = (INDEX4FILE *)d4->indexes.selected ;
         if ( index )
         {
            tag = (TAG4FILE *)index->tags.selected ;
            if ( tag )
               return tag ;
         }
         return (TAG4FILE *)0 ;
      #endif
   #else
      return (TAG4FILE *)0 ;
   #endif
}
#endif

#ifdef S4VB_DOS

TAG4 *d4tag_v( DATA4 *d4, char *name )
{
   return d4tag( d4, c4str(name) ) ;
}

#endif

int S4FUNCTION d4numTags(DATA4 *data)
{
  int numTags;

  #ifdef S4CLIPPER
  numTags = l4numNodes( &data->dataFile->tagfiles ) ;
  #else
  INDEX4FILE *i4fileOn ;
  for ( numTags = 0, i4fileOn = 0 ;; )
  {
     i4fileOn = (INDEX4FILE *)l4next( &data->dataFile->indexes, i4fileOn ) ;
     if ( i4fileOn == 0 )
        break ;
     numTags += l4numNodes( &i4fileOn->tags ) ;
  }
  #endif
  return (numTags);
}
