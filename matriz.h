#include <stdio.h>
#include <stdlib.h>


/*
matriz = ponteiro para um array acessado como matriz
matriz_tam_arestas = quantidade de arestas
matriz_tam_vertices = quantidade de vertices
linha = pos x da matriz
coluna = pos y da matriz
*/

int get_valor(int *matriz, int linha, int coluna, int matriz_tam_arestas){
	return matriz[(linha * matriz_tam_arestas) + coluna];
}


void set_valor(int *matriz, int valor, int linha, int coluna, int matriz_tam_arestas){
	matriz[(linha * matriz_tam_arestas) + coluna] = valor;
}

int *cria_matriz(int aresta, int vertice){
	int (*matriz)[vertice] = malloc(aresta * vertice * sizeof(int));

	// use like // mat[(i*COL) + j] = 0 ;

	if (matriz != NULL){
		return *matriz;		
	}else{
		exit(1);
	}

}

void inicia_matriz(int *matriz, int valor, int matriz_tam_arestas, int matriz_tam_vertices){
	for (int i = 0; i < matriz_tam_arestas; i++){
		for (int j = 0; j < matriz_tam_vertices; j++){
			set_valor(matriz, valor, i, j, matriz_tam_arestas);			
		}
	}
}

void printa_matriz(int *matriz, int matriz_tam_arestas, int matriz_tam_vertices){

	for (int i = 0; i < matriz_tam_arestas; i++){
		printf("\n");
		for (int j = 0; j < matriz_tam_vertices; j++){
			printf("%d ", get_valor(matriz, i, j, matriz_tam_arestas));
		}
	}

}

int libera_matriz(int *matriz){
	if (matriz != NULL){
		free(matriz);			
	}
}