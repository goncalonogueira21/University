#include <stdio.h>                                                                                                 
#include <stdlib.h>                                                                                                
#include <ctype.h>                                                                                                 
#include <string.h>  
#include "../include/cliente.h"



//catalogo de Clientes
struct cliente{
   char a;
   int size;
   Clientes *arr;
};

//funcao que inicializa e aloca memoria para receber o catalogo de clientes
ClientesA initC(){
	int i=0;
	ClientesA ca=malloc(27*sizeof(struct cliente));
	ClientesA aux=ca;
	for(i=0;i<26;i++){
	ca->size=0;
	ca->a=' ';
        ca[i].arr=malloc(21000*sizeof(Clientes));
	
	}
	return aux;
}

//funcao que copia o catalogo de clientes para a memoria
ClientesA copiaS(FILE* f,ClientesA ca){
int i=0;
int count=0;
char g[64];
int aux=0;
ClientesA ret=ca;
char aux2[64];
int guard=0;
int flag=0;
  		for(i=0; fgets(g,64,f)!=NULL ;i++){
  			if((flag=legitC(g))){
  		     count++;
                     aux=g[0]%NUM_ALPHA;
                     ca[aux].a=g[0];         
                     strncpy(aux2, g, 5);
                     switchs(g,aux2);   	
                     guard=(int)strtol(aux2, (char **)NULL, 10);
                     ca[aux].size++;
	             ca[aux].arr[guard].key=guard;
                     ca[aux].arr[guard].value=strdup(strtok(g,"\r\n"));   
                     }                                  
                }
                
return ret;
}

// funcao que verifica a integridade dos codigos de Cliente
int legitC(char g[]){
	int toint=0;
	int ret =0;
	char aux2[64];
	
	switchs(g,aux2);
	toint=(int)strtol(aux2,(char **)NULL,10);
	if(isalpha(g[0]) && isdigit(g[2]) && isdigit(g[2]) && isdigit(g[3]) && isdigit(g[4]) ){

		if(toint<=5000 && toint>=1000){
				ret =1;
		}
	}




	return ret;
}

//Funcao que, sendo untilizada no ficheiro de vendas, verifica a existencia de um dado codigo no catalogo de clientes
int verificaC(char* cod,ClientesA c){
char toint[64];
int ind=0;
int ret=0;

int guard=0;

	
		ind=cod[0]%NUM_ALPHA;
 		switchs(cod,toint);
	        guard=(int)strtol(toint, (char **)NULL, 10);
		if(!(c[ind].arr[guard].value==NULL)) ret =1;
	   
       
return ret;
}
