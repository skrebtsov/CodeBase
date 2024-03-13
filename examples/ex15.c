#include "d4all.h"


#ifdef __TURBOC__
   extern unsigned _stklen = 10000;
#endif

CODE4 cb ;
DATA4 *data ;

int createFiles( )
{
   FIELD4INFO fields [] =
   {
      { "NAME", 'C', 20, 0 },
      { "AGE", 'N', 3, 0 },
      { "BIRTHDATE", 'D', 8, 0 },
      { 0, 0, 0, 0 },
   };

   TAG4INFO tags [] =
   {
      { "NAME_TAG", "NAME", 0, 0, 0 },
      { 0, 0, 0, 0, 0 },
   };

   cb.safety = 0 ; /* Turn off safety -- overwrite files*/
   data = d4create( &cb, "INFO1.DBF", fields, tags ) ;

   return cb.errorCode ;
}

void main()
{
   int rc ;

   code4init( &cb );

   rc = createFiles();

   code4initUndo( &cb ) ;
}
