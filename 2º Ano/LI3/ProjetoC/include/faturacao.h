#ifndef FATURACAO
#define FATURACAO
#include "../include/copia.h" 
#include "../include/cliente.h"
#include "../include/produto.h"


typedef struct fat* Faturacao;



typedef struct Fi4{
   int fi;
   int capacity;
   char **cod;


}Fi4;

typedef struct Quatro
 {

   int total;
   int capacity;
   char **codt;
   Fi4   *f;
 }Quatro;


typedef struct Oito{
   int vendas;
   double totFat;
  int unid;
}Oito;


typedef struct Tres{
   int vendaN;
   int vendaP;
   double fatN;
   double fatP;
	
}Tres;
typedef struct Salao
{  int uf1;
   int uf2;
   int uf3;
   int vf1;
   int vf2;
   int vf3;
   int vtotal; 
}Salao;

typedef struct OnzeP{
 char *codigo;
 Salao *print;
 int unid;
 int sizeC;
}OnzeP;
char** myreversi(char **c,int size);
OnzeP* Printasalao(Faturacao fat,int limit,OnzeP *o);
void organiza(OnzeP *o,int n);
void meteOP(char *codigo,int unid,OnzeP *o,int n);
OnzeP* MaisVendidos(Faturacao fat,int n,OnzeP *op);
Faturacao SGVgetFat(Faturacao f);
void free_Fat(Faturacao f);
Faturacao produtoFat(Faturacao f,FILE* p);
Faturacao initFat();

Faturacao loadFat(Faturacao f,char **aux);

Tres* SGVgetProductSalesAndProfit(Faturacao fat,char* productID,int month);

Quatro* SGVgetProductsNeverBought(Faturacao fat,int branchID);
Oito* SGVgetSalesAndProfit(Faturacao fat, int minMonth, int maxMonth);
int NinguemComprou(Faturacao fat);
#endif