#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data.h"

DicLDE* inicializa(void){                                                           //inicializa lista duplamente encadeada
    return NULL;
}

DicLDE* insereFinal(DicLDE *PtLista, FILE* arquivo){
    DicLDE *novo, *PtAux;

    novo = (DicLDE*) malloc(sizeof(DicLDE));                                        //aloca espa�o na mem�ria para novo nodo
    fscanf(arquivo,"%s %s", novo->info.palavra, novo->info.lema);                   //le a palavra e lema do arquivo de lemas e os colocam no mesmo nodo
    novo->prox = NULL;
    if ((PtLista) == NULL){                                                         //caso lista inicialmente vazia, seta anterior NULL
        PtLista = novo;
        novo->ant = NULL;
    }
    else {                                                                          //caso lista com termos, percorre at� chegar no final e depois coloca nodo
        PtAux = PtLista;
        while (PtAux->prox != NULL){
            PtAux=PtAux->prox;
        }
        PtAux->prox = novo;
        novo->ant = PtAux;
    }
    return PtLista;                                                                 //retorna lista modificada
}

DicLDE* ordenaLista(DicLDE* D){                     //ERRADO: devemos separar em 3 casos: aux->prox->prox==NULL e aux->ant==NULL
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

DicLDE* recebeDicionarioOrdenado(char *txt){                    //ERRADO: sei l� kkkk
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
//fazer uma versão DicAVL
DicLDE* recebeDicionario(char *txt){
    DicLDE *D;

    FILE * arquivo;

    D=inicializa();//chama fun��o que inicializa LDE
    arquivo = fopen(txt,"r");//abre arquivo de lemas
    if(!arquivo)//se nao encontrar arquivo retorna erro
    {
        printf("Erro abrindo o arquivo!");
        return NULL;
    }
    else//enquanto nao chega no final do arquivo de lemas, coloca nodos na LDE com as informacoes do arquivo
    {                                                                           
        while(!feof(arquivo)){
            D=insereFinal(D,arquivo);
        }
    }
    fclose(arquivo);                                                                //fecha arquivo de lemas
    return D;                                                                       //retorna lista criada
}
//da pra reaproveitar na AVl
char* ler_arquivo(FILE *arquivo, char linha[30], char* tab){//ARRUMAR: da pra pegar dois caracteres pra ler 2 tabulacoes seguintes, caso for letra da rewind no ponteiro do arquivo

    fscanf(arquivo,"%s%c",linha,tab);//le palavra e caractere seguinte de tabulacao
    return linha;//retorna palavra lida
}

DicLDE* encontraNoDicOrdenado(DicLDE *D, char *linha, int *comp){   //ERRADO: tirar caracteres n�o-alfabeticos, arrumar while
    int check;

    if(linha==NULL || D->info.palavra==NULL){
        printf("Erro ao procurar no dicionario");
        return NULL;
    }

    for(int i = 0; i < strlen(linha) ; i++){
      linha[i] = tolower(linha[i]);
    }

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

DicLDE* encontraNoDic(DicLDE *D, char *linha, int *comp){
    int check=1, c=0;
    char strip[strlen(linha)];

    if(linha==NULL || D->info.palavra==NULL){//checa se a LDE ou a string palavra estiverem vazias
        printf("Erro ao procurar no dicionario");//retorna erro se uma delas estiver
        return NULL;
    }
    *comp+=1;//aumenta uma comparacao na variavel

    for(int i = 0 ; i < strlen(linha) ; i++){//percorre string, fazendo lowercase de todas as letras e removendo caracteres nao-alfabeticos
      linha[i] = tolower(linha[i]);
      if (isalnum(linha[i]))//retorna zero se não for uma letra
        {
            strip[c] = linha[i];
            c++;
        }
    }//definindo novo final da string(o numero de letras na string ser� sempre menor ou igual que o da string original,
    strip[c] = '\0';//entao 3 preciso colocar um novo final na que removemos os caracteres nao-alfabeticos)
    strcpy(linha,strip);//copia nova string para original

    while(check && D->prox!=NULL){//enquanto nao for achada a palavra na LDE ou nao chegarmos no fim da lista
        *comp+=1;//aumenta numero de comparacoes
        check=strcmp(linha,D->info.palavra);//compara palavra recebida e palavra da lista
        *comp+=1;//aumenta numero de comparacoes
        if(check!=0 && D->prox!=NULL){//se as palavras forem diferentes e o proximo termo nao for nulo
            *comp+=1;//aumenta numero de comparacoes
            D=D->prox;//percorre lista
        }
        else if(!check){//se as palavras forem iguais
            *comp+=1;//aumenta numero de comparacoes e retorna a posicao da palavra na LDE
            return D;
        }
        else
            *comp+=1;//aumenta numero de comparacoes
    }
    *comp+=1;//aumenta numero de comparacoes
    return NULL;//retorna nulo caso nao tenha encontrado palavra na LDE
}

int colocaSaida(FILE *saida, DicLDE *pos, char *palavra, char tab){//ARRUMAR: colocar dois char de tabulacao se existirem
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


