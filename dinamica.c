#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _matrizCustos{
    char *passouPor;
    int custo;
    int usado;
    int numVertices;
    float custoBeneficio;
    int status;      // -1- não pode ser usado (abaixo da diagonal principal); 0- ainda não foi utilizado;  1- já foi utilizado
};


// EXTERNAS
int **lerArquivo(char arquivo[]);
int retI();
int retJ();
int **matriz;
int i, j;
struct _matrizCustos **matrizCustos;
char *caminhoFinal;


//int** matrizCustos;
void gerarCustos(int ii, int k);
void criaMatrizCustos();
void imprimeMatriz();
void imprimirMelhor(int final);
void contadorVertices();

void dinamica(char arquivo[]){
    int x, y;
    matriz = lerArquivo(arquivo);
    i = retI();
    j = retJ();
    criaMatrizCustos();

    for(x=1;x<i;x++){
        for(y=0;y<i;y++){
            if((y+x) < i)
                gerarCustos(y, x);
        }
    }

    contadorVertices();
    imprimeMatriz();

    printf("\n\n");
    strcpy(caminhoFinal, " ");
    //imprimirMelhor(0);

    //printf("caminho: %s\n", caminhoFinal);

    system(EXIT_SUCCESS);
}

void gerarCustos(int ii, int k){
    char aux[10];
    if(k==1){
        //printf("Primeira!\n");
        sprintf(aux, "%i", ii);
        strcpy(matrizCustos[ii][ii+k].passouPor, aux);
        strcat(matrizCustos[ii][ii+k].passouPor, " ");
        matrizCustos[ii][ii+1].custo = matriz[ii][ii+1];
    }
    else{
        if((matrizCustos[ii][ii+(k-1)].custo + matrizCustos[ii+(k-1)][ii+k].custo) < matriz[ii][ii+k]){
            //printf("Soma!\n");
            sprintf(aux, "%i", ii+k);
            strcat(matrizCustos[ii][ii+k].passouPor, matrizCustos[ii][ii+(k-1)].passouPor);
            strcat(matrizCustos[ii][ii+k].passouPor, " ");
            strcat(matrizCustos[ii][ii+k].passouPor, aux);
            matrizCustos[ii][ii+k].custo = matrizCustos[ii][ii+(k-1)].custo + matrizCustos[ii+(k-1)][ii+k].custo;
        }else{
            //printf("Matriz original!\n");
            sprintf(aux, "%i", ii);
            strcpy(matrizCustos[ii][ii+k].passouPor, aux);
            strcat(matrizCustos[ii][ii+k].passouPor, " ");
            sprintf(aux, "%i", ii+k);
            strcat(matrizCustos[ii][ii+k].passouPor, aux);
            matrizCustos[ii][ii+k].custo = matriz[ii][ii+k];
        }
    }
}

void criaMatrizCustos(){
    int x, y;
    matrizCustos = (struct _matrizCustos**)malloc(sizeof(struct _matrizCustos*)*i);
    for(x=0;x<i;x++){
        matrizCustos[x] = (struct _matrizCustos*)malloc(sizeof(struct _matrizCustos)*i);
        for(y=0;y<i;y++){
            matrizCustos[x][y].custo = 0;
            matrizCustos[x][y].passouPor = malloc(sizeof(char)*i*4);
            matrizCustos[x][y].usado = 0;
        }
    }
    caminhoFinal = malloc(sizeof(char)*i*4);
    printf("Matriz de custos criada...\n");
}

void imprimeMatriz(){
    int x, y;
    for(x=0;x<i;x++){
        for(y=0;y<i;y++)
            printf("%i\t", matrizCustos[x][y].custo);
            //printf("%s ||", matrizCustos[x][y].passouPor);
        printf("\n");
    }
    printf("\n--------------------------- VERTICES PASSADOS ---------------------------\n");
    for(x=0;x<i;x++){
        for(y=0;y<i;y++)
            printf("%s\t", matrizCustos[x][y].passouPor);
            //printf("%s ||", matrizCustos[x][y].passouPor);
        printf("\n");
    }
    printf("\n--------------------------- CUSTO custoBeneficio ---------------------------\n");
    for(x=0;x<i;x++){
        for(y=0;y<i;y++)
            printf("%.2f\t", matrizCustos[x][y].custoBeneficio);
            //printf("%s ||", matrizCustos[x][y].passouPor);
        printf("\n");
    }
    printf("\n--------------------------- NUM VERTICES ---------------------------\n");
    for(x=0;x<i;x++){
        for(y=0;y<i;y++)
            printf("%i\t", matrizCustos[x][y].status);
            //printf("%s ||", matrizCustos[x][y].passouPor);
        printf("\n");
    }
}


void imprimirMelhor(int final){
    int x, y;
    int statusFinal = 1;
    int menorVal=-1;
    int menorI=-1;
    int menorJ=-1;
    if(final == 0)
        for(x=0;x<i;x++){
            printf("X= %i\n", x);
            if(x+1<i){
                for(y=x+1; y<i; y++){
                    printf("y = %i\n", y);
                    if(menorVal == -1){
                        if(matrizCustos[x][y].usado == 0){
                            printf("Menor val!\n");
                            menorVal = matrizCustos[x][y].custo;
                            menorI = x;
                            menorJ = y;
                            statusFinal = 0;
                        }
                    }else{
                        if(matrizCustos[x][y].custo < menorVal){
                            printf("Achou menor!\n");
                            if(matrizCustos[x][y].usado == 0){
                                printf("Usou!\n");
                                menorVal = matrizCustos[x][y].custo;
                                menorI = x;
                                menorJ = y;
                                statusFinal = 0;
                            }
                        }
                    }
                }
            }
        }
        strcat(caminhoFinal, matrizCustos[menorI][menorJ].passouPor);
        strcat(caminhoFinal, " ");
        matrizCustos[menorI][menorJ].usado = 1;
        if(final == 0){
            printf("Novamente!: %i\n", statusFinal);
            imprimirMelhor(statusFinal);
        }

}

void contadorVertices(){
    int x, y, z;
    for(x=0;x<i;x++){
        for(y=0;y<j;y++){
            z=0;
            matrizCustos[x][y].numVertices = 0;
            while(matrizCustos[x][y].passouPor[z] != '\0'){
                if(matrizCustos[x][y].passouPor[z] == ' ')
                    matrizCustos[x][y].numVertices++;
                z++;
            }
            if((y < x) || (x == y)){
                matrizCustos[x][y].numVertices = 0;
                matrizCustos[x][y].status = -1;
            }else{
                matrizCustos[x][y].numVertices++;
                matrizCustos[x][y].custoBeneficio = (float)matrizCustos[x][y].custo / (float)matrizCustos[x][y].numVertices;
                matrizCustos[x][y].status = 0;
            }
        }
    }
}
