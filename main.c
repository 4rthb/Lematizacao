#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

int main (int argc, char *argv[])
{
    FILE * entrada;
    FILE * saida;

    if (argc!=4)
    {
        printf ("Numero incorreto de parametros.\n Para chamar o programa digite: ./<programa> <dicionario.txt> <entrada.txt> <saida.txt>");
        return 1;
    }
    else
    {
        recebeDicionario(argv[1]);
        return 0;
    }
}


