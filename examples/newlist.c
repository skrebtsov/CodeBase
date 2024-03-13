/***********************************************************************\
*                                                                       *
*   NEWLIST.C     Copyright (C) 1998 Sequiter Software Inc.             *
*                                                                       *
\***********************************************************************/
/* See User's Manual, chapter 4 */

#include "d4all.h"

#ifdef __TURBOC__
   extern unsigned _stklen = 10000;
#endif

CODE4    codeBase;
DATA4    *dataFile = 0;
FIELD4   *fName,*lName,*address,*age,*birthDate,*married ,*amount,*comment;

FIELD4INFO  fieldInfo [] =
{
   {"F_NAME",r4str,10,0},
   {"L_NAME",r4str,10,0},
   {"ADDRESS",r4str,15,0},
   {"AGE",r4num,2,0},
   {"BIRTH_DATE",r4date,8,0},
   {"MARRIED",r4log,1,0},
   {"AMOUNT",r4num,7,2},
   {"COMMENT",r4memo,10,0},
   {0,0,0,0},
};

void  OpenDataFile( )
{
   dataFile = d4open(&codeBase,"data1.dbf");
   if(dataFile == NULL)
      dataFile = d4create(&codeBase,"data1.dbf",fieldInfo,0);

   fName = d4field(dataFile,"F_NAME");
   lName = d4field(dataFile,"L_NAME");
   address = d4field(dataFile,"ADDRESS");
   age = d4field(dataFile,"AGE");
   birthDate = d4field(dataFile,"BIRTH_DATE");
   married = d4field(dataFile,"MARRIED");
   amount = d4field(dataFile,"AMOUNT");
   comment = d4field(dataFile,"COMMENT");

}

void PrintRecords( )
{
   int      rc,ageValue;
   double   amountValue;
   char     nameStr[25];
   char     addressStr[20];
   char     dateStr[9];
   char     marriedStr[2];
   const char     *commentStr;

   for(rc = d4top(dataFile);rc == r4success
                      ;rc = d4skip(dataFile, 1L))
   {
      u4ncpy(nameStr,f4str(fName)
                             ,sizeof(nameStr));
      u4ncpy(addressStr,f4str(address)
                           ,sizeof(addressStr));
      ageValue = f4int(age);
      amountValue = f4double(amount);

      u4ncpy(dateStr,f4str(birthDate)
                              ,sizeof(dateStr));
      u4ncpy(marriedStr,f4str(married),
                            sizeof(marriedStr));
      commentStr = f4memoStr(comment);

      printf("------------------------------\n");
      printf("Name     : %20s\n",nameStr);
      printf("Address  : %15s\n",addressStr);
      printf("Age : %3d   Married : %1s\n"
                          ,ageValue,marriedStr);
      printf("Comment: %s\n",commentStr);
      printf("Purchased this year : $%5.2lf \n"
                                   ,amountValue);

      printf("\n");
   }
}


void AddNewRecord(char *fNameStr
                 ,char*lNameStr
                 ,char *addressStr
                 ,int ageValue
                 ,int marriedValue
                 ,double amountValue
                 ,char *commentStr)
{

   d4appendStart(dataFile,0);

   f4assign(fName,fNameStr);
   f4assign(lName,lNameStr);
   f4assign(address,addressStr);

   f4assignInt(age,ageValue);

   if(marriedValue)
      f4assign(married,"T");
   else
      f4assign(married,"F");

   f4assignDouble(amount,amountValue);
   f4memoAssign(comment,commentStr);

   d4append(dataFile);
}



int main( )
{

   code4init(&codeBase);
   codeBase.errOpen = 0;
   codeBase.safety = 0;

   OpenDataFile();

   PrintRecords();

   AddNewRecord("Sarah"
               ,"Webber"
               ,"132-43 St."
               ,32
               ,1
               ,147.99
               ,"New Customer");

   AddNewRecord("John"
               ,"Albridge"
               ,"1232-76 Ave."
               ,12
               ,0
               ,98.99
               ,"");

   PrintRecords();

   code4close(&codeBase);
   return 0;
}
