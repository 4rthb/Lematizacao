typedef struct dicionario{
    char palavra[30], lema[30];
} Dic;

typedef struct dicionariolde{
    Dic info;
    struct dicionariolde* ant;
    struct dicionariolde* prox;
} DicLDE;

DicLDE* inicializa(void);                                                       //função que inicializa lista
DicLDE* insereFinal(DicLDE *PtLista, FILE* arquivo);                            //função que insere nodo no final da lista
DicLDE* recebeDicionario(char *txt);                                            //função que recebe o dicionário e coloca seus termos na lista
char* ler_arquivo(FILE *arquivo, char a[30], char* tab);                        //função que lê palavra do arquivo de entrada
DicLDE* encontraNoDic(DicLDE *D, char *linha, int *comp);                       //função que encontra palavra dada no dicionário
int colocaSaida(FILE *saida, DicLDE *pos, char *palavra, char tab);             //função que coloca palavra ou lema(se encontrado) no arquivo de saída
