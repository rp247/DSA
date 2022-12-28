/* Ruchit Patel
 * rpatel18
 * pa3
 */
#include <stdio.h>

#include "Graph.h"
#include "List.h"

int main() {
	// constructor test
	Graph G = newGraph(5);

	// print test
	printGraph(stdout, G);

	/* Graph:
	 * 1: 2 3 4 
	 * 2: 1 5
	 * 3: 1 4
	 * 4: 1 2
	 * 5: 1
	 */

	// addEdge test
	addEdge(G, 1, 2);
	addEdge(G, 1, 3);
	addEdge(G, 1, 4);
	
	// addArc test
	addArc(G, 2, 5);
	addArc(G, 3, 4);
	addArc(G, 4, 2);
	addArc(G, 5, 1);

	// Access tests
	printf("Order: %d\n", getOrder(G));
	printf("Size: %d\n", getSize(G));

	// print test
	printGraph(stdout, G);
	
	// BFS test
	BFS(G, 1);

	//getPath test
	List L = newList();
	getPath(L, G, 5);	// 1-2-5
	printList(stdout, L);
	printf("\n");

	//  destructor test
	freeGraph(&G);
	freeList(&L);

	return 0;
}
