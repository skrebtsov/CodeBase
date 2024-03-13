/*ex122.c*/
#include "d4all.h" 

#ifdef __TURBOC__
   extern unsigned _stklen = 10000;
#endif

void main( void ) 
{	int rc ;
    CODE4 cb ;
    DATA4 *enroll ;
    DATA4 *master ;
    DATA4 *student ;
 
    TAG4 *enrollTag ;
    TAG4 *studentTag ;
 
    RELATE4 *MasterRelation ;
    RELATE4 *relation1 ;
    RELATE4 *relation2 ;

    FIELD4 *classCode ;
    FIELD4 *classTitle ;
    FIELD4 *enrollStudentId ;
    FIELD4 *studentName ;
	
	code4init( &cb ) ;
	enroll = d4open( &cb, "ENROLL" ) ;
	master = d4open( &cb, "CLASSES" ) ;
	student = d4open( &cb, "STUDENT" ) ;
	
	enrollTag = d4tag( enroll, "C_CODE_TAG" ) ;
	studentTag = d4tag( student, "ID_TAG" ) ;

	MasterRelation = relate4init( master ) ;
	relation1 = relate4createSlave( MasterRelation, enroll, "CODE", enrollTag ) ;
	relation2 = relate4createSlave( relation1, student, "STU_ID_TAG", studentTag);

	relate4type( relation1, relate4scan ) ;
	relate4sortSet( MasterRelation,  "STUDENT->L_NAME,8,0+ENROLL->CODE" ) ;
	
	classCode = d4field( master, "CODE" ) ;
	classTitle = d4field( master, "TITLE" ) ;
	enrollStudentId = d4field( enroll, "STU_ID_TAG") ;
	studentName = d4field( student, "L_NAME" ) ;

    error4exitTest( &cb ) ;

    for(rc = relate4top( MasterRelation ); rc != r4eof;
								rc = relate4skip( MasterRelation, 1L ) )
    {
		printf( "%s ", f4str( studentName )) ; /* only one f4str per statement*/
		printf( "%s ", f4str( enrollStudentId ) ) ;
		printf( "%s ", f4str( classCode ) ) ;
		printf( "%s\n", f4str(classTitle ) ) ;
    }
 
    printf("Number of records in %s is %d\n", d4alias(master),d4recCount(master));

    relate4free( MasterRelation, 1 ) ;
    code4initUndo( &cb ) ;
}

