// #include "matriz.h"
#include "dijkstra.h"
#include <stdio.h>

int main(){
	cria_grafo("arquivo2.txt");
	print_arestas();
	Dijkstra();
	return 0;
}