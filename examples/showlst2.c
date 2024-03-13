/***********************************************************************\
*                                                                       *
*   SHOWDAT2.C    Copyright (C) 1998 Sequiter Software Inc.             *
*                                                                       *
\***********************************************************************/
/* See User's Manual, chapter 5 */

#include "d4all.h"

#ifdef __TURBOC__
   extern unsigned _stklen = 10000;
#endif

CODE4    codeBase;
DATA4    *dataFile = 0;
FIELD4   *fName
   ,*lName
   ,*address
   ,*age
   ,*birthDate
   ,*married
   ,*amount
   ,*comment;

TAG4     *nameTag
   ,*ageTag
   ,*amountTag
   ,*addressTag
   ,*birthdateTag;

TAG4INFO  tagInfo[] =
{
   {"NAME_TAG","L_NAME+F_NAME",".NOT. DELETED()",0,0},
   {"ADDR_TAG","ADDRESS",0,0,0},
   {"AGE_TAG","AGE","AGE >= 18",0,0},
   {"DATE_TAG","BIRTH_DATE",0,0,0},
   {"AMNT_TAG","AMOUNT",0,0,0},
   {0,0,0,0,0},
};

void OpenDataFile(void)
{

   codeBase.autoOpen = 0;
   codeBase.safety = 0;
   codeBase.accessMode = OPEN4DENY_RW;

   dataFile = d4open(&codeBase,"data1.dbf");

   i4create(dataFile,NULL,tagInfo);

   fName = d4field(dataFile,"F_NAME");
   lName = d4field(dataFile,"L_NAME");
   address = d4field(dataFile,"ADDRESS");
   age = d4field(dataFile,"AGE");
   birthDate = d4field(dataFile,"BIRTH_DATE");
   married = d4field(dataFile,"MARRIED");
   amount = d4field(dataFile,"AMOUNT");
   comment = d4field(dataFile,"COMMENT");

   nameTag = d4tag(dataFile,"NAME_TAG");
   addressTag = d4tag(dataFile,"ADDR_TAG");
   ageTag = d4tag(dataFile,"AGE_TAG");
   birthdateTag = d4tag(dataFile,"DATE_TAG");
   amountTag = d4tag(dataFile,"AMNT_TAG");
}


void PrintRecords(void)
{
   int      rc,ageValue;
   double   amountValue;
   char     fNameStr[15],lNameStr[15];
   char     addressStr[20];
   char     dateStr[9];
   char     marriedStr[2];
   const char     *commentStr;


   for(rc = d4top(dataFile);rc == r4success
           ;rc = d4skip(dataFile, 1L))
   {
      f4ncpy(fName,fNameStr
              ,sizeof(fNameStr));
      f4ncpy(lName,lNameStr
              ,sizeof(lNameStr));
      f4ncpy(address,addressStr
             ,sizeof(addressStr));
      ageValue = f4int(age);
      amountValue = f4double(amount);
      f4ncpy(birthDate,dateStr
                ,sizeof(dateStr));
      f4ncpy(married,marriedStr
             ,sizeof(marriedStr));
      commentStr = f4memoStr(comment);

      printf("---------------------------\n");
      printf("Name     : %10s %10s\n"
           ,fNameStr,lNameStr);

      printf("Address  : %15s\n",addressStr);
      printf("Age : %3d   Married : %1s\n"
           ,ageValue,marriedStr);
      printf("Comment: %s\n",commentStr);
      printf("Amount purchased : $%5.2lf \n"
               ,amountValue);

      printf("\n");
   }

}

int main(void)
{
   code4init(&codeBase);

   OpenDataFile();

   d4tagSelect(dataFile,nameTag);
   PrintRecords();

   d4tagSelect(dataFile,ageTag);
   PrintRecords();

   d4tagSelect(dataFile,amountTag);
   PrintRecords();

   code4close(&codeBase);
   code4initUndo(&codeBase);
   return 0;
}
