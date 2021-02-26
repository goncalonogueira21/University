#ifndef INTERFACE
#define INTERFACE

#include "gestaoFilial.h"
#include "gestaoFilial.h"
#include "../include/cliente.h"
#include "../include/faturacao.h"
#include "../include/produto.h"
#include "../include/gestaoFilial.h"

typedef struct sgv* SGV;



SGV initSGV();



typedef struct Onze{
  int fi;
  OnzeP *c;
}Onze;

typedef struct Seis{
  int nP;
  int nC;
  
}Seis;


SGV loadSGVFromFiles(SGV sgv,
	char* ClientsFilePath,
    char* productsFilePath,
    char* salesFilePath
    );
int getlidas(SGV sgv);
int getValidas(SGV sgv);
SGV loadFIFAT(SGV sgv,FILE* fv);
Zat_Array* getProductsStartedByLetter(SGV sgv, char letter);

Zat_Array* getClientsOfAllBranches(SGV sgv);

Zat_Array* getProductBuyers(SGV sgv, char* ProductID,int branch);

Zat_Numeros* getTotalProductsBoughtByClient(SGV sgv,char* clienteID);

Zat_Array2* getClientFavoriteProducts(SGV sgv, char* clienteID,int month);

Zat_Array2* getClientTopProfitProducts(SGV sgv, char* clientID, int limit);

Quatro* getProductsNeverBought(SGV sgv,int branchID);
Oito* getSalesAndProfit(SGV sgv, int minMonth, int maxMonth);
void destroySGV(SGV sgv);
OnzeP* getTopSelledProducts(SGV sgv,int limit);
Tres* getProductSalesAndProfit(SGV sgv,char* productID,int month);
Seis* getClientsAndProductsNeverBoughtCount(SGV sgv);

int checkCliente(char* clientID, SGV sgv);
int checkProduto(char* productID,SGV sgv);

void destroySGV(SGV sgv);
Faturacao getFat(SGV sgv);
Filial getFilial(SGV sgv);
#endif