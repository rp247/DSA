/*
 * Ruchit Patel
 * rpatel18
 * pa2
 */

#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

#define ERR 1

int main(int argc, char *argv[]) {

	// correct number of arguments
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
		exit(ERR);
	}

	// opening files
	FILE *in = fopen(argv[1], "r");
	if (in == NULL) {
		fprintf(stderr, "Unable to open file %s for reading.\n", argv[1]);
		exit(ERR);
	}

	FILE *out = fopen(argv[2], "w");
	if (out == NULL) {
		fprintf(stderr, "Unable to open file %s for writing.\n", argv[2]);
		exit(ERR);
	}

	// get number of vertices
	int order;
	fscanf(in, "%d", &order);

	// read in edges
	Graph G = newGraph(order);
	int x, y, res = fscanf(in , "%d %d", &x, &y);
	while (res == 2 && (x!=0 && y!=0)) {		// loop till 0 0 or till we get 2 ints
		addEdge(G, x, y);
		res = fscanf(in , "%d %d", &x, &y);
	}

	// print the graph
	fprintf(out, "\n");
	printGraph(out, G);
	fprintf(out, "\n");


	// perform BFS
	res = fscanf(in, "%d %d", &x, &y);
	List L = newList();
	while (res == 2 && (x!=0 && y!=0)) {
		BFS(G, x);				// perform BFS from x to y
		getPath(L, G, y);			// get shortest path from x to y

		// path exists
		if (getDist(G, y) != -1) {		// getDist to chck bounds on y
			fprintf(out, "The distance from %d to %d is %d\n" \
				     "A shortest %d-%d path is: ", x, y, getDist(G, y), x, y);
			printList(out, L);
			fprintf(out, "\n\n");
		}
		
		// no path
		else {
			fprintf(out, "The distance from %d to %d is infinity\n" \
				     "No %d-%d path exists\n", x, y, x, y);
			fprintf(out, "\n\n");
		}

		clear(L);				// clear to create and add new path
		res = fscanf(in, "%d %d", &x, &y);	// read next edge
	}


	// free mem, close files
	freeList(&L);
	freeGraph(&G);
	fclose(in);
	fclose(out);

	return 0; // success :)
}
