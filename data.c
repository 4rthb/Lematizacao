#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data.h"

char* ler_arquivo(FILE *arquivo, char linha[30], char* tab){//ERRO: NAO ESTA LENDO A PARTIR DOS NUMEROS
    fscanf(arquivo,"%s%c",linha,tab);                       //le palavra e caractere seguinte de tabulacao
    return linha;                                           //retorna palavra lida
}

//AVL
DicAVL* inicializaAVL(void)
{                                                           
    return NULL;
}

DicAVL* rotacao_direita(DicAVL* p)
{
    DisAVL *u;

    u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->FB = 0;
    p = u;
    return p;
}

DicAVL* rotacao_esquerda(DicAVL* p)
{
    DicAVL *z;

    z = p->dir;
    p->dir = z->esq;
    z->esq = p;
    p->FB = 0;
    p = z;
    return p;
}

DicAVL* rotacao_dupla_direita(DicAVL* p)
{
    DicAVL *u, *v;

    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;
    if (v->FB == 1) p->FB = -1;
        else p->FB = 0;
    if (v->FB == -1) u->FB = 1;
        else u->FB = 0;    
    p = v;
    return p;
}

DicAVL* rotacao_dupla_esquerda(DicAVL* p)
{
    DicAVL *z, *y;

    z = p->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    p->dir = y->esq;
    y->esq = p;
    if (y->FB == -1) p->FB = 1;
        else p->FB = 0;
    if (y->FB == 1) z->FB = -1;
        else z->FB = 0;    
    p = y;
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
        strcpy(a->info.lema, info.lema);
        strcpy(a->info.palavra,info.palavra);
        a->esq = NULL; 
        a->dir = NULL;
        a->FB = 0; 
        *ok = 1;
    }
    else 
    if (strcmp(info.palavra, a->info.palavra)<0) {                          //se conteúdo do novo nodo eh menor do que o conteudo da raiz
        a->esq = InsereAVL(a->esq,info,ok);
        if (*ok) { 
            switch (a->FB) { 
                case -1: a->FB = 0; *ok = 0; break; 
                case 0: a->FB = 1; break; 
                case 1: a=Caso1(a,ok); break;
            } 
        }
    }
    else {                                                                  //se conteúdo do novo nodo eh maior do que o conteudo da raiz
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

    D=inicializaAVL();                                                              //inicializa AVL
    arquivo = fopen(txt,"r");                                                       //abre arquivo de lemas
    if(!arquivo)                                                                    //se nao encontrar arquivo retorna erro
    {
        printf("Erro abrindo o arquivo!");
        return NULL;
    }
    else                                                                            //enquanto nao chega no final do arquivo de lemas, coloca nodos na AVL com as informacoes do arquivo
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

    if(linha == NULL || D->info.palavra == NULL){                   //checa se a AVL ou a string palavra estiverem vazias
        printf("Erro ao procurar no dicionario");                   //retorna erro se uma delas estiver
        return NULL;
    }
    *comp+=1;

    for(int i = 0 ; i < strlen(linha) ; i++){                       //percorre string, fazendo lowercase de todas as letras e removendo caracteres nao-alfabeticos
      linha[i] = tolower(linha[i]);
      if (isalnum(linha[i]))                                        //retorna zero se não for uma letra
        {
            strip[c] = linha[i];
            c++;
        }
    }                                                               //definindo novo final da string(o numero de letras na string sera sempre menor ou igual que o da string original,
    strip[c] = '\0';                                               
    strcpy(linha,strip);                                            //copia nova string para original

//Pesquisa na AVL
    while(check && (D->esq||D->dir))                                //enquanto nao for achada a palavra na AVL ou não chegar ao fim da arvore
    {
        *comp+=1;
        check = strcmp(linha,D->info.palavra);                        //compara palavra recebida e palavra da arvore
        *comp+=1;
        if(!check)                                                  //se as palavras forem iguais
        {
            *comp+=1;
            return D;                                               //retorna a posicao da palavra na AVL
        }
        else
        {
            if(check<0)                                             //Caso a palavra seja menor desloca para o ramo esquerdo
            {
                *comp+=1;
                if(D->esq==NULL) return NULL;
                D=D->esq;
            }
            else                                                    //Caso a palavra seja maior 
            {
                *comp+=1;
                if(D->dir==NULL) return NULL;
                D=D->dir;
            }
        }
    }
    *comp+=1;
    return NULL;                                                    //retorna nulo caso nao tenha encontrado palavra na AVL
}

int colocaSaidaAVL(FILE *saida, DicAVL *pos, char *palavra, char tab)//PROBLEMA PARA IMPRIMIR NO FILE SAIDA
{
    if(pos!=NULL){                                                                      //checa se existe a posicao da palavra na string
        fputs(pos->info.lema,saida);                                                    //coloca lema no arquivo de saida
        if(tab==' ' || tab=='\n')                                                       //coloca char de tabulacao caso seja valido
            fputs(&tab,saida);
        return 1;
    }
    else{                                                                               //caso nao exista posicao da palavra na lista
        fputs(palavra,saida);                                                           //coloca a propria palavra no arquivo de saida
        if(tab==' ' || tab=='\n')                                                       //coloca char de tabulacao caso seja valido
            fputc(tab,saida);
        return 0;
    }
}
