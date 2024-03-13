/***********************************************************************\
*                                                                       *
*   DATAINFO.C    Copyright (C) 1998 Sequiter Software Inc.             *
*                                                                       *
\***********************************************************************/
/* See User's Manual, chapter 4 */


#include "d4all.h"


#ifdef __TURBOC__
   extern unsigned _stklen = 10000;
#endif
#ifdef S4MACINTOSH
   #include <console.h>
#endif

int main(int argc,char *argv[])
{

   CODE4    codeBase;
   DATA4    *dataFile;
   FIELD4   *field;

   int      j,numFields;
   int      len,dec;
   int      recWidth;
   const char     *name;
   char     type;
   const char     *alias;
   long     recCount;

   #ifdef S4MACINTOSH
      argc = ccommand(&argv) ;
   #endif

   if(argc != 2)
   {
      printf(" USAGE: FLDINFO <FILENAME.DBF> \n");
      exit(0);
   }

   code4init(&codeBase);

   dataFile = d4open(&codeBase,argv[1]);
   error4exitTest(&codeBase);


   recCount = d4recCount(dataFile);
   numFields = d4numFields(dataFile);
   recWidth = d4recWidth(dataFile);
   alias = d4alias(dataFile);

   printf("浜様様様様様様様様様様様様様様様様�\n");
   printf("� Data File: %12s         �\n",argv[1]);
   printf("� Alias    : %12s         �\n",alias);
   printf("�                                 �\n");
   printf("� Number of Records: %7ld      �\n",recCount);
   printf("� Length of Record : %7d      �\n",recWidth);
   printf("� Number of Fields : %7d      �\n",numFields);
   printf("�                                 �\n");
   printf("� Field Information :             �\n");
   printf("麺様様様様様曜様様様僕様様曜様様様�\n");
   printf("� Name       � type � len  � dec  �\n");
   printf("麺様様様様様洋様様様陵様様洋様様様�\n");



   for(j = 1;j <= d4numFields(dataFile);j ++)
   {
      field = d4fieldJ(dataFile,j);
      name = f4name(field);
      type = f4type(field);
      len = f4len(field);
      dec = f4decimals(field);

      printf("� %10s �   %c  � %4d � %4d �\n",name,type,len,dec);

   }
   printf("藩様様様様様擁様様様瞥様様擁様様様�\n");


   d4close(dataFile);

   return 0;
}
