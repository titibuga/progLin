#ifndef LEITURA_H
#define LEITURA_H

#include <list>
#include "aresta.h"

using namespace std;


typedef struct dados{
	int nNos; // Número de nós
	int no, nf; // Nó de origem e nó de destino
	int f; // Fluxo 
	list<Aresta*> ars; // Lista de arestas
}Dados;



// Funções

Dados* leDados(char*);
int gravaSaida(Dados*, char*);

#endif