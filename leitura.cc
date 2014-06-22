#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>

/* Minhas bibliotecas */

#include "leitura.h"
#include "simplex.h"
#include "aresta.h"

using namespace std;

/****************************
leDados(char* arquivo) Lê os dados fornecidos no 
arquivo de nome "arquivo."

Retorna uma estrutuda do tipo Dados com as informações.


****************************/

Dados* leDados(char* arquivo)
{
	Dados *ds = new Dados();
	int a,b,c; 	// Arco a->b com custo c. 
				// Quem diria que "a,b,c" não seriam nomes
				// aleatórios, em?
	ifstream in(arquivo);
	streambuf *cinbuf = std::cin.rdbuf();



	cin.rdbuf(in.rdbuf());

	cin >> ds->nNos;
	cin >> ds->no >> ds->nf;
	cin >> ds->f;

	while(cin >> a >> b >> c)
	{
		Aresta *atemp = new Aresta(a,b,c); 
		ds->ars.push_back(atemp);
	}

	cin.rdbuf(cinbuf);



	return ds;

}

/*****************************
int gravaSaida(Dados *ds, char* saida) recebe um objeto
do tipo Dados e um nome "saida".

As arestas em "Dados" serão impressas no arquivo "saida"
da seguinte forma:

Para cada aresta que vai de a para b, com cursto c r
fluxo f, vai existir uma linha com:

a b c f

******************************/

int gravaSaida(Dados *ds, char* saida)
{
	ofstream out(saida);
    streambuf *coutbuf = std::cout.rdbuf();

    cout.rdbuf(out.rdbuf());


   for( list<Aresta*>::const_iterator it = ds->ars.begin();
				it != ds->ars.end(); ++it)
   	{
   		Aresta *a = *it;
   		cout << a->a <<" "<< a->b <<" "<< a->c <<" "<< a->f << endl;
   	}



    cout.rdbuf(coutbuf);

    return 1;
}
