#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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


void Dijkstra(){
    double custo[quantidade_vertices];
    int anterior[quantidade_vertices];
    int usados[quantidade_vertices];

    for(int i = 0; i < quantidade_vertices; i++){
        usados[i] = 0;
        custo[i] = INFINITY;
        anterior[i] = -1;
    }
    
    int inicio = vertice_origem-1; // index da aresta de origem
    custo[inicio] = 0;
    usados[inicio] = 1;
    anterior[inicio] = 0;  

    while(usados[vertice_destino-1] == 0){    
        //printf("%d \n", usados[vertice_destino]);
        float menor_custo = INFINITY;
        int prox_inicial = -1;

        for(int i = 0; i < quantidade_arcos; i++){ // iterando sobre as arestas
            if (GRAFO[i].vertice_inicio == inicio){ // aquela aresta é a de inicio?
                //printf("1");
        
                custo_atual = custo[inicio] + GRAFO[i].peso; // incrementa custo_atual
                //printf("\nCUSTO %d\n", custo_atual);
                /*
                    verifica o custo e se o vertice atual ja foi usado
                */
                if (custo_atual < custo[GRAFO[i].vertice_fim] && usados[GRAFO[i].vertice_fim] == 0){ 
                    custo[GRAFO[i].vertice_fim] = custo_atual;
                    anterior[GRAFO[i].vertice_fim] = inicio+1;
                    // printf("%d ", GRAFO[i].vertice_fim);
                }
                if (menor_custo > custo[GRAFO[i].vertice_fim] && usados[GRAFO[i].vertice_fim] == 0){
                    menor_custo = custo[GRAFO[i].vertice_fim];
                    prox_inicial = GRAFO[i].vertice_fim;
                    // printf("%d ", GRAFO[i].vertice_inicio);
                }
            }
        }
        //printf("Sai\n");
        if(prox_inicial!=-1){
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
        printf("%.0f ",custo[i]);
    }
    printf("\n----ANTERIOR----\n");
    for (int i=0;i<quantidade_vertices; i++){
        printf("%d ",anterior[i]);
    }
    printf("\n");
    libera_grafo();   
}