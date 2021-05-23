#include <stdio.h>
#include <stdlib.h>

int linhaArquivo(char *palavra, int linha); //define apenas o cabeçalho da função. Sem o cabeçalho, a função deve ficar acima do main



void testa(){
    char caracter[50];
    int linha;
    int aux;

    int cont=1;
    while(cont <= 4){
        linha=cont; //para pegar a palavra na primeira linha
        linhaArquivo(caracter, linha);
        printf("Linha %i: %s\n", cont, caracter);
        cont++;
    }

    printf("-----------------------\n");

    aux = (3 * 7) + 4;
    cont=5;
    while(cont <= aux){
        linha=cont; //para pegar a palavra na primeira linha
        linhaArquivo(caracter, linha);
        printf("Linha %i: %s\n", cont, caracter);
        cont++;
    }

}

int linhaArquivo(char *palavra, int linha){
    FILE *file;
    if((file=fopen("arquivo.txt", "r"))==NULL){ //poupa linha atribuindo e comparando ao mesmo tempo
        printf("ERROR: linhaArquivo fopen == NULL\n"); //informa onde e qual foi o erro
        exit(1); 
    }

    int cont=0;
    while(cont!=linha){
        fscanf(file, "%s", palavra); //lê uma linha
        cont++;
    }

    fclose(file);
    return 0;
}

long calcularTamanhoArquivo(FILE *arquivo) {
    // guarda o estado ante de chamar a função fseek
    long posicaoAtual = ftell(arquivo);
 
    // guarda tamanho do arquivo
    long tamanho;
 
    // calcula o tamanho
    fseek(arquivo, 0, SEEK_END);
    tamanho = ftell(arquivo);
 
    // recupera o estado antigo do arquivo
    fseek(arquivo, posicaoAtual, SEEK_SET);
 
    return tamanho;
}