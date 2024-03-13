/***********************************************************************\
*                                                                       *
*   RELATE1.C     Copyright (C) 1998 Sequiter Software Inc.             *
*                                                                       *
\***********************************************************************/
/* See User's Manual, chapter 6 */

#include "d4all.h"

#ifdef __TURBOC__
   extern unsigned _stklen = 10000;
#endif

CODE4   codeBase;
DATA4   *student = NULL,*enrollment = NULL;
RELATE4 *master = NULL,*slave = NULL;
TAG4    *idTag,*nameTag;

void openDataFiles(void) ;
void setRelation(void) ;
void printRecord(void) ;

void openDataFiles(void)
{
    code4init(&codeBase);

    student = d4open(&codeBase,"student");
    enrollment = d4open(&codeBase,"enroll");

    nameTag = d4tag(student,"NAME");
    idTag = d4tag(enrollment,"STU_ID_TAG");

    error4exitTest(&codeBase);

}

void setRelation(void)
{
    master = relate4init(student);
    if(master == NULL) exit(1);

    slave = relate4createSlave(master,enrollment
                ,"ID",idTag);

    relate4type(slave,relate4scan);

    relate4top(master);
}

void printRecord(void)
{
    RELATE4 *relation;
    DATA4   *data;
    int     j;

    for(relation = master;relation != NULL
           ;relate4next(&relation))
    {
         data = relation->data ;

   for(j = 1;j <= d4numFields(data);j++)
       printf("%s "
      ,f4memoStr(d4fieldJ(data,j)));

    }
    printf("\n");
}

void listRecords(void)
{
    int rc;

    for(rc = relate4top(master);rc != r4eof;rc = relate4skip(master,1L))
   printRecord();

    printf("\n");

    code4unlock(&codeBase);
}

void main(void)
{
    openDataFiles();

    setRelation();

    listRecords();

    relate4free(master,0);

    code4close(&codeBase);
    code4initUndo(&codeBase);
}
