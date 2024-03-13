/***********************************************************************\
*                                                                       *
*   LIST2.C    Copyright (C) 1998 Sequiter Software Inc.             *
*                                                                       *
\***********************************************************************/
/* See User's Manual, chapter 9*/

#include "d4all.h"

#ifdef __TURBOC__
   extern unsigned _stklen = 10000;
#endif

typedef struct
{
    LINK4   link;
    int     age;
} AGES;

void printList(LIST4 *);
AGES *addAge(LIST4 *,int);
void removeAge(LIST4 *,AGES *);
void freeAges(LIST4 *);

void main(void)
{

    LIST4   ageList;
    AGES    *agePtr;

    memset(&ageList,0,sizeof(ageList));

    addAge(&ageList,3);
    agePtr = addAge(&ageList,5);
    addAge(&ageList,7);
    addAge(&ageList,6);
    addAge(&ageList,2);

    ageList.selected = (LINK4 *)agePtr;

    printList(&ageList);

    removeAge(&ageList,agePtr);

    printList(&ageList);

    freeAges(&ageList);

    printList(&ageList);
}


void printList(LIST4 *list)
{
    AGES    *agePtr;

    printf("\nThere are %d links\n",l4numNodes(list));
    if (list->selected != NULL )
       printf("The selected node contains the age %d\n",((AGES *)(list->selected))->age);

    agePtr = (AGES *) l4first(list);
    while(agePtr != NULL)
    {
   printf("%d\n",agePtr->age);
   agePtr = (AGES *) l4next(list,agePtr);
    }

}


AGES *addAge(LIST4 *list,int age)
{
    AGES* agePtr;

    agePtr = (AGES *) u4alloc(sizeof(AGES));

    agePtr->age = age;
    l4add(list,agePtr);

    return(agePtr);
}

void removeAge(LIST4 *list,AGES *agePtr)
{
    l4remove(list,agePtr);
    u4free(agePtr);
}

void freeAges(LIST4 *list)
{
    AGES *agePtr;

    while( (agePtr = (AGES *) l4pop(list)) )
   u4free(agePtr);

}
