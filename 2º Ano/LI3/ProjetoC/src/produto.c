#include <stdio.h>                                                                                                 
#include <stdlib.h>                                                                                                
#include <ctype.h>                                                                                                 
#include <string.h>  
#include "../include/produto.h"
#include "../include/copia.h"

//estrutura do catalogo de produtos
 struct Produto{
   char a;
   ClientesAP *ca;
 };



//funcao responsavel por verificar a integridade de um codigo de Produto
int legitP(char g[]){
	int toint=0;
	int ret =0;
	char aux2[64];
	char aux3[64];
	switchs(g,aux2);
	switchs(aux2,aux3);
	toint=(int)strtol(aux3,(char **)NULL,10);
	if(isalpha(g[0]) && isalpha(g[1]) && isdigit(g[2]) && isalnum(g[3]) && isalnum(g[4]) && isalnum(g[5]) ){

		if(toint<=9999 && toint>=1000){
				ret =1;
		}
	}


return ret;

}         

// funcao responsavel por initializar e alocar a memoria necessaria a guardar os valores do catalogo de produtos
Produtos initP(){
	Produtos p=malloc(26*sizeof(struct Produto));
int i=0;
	for(int j=0;j<26;j++){
	p[j].a=' ';
        p[j].ca=malloc(26*sizeof(ClientesAP));
	for(i=0;i<26;i++){
	p[j].ca->size=0;
	p[j].ca->a=' ';
        p[j].ca[i].arr=malloc(5001*sizeof(ClientesP));
	
	}
}
return p;
}

// funcao responsavel por analisar cada linha de produto e guardar o respetivo produto no catalogo de produtos
Produtos copiaP(FILE* f,Produtos p){
int i=0;
int count=0;
char g[64];
int aux=0;
int l=0;
char aux2[64];
char aux3[64];
int guard=0;
int count1=0;
int flag=0;
  		for(i=0; fgets(g,64,f)!=NULL ;i++){
  			count1++;
  			if((flag=legitP(g))){
  			 
  			 count++;
  			
		 l=g[0]%NUM_ALPHA;
                 aux=g[1]%NUM_ALPHA;
		p[l].a=g[0];
          	 p[l].ca[aux].a=g[1];         
                 strncpy(aux2, g, 6);
                 switchs(g,aux2);
		 switchs(aux2,aux3);
		guard=(int)strtol(aux3, (char **)NULL, 10);
                p[l].ca[aux].size++;
		p[l].ca[aux].arr[guard].key=guard;
                p[l].ca[aux].arr[guard].value=strdup(strtok(g,"\r\n"));  
         		 p[l].ca[aux].arr[guard].existe=1;
}
  }
  return p;
  }     

// funcao que verifica a existencia de um determinado produto no catalog de produtos
int verificaP(char *cod,Produtos p){
char toint[64];
char aux3[64];
int ind=0;
int ind2=0;
int ret=0;

int guard=0;

	
		ind=cod[0]%NUM_ALPHA;		
		ind2=cod[1]%NUM_ALPHA;
 		switchs(cod,toint);
		switchs(toint,aux3);
	    guard=(int)strtol(aux3, (char **)NULL, 10);
		if(!(p[ind].ca[ind2].arr[guard].value==NULL)) ret=1;
	   
       
return ret;
}
      


 // funcao que devolve a lista de produtos comecados por uma dada letra               
Zat_Array* SGVgetProductsStartedByLetter(Produtos p, char letter){
	
	Zat_Array* teste = malloc(sizeof(struct Zat_Array));
    teste->result =NULL;
  	teste->size = 0;
	int ind=letter%NUM_ALPHA;
	int ind2=13;
	for(int i=0;i<26;i++){
		
		for(int j=1000;j<10000;j++){
			
			if(p[ind].ca[ind2].arr[j].existe==1){
          		teste->result = realloc(teste->result, ((teste->size)+1)* sizeof(char*));
      	  		teste->result[teste->size]=strdup(p[ind].ca[ind2].arr[j].value);
      	  		teste->size++;
			
				
			}
			
		}
		ind2=(ind2+1)%NUM_ALPHA;
	}

return teste;
}                                     
