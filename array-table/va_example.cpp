/* VA.C: The program below illustrates passing a variable
 * number of arguments using the following macros:
 *      va_start            va_arg              va_end
 *      va_list             va_dcl (UNIX only)
 */

#include <stdio.h>
#define ANSI            /* Comment out for UNIX version     */
#ifdef ANSI             /* ANSI compatible version          */
#include <stdarg.h>
int average( int first, ... );
#else                   /* UNIX compatible version          */
#include <varargs.h>
int average( va_list );
#endif

void main( void )
{
   /* Call with 3 integers (-1 is used as terminator). */
   printf( "Average is: %d\n", average( 2, 3, 4, -1 ) );

   /* Call with 4 integers. */
   printf( "Average is: %d\n", average( 5, 7, 9, 11, -1 ) );

   /* Call with just -1 terminator. */
   printf( "Average is: %d\n", average( -1 ) );
}

/* Returns the average of a variable list of integers. */
#ifdef ANSI             /* ANSI compatible version    */
int average( int first, ... )
{
   int count = 0, sum = 0, i = first;
   va_list marker;

   va_start( marker, first );     /* Initialize variable arguments. */
   while( i != -1 )
   {
      sum += i;
      count++;
      i = va_arg( marker, int);
   }
   va_end( marker );              /* Reset variable arguments.      */
   return( sum ? (sum / count) : 0 );
}
#else       /* UNIX compatible version must use old-style definition.  */
int average( va_alist )
va_dcl
{
   int i, count, sum;
   va_list marker;

   va_start( marker );            /* Initialize variable arguments. */
   for( sum = count = 0; (i = va_arg( marker, int)) != -1; count++ )
      sum += i;
   va_end( marker );              /* Reset variable arguments.      */
   return( sum ? (sum / count) : 0 );
}
#endif
