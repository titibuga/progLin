#include <cstdlib>
#include <cstdio>
#include <list>


#include "leitura.h"
#include "aresta.h"
#include "simplex.h"

#include "simplex.h"
#include "graph.h"


#define INF 1<<20


using namespace std;





list<Aresta*> artificiais;


int inicializa(Dados *ds)
{
	vector<Aresta*> arvTemp;
	int source = ds->no;
	int sink = ds->nf;
	int w = 0;
	Aresta *a;

	arvTemp.resize(ds->nNos);

	while(w == source || w == sink) w++;

	// Falta verificar se w continua válido

	Tree *T = new Tree(ds->nNos);

	T->p[w] = NULL;
	T->d[w] = 0;
	T->r = w;

	for(int i = 0; i < ds->nNos; i++)
	{
		if(i == w) continue;
		if(i == source)
		{
			addAresta(T->T, a = new Aresta(i,w,INF));
			a->f = ds->f;
		}
		else if(i == sink)
		{
			addAresta(T->T, a = new Aresta(w, i,INF));
			a->f = ds->f;			
		}			
		else addAresta(T->T,a = new Aresta(w,i,INF));

		artificiais.push_back(a);
			
	}

	printf("-------------Árvore Inicial-----------------\n");
	dfsReconstroiP(T,T->r);
	printf("------------------------------------\n");


	networkSimplex(T, ds);

	for( list<Aresta*>::const_iterator it = artificiais.begin();
				it != artificiais.end(); ++it)
		{
			Aresta *a = *it;
			if(a->f != 0) return 0;
		}


	//Falta terminar

	return 1;






}

