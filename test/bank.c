// BANK.C
// Creates new data file for TRANSFER.C program
#include <stdio.h>

#include "d4all.h"

CODE4 codeBase ;
DATA4 *dataFile ;
FIELD4 *acctNo, *balance ;
TAG4 *acctTag, *balTag ;

FIELD4INFO fieldInfo [] =
{
    { "ACCT_NO", r4num, 5, 0},
    { "BALANCE", r4num, 8, 2},
    NULL
};

TAG4INFO tagInfo [] =
{
    { "acct", "ACCT_NO", 0, 0, 0},
    { "balance", "BALANCE", 0, 0, 0},
    NULL
};

void  OpenDataFile( void)
{
    dataFile = d4create( &codeBase, "bank_test.dbf", fieldInfo, tagInfo) ;

    acctNo = d4field( dataFile, "ACCT_NO") ;
    balance = d4field( dataFile, "BALANCE") ;

    acctTag = d4tag( dataFile, "acct") ;
    balTag = d4tag( dataFile, "balance") ;
}

void PrintRecords( void)
{
    int rc ;

    printf( "printrecords\n");

    for( rc = d4top( dataFile ); rc == r4success; rc = d4skip( dataFile, 1L)) {
        printf( "-------------------------------\n") ;
        printf( "Account Number: %ld\n", f4long( acctNo)) ;
        printf( "Balance       : %f\n " , f4double( balance)) ;
     }
}

void AddNewRecord( long acct, double bal)
{
    d4appendStart( dataFile, 0) ;
    d4blank( dataFile) ;

    d4lockFile( dataFile) ;

    f4assignLong( acctNo, acct) ;
    f4assignDouble( balance, bal) ;

    d4append( dataFile) ;

    d4unlock( dataFile) ;
}

int main( void )
{
    code4init( &codeBase) ;
    codeBase.errOpen = 1;
    codeBase.safety = 0;

    OpenDataFile() ;
    AddNewRecord( 12345L, 600.00);
    AddNewRecord( 55555L, 300.00);
    AddNewRecord( 333L, 777.00);

    PrintRecords() ;

    code4close( &codeBase) ;
    code4initUndo( &codeBase) ;

    return 0 ;
}
