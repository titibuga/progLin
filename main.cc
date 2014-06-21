#include <cstdio>
#include <cstdlib>
#include <iostream>


// Minhas bibliotecas

#include "leitura.h"
#include "inicializar.h"

using namespace std;



int main(int argc, char* argv[])
{

	Dados *ds = leDados();
	printf("Source: %d Sink: %d Fluxo: %d\n", ds->no, ds->nf, ds->f);
	for(list<Aresta*>::const_iterator it  = ds->ars.begin();
				it != ds->ars.end(); ++it)
	{
		Aresta *a = *it;
		printf("%d->%d\n", a->a, a->b);
	}



	printf("----------------SIMPLEX---------------\n");

	if(inicializa(ds)) printf("Viável!");
	else printf("Inviável!!!!!!!!!!jnsajdj");




	return 0;
}