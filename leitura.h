#include <list>

#include "aresta.h"

using namespace std;


typedef struct dados{
	int nNos;
	int no, nf; // Nó de origem e nó de destino
	list<Aresta*> ars;


}Dados;



// Funções

Dados* leDados();