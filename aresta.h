#ifndef ARESTA_H
#define ARESTA_H


typedef struct aresta{
	int a,b; // Arco vai de a para b (a->b)
	int c; // custo
	int f; //Fluxo

	aresta()
	{
		f = a = b = c = 0;
	}

	aresta(int at, int bt, int ct)
	{
		a = at;
		b = bt;
		c = ct;
		f = 0;
	}

}Aresta;


#endif