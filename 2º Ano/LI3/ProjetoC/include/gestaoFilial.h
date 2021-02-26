#ifndef GESTAOFILIAL
#define GESTAOFILIAL
#include "../include/cliente.h"
#include "../include/produto.h"
#include "../include/faturacao.h"

typedef struct fil* Filial;


typedef struct resultados{
  char *codigo1;
  double total1;
}resultados;



typedef struct Zat_Array2{
	resultados **res;
	int size;
}Zat_Array2;

typedef struct Zat_Numeros{
	int mat[3][12];
}Zat_Numeros;
Filial clienteFil(Filial fil,FILE* fp);
Filial initFilial();

Filial loadGF(char **aux,Filial fil);
OnzeP* insereClientes(OnzeP *o,int n,Filial fil);

char *str_slice(char str[], int slice_from, int slice_to);

Zat_Numeros* SGVgetTotalProductsMonthandBranch(Filial fil, char* clienteID);

Zat_Array* SGVgetClientsOfAllBranches(Filial fil);

Zat_Array* SGVgetProductBuyers(Filial fil, char* productID, int branch);

Zat_Array2* SGVgetClientFavoriteProducts(Filial fil, char* clienteID,int month);

Zat_Array2* arranjaArray(resultados* res, int k);

Zat_Array2* SGVgetClientTopProfitProducts(Filial fil, char* clienteID);
Filial SGVgetFilial(Filial f);
int NinguemCli(Filial f);
#endif