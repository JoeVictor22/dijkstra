/*
EQUIPE DE DESENVOLVIMENTO:
Davi Pinho da Silva
Francisco Gleyson Braga Vieira
Joel Victor de Castro Galvão
Raynan Serafim de Souza
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 2147483647 // "infinito"

typedef struct          // Struct para armazenar os dados de uma aresta
{
    int aresta;         // Indice da aresta
    int vertice_inicio; // Vértice origem
    int vertice_fim;    // Vértice destino
    int peso;           // Peso da aresta
} Aresta;

/* Configuração do grafo e caminho*/
Aresta *GRAFO;          // Ponteiro para as arestas do grafo
int quantidade_vertices;
int quantidade_arcos;
int vertice_origem;
int vertice_destino;

/* Variáveis auxiliares */
int custo_atual = 0;
int arestas_achadas = 0;
int no_lock = 0;
int aux = 0;


void set_aresta(int index, int v_inicio, int v_fim, int peso){
    /* Cria uma nova aresta e a salva no index informado */
    Aresta new_aresta;
    new_aresta.aresta = index;
    new_aresta.vertice_inicio = v_inicio;
    new_aresta.vertice_fim = v_fim;
    new_aresta.peso = peso;

    GRAFO[index] = new_aresta;
}

Aresta get_aresta(int index){
    /* Captura uma aresta do grafo */
    return GRAFO[index];
}

void aloca_grafo(){
    /* Aloca o espaço de memória a ser usado pelo programa */
    GRAFO = malloc(quantidade_arcos * sizeof(Aresta));
    if (GRAFO == NULL){
        printf("Não foi possivel alocar memória para a execução\n");   
        exit(1);
    }
}

void libera_grafo(){
    /* Libera memória */
    free(GRAFO);
}

void cria_grafo(char *arquivo){
    /* Realiza leitura do arquivo.txt e construi o vetor de arestas para ser utilizado pelo algoritmo */
    int palavra[10]; // buffer utilizado na leitura

    FILE *file = fopen(arquivo, "r");
    if(file == NULL){
        printf("Não foi possivel encontrar o arquivo %s\n", arquivo);
        exit(1);
    }

    /* Captura variáveis globais */
    fscanf(file, "%d", palavra);
    quantidade_vertices = *palavra;
    fscanf(file, "%d", palavra);
    quantidade_arcos = *palavra;
    fscanf(file, "%d", palavra);
    vertice_origem = *palavra;
    fscanf(file, "%d", palavra);
    vertice_destino = *palavra;

    aloca_grafo();

    for(int i = 0; i < quantidade_arcos; i++){
        /* Cria uma aresta com peso para cada par de vertices */
        fscanf(file, "%d", palavra);
        int v_inicio = *palavra;

        fscanf(file, "%d", palavra);
        int v_fim = *palavra;

        fscanf(file, "%d", palavra);
        int peso = *palavra;

        set_aresta(i, v_inicio-1, v_fim-1, peso);
    }
  fclose(file);
}

void printar_saida(int vetor_anterior[], int custo_final){
    /* Utilitário para printar o resultado */

    if (custo_final == INF){ // Caso o custo seja infinito
        printf("Não existe caminho para a configuração informada");
    }else{
        printf("Caminho mínimo do vértice %d para o vértice %d: ", vertice_origem, vertice_destino);

        /* Itera ,a partir do final, sobre o vetor de saida para refazer o caminho percorrido */
        int vetor_saida[quantidade_vertices-1];
        int size = 1;
        int callback = vertice_destino;

        vetor_saida[0] = vertice_destino;

        while(callback != 0){
            vetor_saida[size]=vetor_anterior[callback-1];
            callback=vetor_saida[size];
            size++;
        }

        for (int i=0;i<size-2;size--){
            printf("(%d, %d)", vetor_saida[size-2],vetor_saida[size-3]);
        }
    }
    printf("\nCusto: %d\n", custo_final);
}

void Dijkstra(){
    /* 
        Implementação do algoritmo 
        A indexação dos vetores foi reduzida de 1 para evitar problemas com o index 0 dos vetores 
    */

    /* Vetores auxiliares */
    int custo[quantidade_vertices];
    int anterior[quantidade_vertices];
    int usados[quantidade_arcos];


    /* Inicialização dos vetores */
    for(int i = 0; i < quantidade_vertices; i++){
        custo[i] = INF;
        anterior[i] = -1;
    }
    for(int i = 0; i < quantidade_arcos; i++){
        usados[i] = 0;
    }

    /* Configura valores para o vertice de origem */
    int inicio = vertice_origem-1; // Index da aresta de origem
    custo[inicio] = 0;
    usados[inicio] = 1;
    anterior[inicio] = 0;

    while(usados[vertice_destino-1] == 0){
        int menor_custo = INF;
        int prox_inicial = -1;

        arestas_achadas = 0;
        no_lock = 0;

        for(int i = 0; i < quantidade_arcos; i++){ // Para cada aresta
            if (GRAFO[i].vertice_inicio == inicio){ // Se o vertice estiver conectado a aresta
                arestas_achadas++;
                custo_atual = custo[inicio] + GRAFO[i].peso; // Incrementa custo_atual

                /* Verifica o custo e se o vertice atual ja foi usado */
                if (custo_atual < custo[GRAFO[i].vertice_fim] && usados[GRAFO[i].vertice_fim] == 0){
                    custo[GRAFO[i].vertice_fim] = custo_atual;
                    anterior[GRAFO[i].vertice_fim] = inicio+1;
                }
                if (menor_custo > custo[GRAFO[i].vertice_fim] && usados[GRAFO[i].vertice_fim] == 0){
                    menor_custo = custo[GRAFO[i].vertice_fim];
                    prox_inicial = GRAFO[i].vertice_fim;
                }
                if (usados[GRAFO[i].vertice_fim] == 1){
                    no_lock++;
                }
            }
        }

        if(prox_inicial != -1){
            inicio = prox_inicial;
            usados[inicio] = 1;
        }else if (arestas_achadas == no_lock){
            break;
        }
    }
    printar_saida(anterior, custo[vertice_destino-1]);

    libera_grafo();
}

int main(int argc, char **argv){
    /* Captura o arquivo a ser utilizado */

    if(argc != 2){
        printf("O caminho do arquivo não foi informado corretamente\n");
        return 1;
    }

	cria_grafo(argv[1]);
	Dijkstra();
	return 0;
}