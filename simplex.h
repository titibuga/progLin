#ifndef SIMPLEX_H
#define SIMPLEX_H


#include <vector>

#include "graph.h"
#include "aresta.h"
#include "leitura.h"

using namespace std;

typedef struct circA{
	Aresta *a;
	int dir;
	circA(Aresta *at, int dirt){
		a = at;
		dir = dirt;
	}
}CircA;

typedef struct tree{

	Graph *T; // Lista de Adjacencia.
	int r; // Root
	vector<Aresta*> p; // Parent
	vector<int> d; // Depth
	tree(int n)
	{
		p.resize(n);
		d.resize(n);
		T = new Graph(n);
	}


	//vector<int> f; //Flow

}Tree;

int networkSimplex(Tree *T, Dados *ds);
void trocaAresta(Tree *T, Aresta *e, Aresta *f);
void dfsReconstroiP(Tree *T, int v);
void dfsAtualizaY(Graph *G, int v, float c2);
Aresta* cicloFund(Tree *T, Aresta *a, list<CircA*> &circ);
void calculaDual(Tree *T);


#endif