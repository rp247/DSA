/*
 * Ruchit Patel
 * rpatel18
 * pa4
 */

#include <stdio.h>
#include <stdlib.h>

#include "List.h"

int main() {
	List L = newList();
	List L2 = newList();

	typedef struct entryObj {
		int col;
		double val;
	} entryObj;

	typedef entryObj *entry;

	entry e_1 = malloc(sizeof(entryObj)); e_1->col = 1; e_1->val = 1.0;
	entry e_2 = malloc(sizeof(entryObj)); e_2->col = 2; e_2->val = 2.0;
	entry e_3 = malloc(sizeof(entryObj)); e_3->col = 3; e_3->val = 3.0;
	entry e_4 = malloc(sizeof(entryObj)); e_4->col = 4; e_4->val = 4.0;
	entry e_5 = malloc(sizeof(entryObj)); e_5->col = 5; e_5->val = 5.0;
	entry e_6 = malloc(sizeof(entryObj)); e_6->col = 6; e_6->val = 6.0;



	// prepend
	prepend(L, e_1);

	// append
	append(L, e_2);

	// moveBack
	moveBack(L);

	// set
	set(L, e_3);

	// moveFront
	moveFront(L);
	set(L, e_2);

	prepend(L, e_1);		// 1-2-3, back to og state

	append(L, e_5);			// 1-2-3-5

	moveBack(L);
	movePrev(L);
	moveNext(L);

	// insertBefore
	insertBefore(L, e_4);		// 1-2-3-4-5

	moveBack(L);

	// insertAfter
	insertAfter(L, e_6);		// 1-2-3-4-5-6

	// deleteFront
	deleteFront(L);

	// deleteBack
	deleteBack(L);			// 2-3-4-5

	// delete
	moveFront(L);
	moveNext(L);
	delete(L);			// 2-4-5

	// concatList
	append(L2, e_6);
	List L3 = concatList(L, L2);	// 2-4-5-6

	// access

	entry e;
	
	// length
	printf("L3 length: %d.\n", length(L3));	// 4

	// index
	printf("L3 index: %d.\n", index(L3));	// -1

	// front
	e = front(L3);
	printf("L3 front: {%d, %lf}.\n", e->col, e->val);	// {2, 2.0}

	// back
	e = back(L3);
	printf("L3 back: {%d, %lf}.\n", e->col, e->val);	// invalid

	// get
	moveBack(L3);
	e = get(L3);
	printf("L3 get: {%d, %lf}.\n", e->col, e->val);	// invalid
	
	/* test later */
	//clear(L3);
	printf("L3 length: %d.\n", length(L3));	// 0

	/* test later */
	//freeList(&L);
	//freeList(&L2);
	//freeList(&L3);
}
