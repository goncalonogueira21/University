#include <stdio.h>                                                                                                 
#include <stdlib.h>                                                                                                
#include <ctype.h>                                                                                                 
#include <string.h>                                                                                                
#include "../include/faturacao.h"
#include "../include/copia.h"
#define INIT_SIZE  500


// estrutura do catalogo da faturacao
typedef struct InFat
{
  int vP;
  int vN;
float fatP;
float gay;
float fatN;
 int vendaN;
 int vendaP;
 			
 

}InFat;



typedef struct FatF{
int f;
int unidades;
float faturacao;
int vendas;
InFat *mes;

}FatF;

typedef struct FatK
{
 int key;
 char *codigo;
 int alguemComprou;
 int produtoLista;
 float faturacao;
 int totalU;
 FatF  *ff; 

  
}FatK;

typedef struct Fat2{

char key;
FatK *fak;	


}Fat2;

struct fat
{ 
 char key;
 Fat2 *fa;
 


};

// funcao que initializa a e aloca a memoria necessaria para guardar a informacao relativa ao catalogo da faturacao
Faturacao initFat(){
	Faturacao c=malloc(26*sizeof(struct fat));
int i=0;
 for(i=0;i<26;i++){
   	
   c[i].key=' ';
   c[i].fa=malloc(26*sizeof(Fat2));
	for(int j=0;j<26;j++){
		c[i].fa[j].key=' ';
		c[i].fa[j].fak=malloc(10000*sizeof(FatK));

		for(int k=1000;k<=10000;k++){
		  c[i].fa[j].fak[k].key=' ';
 		   c[i].fa[j].fak[k].codigo=" ";
 		   c[i].fa[j].fak[k].alguemComprou=-1;
 		   c[i].fa[j].fak[k].produtoLista=-1;
		   c[i].fa[j].fak[k].faturacao=0;
		   c[i].fa[j].fak[k].totalU=0;
		   c[i].fa[j].fak[k].ff=malloc(4*sizeof(FatF));
			for (int l=0;l<4;l++){
				 c[i].fa[j].fak[k].ff[l].f=l;
				 c[i].fa[j].fak[k].ff[l].unidades=0;
				 c[i].fa[j].fak[k].ff[l].vendas=0;
				 c[i].fa[j].fak[k].ff[l].faturacao=0;
				 c[i].fa[j].fak[k].ff[l].mes=malloc(13*sizeof(InFat));
				 for(int u=1;u<13;u++){
				 	c[i].fa[j].fak[k].ff[l].mes[u].vendaN=0;
				 	c[i].fa[j].fak[k].ff[l].mes[u].vendaP=0;
				 	c[i].fa[j].fak[k].ff[l].mes[u].vP=0;
				 	c[i].fa[j].fak[k].ff[l].mes[u].gay=0;
				 	c[i].fa[j].fak[k].ff[l].mes[u].vN=0;
				 	c[i].fa[j].fak[k].ff[l].mes[u].fatP=0.0;
				 	c[i].fa[j].fak[k].ff[l].mes[u].fatN=0.0;
				 }
				
			}
  		}
	}
 }
return c;
}


//funcao que insere os produtos que nao sao mencionados nas vendas, no catalogo de produtos
Faturacao produtoFat(Faturacao f,FILE* p){
		char x[64];
  		char auxp1[6];
  		char auxp2[6];
  		int chave=0;
  		int indp1,indp2=0;
  		int i;
          char *aux=malloc(7*sizeof(char));

			for(i=0; fgets(x,64,p)!=NULL ;i++){
   strcpy(aux,x);

  							indp1=x[0]%NUM_ALPHA;
     						indp2=x[1]%NUM_ALPHA;
     						switchs(x,auxp1);
 							switchs(auxp1,auxp2);
							chave=(int)strtol(auxp2,(char **)NULL,10);
							f[indp1].fa[indp2].fak[chave].produtoLista=1;
						
							f[indp1].fa[indp2].fak[chave].codigo=strdup(aux);



  					}


free(aux);
return f;

}

