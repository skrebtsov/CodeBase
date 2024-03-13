/***********************************************************************\
*                                                                       *
*   DELETION.C     Copyright (C) 1998 Sequiter Software Inc.             *
*                                                                       *
\***********************************************************************/
/* See User's Manual, chapter 4 */


#include "d4all.h"


#ifdef __TURBOC__
   extern unsigned _stklen = 10000;
#endif

CODE4      codeBase;
DATA4      *dataFile = 0;

FIELD4INFO fieldInfo[]=
{
   {"DUMMY",'C',10,0},
   {"MEMO",'M',10,0},
   {0,0,0,0},
};

void printDeleteStatus(int status,long recNo)
{
   if(status)
       printf("Record %5ld - DELETED\n",recNo);
   else
       printf("Record %5ld - NOT DELETED\n",recNo);
}

void printRecords(DATA4 *dataFile)
{
   int  rc,status;
   long recNo;

   printf("\n");

   rc = d4top(dataFile);
   while(rc != r4eof)
   {
      recNo = d4recNo(dataFile);
      status = d4deleted(dataFile);
      printDeleteStatus(status,recNo);
      rc = d4skip(dataFile,1L);
   }

}

void main(void)
{
   int count;

   code4init(&codeBase);
   codeBase.safety = 0;

   dataFile = d4create(&codeBase, "tutor5", fieldInfo, 0);
   error4exitTest(&codeBase);

   for(count = 0;count < 5;count ++)
       d4appendBlank(dataFile);


   printRecords(dataFile);

   d4go(dataFile,3L);
   d4delete(dataFile);
   d4go(dataFile,1L);
   d4delete(dataFile);
   d4go(dataFile,4L);
   d4delete(dataFile);
   printRecords(dataFile);

   d4go(dataFile,3L);
   d4recall(dataFile);
   printRecords(dataFile);

   d4pack(dataFile);
   d4memoCompress(dataFile);
   printRecords(dataFile);

   code4close(&codeBase);
   code4initUndo(&codeBase);

}
