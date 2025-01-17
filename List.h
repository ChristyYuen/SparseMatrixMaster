#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

#include <stdio.h>
#include <stdlib.h>

typedef struct ListObj* List;

//Constructor
List newList(void);

//Destructor
void freeList(List* pL);

//Access Function (Getter)
int length(List L);
int index(List L);
void* front(List L);
void* back(List L);
void* get(List L);
//int equals(List A, List B);

//Manipulation procedures (Setter)
void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, void* data);
void append(List L, void* data);
void insertBefore(List L, void* data);
void insertAfter(List L, void* data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

// Other operations 
//void printList(FILE* out, List L);
//List copyList(List L);

#endif 
