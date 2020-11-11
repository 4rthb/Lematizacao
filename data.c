#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

DicLDE* ordenaLista(DicLDE* D){
    DicLDE *Aux;
    int flag=1, check;

    Aux=D;
    while(flag){
        flag=0;
        while(Aux->prox!=NULL){
            check=strcmp(Aux->info.palavra,Aux->prox->info.palavra);
            if(check>0){
                flag=1;
                Aux->prox->ant=Aux->ant;
                Aux->ant->prox=Aux->prox;
                Aux->prox->prox->ant=Aux;
                Aux->prox=Aux->prox->prox;
                Aux->ant->prox->prox=Aux;
                Aux->ant=Aux->ant->prox;
            }
            Aux=Aux->prox;
        Aux=D;
        }
    }
    return D;
}

DicLDE* recebeDicionarioOrdenado(char *txt){
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
    D=ordenaLista(D);
    return D;
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

char* ler_arquivo(FILE *arquivo, char linha[30]){

    fscanf(arquivo,"%s",linha);
    return linha;
}

DicLDE* encontraNoDicOrdenado(DicLDE *D, char *linha){
    int check;

    if(linha==NULL || D->info.palavra==NULL){
        printf("Erro ao procurar no dicionario");
        return NULL;
    }
    linha[0]=tolower(linha[0]);
    do{
        check=strcmp(linha,D->info.palavra);
        if(!check){
            return D;
        }
        else if(check<0){
            D=D->prox;
        }
        else return NULL;
    }while(check && D->prox!=NULL);
    return NULL;
}

DicLDE* encontraNoDic(DicLDE *D, char *linha){
    int check;

    if(linha==NULL || D->info.palavra==NULL){
        printf("Erro ao procurar no dicionario");
        return NULL;
    }
    linha[0]=tolower(linha[0]);
    do{
        check=strcmp(linha,D->info.palavra);
        if(!check){
            return D;
        }
        else if(check){
            D=D->prox;
        }
    }while(check && D->prox!=NULL);
    return NULL;
}

void colocaSaida(FILE *saida, DicLDE *pos){
    fputs(pos->info.lema,saida);
}


