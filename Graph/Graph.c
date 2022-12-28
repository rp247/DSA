/*
 * Ruchit Patel
 * rpatel18
 * pa2
 */

#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "List.h"

#define ERR 1

//structs
//private Graph type


typedef struct GraphObj* Graph;

typedef struct GraphObj {
	List *neighbors;		// array of lists
	int *color;			// array of colors
	int *parent;			// array of parents
	int *distance;			// array of distance from source
	int order;			// number of vertices
	int size;			// number of edges
	int source;			// most recently used vertex
} GraphObj;


// newGraph()
// Creates and returns a new empty Graph with n vertices. 
Graph newGraph(int n) {
	Graph G = (Graph) malloc(sizeof(GraphObj));

	if (G) {
		G->neighbors = (List *) malloc((n+1) * sizeof(List)); // n+1 for access ease
		G->color = (int *) malloc((n+1) * sizeof(int));
		G->parent = (int *) malloc((n+1) * sizeof(int));
		G->distance = (int *) malloc((n+1) * sizeof(int));
		G->order = n;
		G->size = 0;
		G->source = NIL;
	}

	// set the default values
	int i = 1;
	while (i < n+1) {
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->distance[i] = INF;
		G->neighbors[i] = newList();		// init empty lists
		i++;
	}	

	return G;
}


// freeGraph()
// Frees all heap memory associated with *pG, and sets *pG to NULL.
void freeGraph(Graph *pG) {

	if (pG && *pG) {
		free((*pG)->color);
		free((*pG)->parent);
		free((*pG)->distance);

		// free all lists
		int i = 1;
		while (i <= (*pG)->order) {
			freeList(&(*pG)->neighbors[i]);
			i++;
		}
		free((*pG)->neighbors);

		free(*pG);
		*pG = NULL;
	}

	return;
}


// getOrder()
// returns the order of the graph
int getOrder(Graph G) {

	if (G == NULL) {
		fprintf(stderr, "Graph Error: calling getOrder() on NULL Graph reference.\n");
		exit(ERR);
	}

	return G->order;
}


// getSize()
// returns the size of the graph
int getSize(Graph G) {

	if (G == NULL) {
		fprintf(stderr, "Graph Error: calling getSize() on NULL Graph reference.\n");
		exit(ERR);
	}

	return G->size;
}


// getSource()
// returns the source of the graph
int getSource(Graph G) {

	if (G == NULL) {
		fprintf(stderr, "Graph Error: calling getSource() on NULL Graph reference.\n");
		exit(ERR);
	}

	return G->source;
}


// getParent()
// returns the parent of vertex u in BF tree or NIL if BFS() has not been called yet. 
// Pre: u is in range [1, getOrder(G)]. 
int getParent(Graph G, int u) {

	if (G == NULL) {
		fprintf(stderr, "Graph Error: calling getParent() on NULL Graph reference.\n");
		exit(ERR);
	}

	// vertex range : [1, order(G)]
	if (u < 1 || u > G->order) {
		fprintf(stderr, "Graph Error: calling getParent() with vertex out of range.\n");
		exit(ERR);
	}

	return G->parent[u];
}


// getDist()
// returns the distance from most recent BFS source to vertex u or INF if BFS() has not been called yet. 
// Pre: u is in range [1, getOrder(G)]. 
int getDist(Graph G, int u) {

	if (G == NULL) {
		fprintf(stderr, "Graph Error: calling getDist() on NULL Graph reference.\n");
		exit(ERR);
	}

	// vertex range : [1, order(G)]
	if (u < 1 || u > G->order) {
		fprintf(stderr, "Graph Error: calling getDist() with vertex out of range.\n");
		exit(ERR);
	}

	return G->source == NIL ? INF : G->distance[u];		// no source then INF, else distance
}


// getPath()
// appends to list vertices of shortest past from source to u, or appends NIL if no such path exists. 
// Pre: getSource(G) != NIL, u is in range [1, getOrder(G)] 
// Pseudocode from GraphAlgorithms pdf
void getPath(List L, Graph G, int u) {

	if (G == NULL) {
		fprintf(stderr, "Graph Error: calling getPath() on NULL Graph reference.\n");
		exit(ERR);
	}

	if (L == NULL) {
		fprintf(stderr, "List Error: calling getPath() on NULL List reference.\n");
		exit(ERR);
	}

	// vertex range : [1, order(G)]
	if (u < 1 || u > G->order) {
		fprintf(stderr, "Graph Error: calling getPath() with vertex out of range.\n");
		exit(ERR);
	}

	if (G->source == NIL) {
		fprintf(stderr, "Graph Error: calling getPath() with NIL source.\n");
		exit(ERR);
	}

	// we just need to append parent as BFS would have already found the shortest path

	// reached source. path complete.
	if (u == G->source) {
		append(L, u);				// from ModelGraphTest it seems test 2 it seems apparent we need to append if u == source, rest of code is 
							// such that it would correctly implement the order given this base condition
	}

	// no path exists between source and u. parent == null.
	else if (G->parent[u] == NIL) {
		append(L, NIL);
	}

	else {
		getPath(L, G, G->parent[u]);		
		append(L, u);				// prepend each parent and do the same again
	}

	return;
}