// funcao responsavel por guardar uma linha de venda no catalogo da faturacao
Faturacao loadFat(Faturacao f,char **aux){


int ind1;
int ind2;
char aux2[7];
char aux3[7];
int fil,keyP,mesz=0;
int flag=-1;
float fatur=0.0;
int unid=0;


int count=0;
			
		
				count ++;
  			     
     			ind1=aux[1][0]%NUM_ALPHA;
     		
     			ind2=aux[1][1]%NUM_ALPHA;
     			fil=(int)strtol(aux[7],(char **)NULL,10);
     		    
 				switchs(aux[1],aux2);
 				switchs(aux2,aux3);
 			
				keyP=(int)strtol(aux3,(char **)NULL,10);
				fatur=(double)strtod(aux[2],(char **)NULL);	
			
				unid=(int)strtol(aux[3],(char **)NULL,10);
			
				 f[ind1].key=aux[1][0];
				 f[ind1].fa[ind2].key=aux[1][1];
				 f[ind1].fa[ind2].fak[keyP].key=keyP;
 		  		 f[ind1].fa[ind2].fak[keyP].codigo=strdup(aux[1]);
 		  		 //printf("%s\n", f[ind1].fa[ind2].fak[keyP].codigo );
 		  		 f[ind1].fa[ind2].fak[keyP].alguemComprou=1;

 		  		 //total do produto
		 		 f[ind1].fa[ind2].fak[keyP].faturacao+=fatur;
		   		 f[ind1].fa[ind2].fak[keyP].totalU+=unid;
		   		 // total do produto por filial
				 f[ind1].fa[ind2].fak[keyP].ff[fil].unidades+=unid;
				 f[ind1].fa[ind2].fak[keyP].ff[fil].faturacao+=fatur;
				 f[ind1].fa[ind2].fak[keyP].ff[fil].vendas++;
				 //divisao por mes
			

				    mesz=(int)strtol(aux[6],(char **)NULL,10);
				   
				     f[ind1].fa[ind2].fak[keyP].ff[fil].mes[mesz].gay+=unid*fatur;
				    
				   	if((flag=strcmp("N",aux[4]))==0){
				  
				  f[ind1].fa[ind2].fak[keyP].ff[fil].mes[mesz].vN+=unid;
				  	
				  f[ind1].fa[ind2].fak[keyP].ff[fil].mes[mesz].fatN+=fatur;
				  f[ind1].fa[ind2].fak[keyP].ff[fil].mes[mesz].vendaN++;
				
						}else {
							f[ind1].fa[ind2].fak[keyP].ff[fil].mes[mesz].vP+=unid;
							f[ind1].fa[ind2].fak[keyP].ff[fil].mes[mesz].fatP+=fatur;
							
							f[ind1].fa[ind2].fak[keyP].ff[fil].mes[mesz].vendaP++;
						}
			
  		


  						
  					

  
return f;
  	}

//funcao que mantem o encapsulamento do catalog da faturacao
Faturacao SGVgetFat(Faturacao f){
	return f;
}





//funcao responsavel pela resposta ä query3
Tres* SGVgetProductSalesAndProfit(Faturacao fat,char* productID,int month){
int ind1,ind2,keyP=0;
char aux2[7];
char aux3[7];
Tres *tres=malloc(4*sizeof(Tres));
for(int j=1;j<4;j++){
				tres[j].vendaN=0;
      			tres[j].vendaP=0;
      			tres[j].fatN=0.0;
      			tres[j].fatP=0.0;
}
 				ind1=productID[0]%NUM_ALPHA;
 				
     			ind2=productID[1]%NUM_ALPHA;
     			
 				switchs(productID,aux2);
 				switchs(aux2,aux3);
				keyP=(int)strtol(aux3,(char **)NULL,10);
				


			for(int i=1;i<4;i++){
				
      tres[i].vendaN=fat[ind1].fa[ind2].fak[keyP].ff[i].mes[month].vendaN;
   
      tres[i].vendaP=fat[ind1].fa[ind2].fak[keyP].ff[i].mes[month].vendaP;
     
	  tres[i].fatN=fat[ind1].fa[ind2].fak[keyP].ff[i].mes[month].fatN;
	
      tres[i].fatP=fat[ind1].fa[ind2].fak[keyP].ff[i].mes[month].fatP;
      
}

return tres;
}

