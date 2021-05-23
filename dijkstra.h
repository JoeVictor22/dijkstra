#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define INF 100000
typedef struct          // struct para armazenar os dados de uma aresta
{
    int aresta;         // indice da aresta
    int vertice_inicio; // vertice origem
    int vertice_fim;    // vertice destino
    int peso;           // peso da aresta
} Aresta; 

Aresta *GRAFO;          // Ponteiro para as arestas do grafo
int quantidade_vertices; 
int quantidade_arcos;
int vertice_origem;
int vertice_destino;
int custo_atual = 0;


void set_aresta(int index, int v_inicio, int v_fim, int peso){
    /*
    Cria uma nova aresta e a salva no index informado
    */
    Aresta new_aresta;
    new_aresta.aresta = index;
    new_aresta.vertice_inicio = v_inicio;
    new_aresta.vertice_fim = v_fim;
    new_aresta.peso = peso;   
    
    GRAFO[index] = new_aresta;
}

Aresta get_aresta(int index){
    /*
    Captura uma aresta do grafo
    */
    return GRAFO[index];
}

void print_arestas(){
    /*
    Utilitário para printar as arestas
    */
    for(int i = 0; i < quantidade_arcos; i++){
        printf("%d = %d -> %d : %d\n", GRAFO[i].aresta, GRAFO[i].vertice_inicio, GRAFO[i].vertice_fim, GRAFO[i].peso);
    }
}

void aloca_grafo(){
    /*
    Aloca o espaçõ de memória a ser usado pelo programa
    */
    GRAFO = malloc(quantidade_arcos * sizeof(Aresta));
    if (GRAFO == NULL){
        exit(1);
    }
}

void libera_grafo(){
    free(GRAFO);
}

void cria_grafo(char *arquivo){
    /*
    Realiza leitura do arquivo.txt e construi o vetor de arestas para ser utilizado pelo algoritmo  
    */
    int palavra[10]; // buffer para file

    FILE *file = fopen(arquivo, "r");
    if(file == NULL){ 
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

    printf("%d / %d / %d / %d\n", quantidade_vertices, quantidade_arcos, vertice_origem, vertice_destino);


    int i = 0;
    while(i < quantidade_arcos){
        /*
        Cria uma aresta para cada par de vertices com peso
        */
        fscanf(file, "%d", palavra);        
        int v_inicio = *palavra;

        fscanf(file, "%d", palavra);
        int v_fim = *palavra;
        
        fscanf(file, "%d", palavra); 
        int peso = *palavra;

        printf("%d - %d - %d\n", v_inicio-1, v_fim-1, peso);

        set_aresta(i, v_inicio-1, v_fim-1, peso);
        i++;

    }

  fclose(file);
}

void printar_saida(int vetor_anterior[], float custo_final){
    
    printf("Caminho mínimo do vértice %d para o vértice %d: ", vertice_origem, vertice_destino);
    
    int vetor_saida[quantidade_vertices-1];
    int size=1;
    int callback=vertice_destino;
    
    vetor_saida[0]=vertice_destino;
    
    while(callback!=0){
    vetor_saida[size]=vetor_anterior[callback-1];
        callback=vetor_saida[size];
    size++;
    }

    for (int i=0;i<size-2;size--){
        printf("(%d, %d)", vetor_saida[size-2],vetor_saida[size-3]);
    }
    printf("\n");

    printf("Custo: %.0f\n", custo_final);
}

void Dijkstra(){
    int custo[quantidade_vertices];
    int anterior[quantidade_vertices];
    int usados[quantidade_arcos];

    for(int i = 0; i < quantidade_vertices; i++){
        custo[i] = INF;
        anterior[i] = -1;
    }

    for(int i = 0; i < quantidade_arcos; i++){
        usados[i] = 0;
    }
    
    int inicio = vertice_origem-1; // index da aresta de origem
    custo[inicio] = 0;
    usados[inicio] = 1;
    anterior[inicio] = 0;  


    printf("comecou em -> %d \n", inicio);
    while(usados[vertice_destino-1] == 0){    
        int menor_custo = INF;
        int prox_inicial = -1;
        printf("\n\nRESET\n\n");
        for(int i = 0; i < quantidade_arcos; i++){ // iterando sobre as arestas
            if (GRAFO[i].vertice_inicio == inicio){ // aquela aresta é a de inicio?
                custo_atual = custo[inicio] + GRAFO[i].peso; // incrementa custo_atual
                printf("\nCUSTO (%d + %d = %d)\n", custo[inicio], GRAFO[i].peso, custo_atual);
                /*
                    verifica o custo e se o vertice atual ja foi usado
                */
                if (custo_atual < custo[GRAFO[i].vertice_fim] && usados[GRAFO[i].vertice_fim] == 0){ 
                    custo[GRAFO[i].vertice_fim] = custo_atual;
                    anterior[GRAFO[i].vertice_fim] = inicio;
                    // printf("%d ", GRAFO[i].vertice_fim);
                    printf("morri¹");
                }
                if (menor_custo > custo[GRAFO[i].vertice_fim] && usados[GRAFO[i].vertice_fim] == 0){
                    menor_custo = custo[GRAFO[i].vertice_fim];
                    prox_inicial = GRAFO[i].vertice_fim;
                    printf("morri²");
                }

                printf("\nCUSTOS i=%d\n", i);
                for(int i = 0; i <quantidade_vertices; i++ ){
                    printf("%d | ", custo[i]);
                }
                printf("\nVISITADO i=%d\n", i);
                for(int i = 0; i <quantidade_arcos; i++ ){
                    printf("%d | ", usados[i]);
                }
                printf("\nANTERIOR i=%d\n", i);
                for(int i = 0; i <quantidade_vertices; i++ ){
                    printf("%d | ", anterior[i]);
                }
                getchar();
            }
        }
        
        printf("SAIDAQ DISGRAÇA %d\n", prox_inicial);
        if(prox_inicial!=-1){
            printf("foi para -> %d\n", prox_inicial);
            inicio = prox_inicial;
            usados[inicio] = 1; 
        }
    }

    printf("\n----USADOS----\n");
    for (int i=0;i<quantidade_vertices; i++){
        printf("%d ",usados[i]);
    }
    printf("\n----CUSTO----\n");
    for (int i=0;i<quantidade_vertices; i++){
        printf("%d ",custo[i]);
    }
    printf("\n----ANTERIOR----\n");
    for (int i=0;i<quantidade_vertices; i++){
        printf("%d ",anterior[i]);
    }
    printf("\n");
    printar_saida(anterior,custo[vertice_destino-1]);

    libera_grafo();   
}