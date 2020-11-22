typedef struct dicionario{
    char palavra[30], lema[30];
} Dic;

typedef struct dicionariolde{
    Dic info;
    struct dicionariolde* ant;
    struct dicionariolde* prox;
} DicLDE;

DicLDE* inicializa(void);                                                       //fun��o que inicializa lista
DicLDE* insereCresc(DicLDE* ptLista, DicLDE* novo, int* comp);
DicLDE* insereOrdenado(DicLDE *PtLista, FILE* arquivo, int *comp);              //fun��o que insere nodo no final da lista
DicLDE* recebeDicionarioOrdenado(char *txt, int *comp);                         //fun��o que recebe o dicion�rio, o coloca na lista e o ordena
char* ler_arquivo(FILE *arquivo, char a[30], char* tab);                        //fun��o que l� palavra do arquivo de entrada
DicLDE* encontraNoDicOrdenado(DicLDE *D, char linha[30], int *comp);            //fun��o que encontra palavra dada no dicion�rio ordenado
int colocaSaida(FILE *saida, DicLDE *pos, char *palavra, char tab);             //fun��o que coloca palavra ou lema(se encontrado) no arquivo de sa�da
