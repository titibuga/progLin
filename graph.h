#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "aresta.h"

using namespace std;

typedef struct graph{
	int V; // Número de vértices
	vector< list<Aresta*> > adj; // Lista de adjacência
	graph(int n){
		V = n;
		adj.resize(n);
	}


}Graph;

void addAresta(Graph *G, Aresta *a);
void delAresta(Graph *G, Aresta *a);

#endif