/*ex124.c*/
#include "d4all.h"


#ifdef __TURBOC__
   extern unsigned _stklen = 10000;
#endif

int seekMaster( DATA4 *master, RELATE4 *r, TAG4 *masterTag, char *seekKey )
{
	int rc ;

	d4tagSelect( master, masterTag ) ;
	rc = d4seek( master, seekKey ) ; /* seek for the requested value*/

	if( rc == r4success )
	relate4doOne( r ) ; /* position the slave data file to the appropriate
						record according to its master*/
	return rc ;
}

void main( void )
{
	CODE4 cb ;
	DATA4 *enroll ;
	DATA4 *master ;

	TAG4 *enrollTag ;
	TAG4 *codeTag ;
	RELATE4 *MasterRelation ;
	RELATE4 *relation1 ;

	FIELD4 *classCode ;
	FIELD4 *classTitle ;
	FIELD4 *enrollStudentId ;

	code4init( &cb ) ;
	enroll = d4open( &cb, "ENROLL" ) ;
	master = d4open( &cb, "CLASSES" ) ;

	enrollTag = d4tag( enroll, "C_CODE_TAG" ) ;
	codeTag = d4tag( master, "CODE_TAG" ) ;

	MasterRelation = relate4init( master ) ;
	relation1 = relate4createSlave( MasterRelation, enroll, "CODE", enrollTag ) ;

	relate4type( relation1, relate4scan ) ;

	classCode = d4field( master, "CODE" ) ;
	classTitle = d4field( master, "TITLE" ) ;
	enrollStudentId = d4field( enroll, "STU_ID_TAG") ;

	error4exitTest( &cb ) ;

	seekMaster( master, relation1, codeTag, "MATH521" ) ;
	printf( "%s ", f4str( enrollStudentId ) ) ;
	printf( "%s ", f4str( classCode ) ) ;
	printf( "%s\n", f4str(classTitle ) ) ;

	relate4free( MasterRelation, 1 ) ;
	code4initUndo( &cb ) ;
}

