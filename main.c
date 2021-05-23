#include "matriz.h"
#include <stdio.h>

int main(){
	int arestas = 5;
	int vertices = 10;

	int *matriz = cria_matriz(arestas, vertices);
	inicia_matriz(matriz, 2, arestas, vertices);
	printa_matriz(matriz, arestas, vertices);
	libera_matriz(matriz);

	return 0;
}