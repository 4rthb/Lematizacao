#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data.h"

int main (int argc, char *argv[])
{
    FILE *entrada;
    FILE *saida;
    DicLDE *D, *posicao;
    char palavra[30];

    if (argc!=4)
    {
        printf ("Numero incorreto de parametros.\n Para chamar o programa digite: ./<programa> <dicionario.txt> <entrada.txt> <saida.txt>");
        return 1;
    }
    else
    {
        D=recebeDicionario(argv[1]);
        if((entrada=fopen(argv[2],"r")) == NULL){
            printf("Não foi possível ler arquivo de entrada");
            return 2;
        }
        saida=fopen(argv[3],"a+");
        while(!feof(entrada)){
            strcpy(palavra,ler_arquivo(entrada,palavra));
            posicao=encontraNoDic(D,palavra);
            colocaSaida(saida,posicao);

        }
        return 0;
    }

}


