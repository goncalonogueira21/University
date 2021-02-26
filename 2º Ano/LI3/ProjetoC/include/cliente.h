#ifndef CLIENTE
#define CLIENTE




#define MAX_BUFF 1000000
#define NUM_ALPHA 26
#include "../include/copia.h"


typedef struct Clientes{
  int key;
  char *value;


}Clientes;




typedef struct cliente* ClientesA;



int legitC(char g[]);

ClientesA initC();
ClientesA copiaS(FILE* f,ClientesA ca);

int verificaC(char *v,ClientesA c);


#endif