//=========================================================================
// dlist.h
//=========================================================================
// Declarations for dlist

#ifndef DLIST_H
#define DLIST_H

typedef struct _node_t {
  int             value;
  struct _node_t* next;
  struct _node_t* prev;
}
node_t;

typedef struct {
  size_t  size;
  node_t* head;
  node_t* tail;
}
dlist_int_t;

void swap_nodes( dlist_int_t* this, node_t* node_1, node_t* node_2 );

void dlist_print     ( dlist_int_t* this );
void dlist_construct ( dlist_int_t* this );
void dlist_destruct  ( dlist_int_t* this );
void dlist_push_back ( dlist_int_t* this, int value );
int  dlist_at        ( dlist_int_t* this, size_t idx );
int  dlist_find      ( dlist_int_t* this, int value );
void dlist_sort      ( dlist_int_t* this );

#endif // DLIST_H
