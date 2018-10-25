//========================================================================
// dlist-test.c
//========================================================================
// This file contains the tests for the dlist-related functions

#include <stdio.h>
#include "utst.h"
#include "dlist.h"

//------------------------------------------------------------------------
// compare
//------------------------------------------------------------------------
// Compare two integers, returning 0 if equal, negative if a < b, and
// positive if a > b.
//
// This function is intended to be used with the standard library qsort().

int compare( const void* a_p, const void* b_p )
{
  int a = *(int*)a_p;
  int b = *(int*)b_p;

  if      ( a > 0 && b < 0 ) return  1;
  else if ( a < 0 && b > 0 ) return -1;
  else                       return ( a - b );
}

int main() {

  UTST_BEGIN();

  //------------------------------------------------------------------------
  // Basic Tests
  //------------------------------------------------------------------------
  // These are simple test cases to check that the most basic functionality
  // works correctly.
  //
  // Do not add any additional tests here.

  // Basic construct and destruct case

  UTST_TEST_LABEL( "Test dlist_construct and dlist_destruct" );

  {
    dlist_int_t mydlist;
    dlist_construct ( &mydlist );
    dlist_destruct  ( &mydlist );
  }

  // Basic push_back and get

  UTST_TEST_LABEL( "Test dlist_push_back and dlist_get" );

  {
    dlist_int_t mydlist;
    dlist_construct ( &mydlist );

    // Push data into the data structure

    dlist_push_back( &mydlist, 1 );

    // Access and test data

    UTST_ASSERT_INT_EQ( dlist_at( &mydlist, 0 ), 1 );

    // Test size

    UTST_ASSERT_INT_EQ( mydlist.size, 1 );

    dlist_destruct( &mydlist );
  }

  // Basic find

  UTST_TEST_LABEL( "Test dlist_find" );

  {
    dlist_int_t mydlist;
    dlist_construct ( &mydlist );

    // Push data into the data structure

    dlist_push_back( &mydlist, 1 );
    dlist_push_back( &mydlist, 2 );
    dlist_push_back( &mydlist, 3 );

    // Test find

    UTST_ASSERT_INT_EQ( dlist_find( &mydlist, 3 ), 1 );

    dlist_destruct( &mydlist );
  }

  // Basic sort

  UTST_TEST_LABEL( "Test dlist_sort" );

  {

    srand( 0xdeadbeef );

    const size_t  size = 1000;
    dlist_int_t   my_list;
    int           ref_arr[ size ];

    dlist_construct( &my_list );

    for ( size_t i = 0; i < size; ++i ) {
      ref_arr[ i ] = rand() % 1000;
      dlist_push_back( &my_list, ref_arr[ i ] );
    }

    // Call my sort function

    dlist_sort( &my_list );

    // Call qsort on ref_arr

    qsort( ref_arr, size, sizeof( int ), compare );

    // Verify

    for ( size_t i = 0; i < size; ++i ) {
      UTST_ASSERT_INT_EQ( ref_arr[ i ], dlist_at( &my_list, i ) );
    }

    dlist_destruct( &my_list );

  }

  UTST_END();

  return 0;
}
