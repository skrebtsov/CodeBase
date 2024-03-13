/***********************************************************************\
*                                                                       *
*   NOGROUP1.C    Copyright (C) 1993 Sequiter Software Inc.             *
*                                                                       *
\***********************************************************************/
/* See User's Manual, chapter 5 */

#include "d4all.h"

#ifdef __TURBOC__
   extern unsigned _stklen = 10000;
#endif

CODE4  codeBase;
DATA4  *dataFile = 0;
TAG4   *nameTag,*addressTag,*ageTag,*dateTag;

TAG4INFO tagInfo[] =
{
   {"NAME","L_NAME+F_NAME",0,0,0},
   {"ADDRESS","ADDRESS",0,0,0},
   {"AGE_TAG","AGE",0,0,0},
   {"DATE","BIRTH_DATE",0,0,0},
   {0,0,0,0,0}
} ;

int PASCAL WinMain (HANDLE a, HANDLE b, LPSTR c, int d)
{
   #ifdef N4OTHER
      code4init(&codeBase);

      codeBase.autoOpen = 0;
      codeBase.safety = 0;
      codeBase.accessMode = OPEN4DENY_RW;

      dataFile = d4open(&codeBase,"DATA1.DBF");

      i4create( dataFile, 0, tagInfo ) ;
      nameTag = d4tag( dataFile, "NAME" ) ;
      addressTag = d4tag( dataFile, "ADDRESS" ) ;
      ageTag = d4tag( dataFile, "AGE_TAG" ) ;
      dateTag = d4tag(dataFile, "DATE" );

      code4close(&codeBase);
   #endif

   return 1;
}
