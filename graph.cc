#include <cstdlib>
#include <vector>
#include <list>


#include "graph.h"

void addAresta(Graph *G, Aresta *a)
{
	int v = a->a;
	int u = a->b;

	G->adj[v].push_back(a);
	G->adj[u].push_back(a);
}

void delAresta(Graph *G, Aresta *a)
{
	int v = a->a;
	int u = a->b;

	G->adj[v].remove(a);
	G->adj[u].remove(a);	
}

