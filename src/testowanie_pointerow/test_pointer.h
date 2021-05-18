/*
 * test_pointer.h
 *
 *  Created on: May 14, 2021
 *      Author: anana
 */

#ifndef TESTOWANIE_POINTEROW_TEST_POINTER_H_
#define TESTOWANIE_POINTEROW_TEST_POINTER_H_

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>

bool isPointerBad( void * p )
{
   int fh = open( p, 0, 0 );
   int e = errno;

   if ( -1 == fh && e == EFAULT )
   {
      printf( "ERROR pointer: %p\n", p );
      return true;
   }
   else if ( fh != -1 )
   {
      close( fh );
   }

   printf( "OK pointer: %p\n", p );
   return false;
}

int test_pointer()
{
	int *dana = malloc(10 * sizeof(*dana));

	int good = 4;
	isPointerBad( (int *)3 );
	isPointerBad( &good );
	isPointerBad( "/tmp/blah" );

	return 0;
}


#endif /* TESTOWANIE_POINTEROW_TEST_POINTER_H_ */
