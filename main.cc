#include <cstdio>
#include <cstdlib>
#include <iostream>


// Minhas bibliotecas

#include "leitura.h"

using namespace std;



int main(int argc, char* argv[])
{

	Dados *ds = leDados();

	printf("HUE: %d\n", ds->nNos);


	return 0;
}