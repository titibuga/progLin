#include <cstdio>
#include <cstdlib>
#include <iostream>

/* Minhas bibliotecas */

#include "leitura.h"

using namespace std;



Dados* leDados()
{
	Dados *ds = new Dados();
	int a,b,c; 	// Arco a->b com custo c. 
				// Quem diria que "a,b,c" não seriam nomes
				// aleatórios, em?

	cin >> ds->nNos;
	cin >> ds->no >> ds->nf;

	while(cin >> a >> b >> c)
	{
		Aresta *atemp = new Aresta(a,b,c); 
		ds->ars.push_back(atemp);
	}



	return ds;

}