char** myreversi(char **c,int size){

 int j = size - 1; 
 char *temp=malloc(6*sizeof(char));
    for (int i = 0; i < j; i++) { 
       temp=strdup(c[i]);
       
        c[i]=strdup(c[j]);
        c[j]=strdup(temp);
        
       
        j--; 

}
	return c;
};



//funcao responsavel por dar resposta ä query 4
Quatro* SGVgetProductsNeverBought(Faturacao fat,int branchID){

	Quatro *q=malloc(sizeof(Quatro));
	q->total=0;
	q->capacity=INIT_SIZE*sizeof(char*);
	q->codt=malloc(INIT_SIZE*sizeof(char*));
	q->f=malloc(4*sizeof(Fi4));
	for(int u=1;u<4;u++){
		q->f[u].fi=0;
		q->f[u].capacity=INIT_SIZE*sizeof(char*);
		q->f[u].cod=malloc(INIT_SIZE*sizeof(char*));
	}

	int ind2=13;
	int ind=13;
	
	for(int i=0;i<26;i++){
 
		for(int j=0;j<26;j++){
	
			for(int k=1000;k<=10000;k++){

				 if(fat[ind2].fa[ind].fak[k].alguemComprou<0 && fat[ind2].fa[ind].fak[k].produtoLista>0){
				 	if(q->total*(sizeof(char*))+(sizeof(char*))>q->capacity){
				 		q->codt=realloc(q->codt,q->capacity*4);
						q->capacity=q->capacity*4;
				 	}   
				 	  
				      
				 		q->codt[q->total]=strdup(fat[ind2].fa[ind].fak[k].codigo);
				 		q->total++;

				 	for(int o=1;o<4;o++){
				 		if(fat[ind2].fa[ind].fak[k].ff[o].unidades==0){
				 	if(q->f[o].fi*(sizeof(char*))+(sizeof(char*))>q->f[o].capacity){
				 				q->f[o].cod=realloc(q->f[o].cod,q->f[o].capacity*4);
				 				q->f[o].capacity=q->f[o].capacity*4;
				 	}
				 			
				 			q->f[o].cod[q->f[o].fi]=strdup(fat[ind2].fa[ind].fak[k].codigo);
				 			q->f[o].fi++;
				 		}
				 		
				 		}
				 	}



				 }
		ind=(ind+1)%NUM_ALPHA;
	 	}
	 	ind2=(ind2+1)%NUM_ALPHA;
}




return q;
}




//funcao responsavel por dar resposta à query 8
Oito* SGVgetSalesAndProfit(Faturacao fat, int minMonth, int maxMonth){

Oito *sp=malloc(sizeof(Oito));
sp->vendas=0;
sp->totFat=0.0;
sp->unid=0;
for(int i=0;i<26;i++){
 
		for(int j=0;j<26;j++){
	
			for(int k=1000;k<=10000;k++){
				 if(fat[i].fa[j].fak[k].alguemComprou==1 && fat[i].fa[j].fak[k].produtoLista==1){
				 	
				 	for(int o=1;o<4;o++){
				 			for (int aux=minMonth;aux<=maxMonth;aux++){
				 				sp->vendas+=fat[i].fa[j].fak[k].ff[o].mes[aux].vendaN + fat[i].fa[j].fak[k].ff[o].mes[aux].vendaP;
				 				
				 				sp->totFat+=fat[i].fa[j].fak[k].ff[o].mes[aux].gay;
				 				
				 			}	
				 	
				 	}

			 }
	 	}
	}

}

return sp;
}



