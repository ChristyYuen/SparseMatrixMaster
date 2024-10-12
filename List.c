#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include <stdbool.h>
//based on Queue.c 

// private NodeObj type
typedef struct NodeObj
{
   void* data;
   struct NodeObj* next;
   struct NodeObj* prev;
}NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj
{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
}ListObj;

//Makes a newNode
Node newNode(void* data)
{
   Node N = NULL;
   N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = N->prev = NULL;
   return(N);
}

void freeNode(Node* pN) 
{
   if(pN != NULL && *pN != NULL) 
   {
      free(*pN);
      *pN = NULL;
   }
}

// Creates and returns a new empty List
List newList()
{
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}

// Frees all heap memory associated with *pL, and sets
// *pL to NULL.
void freeList(List* pL)
{
   if(pL != NULL && *pL != NULL)
   {
      clear(*pL);
      free(*pL);
      *pL = NULL;
   }
}

// Returns the number of elements in L.
int length(List L)
{
   if(L == NULL)
   {
      printf("List Error: calling length() on NULL List reference\n");
      exit(1);
   }
   return (L->length);
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L)
{
   if(L == NULL)
   {
      printf("List Error: calling index() on NULL List reference\n");
      exit(1);
   }
   return (L->index);
}

// Returns front element of L. Pre: length()>0
void* front(List L) 
{
   if(L == NULL)
   {
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
   }
   if(L->length < 1)
   {
      printf("List Error: calling front() on empty List reference\n");
      exit(1);
   }
   return (L->front->data);
}

