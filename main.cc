#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>


// Minhas bibliotecas

#include "leitura.h"
#include "inicializar.h"

using namespace std;



int main(int argc, char* argv[])
{

	if(argc <=2)
	{
		cout << "Modo de uso:" << endl;
		cout << "./ep <nome_da_entrada> <nome_da_saida>" << endl;
		cout << "O programa irá terminar" << endl;
		return -1;
	}

	Dados *ds = leDados(argv[1]);
	if(!ds)
	{
		cout << "Erro ao tentar ler:" << argv[1] << endl;
		return -1;
	}

	/*
	printf("Source: %d Sink: %d Fluxo: %d\n", ds->no, ds->nf, ds->f);
	for(list<Aresta*>::const_iterator it  = ds->ars.begin();
				it != ds->ars.end(); ++it)
	{
		Aresta *a = *it;
		printf("%d->%d (%d) F = %d\n", a->a, a->b, a->c, a->f);
	}
	*/



	if(inicializa(ds))
	{
		printf("Viável!\n");
		gravaSaida(ds, argv[2]);
		printf("Solução impressa em %s\n", argv[2]);
	}
	else printf("O problema é inviável!\n");




	return 0;
}