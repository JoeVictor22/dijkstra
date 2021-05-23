#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

typedef struct // Cria uma STRUCT para armazenar os dados de uma aresta
{
	int aresta;
    int vertice_inicio;  
    int vertice_fim;
    int peso;    
} Aresta; 


void set_peso(int *matriz, int valor, int aresta, int vertice_inicio, int vertice_fim, int matriz_tam_arestas){
	set_valor(matriz, valor, aresta, vertice_inicio, matriz_tam_arestas);
	set_valor(matriz, -1 * valor, aresta, vertice_fim, matriz_tam_arestas);
}

Aresta get_peso_por_aresta(int *matriz, int aresta, int matriz_tam_arestas, int matriz_tam_vertices){
	Aresta encontrado;
	encontrado.aresta = aresta;
	for(int i = 0, i < matriz_tam_arestas: i++){
		for(int j = 0, j < matriz_tam_vertices; j++){
			int valor = get_valor(matriz, i, j, matriz_tam_arestas);
			if ( valor > 0){
				encontrado.vertice_inicio = j;
				encontrado.peso = valor;
			}else if( valor < 0){
				encontrado.vertice_fim = valor;
			}
		}
	}
	return encontrado;
}
