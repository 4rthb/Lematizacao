#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data.h"

DicLDE* inicializa(void){                                                               //inicializa lista duplamente encadeada
    return NULL;
}

DicLDE* insereCresc(DicLDE* ptLista, DicLDE* novo, int* comp){
    DicLDE *ptAux=ptLista;

    if(ptAux==NULL){                                                                    //Se a lista estiver vazia, coloca termo como inicial
        *comp+=1;                                                                       //aumenta numero de comparacoes
        novo->ant=NULL;
        novo->prox=NULL;
        ptLista=novo;
    }
    else{
        *comp+=1;                                                                       //aumenta numero de comparacoes
        while(ptAux->prox!=NULL && strcmp(ptAux->info.palavra,novo->info.palavra)<=0){  //enquanto não chega no fim e não encontrar palavra "maior", percorre dicionario
            *comp+=2;                                                                   //aumenta numero de comparacoes
            ptAux=ptAux->prox;
        }
        *comp+=2;                                                                       //aumenta numero de comparacoes
        if(ptAux->prox==NULL){                                                          //se chegar no final da lista
            *comp+=1;                                                                   //aumenta numero de comparacoes
            if(ptAux->ant==NULL){                                                       //se o ultimo termo tambem for o inicial(lista com um termo)
                *comp+=1;                                                               //aumenta numero de comparacoes
                if(strcmp(ptAux->info.palavra,novo->info.palavra)>0){                   //quando o termo é maior
                    *comp+=1;                                                           //aumenta numero de comparacoes
                    ptAux->ant=novo;
                    novo->ant=NULL;
                    novo->prox=ptAux;
                    ptLista=novo;
                }
                else{                                                                   //quando o termo é menor
                    *comp+=1;                                                           //aumenta numero de comparacoes
                    ptAux->prox=novo;
                    novo->prox=NULL;
                    novo->ant=ptAux;
                }
            }
            else{                                                                       //caso o termo final tenha uma anterior
                *comp+=1;                                                               //aumenta numero de comparacoes
                if(strcmp(ptAux->info.palavra,novo->info.palavra)>0){                   //caso o termo final seja maior
                    *comp+=1;                                                           //aumenta numero de comparacoes
                    novo->ant=ptAux->ant;
                    novo->prox=ptAux;
                    ptAux->ant=novo;
                    novo->ant->prox=novo;
                }
                else{                                                                   //caso o termo final seja menor
                    *comp+=1;                                                           //aumenta numero de comparacoes
                    ptAux->prox=novo;
                    novo->ant=ptAux;
                    novo->prox=NULL;
                }
            }
        }
        else{                                                                           //caso tenha parado por que achou um termo maior
            *comp+=1;                                                                   //aumenta numero de comparacoes
            if(ptAux->ant==NULL){                                                       //este termo é o primeiro da lista
                *comp+=1;                                                               //aumenta numero de comparacoes
                ptAux->ant=novo;
                novo->prox=ptAux;
                novo->ant=NULL;
                ptLista=novo;
            }
            else{                                                                       //este termo não é o primeiro da lista
                *comp+=1;                                                               //aumenta numero de comparacoes
                novo->ant=ptAux->ant;
                novo->prox=ptAux;
                novo->ant->prox=novo;
                ptAux->ant=novo;
            }
        }
    }
    return ptLista;
}

DicLDE* insereOrdenado(DicLDE *PtLista, FILE* arquivo, int* comp){
    DicLDE *novo;

    novo = (DicLDE*) malloc(sizeof(DicLDE));                                            //aloca espa�o na mem�ria para novo nodo
    fscanf(arquivo,"%s %s", novo->info.palavra, novo->info.lema);                       //le a palavra e lema do arquivo de lemas e os colocam no mesmo nodo
    PtLista=insereCresc(PtLista,novo,comp);

    return PtLista;                                                                     //retorna lista modificada
}

DicLDE* recebeDicionarioOrdenado(char *txt, int *comp){
    DicLDE *D;

    FILE * arquivo;

    D=inicializa();                                                                     //chama fun��o que inicializa LDE
    arquivo = fopen(txt,"r");                                                           //abre arquivo de lemas
    if(!arquivo){                                                                       //se n� encontrar arquivo retorna erro
        printf("Erro abrindo o arquivo!");
        return NULL;
    }
    else{                                                                               //enquanto n�o chega no final do arquivo de lemas, coloca nodos na LDE com as informa��es do arquivo
        while(!feof(arquivo)){
            D=insereOrdenado(D,arquivo,comp);
        }
    }
    fclose(arquivo);                                                                    //fecha arquivo de lemas
    return D;                                                                           //retorna lista criada
}

char* ler_arquivo(FILE *arquivo, char linha[30], char* tab){

    fscanf(arquivo,"%s%c",linha,tab);                                                   //l� palavra e caractere seguinte de tabula��o
    return linha;                                                                       //retorna palavra lida
}

DicLDE* encontraNoDicOrdenado(DicLDE *D, char *linha, int *comp){
    int check=1, c=0;
    char strip[strlen(linha)];

    if(linha==NULL || D->info.palavra==NULL){                                           //checa se a LDE ou a string palavra estiverem vazias
        printf("Erro ao procurar no dicionario");                                       //retorna erro se uma delas estiver
        return NULL;
    }
    *comp+=1;                                                                           //aumenta numero de comparacoes
    for(int i = 0 ; i < strlen(linha) ; i++){                                           //percorre string, fazendo lowercase de todas as letras e removendo caracteres n�o-alfabeticos
      linha[i] = tolower(linha[i]);
      if (isalnum(linha[i]))
        {
            strip[c] = linha[i];
            c++;
        }
    }                                                                                   //definindo novo final da string(o numero de letras na string ser� sempre menor ou igual que o da string original,
    strip[c] = '\0';                                                                    //ent�o � preciso colocar um novo final na que removemos os caracteres n�o-alfabeticos)
    strcpy(linha,strip);                                                                //copia nova string para original

    while(check>=0 && D!=NULL){                                                         //percorre dicionario enquanto não chega no fim e palavras não são maiores do que a recebida
        check=strcmp(linha,D->info.palavra);                                            //retorna 0 quando encontra palavra igual, ou diferente dependendo de qual string é "maior"
        *comp+=2;                                                                       //aumenta numero de comparacoes
        if(!check){                                                                     //quando encontra a palavra no dicionario, retorna posicao dela no dicionario
            return D;
        }
        D=D->prox;
    }
    return NULL;                                                                        //retorna NULL quando não encontra no dicionario
}

int colocaSaida(FILE *saida, DicLDE *pos, char *palavra, char tab){
    if(pos!=NULL){                                                                      //checa se existe a posicao da palavra na string
        fputs(pos->info.lema,saida);                                                    //coloca lema no arquivo de saida
        if(tab==' ' || tab=='\n')                                                       //coloca char de tabula��o caso seja v�lido
            fputs(&tab,saida);
        return 1;
    }
    else{                                                                               //caso n�o exista posi��o da palavra na lista
        fputs(palavra,saida);                                                           //coloca a pr�pria palavra no arquivo de saida
        if(tab==' ' || tab=='\n')                                                       //coloca char de tabula��o caso seja v�lido
            fputc(tab,saida);
        return 0;
    }
}


