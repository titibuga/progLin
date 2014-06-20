typedef struct aresta{
	int a,b; // Arco vai de a para b (a->b)
	int c; // custo

	aresta()
	{
		a = b = c = 0;
	}

	aresta(int at, int bt, int ct)
	{
		a = at;
		b = bt;
		c = ct;
	}

}Aresta;