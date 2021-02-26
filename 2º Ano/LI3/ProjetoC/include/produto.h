#ifndef PRODUTO
#define PRODUTO


#include "../include/copia.h"

#define MAX_BUFF 1000000
#define NUM_ALPHA 26

typedef struct ClientesP{
  int key;
  char *value;
  int existe;


}ClientesP;

typedef struct ClientesAP{
   char a;
   int size;
   ClientesP *arr;

   

}ClientesAP;

typedef struct Zat_Array{
	char** result;
	int size;
}Zat_Array;



typedef struct Produto* Produtos;

int  verificaP(char *v,Produtos p);

Produtos initP();

int legitP(char g[]);

Produtos copiaP(FILE* f,Produtos p);

Zat_Array* SGVgetProductsStartedByLetter(Produtos p, char letter);


#endif