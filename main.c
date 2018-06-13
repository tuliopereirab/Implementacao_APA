#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//EXTERNAS
void gerar(char entI[], char entJ[], char arquivo[]);
void ajuda();
void forcaBruta(char arquivo[]);
void dinamica(char arquivo[]);
void gulosa(char arquivo[]);


int main(int argc, char **argv){
    int tam, op;
    tam = argc;
    if(tam == 1){
        printf("Não existem argumentos na chamada. Utilize './Viajante -h' ou './Viajante --help' para ajuda.\n");
        return 0;
    }

    if(((strcmp(argv[1], "-h")) == 0) || ((strcmp(argv[1], "--help")) == 0))
        op = 0;
    else if(((strcmp(argv[1], "-g")) == 0) || ((strcmp(argv[1], "--gerar")) == 0))
        op = 1;
    else if(((strcmp(argv[1], "-s")) == 0) || ((strcmp(argv[1], "--soluciona")) == 0))            //./Viajante -s <tipo (-b, -g, -d)> <arquivo>
        op = 10;
    else
        op = 99;

    switch(op){
        case 0:
            ajuda();
            break;
        case 1:
            if(tam != 5){
                printf("Número incorreto de parametros para esta operação. \nUtilize './Viajante -h' ou './Viajante --help' para ajuda.\n");
                return 0;
            }
            gerar(argv[2], argv[3], argv[4]);
            break;
        case 10:
            if(tam != 4){
                printf("Número incorreto de parametros para esta operação. \nUtilize './Viajante -h' ou './Viajante --help' para ajuda.\n");
                return 0;
            }
            if((strcmp(argv[2], "-b")) == 0)
                forcaBruta(argv[3]);
            else if((strcmp(argv[2], "-g")) == 0)
                gulosa(argv[3]);
            else if((strcmp(argv[2], "-d")) == 0)
                dinamica(argv[3]);
            else{
                printf("Solução solicitada inexistente.\nUtilize './Viajante -h' ou './Viajante --help' para ajuda.\n");
                return 0;
            }
            break;
        case 99:
            printf("Opção desejada não existe. Utilize './Viajante -h' ou './Viajante --help' para ajuda.\n");
            break;
    }
    return 0;
}