//funcao responsavel por dar resposta á query 6 de forma a manter o encapsulamento e uma reposta eficiente, esta funcao corresponde a metade da query
int NinguemComprou(Faturacao fat){
int re=0;
	for(int i=0;i<26;i++){
 
		for(int j=0;j<26;j++){
	
			for(int k=1000;k<=10000;k++){

				 if(fat[i].fa[j].fak[k].alguemComprou==-1 && fat[i].fa[j].fak[k].produtoLista==1){

re++;
}
		
			}	
		}	
	}
return re;
}

//funcao auxiliar que ajudar a responder à query 11
void meteOP(char *codigo,int unid,OnzeP *o,int n){


o[0].codigo=strdup(codigo);
o[0].unid=unid;

}


//algoritmo de ordenacao, de forma a facilitar a resposta à query11
void organiza(OnzeP *o,int n){
int i,j=0;
int a=0;
char *ord=NULL;
	 for (i = 0; i < n; ++i){
            for (j = i + 1; j < n; ++j){
					if (o[i].unid > o[j].unid){
                    	a =  o[i].unid;
                   	 	o[i].unid = o[j].unid;
                   		o[j].unid = a;
						ord=strdup(o[i].codigo);
 						o[i].codigo = strdup(o[j].codigo);
                   		o[j].codigo = strdup(ord);

                }

 

            }

 

        }

}

//funcao responsavel por guardar as informacoes que necessitam de ser impressas, de forma a responder à query 11
OnzeP* Printasalao(Faturacao fat,int limit,OnzeP *o){
char *aux=malloc(7*sizeof(char));	

int ind1,ind2=0;
char aux2[7];
char aux3[7];
int keyP=0;
	for(int i=0;i<limit;i++){
o[i].print=malloc(sizeof(Salao));

				aux=strdup(o[i].codigo);
				ind1=aux[0]%NUM_ALPHA;
     			ind2=aux[1]%NUM_ALPHA;   		    
 				switchs(aux,aux2);
 				switchs(aux2,aux3);
				keyP=(int)strtol(aux3,(char **)NULL,10);

o[i].print->uf1=fat[ind1].fa[ind2].fak[keyP].ff[1].unidades;
o[i].print->uf2=fat[ind1].fa[ind2].fak[keyP].ff[2].unidades;
o[i].print->uf3=fat[ind1].fa[ind2].fak[keyP].ff[3].unidades;
o[i].print->vf1=fat[ind1].fa[ind2].fak[keyP].ff[1].vendas;
o[i].print->vf2=fat[ind1].fa[ind2].fak[keyP].ff[2].vendas;
o[i].print->vf3=fat[ind1].fa[ind2].fak[keyP].ff[3].vendas;
o[i].print->vtotal=o[i].print->vf1 + o[i].print->vf2 + o[i].print->vf3;





	}


return o;

}

//funcao que realiza devolve os n produtos mais vendidos, esta funcao é metade da resposta á query11 
OnzeP* MaisVendidos(Faturacao fat,int n,OnzeP *op){


int inc=0;
for(int p=0;p<=n;p++){
	op[p].codigo=malloc(6*sizeof(char));
	op[p].unid=0;
	op[p].sizeC=0;


}
	for(int i=0;i<26;i++){
 
		for(int j=0;j<26;j++){
	
			for(int k=1000;k<=10000;k++){

				if(fat[i].fa[j].fak[k].alguemComprou==1 && fat[i].fa[j].fak[k].produtoLista==1){
				
						
						if(inc<n){
							op[inc].codigo=strdup(fat[i].fa[j].fak[k].codigo);
						    op[inc].unid=fat[i].fa[j].fak[k].totalU;
						    inc++;
						    
						}else{
							organiza(op,n);
								if(fat[i].fa[j].fak[k].totalU>op[0].unid){
									meteOP(fat[i].fa[j].fak[k].codigo,fat[i].fa[j].fak[k].totalU,op,n);
								}
						}
	
				}
				}

			}

		}
	

return op;

}