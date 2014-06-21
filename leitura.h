#ifndef LEITURA_H
#define LEITURA_H

#include <list>
#include "aresta.h"

using namespace std;


typedef struct dados{
	int nNos;
	int no, nf; // Nó de origem e nó de destino
	int f;
	list<Aresta*> ars;


}Dados;



// Funções

Dados* leDados();

#endif