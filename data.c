#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data.h"

DicLDE* inicializa(void){                                                               //inicializa lista duplamente encadeada
    return NULL;
}

DicLDE* insereFinal(DicLDE *PtLista, FILE* arquivo){
    DicLDE *novo, *PtAux;

    novo = (DicLDE*) malloc(sizeof(DicLDE));                                            //aloca espaço na memória para novo nodo
    fscanf(arquivo,"%s %s", novo->info.palavra, novo->info.lema);                       //le a palavra e lema do arquivo de lemas e os colocam no mesmo nodo
    novo->prox = NULL;
    if ((PtLista) == NULL){                                                             //caso lista inicialmente vazia, seta anterior NULL
        PtLista = novo;
        novo->ant = NULL;
    }
    else {                                                                              //caso lista com termos, percorre até chegar no final e depois coloca nodo
        PtAux = PtLista;
        while (PtAux->prox != NULL){
            PtAux=PtAux->prox;
        }
        PtAux->prox = novo;
        novo->ant = PtAux;
    }
    return PtLista;                                                                     //retorna lista modificada
}

DicLDE* recebeDicionario(char *txt){
    DicLDE *D;

    FILE * arquivo;

    D=inicializa();                                                                     //chama função que inicializa LDE
    arquivo = fopen(txt,"r");                                                           //abre arquivo de lemas
    if(!arquivo){                                                                       //se nã encontrar arquivo retorna erro
        printf("Erro abrindo o arquivo!");
        return NULL;
    }
    else{                                                                               //enquanto não chega no final do arquivo de lemas, coloca nodos na LDE com as informações do arquivo
        while(!feof(arquivo)){
            D=insereFinal(D,arquivo);
        }
    }
    fclose(arquivo);                                                                    //fecha arquivo de lemas
    return D;                                                                           //retorna lista criada
}

char* ler_arquivo(FILE *arquivo, char linha[50], char* tab){

    fscanf(arquivo,"%s%c",linha,tab);                                                   //lê palavra e caractere seguinte de tabulação
    return linha;                                                                       //retorna palavra lida
}

DicLDE* encontraNoDic(DicLDE *D, char *linha, int *comp){
    int check=1, c=0;
    char strip[strlen(linha)];

    if(linha==NULL || D->info.palavra==NULL){                                           //checa se a LDE ou a string palavra estiverem vazias
        printf("Erro ao procurar no dicionario");                                       //retorna erro se uma delas estiver
        return NULL;
    }
    *comp+=1;                                                                           //aumenta uma comparacao na variavel

    for(int i = 0 ; i < strlen(linha) ; i++){                                           //percorre string, fazendo lowercase de todas as letras e removendo caracteres não-alfabeticos
      linha[i] = tolower(linha[i]);
      if (isalnum(linha[i]))
        {
            strip[c] = linha[i];
            c++;
        }
    }                                                                                   //definindo novo final da string(o numero de letras na string será sempre menor ou igual que o da string original,
    strip[c] = '\0';                                                                    //então é preciso colocar um novo final na que removemos os caracteres não-alfabeticos)
    strcpy(linha,strip);                                                                //copia nova string para original

    while(check && D->prox!=NULL){                                                      //enquanto não for achada a palavra na LDE ou não chegarmos no fim da lista
        *comp+=1;                                                                       //aumenta numero de comparacoes
        check=strcmp(linha,D->info.palavra);                                            //compara palavra recebida e palavra da lista
        *comp+=1;                                                                       //aumenta numero de comparacoes
        if(check!=0 && D->prox!=NULL){                                                  //se as palavras forem diferentes e o proximo termo não for nulo
            *comp+=1;                                                                   //aumenta numero de comparacoes
            D=D->prox;                                                                  //percorre lista
        }
        else if(!check){                                                                //se as palavras forem iguais
            *comp+=1;                                                                   //aumenta numero de comparacoes e retorna a posicao da palavra na LDE
            return D;
        }
        else
            *comp+=1;                                                                   //aumenta numero de comparacoes
    }
    *comp+=1;                                                                           //aumenta numero de comparacoes
    return NULL;                                                                        //retorna nulo caso não tenha encontrado palavra na LDE
}

int colocaSaida(FILE *saida, DicLDE *pos, char *palavra, char tab){
    if(pos!=NULL){                                                                      //checa se existe a posicao da palavra na string
        fputs(pos->info.lema,saida);                                                    //coloca lema no arquivo de saida
        if(tab==' ' || tab=='\n')                                                       //coloca char de tabulação caso seja válido
            fputs(&tab,saida);
        return 1;
    }
    else{                                                                               //caso não exista posição da palavra na lista
        fputs(palavra,saida);                                                           //coloca a própria palavra no arquivo de saida
        if(tab==' ' || tab=='\n')                                                       //coloca char de tabulação caso seja válido
            fputc(tab,saida);
        return 0;
    }
}


