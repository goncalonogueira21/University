#include <stdio.h>                                                                                                 
#include <stdlib.h>                                                                                                
#include <ctype.h>                                                                                                 
#include <string.h>                    
#include "../include/interface.h"
#define NUM_ALPHA 26

#define init_capacity  50
//estrutura do SGV
 struct sgv{

  ClientesA cl;
  Produtos prod;
  Filial fil;
  Faturacao fat;
  int lidas;
  int validas;
 

};

// funcao que mantem encapsulamento dos modulos GF e Faturacao
Faturacao getFat(SGV sgv){
	return SGVgetFat(sgv->fat);
}
Filial getFilial(SGV sgv){
	return SGVgetFilial(sgv->fil);
}

//Funcao que initializa todos os modulos de dados
SGV initSGV(){

	SGV sgv = malloc(sizeof(struct sgv));
	
   	sgv->cl=initC();
   	sgv->prod=initP();
    sgv->fil=initFilial();
    sgv->fat=initFat();	
    
   

    return sgv;
}

// funcao responsavel por abrir e carregar todos os dados para memoria
SGV loadSGVFromFiles(SGV sgv,
	char* ClientsFilePath,
    char* productsFilePath,
    char* salesFilePath
    ){

	FILE * fp;
	FILE * fv;
	FILE * fc;

	fp = fopen(ClientsFilePath, "r");
	fc = fopen(productsFilePath,"r");
	fv = fopen(salesFilePath,"r");

	if(fp==NULL) printf("ficheiro Clientes nao abriu\n");
	if(fc==NULL) printf("ficheiro Produtos nao abriu\n");
	if(fv==NULL) printf("ficheiro Vendas nao abriu\n");
	sgv->cl=copiaS(fp,sgv->cl);
    sgv->prod=copiaP(fc,sgv->prod);
	rewind(fc);
	rewind(fp);
	sgv->fil=clienteFil(sgv->fil,fp);
	sgv->fat=produtoFat(sgv->fat,fc);

	sgv=loadFIFAT(sgv,fv); 
					

	

 	fclose(fp);
  	fclose(fc);
    fclose(fv);
return sgv;

}


// funcao responsavel por ler o ficheiro de vendas e guardar os valores nos 2 modulos GF e faturacao
SGV loadFIFAT(SGV sgv,FILE* fv){

char g[64];
int count=0;
int i;		
sgv->lidas=0;
sgv->validas=0;
	for( i=0; fgets(g,64,fv)!=NULL ;i++){
sgv->lidas++;
 char **aux;
 aux=split(g);
   count++;
     
				if(legitC(aux[5]) && legitP(aux[1]) && verificaC(aux[5],sgv->cl) && verificaP(aux[1],sgv->prod)){
				    sgv->validas++;
					sgv->fat=loadFat(sgv->fat,aux);
					sgv->fil=loadGF(aux,sgv->fil);
				}
	
		}


return sgv;
			}
// funcao q retorna o numero de linhas lidas de vendas
int getlidas(SGV sgv){
	return sgv->lidas;
}
// funcao que retorna o numero de linhas validas de vendas
int getValidas(SGV sgv){
	return sgv->validas;
}

//funcoes  que sao utilizadas de forma a preservar o encapsulamento....

Zat_Array* getProductsStartedByLetter(SGV sgv, char letter){
	return SGVgetProductsStartedByLetter(sgv->prod, letter);
}

Zat_Array* getClientsOfAllBranches(SGV sgv){
	return SGVgetClientsOfAllBranches(sgv->fil);
}

Zat_Array* getProductBuyers(SGV sgv, char* productID,int branch){
	return SGVgetProductBuyers(sgv->fil, productID, branch);
}

Zat_Numeros* getTotalProductsBoughtByClient(SGV sgv,char* clienteID){
	return SGVgetTotalProductsMonthandBranch(sgv->fil, clienteID);
}

Zat_Array2* getClientFavoriteProducts(SGV sgv, char* clienteID,int month){
	return SGVgetClientFavoriteProducts(sgv->fil, clienteID, month);
}


Tres* getProductSalesAndProfit(SGV sgv,char* productID,int month){
   return SGVgetProductSalesAndProfit(sgv->fat,productID,month);
}

Quatro* getProductsNeverBought(SGV sgv,int branchID){
	return SGVgetProductsNeverBought(sgv->fat,branchID);
}
Oito* getSalesAndProfit(SGV sgv, int minMonth, int maxMonth){
	return SGVgetSalesAndProfit(sgv->fat,minMonth,maxMonth);
  
}
Seis* getClientsAndProductsNeverBoughtCount(SGV sgv){
	Seis* s=malloc(sizeof(Seis));
	s->nP=NinguemComprou(sgv->fat);
	s->nC=NinguemCli(sgv->fil);
return s;
 }

OnzeP* getTopSelledProducts(SGV sgv,int limit){
	OnzeP *o;
	o=malloc(limit+1*sizeof(OnzeP));
	o=MaisVendidos(sgv->fat,limit,o);
	o=Printasalao(sgv->fat,limit,o);
	o=insereClientes(o,limit,sgv->fil);
return o;
}

Zat_Array2* getClientTopProfitProducts(SGV sgv, char* clientID, int limit){
	Zat_Array2* teste = SGVgetClientTopProfitProducts(sgv->fil, clientID);
	if((teste->size)>limit) teste->size=limit;
	return teste; 
}


int checkCliente(char* clientID, SGV sgv){
	return verificaC(clientID,sgv->cl);
}

int checkProduto(char* productID,SGV sgv){
	return verificaP(productID,sgv->prod);
}
// funcao que liberta toda a memoria alocada relativa ao sgv
void destroySGV(SGV sgv){
free(sgv);
 
}


