#include <stdio.h>
#include <stdlib.h>

void ajuda(){
    printf("LISTA DE COMANDOS: \n");
    printf("* GERAR ARQUIVO: \n\t- './Viajante -g <valor_i> <nome_arquivo>'\n");
    printf("\t- './Viajante --gerar <valor_i> <nome_arquivo>'\n");
    printf("* SOLUCIONAR 'Caixeiro Viajante': \n\t- './Viajante -s <solucao***> <nome_arquivo>'\n");
    printf("\t- './Viajante --soluciona <solucao***> <nome_arquivo>'\n");
    printf("\n---------------------------\n");
    printf("*** Solucao: \n");
    printf("\t- '-b': solução de Força Bruta\n\t- '-g': solução de Programação Gusola\n\t- '-d': solução de Programação Dinâmica\n");
    system(EXIT_SUCCESS);
}
