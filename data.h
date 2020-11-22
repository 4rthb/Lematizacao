typedef struct dicionario{
    char palavra[30], lema[30];
} Dic;

typedef struct dicionariolde{
    Dic info;
    struct dicionariolde* ant;
    struct dicionariolde* prox;
} DicLDE;

typedef struct dicionarioavl{
    Dic info;
    int FB;
    struct dicionarioavl *esq;
    struct dicionarioavl *dir;
}DicAVL;


DicLDE* inicializa(void);
DicLDE* insereFinal(DicLDE *PtLista, FILE* arquivo);
DicLDE* ordenaLista(DicLDE* D);
DicLDE* recebeDicionario(char *txt);
DicLDE* recebeDicionarioOrdenado(char *txt);
char* ler_arquivo(FILE *arquivo, char a[30], char* tab);
DicLDE* encontraNoDicOrdenado(DicLDE *D, char linha[30], int *comp);
DicLDE* encontraNoDic(DicLDE *D, char *linha, int *comp);
int colocaSaida(FILE *saida, DicLDE *pos, char *palavra, char tab);
//AVL
DicAVL* inicializaAVL(void);
DicAVL* rotacao_direita(DicAVL* p);
DicAVL* rotacao_esquerda(DicAVL* p);
DicAVL* rotacao_dupla_direita(DicAVL* p);
DicAVL* rotacao_dupla_esquerda(DicAVL* p);
DicAVL* Caso1(DicAVL *a, int *ok);
DicAVL* Caso2 (DicAVL *a , int *ok);
DicAVL* insereAVL(DicAVL *a, Dic info, int *ok);
DicAVL* recebeDicionarioAVL(char *txt);
DicAVL* encontraNoDicAVL(DicAVL *D, char *linha, int *comp);
int colocaSaidaAVL(FILE *saida, DicAVL *pos, char *palavra, char tab);
