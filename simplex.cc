#include <cstdlib>
#include <cstdio>
#include <vector>
#include <list>
#include <queue>

#include "aresta.h"
#include "simplex.h"
#include "graph.h"
#include "leitura.h"

vector<int> y;
vector<int> visit;


/*****************************

A função networkSimplex(Tree *T, Dados *ds)
recebe uma árvore inicial factível T e uma instancia
de dados ds que descreve o problema.

As arestas de ds e as de T são dois conjuntos disjuntos
(Ou seja, as arestas de uma não estão na outra.)

Ao final da execução do algorítimo, T será uma árvore
factível ótima, e todas as arestas que não estiverem
em T estarão na lista de arestas de ds.


*****************************/

int networkSimplex(Tree *T, Dados *ds)
{


	y.resize(T->T->V);
	visit.resize(T->T->V);

	calculaDual(T);



	while(1)
	{
		
		// Procura por aresta para entrar
		Aresta *aIn;
		float c2 = 0;

		list<Aresta*>::const_iterator it;
		for(it  = ds->ars.begin();
				it != ds->ars.end(); ++it)
		{

			aIn = *it;
			c2 = aIn->c + y[aIn->a] - y[aIn->b];
			if(c2 < 0) break; // Aresta "a" vai entrar;

		}

		if(it == ds->ars.end() || c2 >= 0) break; // Se não achou aresta
												// Para entrar, achou
												// a árvore ótima

		
		ds->ars.remove(aIn);

		// Detecta ciclo
		//Acha aresta que irá sair.

		list<CircA*> circ;

		Aresta *aOut = cicloFund(T, aIn, circ);

		//printf("Aout: %d->%d (%d) F = %d\n", aOut->a, aOut->b, aOut->c, aOut->f);
		aIn->f = aOut->f;

		for( list<CircA*>::const_iterator it = circ.begin();
				it != circ.end(); ++it)
		{
			CircA* ca = *it;
			Aresta *a = ca->a;
			a->f += aOut->f*ca->dir;
			delete ca;
		}


		//printf("aIn: %d->%d (%d) F = %d\n", aIn->a, aIn->b, aIn->c, aIn->f);

		trocaAresta(T, aIn, aOut);
		ds->ars.push_back(aOut);

		

		circ.clear();


			
	}

	return 1;
}


/***************
A função trocaAresta(Tree *T, Aresta *e, Aresta *f)
revebe uma árvore factível T e duas arestas e,f, sendo
que f está em T e e não está em T.

Ao final da função, a árvore se tornará T + e - f,
com as variaveis duais y e fluxos nas arestas ajustadas
de acordo.
*****************/

void trocaAresta(Tree *T, Aresta *e, Aresta *f)
{
	//int u = e->a, v = e->b;
	//float c2 = e->c + y[u] - y[v];
	//int u2 = f->a, v2 = f->b;

	delAresta(T->T,f);
	addAresta(T->T,e);

	for(int i = 0; i < T->T->V; i++)
		{
			visit[i] = 0;
			T->p[i] = NULL;
		}

	//dfsAtualizaY(T->T,v, c2);

	T->p[T->r] = NULL;
	T->d[T->r] = 0;
	dfsReconstroiP(T,T->r);

	// Recalcula os y's
	calculaDual(T);
/*	Graph *G = T->T;

	for( list<Aresta*>::const_iterator it = G->adj[v].begin();
				it != G->adj[v].end(); ++it)
		{
			Aresta *a = *it;
			int u = a->a == v? a->b : a->a ;
			if(!visit[u])
				dfsAtualizaY(G,u, c2);
		}
*/




}

/*****************************
dfsReconstroiP(Tree *T, int v) é uma função recursiva no
estilo Depth First Search. Ela se baseia na lista de
adjacência em T->T para reconstruir o vetor T->p de
pais da árvore.
*******************************/


void dfsReconstroiP(Tree *T, int v)
{

	Graph *G = T->T;
	for( list<Aresta*>::const_iterator it = G->adj[v].begin();
				it != G->adj[v].end(); ++it)
		{
			Aresta *a = *it;
			
			int u = a->a == v? a->b : a->a ;
			//printf("HUE(%d,%d) r = %d\n",v,u, T->r);
			
			if(T->p[u] == NULL && u != T->r)
			{
				
				T->p[u] = a;
				T->d[u] = T->d[v] + 1;	
				dfsReconstroiP(T, u);
			}
		}
}


