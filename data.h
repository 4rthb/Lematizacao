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
DicLDE* recebeDicionario(char *txt);

