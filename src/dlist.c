//========================================================================
// dlist.c
//========================================================================
// Baseline implementation of the dlist functions

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#include "dlist.h"

//------------------------------------------------------------------------
// dlist_print (helper function)
//------------------------------------------------------------------------
// Print out the metadata of the dlist_int_t

void dlist_print( dlist_int_t* this )
{
  // Print maxsize and size

  printf( "LIST: List has size: %zd\n", this->size );
  printf("\n");

  // Print data up to size

  printf("LIST: Size data:\n");

  node_t* current_node = this->head;

  for ( size_t i = 0; i < this->size; i++ ) {
    printf( "dlist[%zd] = %d\n", i, current_node->value );
    current_node = current_node->next;
  }

  printf("\n");
}

//------------------------------------------------------------------------
// dlist_construct
//------------------------------------------------------------------------
// Construct the dlist_int_t and initialize the fields inside

void dlist_construct( dlist_int_t* this )
{

  // Constructing a dlist_int_t involves initializing with a NULL head node and
  // initializing other fields

  this->head  = NULL;
  this->tail  = NULL;
  this->size  = 0;
}

//------------------------------------------------------------------------
// dlist_destruct
//------------------------------------------------------------------------
// Destruct the dlist_int_t, freeing any dynamically allocated memory if
// necessary

void dlist_destruct( dlist_int_t* this )
{
  node_t* current_node = this->head;

  while ( current_node != NULL ) {
    node_t* next_node = current_node->next;
    free( current_node );
    current_node = next_node;
  }
}

//------------------------------------------------------------------------
// dlist_at
//------------------------------------------------------------------------
// Pointer chase and return the value at the given index
// If the index is out of bound, then return 0

int dlist_at( dlist_int_t* this, size_t idx )
{
  // Return 0 if idx is out of bound

  if ( idx >= this->size ) return 0;

  node_t* current_node = this->head;

  for ( size_t i = 0; i < idx; i++ ) {
    current_node = current_node->next;
  }

  return current_node->value;
}

//------------------------------------------------------------------------
// dlist_find
//------------------------------------------------------------------------
// Search the dlist for a value and return whether a value is found or not.
// Returning 1 means found, and 0 means not found.

int dlist_find( dlist_int_t* this, int value )
{

  // We could use the dlist_at() function to search, but this will restart
  // the access from the head node on each iteration. Instead, we make a
  // single pass through the dlist and search each node for the value.

  node_t* current_node = this->head;

  while ( current_node != NULL ) {
    if ( current_node->value == value ) return 1;
    current_node = current_node->next;
  }

  // Not found

  return 0;
}

//------------------------------------------------------------------------
// dlist_push_back
//------------------------------------------------------------------------
// Push a new value into the dlist_int_t

void dlist_push_back( dlist_int_t* this, int value )
{
  node_t* new_node = malloc( sizeof(node_t) );

  assert( new_node != NULL && "Could not malloc!" );

  // Set the fields in the new node

  new_node->next  = NULL;
  new_node->prev  = NULL;
  new_node->value = value;

  // Push new node into the dlist. If the dlist is not empty (i.e., if the tail
  // is not NULL), then we update pointers and make the new node the new
  // tail. If the dlist is empty (i.e., if the tail is NULL), then we make
  // the new node the head and also the tail.

  if ( this->tail != NULL ) {
    this->tail->next  = new_node;
    new_node->prev    = this->tail;
    this->tail        = new_node;
  } else {
    this->head        = new_node;
    this->tail        = new_node;
  }

  this->size++;
}

//------------------------------------------------------------------------
// dlist_swap_nodes
//------------------------------------------------------------------------
// Swap two nodes in a linked list

void dlist_swap_nodes( dlist_int_t* this, node_t* node_1, node_t* node_2 )
{

  // Two nodes are the same, nothing to do here

  if ( node_1 == node_2 )
    return;

  node_t* p_node_1  = node_1->prev;
  node_t* n_node_1  = node_1->next;

  node_t* p_node_2  = node_2->prev;
  node_t* n_node_2  = node_2->next;

  if        ( n_node_1 == node_2 ) {

    // node_1 <-> node_2 (right next to each other)

    node_1->next = node_2->next;
    node_2->prev = node_1->prev;

    node_2->next = node_1;
    node_1->prev = node_2;

    if ( p_node_1 ) {
      p_node_1->next  = node_2;
    } else {
      this->head      = node_2;
    }

    if ( n_node_2 ) {
      n_node_2->prev  = node_1;
    } else {
      this->tail      = node_1;
    }

  } else if ( n_node_2 == node_1 ) {

    // node_2 <-> node_1 (right next to each other)

    node_2->next = node_1->next;
    node_1->prev = node_2->prev;

    node_1->next = node_2;
    node_2->prev = node_1;

    if ( p_node_2 ) {
      p_node_2->next  = node_1;
    } else {
      this->head      = node_1;
    }

    if ( n_node_1 ) {
      n_node_1->prev  = node_2;
    } else {
      this->tail      = node_2;
    }

  } else {

    // node_1 <-> ... some nodes ... <-> node_2
    // node_2 <-> ... some nodes ... <-> node_1

    if ( p_node_1 ) {
      p_node_1->next  = node_2;
      node_2->prev    = p_node_1;
    } else {
      this->head      = node_2;
      node_2->prev    = NULL;
    }

    if ( n_node_1 ) {
      n_node_1->prev  = node_2;
      node_2->next    = n_node_1;
    } else {
      this->tail      = node_2;
      node_2->next    = NULL;
    }

    if ( p_node_2 ) {
      p_node_2->next  = node_1;
      node_1->prev    = p_node_2;
    } else {
      this->head      = node_1;
      node_1->prev    = NULL;
    }

    if ( n_node_2 ) {
      n_node_2->prev  = node_1;
      node_1->next    = n_node_2;
    } else {
      this->tail      = node_1;
      node_1->next    = NULL;
    }

  }
}

//------------------------------------------------------------------------
// find_min
//------------------------------------------------------------------------
// Return a pointer to a node that has the minimum value between begin
// and end

node_t* find_min( node_t* begin, node_t* end )
{
  node_t* cur_node  = begin;
  int     min_value = INT_MAX;
  node_t* min_node  = begin;

  while ( cur_node != NULL ) {

    if ( cur_node->value < min_value ) {
      min_node  = cur_node;
      min_value = cur_node->value;
    }

    if ( cur_node == end ) {
      break;
    }

    cur_node = cur_node->next;
  }

  return min_node;
}

//------------------------------------------------------------------------
// dlist_sort
//------------------------------------------------------------------------
// Sort a given linked list in an ascending order

void dlist_sort( dlist_int_t* this )
{
  if ( this->size <= 1 )
    return;

  node_t* cur_node = this->head;

  while ( cur_node != NULL ) {

    // Find the min node
    node_t* min_node = find_min( cur_node, this->tail );
    assert( min_node );

    // Swap the cur_node and min_node
    dlist_swap_nodes( this, cur_node, min_node );

    // Advance cur_node
    cur_node = cur_node->next;
  }
}
