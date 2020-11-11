typedef struct dicionario{
    char palavra[30], lema[30];
} Dic;

typedef struct dicionariolde{
    Dic info;
    struct dicionariolde* ant;
    struct dicionariolde* prox;
} DicLDE;

DicLDE* inicializa(void);
DicLDE* insereFinal(DicLDE *PtLista, FILE* arquivo);
DicLDE* ordenaLista(DicLDE* D);
DicLDE* recebeDicionario(char *txt);
DicLDE* recebeDicionarioOrdenado(char *txt);
char* ler_arquivo(FILE *arquivo, char a[30]);
DicLDE* encontraNoDicOrdenado(DicLDE *D, char linha[30]);
DicLDE* encontraNoDic(DicLDE *D, char *linha);
void colocaSaida(FILE *saida, DicLDE *pos);
