/* f4int.c (c)Copyright Sequiter Software Inc., 1988-1998.  All rights reserved. */

#include "d4all.h"
#ifndef S4UNIX
   #ifdef __TURBOC__
      #pragma hdrstop
   #endif
#endif

#ifndef S4OFF_WRITE
void S4FUNCTION f4assignInt( FIELD4 *field, const int iValue )
{
   CODE4 *c4 ;

   #ifdef S4VBASIC
      if ( c4parm_check( field, 3, E90514 ) )
         return ;
   #endif

   #ifdef E4PARM_HIGH
      if ( field == 0 )
      {
         error4( 0, e4parm_null, E90514 ) ;
         return ;
      }
      switch( field->type )
      {
         case r4date:
         case r4log:
         case r4memo:
         case r4gen:
         #ifdef S4CLIENT_OR_FOX
            case r4dateTime:
            case r4system:
            case r4memoBin:
         #endif
            error4( field->data->codeBase, e4parm, E81409 ) ;
            return ;
         default:
            break ;
      }
   #endif

   #ifdef E4ANALYZE
      if ( field->data == 0 )
      {
         error4( 0, e4struct, E90514 ) ;
         return ;
      }
      if ( field->data->codeBase == 0 )
      {
         error4( 0, e4struct, E90514 ) ;
         return ;
      }
   #endif

   c4 = field->data->codeBase ;

   if ( error4code( c4 ) < 0 )
      return ;

   #ifndef S4SERVER
      #ifndef S4OFF_ENFORCE_LOCK
         if ( c4->lockEnforce && field->data->recNum > 0L )
            if ( d4lockTest( field->data, field->data->recNum ) != 1 )
            {
               error4( c4, e4lock, E90514 ) ;
               return ;
            }
      #endif
   #endif

   switch( field->type )
   {
      case r4int:
         #ifdef S4BYTE_SWAP
            *((S4LONG *)f4assignPtr( field )) = x4reverseLong(&iValue) ;
         #else
            *((int *)f4assignPtr( field )) = iValue ;
         #endif
         break ;
      #ifdef S4CLIENT_OR_FOX
         case r4currency:
         case r4double:
            f4assignDouble( field, (double)iValue ) ;
         break ;
      #endif
      default:
         if ( field->dec == 0 )
            c4ltoa45( (long)iValue, f4assignPtr( field ), field->len ) ;
         else
            f4assignDouble( field, (double)iValue ) ;
         break ;
   }
}
#endif

int S4FUNCTION f4int( const FIELD4 *field )
{
   #ifdef S4CLIENT_OR_FOX
      const char *ptr ;
   #endif
   #ifdef S4BYTE_SWAP
      S4LONG rcLong ;
   #endif
   #ifdef S4VBASIC
      if ( c4parm_check( field, 3, E90515 ) )
         return -1 ;
   #endif

   #ifdef E4PARM_HIGH
      if ( field == 0 )
      {
         error4( 0, e4parm, E90515 ) ;
         return -1 ;
      }
      switch( field->type )
      {
         case r4date:
         case r4log:
         case r4memo:
         case r4gen:
         #ifdef S4CLIENT_OR_FOX
            case r4dateTime:
            case r4system:
            case r4memoBin:
         #endif
            error4( field->data->codeBase, e4parm, E81409 ) ;
            return -1 ;
         default:
            break ;
      }
   #endif

   if ( error4code( field->data->codeBase ) < 0 )
      return -1 ;

   /* Convert the field data into an 'int' */
   switch( field->type )
   {
      case r4int:
         #ifdef S4BYTE_SWAP
            rcLong = x4reverseLong(f4ptr(field)) ;
            return (int)rcLong ;
         #else
            return *((int *)f4ptr( field )) ;
         #endif
      #ifdef S4CLIENT_OR_FOX
         case r4double:
            return (int)(*((double *)f4ptr( field ))) ;
         case r4currency:
            ptr = f4currency( field, 0 ) ;
            return c4atoi( ptr, strlen( ptr ) ) ;
      #endif
      default:
         return c4atoi( f4ptr( field ), field->len ) ;
   }
}
