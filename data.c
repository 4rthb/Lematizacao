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

//AVL
DicAVL* inicializaAVL(void)//inicializa AVL
{                                                           
    return NULL;
}

DicAVL* rotacao_direita(DicAVL* p)
{
    DisAVL *u;

    u=p->esq;
    p->esq=u->dir;
    u->dir=p;
    p->FB=0;
    p=u;
    return p;
}

DicAVL* rotacao_esquerda(DicAVL* p)
{
    DicAVL *z;

    z=p->dir;
    p->dir=z->esq;
    z->esq=p;
    p->FB=0;
    p=z;
    return p;
}

DicAVL* rotacao_dupla_direita(DicAVL* p)
{
    DicAVL *u, *v;

    u=p->esq;
    v=u->dir;
    u->dir=v->esq;
    v->esq=u;
    p->esq=v->dir;
    v->dir=p;
    if (v->FB==1) p->FB=-1;
        else p->FB=0;
    if (v->FB==-1) u->FB=1;
        else u->FB=0;    
    p=v;
    return p;
}

DicAVL* rotacao_dupla_esquerda(DicAVL* p)
{
    DicAVL *z, *y;

    z=p->dir;
    y=z->esq;
    z->esq=y->dir;
    y->dir=z;
    p->dir=y->esq;
    y->esq=p;
    if (y->FB==-1) p->FB=1;
        else p->FB=0;
    if (y->FB==1) z->FB=-1;
        else z->FB=0;    
    p=y;
    return p;
}

DicAVL* Caso1(DicAVL *a, int *ok)
{
    DicAVL *z; 
    z = a->esq; 
    if (z->FB == 1) 
        a = rotacao_direita(a);
    else 
        a = rotacao_dupla_direita(a);

    a->FB = 0;  
    *ok = 0;
    return a;
}

DicAVL* Caso2 (DicAVL *a , int *ok) {
    DicAVL *z;
    z = a->dir;     
    if (z->FB == -1) 
        a = rotacao_esquerda(a);
    else 
        a = rotacao_dupla_esquerda(a);
    
    a->FB = 0; 
    *ok = 0; 
    return a;
}

DicAVL* insereAVL(DicAVL *a, Dic info, int *ok)
{
    if (a == NULL) { 
        a = (DicAVL*) malloc(sizeof(DicAVL)); 
        a->info.lema = info.lema; 
        a->info.palavra = info.palavra;
        a->esq = NULL; 
        a->dir = NULL;
        a->FB = 0; 
        *ok = 1;
    }
    else 
    if (strcmp(info.palavra, a->info.palavra)<0) { //se conteúdo do novo nodo é menor do que o conteudo da raiz
            a->esq = InsereAVL(a->esq,info,ok);
        if (*ok) { 
            switch (a->FB) { 
                case -1: a->FB = 0; *ok = 0; break; 
                case 0: a->FB = 1; break; 
                case 1: a=Caso1(a,ok); break;
            } 
        }
    }
    else {
        a->dir = InsereAVL(a->dir,info,ok); 
        if (*ok) { 
            switch (a->FB) { 
                case 1: a->FB = 0; *ok = 0; break; 
                case 0: a->FB = -1; break; 
                case -1: a = Caso2(a,ok); break;
            }
        }
    }
    return a;
}
    
DicAVL* recebeDicionarioAVL(char *txt)
{
    DicAVL *D;
    Dic info;
    FILE * arquivo;
    int ok=0;

    D=inicializaAVL();//inicializa AVL
    arquivo = fopen(txt,"r");//abre arquivo de lemas
    if(!arquivo)//se nao encontrar arquivo retorna erro
    {
        printf("Erro abrindo o arquivo!");
        return NULL;
    }
    else//enquanto nao chega no final do arquivo de lemas, coloca nodos na AVL com as informacoes do arquivo
    {                                                                           
        while(!feof(arquivo)){
            fscanf(arquivo,"%s %s", info.palavra, info.lema);
            D=insereAVL(D,info,&ok);
        }
    }
    fclose(arquivo);                                                                //fecha arquivo de lemas
    return D;                                                                       //retorna raiz da AVL criada
}

DicAVL* encontraNoDicAVL(DicAVL *D, char *linha, int *comp){
    int check=1, c=0;
    char strip[strlen(linha)];

    if(linha==NULL || D->info.palavra==NULL){//checa se a AVL ou a string palavra estiverem vazias
        printf("Erro ao procurar no dicionario");//retorna erro se uma delas estiver
        return NULL;
    }
    *comp+=1;

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

//Pesquisa na AVL
    while(check && (D->esq||D->dir))//enquanto nao for achada a palavra na AVL ou não chegar ao fim da arvore
    {
        *comp+=1;
        check=strcmp(linha,D->info.palavra);//compara palavra recebida e palavra da arvore
        *comp+=1;
        if(!check)//se as palavras forem iguais
        {
            *comp+=1;
            return D;//retorna a posicao da palavra na AVL
        }
        else
        {
            if(check<0)//Caso a palavra seja menor desloca para o ramo esquerdo
            {
                *comp+=1;
                D=D->esq;
            }
            else//Caso a palavra seja maior 
            {
                *comp+=1;
                D=D->dir;
            }
        }
    }
    *comp+=1;
    return NULL;//retorna nulo caso nao tenha encontrado palavra na AVL
}

int colocaSaidaAVL(FILE *saida, DicAVL *pos, char *palavra, char tab)
{//ARRUMAR: colocar dois char de tabulacao se existirem
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
