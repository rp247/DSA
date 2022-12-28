/*
 * Ruchit Patel
 * rpatel18
 * pa2
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"

#define ERROR 1

// structs 

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj {
	int data;
	Node prev;
	Node next;
} NodeObj;

// private ListObj type
typedef struct ListObj {
	int length;
	int index;
	Node front;
	Node back;
	Node cursor;
} ListObj;

// Constructors-Destructors 

// newNode()
// Creates and returns a new empty Node.
Node newNode(int data) {
	Node N = (Node) malloc(sizeof(NodeObj));

	if (N) {
		N->data = data;
		N->prev = NULL;
		N->next = NULL;	
	}

	return N;
}

// freeNode()
// Frees all heap memory associated with *pN, and sets *pN to NULL.
void freeNode(Node *pN) {

	if (pN && *pN) {
		free(*pN);
		*pN = NULL;
	}

	return;
}

// newList()
// Creates and returns a new empty List.
List newList(void) {
	List L = (List) malloc(sizeof(ListObj));

	if (L) {
		L->front = NULL;
		L->back = NULL;
		L->cursor = NULL;
		L->length = 0;
		L->index = -1;
	}

	return L;
}

// freeList()
// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List* pL) {
	if (pL && *pL && (*pL)->length > 0) {
		// free dll
		Node curr = (*pL)->front;
		Node temp;
		int len = (*pL)->length;

		while (len > 0) {
			temp = curr->next;
			freeNode(&curr);
			curr = temp;
			len--;
		}

	}

	free(*pL);
	*pL= NULL;
	
	return;
}

// Access functions

// length()
// Returns the number of elements in L.
int length(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling getLength() on NULL List reference.\n");
		exit(ERROR);
	}
	return L->length;
}	

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling index() on NULL List reference.\n");
		exit(ERROR);
	}
	// return L->cursor ? L->index : -1;
	return L->index;
}	

// front()
// Returns front element of L. Pre: length()>0
int front(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling front() on NULL List reference.\n");
		exit(ERROR);
	}

	if (L->length == 0) {
		fprintf(stderr, "List Error: calling front() on list with length 0.\n");
		exit(ERROR);
	}
	
	return L->front->data;
}	

// back()
// Returns back element of L. Pre: length()>0
int back(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling back() on NULL List reference.\n");
		exit(ERROR);
	}

	if (L->length == 0) {
		fprintf(stderr, "List Error: calling back() on list with length 0.\n");
		exit(ERROR);
	}
	
	return L->back->data;
}

// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling get() on NULL List reference.\n");
		exit(ERROR);
	}

	if (L->index == -1 || L->length == 0) {
		fprintf(stderr, "List Error: calling get() on list with no cursor.\n");
		exit(ERROR);
	}

	return L->cursor->data;
}	

// equals()
// Returns true iff Lists A and B are in same state, and returns false otherwise.
bool equals(List A, List B) {
	if (!A || !B) {
		fprintf(stderr, "List Error: calling equals() on a NULL List reference.\n");
		exit(ERROR);
	}

	if (A->length != B->length) return false;

	Node tempOne = A->front, tempTwo = B->front;

	while (tempOne != NULL) {
		if (tempOne->data != tempTwo->data) return false; 
		tempOne = tempOne->next; tempTwo = tempTwo->next;
	}	

	return true;
}	

// Manipulation procedures

// clear()
// Resets L to its original empty state.
void clear(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling clear() on NULL List reference.\n");
		exit(ERROR);
	}

	// basically delete but without freeing the list 
	Node curr = L->front;
	Node temp;
	int len = L->length;

	while (len > 0) {
		temp = curr->next;
		freeNode(&curr);
		curr = temp;
		len--;
	}

	// reset to original state
	L->front = L->cursor = L->back = NULL;
	L->length = 0; L->index = -1;

	return;
}	

// set()
// Overwrites the cursor element’s data with x. Pre: length()>0, index()>=0
void set(List L, int x) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling set() on NULL List reference.\n");
		exit(ERROR);
	}

	if (L->length == 0 || L->index == -1) {
		fprintf(stderr, "List Error: calling set() with undefined cursor.\n");
		exit(ERROR);
	}

	L->cursor->data = x;
	return;
}

// moveFront()
// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling moveFront() on NULL List reference.\n");
		exit(ERROR);
	}
	
	if (L->length > 0) {
		L->cursor = L->front;
		L->index = 0;
	}

	return;
}

// moveBack()
// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling moveBack() on NULL List reference.\n");
		exit(ERROR);
	}
	
	if (L->length > 0) {
		L->cursor = L->back;
		L->index = L->length - 1; // the index of last element
	}

	return;
}

// movePrev()
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling movePrev() on NULL List reference.\n");
		exit(ERROR);
	}
	
	// if cursor is defined
	if (L->cursor != NULL) {
		// if cursor is not at the front
		if(L->index != 0) {
			L->cursor = L->cursor->prev;
			L->index--;
		}

		// if cursor is at the front
		else {
			L->cursor = NULL;
			L->index = -1;
		}

	}

	return;
}

// moveNext()
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling moveNext() on NULL List reference.\n");
		exit(ERROR);
	}
	
	// if cursor is defined
	if (L->cursor != NULL) {
		// if cursor is not at the back
		if(L->index != L->length - 1) {
			L->cursor = L->cursor->next;
			L->index++;
		}

		// if cursor is at the back
		else {
			L->cursor = NULL;
			L->index = -1;
		}

	}

	return;
}

// prepend()
// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int x) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling prepend() on NULL List reference.\n");
		exit(ERROR);
	}

	Node N = newNode(x);
	
	if (N) {
		L->index++;	// cursor element moved up, so update the position

		// if L is non-empty
		if (L->length != 0) {
			// prepend N
			L->front->prev = N;
			N->next = L->front;
			L->front = N;
		}

		// L's empty
		else {
			L->front = L->back = N;
		}

		L->length++;
	}

	return;
}

// append()
// Insert new element into L. If L is non-empty, insertion takes place after back element.
void append(List L, int x) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling append() on NULL List reference.\n");
		exit(ERROR);
	}

	Node N = newNode(x);
	
	if (N) {
		// if L is non-empty
		if (L->length != 0) {
			// prepend N
			L->back->next = N;
			N->prev = L->back;
			L->back = N;
			}

		// L's empty
		else {
			L->front = L->back = N;
		}

		L->length++;
	}

	return;
}

// insertBefore()
// Insert new element before cursor. Pre: length()>0, index()>=0
void insertBefore(List L, int x) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling insertBefore() on NULL List reference.\n");
		exit(ERROR);
	}

	if (L->length == 0 || L->index == -1) {
		fprintf(stderr, "List Error: calling insertBefore() with undefined cursor or an empty list.\n");
		exit(ERROR);
	}


	// cursor not at front
	if (L->index != 0) {
		Node N = newNode(x);
		if (N) {
			N->prev = L->cursor->prev;
			N->next = L->cursor;
			L->cursor->prev = N;
			N->prev->next = N;
			L->length++;
			L->index++;
		}
	}

	else {
		prepend(L, x);		// if at front then just prending works
	}


	return;
}	

// insertAfter()
// Insert new element after cursor. Pre: length()>0, index()>=0
void insertAfter(List L, int x) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling insertAfter() on NULL List reference.\n");
		exit(ERROR);
	}

	if (L->length == 0 || L->index == -1) {
		fprintf(stderr, "List Error: calling inserAfter() with undefined cursor or an empty list.\n");
		exit(ERROR);
	}


	// cursor not at back
	if (L->index != L->length -1) {
		Node N = newNode(x);
		if (N) {
			N->next = L->cursor->next;
			N->prev = L->cursor;
			N->next->prev = N;
			L->cursor->next = N;
			L->length++;
		}
	}

	else {
		append(L, x);		// if at back then just appending works
	}


	return;
}

// deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling deleteFront() on NULL List reference.\n");
		exit(ERROR);
	}

	if (L->length == 0) {
		fprintf(stderr, "List Error: calling deleteFront() on an empty list.\n");
		exit(ERROR);
	}

	// only one element in list
	if (L->length == 1) {
		freeNode(&(L->front));
		L->back = NULL;
	}
	
	// more than one elements
	else {
		L->front = L->front->next;
		freeNode(&(L->front->prev));
	}

	L->length--;
	if (L->index != -1) L->index--;		// if index is at front, then makes it undefined. 
						// if it was already undefined, then does nothing.
	

	return;
}

//deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling deleteBack() on NULL List reference.\n");
		exit(ERROR);
	}

	if (L->length == 0) {
		fprintf(stderr, "List Error: calling deleteBack() on an empty list.\n");
		exit(ERROR);
	}

	// only one element in list
	if (L->length == 1) {
		freeNode(&(L->back));
		L->front = NULL;
	}
	
	// more than one elements
	else {
		L->back = L->back->prev;
		freeNode(&(L->back->next));
	}

	if (L->index == L->length - 1) L->index = -1;		// if last element was cursor, make it undefined, else do nothing.
	L->length--;			
	return;
}

// delete()
// Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
void delete(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling delete() on NULL List reference.\n");
		exit(ERROR);
	}

	if (L->length == 0 || L->index == -1) {
		fprintf(stderr, "List Error: calling delete() with undefined cursor or an empty list.\n");
		exit(ERROR);
	}

	// cursor at front, deleteFront
	if (L->index == 0) {
		deleteFront(L);
	}
	
	// cursor at end, deleteBack
	else if (L->index == L->length - 1) {
		deleteBack(L);
	}

	else {
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
		freeNode(&(L->cursor));
		L->length--;
		L->index = -1;
	}

	return;
}

// Other operations

// printList()
// Prints to the file pointed to by out, a string representation of L consisting
// of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L) {
	if (L && L->length > 0) {
		Node temp = L->front;

		while (temp != NULL) {
			fprintf(out, "%d ", temp->data);
			temp = temp->next;
		}

		//fprintf(out, "\n");
	}
}

// copyList()
// Returns a new List representing the same integer sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state of L is unchanged
List copyList(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling delete() on NULL List reference.\n");
		exit(ERROR);
	}

	List newL = newList();

	if (newL) {
		Node temp = L->front;
		while (temp != NULL) {
			append(newL, temp->data);	// append elems of L into newL one by one
			temp = temp->next;
		}
	}

	return newL;
}

// concatList()
// Returns a new List which is the concatenation of A and B. The cursor in the new list is undefined,
// regardless of the states of the cursors in A and B.
List concatList(List A, List B) {

	if (A == NULL || B == NULL) {
		fprintf(stderr, "List Error: calling delete() on NULL List reference.\n");
		exit(ERROR);
	}

	List newL = newList();

	if (newL) {
		// copy A, append
		Node temp = A->front;
		while (temp != NULL) {
			append(newL, temp->data);
			temp = temp->next;
		}

		// copy B, append
		temp = B->front;
		while (temp != NULL) {
			append(newL, temp->data);
			temp = temp->next;
		}
	}

	return newL;
}
