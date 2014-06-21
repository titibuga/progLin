FLAGS=-g -Wall 


ep: leitura.o main.o simplex.o aresta.o graph.o
	g++ $(FLAGS) -o ep leitura.o main.o

main.o: main.cc
	g++ $(FLAGS) -c main.cc

leitura.o: leitura.cc leitura.h
	g++ $(FLAGS) -c leitura.cc

simplex.o: simplex.cc simplex.h
	g++ $(FLAGS) -c simplex.cc

aresta.o: aresta.cc aresta.h
	g++ $(FLAGS) -c aresta.cc

graph.o: graph.cc graph.h
	g++ $(FLAGS) -c graph.cc

