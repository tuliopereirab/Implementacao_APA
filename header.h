#include "main.c"
#include "arquivo.c"
#include "gerador.c"
#include "help.c"

#include "forcaBruta.c"
#include "dinamica.c"
#include "gulosa.c"

// GERADOR.C
void gerar(char entI[], char entJ[], char arquivo[]);
//-----------------------------------------------------------
// ARQUIVO.C
int **lerArquivo(char arquivo[]);
int retI();
int retJ();
//-----------------------------------------------------------
// HELP.c
void ajuda();
//-----------------------------------------------------------
// FORCABRUTA.C
void forcaBruta(char arquivo[]);
//-----------------------------------------------------------
// GULOSA.C
void gulosa(char arquivo[]);
//-----------------------------------------------------------
// DINAMICA.C
void dinamica(char arquivo[]);
//-----------------------------------------------------------