// Returns back element of L. Pre: length()>0
void* back(List L)
{
   if(L == NULL)
    {
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   if(L->length < 1)
   {
      printf("List Error: calling back() on empty List reference\n");
      exit(1);
   }
   return (L->back->data);
}

// Returns cursor element of L. Pre: length()>0, index()>=0
void* get(List L)
{
   if(L == NULL)
    {
      printf("List Error: calling get() on NULL List reference\n");
      exit(1);
   }
   if(L->index < 0)
   {
      printf("List Error: calling get() with an undefined index on List\n");
      exit(1);
   }
   if(L->length < 1)
   {
      printf("List Error: calling get() on empty List reference\n");
      exit(1);
   }
   return (L->cursor->data);
}

// Returns true (1) iff Lists A and B are in same
 // state, and returns false (0) otherwise.
/*
int equals(List A, List B)
{
   int equal = 1;
   if(A == NULL || B == NULL)
   {
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }
   if(A->length != B->length)
   {
      return (0);
   }

   //setting the current node to be in front to B->front
   Node BFront = B->front;
   Node AFront = A->front;
   while(BFront!=NULL && equal)
   {
      equal = (BFront->data==AFront->data);
      BFront = BFront->next;
      AFront = AFront->next;
   }
   return equal;
 
}
*/

// Manipulation procedures ----------------------------------------------------

// Resets L to its original empty state. 
void clear(List pL)
{
   while(pL->length!=0)
   {
      deleteBack(pL);
   }
   pL->length= 0;
   pL->index= -1;
}

// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L)
{
   if(L == NULL)
    {
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(1);
   }
   if(L->length > 0)
   {
      L->cursor = L->front;
      L->index = 0;
   }
}

// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L)
{
   if(L == NULL)
    {
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(1);
   }
   if(L->length > 0)
   {
      L->cursor = L->back;
      L->index = L->length-1;
   }
}

// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L)
{
   if(L == NULL)
    {
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(1);
   }
   if(L->cursor != NULL && L->index != -1)
   {
      L->cursor = L->cursor->prev;
      L->index--;
   }
}

// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L)
{
   if(L == NULL)
    {
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(1);
   }
   if(L->cursor != NULL && L->index != L->length - 1)
   {
      L->cursor = L->cursor->next;
      L->index++;
   }
   else if(L->cursor != NULL && L->index == L->length - 1)
   {
      L->cursor = NULL;
      L->index = -1;
   }
   if(L->length == L->index)
   {
      L->index = -1;
   }
}

// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, void* data)
{
   if(L == NULL)
    {
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(1);
   }
   Node N = newNode(data);
   if(L->length==0)
      L->front = L->back = N;
   else
   {
      L->front->prev = N;
      N->next = L->front;
      L->front = N;
   }
   L->length++;
   if(L->index>=0) 
   L->index++;
   }

// Insert new element into L. If L is non-empty,
 // insertion takes place after back element.
void append(List L, void* data)
{
   if(L == NULL)
   {
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
   }
   Node N = newNode(data);
   if(L->length==0)
      L->front = L->back = N;
   else
   {
      L->back->next = N;
      N->prev = L->back;
      L->back = N;
   }
   L->length++;
}

// Inserts new element after cursor.
// Pre: length()>0, index()>=0


void insertBefore(List L, void* data)
{
   if(L == NULL)
   {
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(1);
   }
   if(L->index < 0)
   {
      printf("List Error: calling insertAfter() on empty List reference\n");
      exit(1);
   }
   if(L->length < 1)
   {
      printf("List Error: calling insertAfter() on empty List reference\n");
      exit(1);
   }
   Node N = newNode(data);

   if(L->index == 0)   
   {
      L->front->prev = N;
      N->next = L->front;
      L->front = N;
   }
   else
   {
      N->next = L->cursor;
      N->prev = L->cursor->prev;
      L->cursor->prev->next = N;
      L->cursor->prev = N; //////////////
   }
   L->length++;
   L->index++;
}
// Insert new element before cursor.
// Pre: length() > 0, index() >= 0
void insertAfter(List L, void* data)
{
   if(L == NULL)
    {
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(1);
   }
   if(L->index < 0)
   {
      printf("List Error:");
      exit(1);
   }
   if(L->length < 1)
   {
      printf("List Error:");
      exit(1);
   }
   Node N = newNode(data);
   if(L->index==(L->length)-1)
   {
      L->back->next = N;
      N->prev = L->back;
      L->back = N;
   }
   else
   {
      N->prev = L->cursor;
      N->next = L->cursor->next;
      L->cursor->next->prev = N;
      L->cursor->next = N;
   }
   (L->length)++;
}

// Deletes the front element. Pre: length()>0
void deleteFront(List L)
{
   Node N = NULL;
   if(L == NULL)
    {
      printf("List Error: deleteFront() called on NULL List reference\n");
      exit(1);
   }
     if(L->length < 1)
   {
      printf("List Error: deleteFront() called on an empty List\n");
      exit(1);
   }
   if(index(L)==0)
   {
      L->cursor=NULL;
      L->index=-1;
   }
   if( (L->length)>=2){
      N = L->front;
      L->front = L->front->next;
      L->front->prev = NULL;
      if ((L->index)!= -1)
      L->index--;
   }else{
      N = L->front;
      L->front = L->back = NULL;
      (L->index) = -1;
   }
   L->length--;
   freeNode(&N);
   //N = NULL;
}

// Deletes the back elementt. Pre: length()>0
void deleteBack(List L)
{
	Node N = NULL;
   
   if(L == NULL)
    {
      printf("List Error: deleteBack() called on NULL List reference\n");
      exit(1);
   }
   if(L->length < 1)
   {
      printf("List Error: deleteBack() called on an empty List\n");
      exit(1);
   }
   if(L->index == (L->length)-1)
   {
      L->cursor = NULL;
      L->index=-1;
   }
   
   if(L->length>1)
   {
   	  N = L->back;
      L->back = L->back->prev;
      L->back->next = NULL;
   }
   else
   {
   	N = L->back;
   	L->front = L->back = NULL;
   }
  
   L->length--;
   freeNode(&N);
   N = NULL;
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L)
{
   if(L == NULL)
    {
      printf("List Error: delete() called on NULL List reference\n");
      exit(1);
   }
   if(L->length < 1)
   {
      printf("List Error: delete() called with an undefined index on List\n");
      exit(1);
   }
   if(L->index < 0)
   {
      printf("List Error: delete() called on empty List");
      exit(1);
   }
   if(L->cursor == L->back)
   {
      deleteBack(L);
   }
   else if(L->cursor == L->front)
   {
      deleteFront(L);
   }
   else
   {
      Node temp = L->cursor;
      L->cursor->prev->next = L->cursor->next;
      L->cursor->next->prev = L->cursor->prev;
      freeNode(&temp);
      L->cursor = NULL;
      L->length--;
   }
}

// Other Functions ------------------------------------------------------------

// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.

/*
void printList(FILE* out, List L)
{
   Node temp = L->front;
   while(temp != NULL)
    {
      printf("%d ", temp->data);
      temp = temp->next;
   }
}
*/


// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
/*
List copyList(List L)
{
   List t = newList();
   Node temp = L->front;
   while(temp != NULL)
    {
      append(t, temp->data);
      temp = temp->next;
   }
   return t;
}
*/
