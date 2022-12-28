#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include "List.h"

// Exported type
typedef struct GraphObj* Graph;

// enum for ease of using constants
enum {INF = -1, NIL, WHITE, GRAY, BLACK};

// Constructors-Destructors
Graph newGraph(int n);			// Creates and returns a new empty Graph with n vertices.
void freeGraph(Graph *pG);		// Frees all heap memory associated with *pG, and sets *pG to NULL.

// Access Functions
int getOrder(Graph G);			// returns the order of the graph 
int getSize(Graph G);			// returns the size of the graph
int getSource(Graph G);			// returns the source vertex most recently used in BFS() function.
int getParent(Graph G, int u);		// returns the parent of vertex u in BF tree or NIL if BFS() has not been called yet. Pre: u is in range [1, getOrder(G)].
int getDist(Graph G, int u);		// returns the distance from most recent BFS source to vertex u or INF if BFS() has not been called yet. Pre: u is in range [1, getOrder(G)].
void getPath(List L, Graph G, int u);	// appends to list vertices of shortest past from source to u, or appends NIL if no such path exists. Pre: getSource(G) != NIL, u is in range [1, getOrder(G)].

// Manupulation procedures
void makeNull(Graph G);			// deletes all edges of G, restoring to its original (no edge) state.
void addEdge(Graph G, int u, int v);	// inserts a new edge joining u to v. Pre: u and v are in range [1, getOrder(G)].
void addArc(Graph G, int u, int v);	// inserts a new directed edge from u to v.	
void BFS(Graph G, int s);		// runs BFS on G's source s.

// Other operations
void printGraph(FILE *out, Graph G);	// prints the graph to out file in the required format.

#endif
