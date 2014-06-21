#include <cstdlib>
#include <vector>


#include "leitura.h"
#include "aresta.h"
#include "simplex.h"


#define INF 2^10


using namespace std;



vector<Aresta*> arv;


int inicializa(Dados *ds)
{
	vector<*	Aresta> arvTemp;
	int source = ds->no;
	int sink = ds->nf;
	int w = 0;

	arvTemp.resize(ds->nNos);

	while(w == source || w == sink) w++;

	// Falta verificar se w continua válido

	arvTemp[w] = NULL;

	for(int i = 0; i < ds->nNos; i++)
	{
		if(i == w) continue
		arvTemp[i] = new Aresta(w,i,INF);
	}


	//Falta terminar

	return 1;






}