// makeNull()
// deletes all edges of G, restoring to its original (no edge) state.
void makeNull(Graph G) {

	if (G == NULL) {
		fprintf(stderr, "Graph Error: calling makeNull() on NULL Graph reference.\n");
		exit(ERR);
	}

	int i = 1;
	while (i <= G->order) {
		G->color[i] = WHITE;
		G->distance[i] = NIL;
		G->parent[i] = INF;
		clear(G->neighbors[i]);		// clear the list as well
		i++;
	}
	G->size = 0;
	G->source = NIL;

	return;
}


// addEdge()
// inserts a new edge joining u to v. 
// Pre: u and v are in range [1, getOrder(G)].
void addEdge(Graph G, int u, int v) {

	if (G == NULL) {
		fprintf(stderr, "Graph Error: calling addEdge() on NULL Graph reference.\n");
		exit(ERR);
	}

	// vertex range : [1, order(G)]
	if ((u < 1 || u > G->order) || (v < 1 || v > G->order)) {
		fprintf(stderr, "Graph Error: calling addEdge() with vertex out of range.\n");
		exit(ERR);
	}

	// find an appropriate spot for u in v's neighbors list and viceversa
	// same algorithm as used in pa1 Lex.c, see that file for more details

	// adding v to u
	List L = G->neighbors[u];
	moveBack(L);
	while(index(L) >= 0 && v < get(L)) {
		movePrev(L);		// move cursor for next comparison
	}
	if (index(L) < 0) prepend(L, v); // cursor becomes undefined. need to prepend (the smallest element)
	else insertAfter(L, v); 	// found place after cursor

	// adding u to v
	L = G->neighbors[v];
	moveBack(L);
	while(index(L) >= 0 && u < get(L)) {
		movePrev(L);		// move cursor for next comparison
	}
	if (index(L) < 0) prepend(L, u); // cursor becomes undefined. need to prepend (the smallest element)
	else insertAfter(L, u); 	// found place after cursor

	G->size++;			// update the size

	return;
}


// addArc()
// inserts a new directed edge from u to v.
// Pre: u and v are in range [1, getOrder(G)].
void addArc(Graph G, int u, int v) {

	if (G == NULL) {
		fprintf(stderr, "Graph Error: calling addArc() on NULL Graph reference.\n");
		exit(ERR);
	}

	// vertex range : [1, order(G)]
	if ((u < 1 || u > G->order) || (v < 1 || v > G->order)) {
		fprintf(stderr, "Graph Error: calling addArc() with vertex out of range.\n");
		exit(ERR);
	}

	// adding v to u
	List L = G->neighbors[u];
	moveBack(L);
	while(index(L) >= 0 && v < get(L)) {
		movePrev(L);		// move cursor for next comparison
	}
	if (index(L) < 0) prepend(L, v); // cursor becomes undefined. need to prepend (the smallest element)
	else insertAfter(L, v); 	// found place after cursor
	G->size++;			// update the size

	return;
}


// BFS()
// runs BFS on G's source s
// pseudo code credits: provided in GraphAlgorithms.pdf
void BFS(Graph G, int s) {

	if (G == NULL) {
		fprintf(stderr, "Graph Error: calling BFS() on NULL Graph reference.\n");
		exit(ERR);
	}

	if (s < 1 || s > G->order){
		fprintf(stderr, "Graph Error: calling BFS() with vertex out of range.\n");
		exit(ERR);
	}


	G->source = s;			// source of G is s
	
	// undiscover everything else
	for (int i = 0; i <= G->order; i++) {
		G->color[i] = WHITE;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}

	// discover the source
	G->color[s] = GRAY;
	G->distance[s] = 0;
	G->parent[s] = NIL;

	List L = newList();		// List for adding neighbors
	int x, y, len;
	
	append(L, s);
	while (length(L) != 0) {
		x = front(L); deleteFront(L);

		// traverse the neighbors list
		moveFront(G->neighbors[x]);
		
		len = length(G->neighbors[x]);
		while (len > 0) {
			y = get(G->neighbors[x]);	// get neighbor

			// if the neighbor is unvisited
			if (G->color[y] == WHITE) {
				G->color[y] = GRAY;			// visit the neighbor
				G->distance[y] = G->distance[x] + 1;	// correct distance
				G->parent[y] = x;			// update parent
				append(L, y);				// add neighbor
			}

			moveNext(G->neighbors[x]);			// onto next neighbor
			len--;
		}
		G->color[x] = BLACK;					// done with x
	}

	freeList(&L);

	return;
}


// printGraph()
// prints the graph to out file in the requred format
void printGraph(FILE *out, Graph G) {

	if (!out || !G) {
		fprintf(stderr, "Graph Error: calling printGraph() on a NULL file or graph reference.\n");
		exit(ERR);
	}

	int i = 1;
	while (i < G->order+1) {
		fprintf(out, "%d: ", i);
		printList(out, G->neighbors[i]);
		fprintf(out, "\n");
		i++;
	}

	return;
}

