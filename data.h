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
DicLDE* recebeDicionario(char *txt);                                            //fun��o que recebe o dicion�rio e coloca seus termos na lista
char* ler_arquivo(FILE *arquivo, char a[30], char* tab);                        //fun��o que l� palavra do arquivo de entrada
DicLDE* encontraNoDic(DicLDE *D, char *linha, int *comp);                       //fun��o que encontra palavra dada no dicion�rio
int colocaSaida(FILE *saida, DicLDE *pos, char *palavra, char tab);             //fun��o que coloca palavra ou lema(se encontrado) no arquivo de sa�da
