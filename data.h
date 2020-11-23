typedef struct dicionario{
    char palavra[50], lema[50];
}Dic;

typedef struct dicionarioavl{
    Dic info;
    int FB;
    struct dicionarioavl *esq;
    struct dicionarioavl *dir;
}DicAVL;

char* ler_arquivo(FILE *arquivo, char a[30], char* tab);

//AVL
DicAVL* inicializaAVL(void);
DicAVL* rotacao_direita(DicAVL* p);
DicAVL* rotacao_esquerda(DicAVL* p);
DicAVL* rotacao_dupla_direita(DicAVL* p);
DicAVL* rotacao_dupla_esquerda(DicAVL* p);
DicAVL* Caso1(DicAVL *a, int *ok);
DicAVL* Caso2(DicAVL *a , int *ok);
DicAVL* insereAVL(DicAVL *a, Dic info, int *ok, int *comp);
DicAVL* recebeDicionarioAVL(char *txt, int *comp);
DicAVL* encontraNoDicAVL(DicAVL *D, char *linha, int *comp);
int colocaSaidaAVL(FILE *saida, DicAVL *pos, char *palavra, char tab);
