typedef struct dicionario{
    char palavra[30], lema[30];
} Dic;

typedef struct dicionariolde{
    Dic info;
    struct dicionariolde* ant;
    struct dicionariolde* prox;
} DicLDE;

DicLDE* inicializa(void);                                                       //fun��o que inicializa lista
DicLDE* insereFinal(DicLDE *PtLista, FILE* arquivo);                            //fun��o que insere nodo no final da lista
DicLDE* ordenaLista(DicLDE* D);                                                 //fun��o que ordena lista com base na ordem lexicogr�fica
DicLDE* recebeDicionario(char *txt);                                            //fun��o que recebe o dicion�rio e coloca seus termos na lista
DicLDE* recebeDicionarioOrdenado(char *txt);                                    //fun��o que recebe o dicion�rio, o coloca na lista e o ordena
char* ler_arquivo(FILE *arquivo, char a[30], char* tab);                        //fun��o que l� palavra do arquivo de entrada
DicLDE* encontraNoDicOrdenado(DicLDE *D, char linha[30], int *comp);            //fun��o que encontra palavra dada no dicion�rio ordenado
DicLDE* encontraNoDic(DicLDE *D, char *linha, int *comp);                       //fun��o que encontra palavra dada no dicion�rio
int colocaSaida(FILE *saida, DicLDE *pos, char *palavra, char tab);             //fun��o que coloca palavra ou lema(se encontrado) no arquivo de sa�da
