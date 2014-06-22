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

/********************************
A função criaArvArtificial(Dados* ds, int r) retorna
uma nova Tree T. 

Essa nova árvore será uma árvore factível para o problema definido
por ds, mas conterá somente arestas artificiais com custo = soma
do custo de todas as outras arestas de ds.

Útil para iniciar o simplex.

*********************************/

Tree* criaArvArtificial(Dados* ds, int r)
{
	Aresta* a;
	Tree *T = new Tree(ds->nNos);
	int sink = ds->nf, source = ds->no;

	T->p[r] = NULL;
	T->d[r] = 0;
	T->r = r;

	for(int i = 0; i < ds->nNos; i++)
	{
		if(i == r) continue;
		if(i == source)
		{
			addAresta(T->T, a = new Aresta(i,r,INF));
			a->f = ds->f;
		}
		else if(i == sink)
		{
			addAresta(T->T, a = new Aresta(r, i,INF));
			a->f = ds->f;			
		}			
		else addAresta(T->T,a = new Aresta(r,i,INF));

		artificiais.push_back(a);
			
	}

	return T;
}


/*****************************
A função inicializa(Dados *ds) irá criar
uma árvore factivel inicial para ds, e irá executar
o simplex em redes para esse problema com a árvore gerada.

Ao final da execução do simplex, verificamos se existe alguma
aresta artificial que tem fluxo != 0. Caso isso aconteça, retornamos
0 por o problema é inviável.

Retornamos 1 caso o problema seja factível.


PS: Foi verificado que nesse passo de inicialização já
se resolvia o problema.


********************************/

int inicializa(Dados *ds)
{
	int source = ds->no;
	int sink = ds->nf;
	int w = 0;


	while(w == source || w == sink) w++;

	// Falta verificar se w continua válido

	Tree *T = criaArvArtificial(ds,w);


	dfsReconstroiP(T,T->r);

	networkSimplex(T, ds);

	//delete T; <---- ERRADO

	for( list<Aresta*>::const_iterator it = artificiais.begin();
				it != artificiais.end(); ++it)
		{
			Aresta *a = *it;
			if(a->f != 0) return 0;
		}

	// Remove as arestas artificiais dos dados.

	for( list<Aresta*>::const_iterator it = artificiais.begin();
			it != artificiais.end(); ++it)
	{
		Aresta *a = *it;
		ds->ars.remove(a);
	}


	for(int i = 0; i < ds->nNos; i++)
		if(T->p[i])
			ds->ars.push_back(T->p[i]);


	return 1;
}

