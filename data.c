#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

DicLDE* inicializa(void){
    return NULL;
}

DicLDE* insereFinal(DicLDE *PtLista, FILE* arquivo){
    DicLDE *novo, *PtAux;

    novo = (DicLDE*) malloc(sizeof(DicLDE));
    fscanf(arquivo,"%s %s", novo->info.palavra, novo->info.lema);
    novo->prox = NULL;
    if ((PtLista) == NULL){
        PtLista = novo;
        novo->ant = NULL;
    }
    else {
        PtAux = PtLista;
        while (PtAux->prox != NULL){
            PtAux=PtAux->prox;
        }
        PtAux->prox = novo;
        novo->ant = PtAux;
    }
    return PtLista;
}

DicLDE* recebeDicionario(char *txt){
    DicLDE *D;

    FILE * arquivo;

    D=inicializa();
    arquivo = fopen(txt,"r");
    if(!arquivo){
        printf("Erro abrindo o arquivo!");
        return NULL;
    }
    else{
        while(!feof(arquivo)){
            D=insereFinal(D,arquivo);
        }
    }
    fclose(arquivo);
    return D;
}

int ler_arquivo(FILE *arquivo, char *linha){

    if(fscanf(arquivo,"%s",linha))
    {
        return linha;
    }
    else
        return NULL;
}