void dfsAtualizaY(Graph *G, int v, float c2)
{
	y[v]+= c2;
	visit[v] = 1;
	for( list<Aresta*>::const_iterator it = G->adj[v].begin();
				it != G->adj[v].end(); ++it)
		{
			Aresta *a = *it;
			int u = a->a == v? a->b : a->a ;
			if(!visit[u])
				dfsAtualizaY(G,u, c2);
		}

}

/************************

A função cicloFund(Tree *T, Aresta *a, list<CircA*> &circ)
detecta o único circuito formado pot T + a, sendo a uma
aresta que não está em T.

As arestas desse circuito que estão na árvore serão armazenadas
na lista "circ" na estrutura especial CircA. 

CircA armazena a aresta do circuito, e armazena em dir
- 1 caso a aresta esteja na mesma direção de a no circuito
- -1 c.c.

Além disso, já detecta a aresta contrária de fluxo mínimo.
Essa será a aresta que irá sair da árvore no próximo passo
do simplex. Essa aresta é retornada pela função.

**************************/

Aresta* cicloFund(Tree *T, Aresta *a, list<CircA*> &circ)
{
	int v = a->a;
	int u = a->b;
	Aresta* aMin = NULL;
	Aresta* aTemp = NULL;
	float fluxoMin = 1<<20; //Mudar

	int dir;


	//v->u
	while(T->d[u] > T->d[v])
	{
		aTemp = T->p[u];
		dir = 1;
		if(aTemp->b == u) // Direção oposta da aresta entrando
		{
			dir = -1;
			if(aTemp->f < fluxoMin)
			{
				fluxoMin = aTemp->f;
				aMin = aTemp;
			}
			u = aTemp->a;
		}
		else u = aTemp->b;

		circ.push_back(new CircA(aTemp, dir));
	}
	while(T->d[v] > T->d[u])
	{
		dir = 1;
		aTemp = T->p[v];
		if(aTemp->a == v) // Direção oposta da aresta entrando
		{
			dir = -1;
			if(aTemp->f < fluxoMin)
			{
				fluxoMin = aTemp->f;
				aMin = aTemp;
			}
			v = aTemp->b;
		}
		else v = aTemp->b;	
		circ.push_back(new CircA(aTemp, dir));			
	}

	while(u != v)
	{
		dir = 1;
		aTemp = T->p[u];
		if(aTemp->b == u) // Direção oposta da aresta entrando
		{
			dir = -1;
			if(aTemp->f < fluxoMin)
			{
				fluxoMin = aTemp->f;
				aMin = aTemp;
			}
			u = aTemp->a;
		}
		else u = aTemp->b;
		circ.push_back(new CircA(aTemp, dir));

		dir = 1;
		aTemp = T->p[v];
		if(aTemp->a == v) // Direção oposta da aresta entrando
		{
			dir = -1;
			if(aTemp->f < fluxoMin)
			{
				fluxoMin = aTemp->f;
				aMin = aTemp;
			}
			v = aTemp->b;
		}
		else v = aTemp->b;
		circ.push_back(new CircA(aTemp, dir));		
	}

	return aMin;
}



/******************************


Recebe uma árvore T.

Cálcula as variaveis duais yi para todo
vértice i, começando fazendo y[r] = 0, sendo
r a raiz da árvore.

********************************/


void calculaDual(Tree *T)
{

	Graph *G = T->T;
	queue<int> Q;
	vector<int> visit(G->V);



	y[T->r] = 0;

	Q.push(T->r);

	while(!Q.empty()) //bfs
	{
		int v = Q.front();
		Q.pop();

		for(list<Aresta*>::const_iterator it = G->adj[v].begin(); it != G->adj[v].end(); ++it)
		{
			Aresta *a = *it;
			int in, u;


			if(a->a == v)
			{
				in = 1;
				u = a->b;
			}
			else
			{ 
				in = -1;
				u = a->a;
			}

			if(T->d[u] == T->d[v]+1)
			{
				y[u] = y[v] + in*a->c;
				Q.push(u);
			}
		}

	}




}