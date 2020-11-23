#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data.h"

int comp=0;                                                                             //vari�vel global para quantidade de compara��es com a estrutura

int main (int argc, char *argv[])
{
    FILE *entrada;
    FILE *saida;
    DicLDE *D, *posicao;
    char palavra[50], tab;

    if (argc!=4)                                                                        //caso seja passado um n�mero menor/maior de argumentos na linha de comando
    {
        printf ("Numero incorreto de parametros.\n Para chamar o programa digite: ./<programa> <dicionario.txt> <entrada.txt> <saida.txt>");
        return 1;
    }
    else                                                                                //caso seja passado exatos 4 argumentos
    {
        D=recebeDicionario(argv[1]);                                                    //passa argumento 2(nome do dicionario) para fun��o que o coloca em uma LDE
        if((entrada=fopen(argv[2],"r")) == NULL){                                       //abre arquivo de entrada(texto a ser lematizado) e checa se ele existe
            printf("N�o foi poss�vel ler arquivo de entrada");
            return 2;
        }
        saida=fopen(argv[3],"a+");                                                      //abre arquivo de sa�da com nome disponibilizado pela linha de comando
        while(!feof(entrada)){                                                          //enquanto n�o chega no final do arquivo de entrada(texto a ser lematizado)
            strcpy(palavra,ler_arquivo(entrada,palavra,&tab));                          //chama fun��o que l� palavra do arquivo e a copia para vari�vel local
            posicao=encontraNoDic(D,palavra,&comp);                                     //chama fun��o que procura posi��o da palavra na lista(se existir) e a devolve
            colocaSaida(saida,posicao,palavra,tab);                                     //chama fun��o que coloca lema(se achado) no arquivo de sa�da
        }
        fclose(entrada);                                                                //fecha arquivos abertos
        fclose(saida);
        printf("Numero de comparacoes: %d\n", comp);                                    //imprime numero de compara��es com a estrutura feitos no c�digo
        return 0;
    }

}


