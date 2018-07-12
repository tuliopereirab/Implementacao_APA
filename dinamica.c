#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct _matrizCustos{
    char *passouPor;
    int custo;
    int usado;
    int numVertices;
    float custoBeneficio;
    int status;      // -1- não pode ser usado (abaixo da diagonal principal); 0- ainda não foi utilizado
};


// EXTERNAS
int **lerArquivo(char arquivo[]);
int retI();
int retJ();
int **matriz;
int i, j;
int verificarVerticesDin(char passouPor[], int index, int numVertices);
int contarVerticesDin(char passouPor[]);
int somatorioDistancias=0;

struct _matrizCustos **matrizCustos;

char *caminhoFinal;
int *vetPassados;


//int** matrizCustos;
int confirmacaoImpressao();
int melhorCaminho();
void termina();
int verifFinal();
void gerarCustos(int ii, int k);
void criaMatrizCustos();
void imprimeMatriz();
void imprimirMelhor(int final);
void contadorVertices();

void dinamica(char arquivo[]){
    int x, y;
    int retorno;
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
    vetPassados = calloc(1, sizeof(int)*i);

    printf("Encontrando melhor caminho...\n");
    retorno = melhorCaminho(1);
    for(x=0;x<i;x++) printf("%i ", vetPassados[x]);
    while((verifFinal() != 0) && (retorno != 0))  // verifFinal: 0-> acabou!; 1-> segue            retorno: 0-> acabou, 1-> segue
        retorno = melhorCaminho(0);

    imprimeMatriz();
    termina();
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

int confirmacaoImpressao(){
    char op;
    printf("Matriz muito grande: [%i][%i]\nDeseja imprimir? [y/n] -> ", i, j);
    scanf("%c", &op);
    while(op != 'y' && op != 'n'){
        printf("\nOpção digitada inválida!\nTente novamente.");
        printf("\nDeseja imprimir matriz [%i][%i]? [y/n] -> ", i, j);
        scanf("%c", &op);
    }
    if(op == 'y') return 1;
    if(op == 'n') return 0;
    return -1;
}

void imprimeMatriz(){
    int x, y;
    int verifImp;
    if(i > 20) verifImp = confirmacaoImpressao();
    else verifImp = 1;     // 1-> indica que é para imprimir, 0-> indica que não é pra imprimir, -1-> erro
    if(verifImp == 1){
        printf("\n--------------------------- CUSTO ---------------------------\n");
        for(x=0;x<i;x++){
            for(y=0;y<i;y++)
                printf("%i\t", matrizCustos[x][y].custo);
                //printf("%s ||", matrizCustos[x][y].passouPor);
            printf("\n");
        }
        // printf("\n--------------------------- VERTICES PASSADOS ---------------------------\n");
        // for(x=0;x<i;x++){
        //     for(y=0;y<i;y++)
        //         printf("%s\t", matrizCustos[x][y].passouPor);
        //         //printf("%s ||", matrizCustos[x][y].passouPor);
        //     printf("\n");
        // }
        // printf("\n--------------------------- CUSTO custoBeneficio ---------------------------\n");
        // for(x=0;x<i;x++){
        //     for(y=0;y<i;y++)
        //         printf("%.2f\t", matrizCustos[x][y].custoBeneficio);
        //         //printf("%s ||", matrizCustos[x][y].passouPor);
        //     printf("\n");
        // }
        // printf("\n--------------------------- NUM VERTICES ---------------------------\n");
        // for(x=0;x<i;x++){
        //     for(y=0;y<i;y++)
        //         printf("%i\t", matrizCustos[x][y].numVertices);
        //         //printf("%s ||", matrizCustos[x][y].passouPor);
        //     printf("\n");
        // }
        // printf("\n--------------------------- STATUS ---------------------------\n");
        // for(x=0;x<i;x++){
        //     for(y=0;y<i;y++)
        //         printf("%i\t", matrizCustos[x][y].status);
        //         //printf("%s ||", matrizCustos[x][y].passouPor);
        //     printf("\n");
        // }
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
            if((y < x) || (x == y) || y == (x+1)){
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

int melhorCaminho(int inicio){
    int menorX=-1, menorY, y, x, statLeituraMatriz=0;   //0 nenhuma posição da matriz disponivel; 1 existe posição disponivel
    int numVertices, verticeUsado;
    int vertice;
    char auxVertice[15];
    int menorX1=-1, menorX2=-1, menorY1=-1,menorY2=-1;
    char *aux = malloc(sizeof(char)*i*4);
    if(inicio == 1){
        for(x=0;x<i;x++){
            for(y=0;y<i;y++){
                if((matrizCustos[x][y].status != -1) && (matrizCustos[x][y].status != 1)){
                    statLeituraMatriz=1;
                    if(menorX == -1){
                        if(matrizCustos[x][y].usado == 0){
                            menorX = x;
                            menorY = y;
                        }
                    }
                    if(matrizCustos[x][y].usado == 0){
                        if(matrizCustos[x][y].custoBeneficio < matrizCustos[menorX][menorY].custoBeneficio){
                            menorX = x;
                            menorY = y;
                        }
                    }
                }
            }
        }
    }else{
        numVertices = contarVerticesDin(caminhoFinal);
        verticeUsado = verificarVerticesDin(caminhoFinal, numVertices-1, numVertices);
        for(x=0;x<i;x++){
            if((matrizCustos[x][verticeUsado].status != -1) && (matrizCustos[x][verticeUsado].status != 1)){
                if(menorX1 == -1){
                    if(matrizCustos[x][verticeUsado].usado == 0)
                        menorX1 = x;
                        menorY1 = verticeUsado;
                }else{
                    if(matrizCustos[x][verticeUsado].custoBeneficio < matrizCustos[menorX1][menorY1].custoBeneficio){
                        if(matrizCustos[x][verticeUsado].usado == 0)
                            menorX1 = x;
                            menorY1 = verticeUsado;
                    }
                }
            }
        }
        for(y=0;y<i;y++){
            if((matrizCustos[verticeUsado][y].status != -1) && (matrizCustos[verticeUsado][y].status != 1)){
                if(matrizCustos[verticeUsado][y].usado == 0){
                    if(menorY2 == -1){
                        if(matrizCustos[verticeUsado][y].usado == 0)
                            menorY2 = y;
                            menorX2 = verticeUsado;
                    }else{
                        if(matrizCustos[verticeUsado][y].custoBeneficio < matrizCustos[menorX2][menorY2].custoBeneficio){
                            menorY2 = y;
                            menorX2 =verticeUsado;
                        }
                    }
                }
            }
        }
        if((menorX1 != -1) && (menorY2 != -1)){
            if(matrizCustos[menorX1][menorY1].custoBeneficio < matrizCustos[menorX2][menorY2].custoBeneficio){
                menorY = menorY1;
                menorX = menorX1;
            }else{
                menorY = menorY2;
                menorX = menorX2;
            }
        }else if((menorX1 == -1) && (menorY2 != -1)){
            menorY = menorY2;
            menorX = menorX2;
        }else if((menorY2 == -1) && (menorX1 != -1)){
            menorY = menorY1;
            menorX = menorX1;
        }else{
            printf("Nao achou caminho!\n");
            return 0;
        }
    }
    //if(statLeituraMatriz == 0) system(EXIT_SUCCESS);
    strcpy(aux, caminhoFinal);
    matrizCustos[menorX][menorY].usado = 1;
    numVertices = contarVerticesDin(matrizCustos[menorX][menorY].passouPor);
    if(inicio == 1){
        for(x=0;x<numVertices;x++){
            vertice = verificarVerticesDin(matrizCustos[menorX][menorY].passouPor, x, numVertices);
            if((vetPassados[vertice] == 0)){
                sprintf(auxVertice, " %i", vertice);
                strcat(aux, auxVertice);
            }else{
                printf("Não pode usar %i %i\n", menorX, menorY);
                free(aux);
                return 1;
            }
        }
    }else{
        for(x=0;x<numVertices;x++){
            vertice = verificarVerticesDin(matrizCustos[menorX][menorY].passouPor, x, numVertices);
            if((vetPassados[vertice] == 0) || (vertice == verticeUsado)){
                if(vertice != verticeUsado){
                    sprintf(auxVertice, " %i", vertice);
                    strcat(aux, auxVertice);
                }
            }else{
                free(aux);
                return 1;
            }
        }
    }
    strcpy(caminhoFinal, aux);
    printf("Caminho: %s\n", caminhoFinal);
    numVertices = contarVerticesDin(caminhoFinal);
    for(x=1;x<numVertices;x++){
        vertice = verificarVerticesDin(caminhoFinal, x, numVertices);
        vetPassados[vertice] = 1;
    }
    free(aux);
     // for(x=0;x<i;x++){
     //     for(y=0;y<i;y++)
     //         printf("%i\t", matrizCustos[x][y].usado);
     //         //printf("%s ||", matrizCustos[x][y].passouPor);
     //     printf("\n");
     // }
    somatorioDistancias = somatorioDistancias + matrizCustos[menorX][menorY].custo;
    return 1;
}

int verifFinal(){
    int x, status = 0;      // 0-> acabou; 1-> ainda não acabou
    for(x=0;x<i;x++){
        if(vetPassados[x] == 0) status = 1;
    }
    return status;
}

void termina(){
    printf("------------------------------------------\n");
    printf("Melhor caminho:\n%s\nSOMA: %i\n", caminhoFinal, somatorioDistancias);
    printf("------------------------------------------\n");
    system(EXIT_SUCCESS);
}


int contarVerticesDin(char passouPor[]){
    int val=0, i;
    i =0;
    while(passouPor[i] != '\0'){
        if(passouPor[i] == ' ')
            val++;
        i++;
    }
    if(i == 0)
        val = 0;
    else
        val++;
    return val;
}


int verificarVerticesDin(char passouPor[], int index, int numVertices){
    int i, j=0, z, vertice;
    char vert[10];
    if(index > (numVertices-1)) return -1;
    i=0;
    while(passouPor[i] != '\0'){
        if(j == index){
            z=0;
            while((passouPor[i] != ' ') && (passouPor[i] != '\0')){
                vert[z] = passouPor[i];
                i++;
                z++;
            }
            vert[z] = '\0';
            vertice = atoi(vert);
            return vertice;
        }
        if(passouPor[i] == ' ') j++;
        i++;
    }

}
