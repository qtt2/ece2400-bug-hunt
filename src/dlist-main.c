#include <stdlib.h>
#include <stdio.h>

#include "dlist.h"

#define SIZE 10

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

  srand( 0xdeadbeef );

  dlist_int_t my_list;
  int         ref_arr[ SIZE ];

  dlist_construct( &my_list );

  for ( size_t i = 0; i < SIZE; ++i ) {
    ref_arr[ i ] = rand() % 1000;
    dlist_push_back( &my_list, ref_arr[ i ] );
  }

  // Call my sort function

  dlist_sort( &my_list );

  // Call qsort on ref_arr

  qsort( ref_arr, SIZE, sizeof( int ), compare );

  // Verify

  for ( size_t i = 0; i < SIZE; ++i ) {
    if ( ref_arr[ i ] != dlist_at( &my_list, i ) ) {
      printf("FAILED at i = %d: %d != %d\n", i, ref_arr[ i ], dlist_at( &my_list, i ) );
      return 1;
    }
  }

  printf("Verified!\n");

  dlist_destruct( &my_list );

  return 0;
}
