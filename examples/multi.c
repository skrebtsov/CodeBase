/***********************************************************************\
*                                                                       *
*   MULTI.C       Copyright (C) 1998 Sequiter Software Inc.             *
*                                                                       *
\***********************************************************************/
/* See User's Manual, chapter 11 */

#include "d4all.h"

#ifdef __TURBOC__
   extern unsigned _stklen = 10000;
#endif

CODE4 cb ;
FIELD4 *fieldName ;
DATA4 *dataNames ;
TAG4 *tagName ;

void addRecord(void), findRecord(void), modifyRecord(void), listData(void) ;

void main(void)
{
   int command ;

   code4init( &cb ) ;

   cb.accessMode = OPEN4DENY_NONE ;
   cb.readOnly = 0 ;
   cb.readLock = 0 ;
   cb.lockAttempts = WAIT4EVER ;
   cb.lockEnforce = 1 ;

   dataNames = d4open( &cb, "names" ) ;
   error4exitTest( &cb ) ;

   fieldName = d4field( dataNames, "NAME" ) ;
   tagName = d4tag( dataNames, "NAME" ) ;

   d4top( dataNames ) ;

   for(;;)
   {
      error4set( &cb, 0 ) ;

      printf( "\n\nRecord #: %ld   Name: %s\n"
         ,d4recNo( dataNames )
         , f4str( fieldName ) ) ;

      printf( "Enter Command ('a','f','l','m' or 'x')\n" ) ;

      command =  getchar() ;
      switch( command )
      {
         case 'a':
            addRecord() ;
            break ;
         case 'f':
            findRecord() ;
            break ;
         case 'l':
            listData() ;
            break ;
         case 'm':
            modifyRecord() ;
            break ;
         case 'x':
            code4close( &cb ) ;
            exit(0) ;
      }
   }
}

void addRecord(void)
{
   char buf[100] ;
   printf( "Enter New Record\n" ) ;
   scanf( "%s", buf ) ;

   d4appendStart( dataNames, 0 ) ;
   f4assign( fieldName, buf ) ;
   d4append( dataNames ) ;

   d4unlock( dataNames ) ;
}

void findRecord(void)
{
   char buf[100] ;
   printf( "Enter Name to Find\n" ) ;
   scanf( "%s", buf ) ;

   d4tagSelect( dataNames, tagName ) ;
   d4seek( dataNames, buf ) ;
}

void modifyRecord(void)
{
   char buf[100] ;
   int oldLockAttempts, rc ;

   oldLockAttempts = cb.lockAttempts ;
   cb.lockAttempts = 1 ;      /* Only make one lock attempt */

   rc = d4lock(dataNames, d4recNo(dataNames)) ;
   if(rc == r4locked)
      printf("Record locked. Unable to Edit\n") ;
   else
   {
      printf("Enter Replacement Record\n") ;
      scanf("%s", buf) ;
      f4assign(fieldName, buf);
      d4flush(dataNames) ;
      d4unlock(dataNames) ;
   }
   cb.lockAttempts = oldLockAttempts ;
}

void listData(void)
{
   code4optStart( &cb ) ;
   d4optimize( dataNames, 1 ) ;

   d4tagSelect( dataNames, tagName ) ;

   for( d4top(dataNames); ! d4eof(dataNames)
           ; d4skip(dataNames,1) )
      printf( "%ld %s\n", d4recNo(dataNames)
            , f4str(fieldName) ) ;

   d4optimize( dataNames, 0 ) ;
   code4optSuspend( &cb ) ;
}
