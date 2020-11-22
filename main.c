#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data.h"

int comp=0;//vari�vel global para quantidade de compara��es com a estrutura

int main (int argc, char *argv[])
{
    FILE *entrada;
    FILE *saida;
    DicAVL *D, *posicao;
    char palavra[30], tab;

    if (argc!=4)                                                        //caso seja passado um numero menor/maior de argumentos na linha de comando
    {
        printf ("Numero incorreto de parametros.\n Para chamar o programa digite: ./<programa> <dicionario.txt> <entrada.txt> <saida.txt>");
        return 1;
    }
    else                                                                //caso seja passado exatos 4 argumentos
    {   
        D=recebeDicionarioAVL(argv[1]);                                 //passa argumento 2(nome do dicionario) para funcao que o coloca em uma AVL
        if((entrada=fopen(argv[2],"r")) == NULL){                       //abre arquivo de entrada(texto a ser lematizado) e checa se ele existe
            printf("Nao foi possivel ler arquivo de entrada");
            return 2;
        }
        saida=fopen(argv[3],"a+");                                      //abre arquivo de saida com nome disponibilizado pela linha de comando
        while(!feof(entrada)){                                          //enquanto nao chega no final do arquivo de entrada(texto a ser lematizado)
            strcpy(palavra,ler_arquivo(entrada,palavra,&tab));          //chama funcao que le palavra do arquivo e a copia para variavel local
            posicao=encontraNoDicAVL(D,palavra,&comp);                  //chama funcao que procura posicao da palavra na arvore(se existir) e a devolve seu lema
            colocaSaidaAVL(saida,posicao,palavra,tab);                  //chama funcao que coloca palavra ou lema(se achado) no arquivo de saida
        }
        fclose(entrada);                                                //fecha arquivos abertos
        fclose(saida);
        printf("Numero de comparacoes: %d\n", comp);                    //imprime numero de comparacoes, com a estrutura AVL, feitos no codigo
        return 0;
    }

}


