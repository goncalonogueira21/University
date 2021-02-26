#include <stdio.h>                                                                                                 
#include <stdlib.h>                                                                                                
#include <ctype.h>                                                                                                 
#include <string.h> 
#include "../include/gestaoFilial.h"
#include "../include/copia.h"



#define Init_capacity  500
//4
// estrutura responsavel por guardar o modulo da gestaofilial
typedef struct CodigosProduto3{
  int mes;
  char *codigo;
  double preco;
  char tipo;
  int total;
  

}CodigosProduto3;


//3
typedef struct ClienteZZ{
  int key; // codigo cliente
  int size;
  char *codigo;
  char **produtos;
  int sizeProdutos;
  int capacityProdutos;
  int capacity;
  int lista;
  int flag; // 1 se tiver comprado 
  CodigosProduto3 *cp3;

}ClienteZZ;

//2
typedef struct ClientesZ{
  char key; // primeira letra
  ClienteZZ *cp2;

}ClientesZ;
//um

struct fil{
  int id;
  ClientesZ *cp;
  
};

//funcao responsavel por manter o encapsulamento de GestaoFilial
Filial SGVgetFilial(Filial f){
  return f;
}



// funcao responsavel por inserir todos os valores do catalogo de clientes na gestao de filial
Filial clienteFil(Filial fil,FILE* fp){
      char x[64];
      char auxp1[6];
     
      int chave=0;
      int indp1=0;
      int i;
          char *aux=malloc(6*sizeof(char));

      for(i=0; fgets(x,64,fp)!=NULL ;i++){
   strcpy(aux,x);

                indp1=x[0]%NUM_ALPHA;               
                switchs(x,auxp1);
               chave=(int)strtol(auxp1,(char **)NULL,10);
             for(int j=1;j<4;j++){
            fil[j].cp[indp1].cp2[chave].lista=1;
            fil[j].cp[indp1].cp2[chave].codigo=strdup(aux);

}

            }



return fil;

}





// funcao que tem como objetivo intializar o modulo da Gestao de Filial, alocando o espaco necessario 
Filial initFilial(){

  Filial gf=malloc(4*sizeof(struct fil));


  for(int i=1;i<4;i++){
      gf[i].id=i;
      gf[i].cp=malloc(26*sizeof(ClientesZ));
        for(int j=0;j<27;j++){
            gf[i].cp[j].key=' ';
            gf[i].cp[j].cp2=malloc(5000*sizeof(ClienteZZ));
              for(int k=1000;k<=5001;k++){

                   gf[i].cp[j].cp2[k].key=0;
                    gf[i].cp[j].cp2[k].lista=-1;
                   gf[i].cp[j].cp2[k].flag=0;
                  gf[i].cp[j].cp2[k].cp3=malloc(Init_capacity*sizeof(CodigosProduto3));
                  gf[i].cp[j].cp2[k].size=0;
                  gf[i].cp[j].cp2[k].sizeProdutos=0;
                  gf[i].cp[j].cp2[k].capacityProdutos=Init_capacity*sizeof(char*);
                  gf[i].cp[j].cp2[k].produtos=malloc(Init_capacity*sizeof(char*));
                  gf[i].cp[j].cp2[k].codigo=" ";
                  gf[i].cp[j].cp2[k].capacity=Init_capacity*sizeof(CodigosProduto3);
              }
        }
  }

  return gf;
}


// funcao que tem como objetivo copiar uma linha de vendas para o modulo da gestao de filial
Filial loadGF(char **aux,Filial fil){
int aux4;
int ind;
char aux2[64];
int keyC;
int tam;
      
            ind=aux[5][0]%NUM_ALPHA;
            //filial
            aux4=(int)strtol(aux[7],(char **)NULL,10);
            switchs(aux[5],aux2);
            keyC=(int)strtol(aux2,(char **)NULL,10);
            tam=fil[aux4].cp[ind].cp2[keyC].size;
            //caminho para lista preenche
            fil[aux4].id=aux4;
            fil[aux4].cp[ind].key=aux[5][0]; 
            fil[aux4].cp[ind].cp2[keyC].key=keyC;
            fil[aux4].cp[ind].cp2[keyC].flag=1;
            fil[aux4].cp[ind].cp2[keyC].codigo=strdup(aux[5]);

              if(!existeP(aux[1], fil[aux4].cp[ind].cp2[keyC].produtos)){
                    //lista de produtos cheia, realloc
                  if(fil[aux4].cp[ind].cp2[keyC].sizeProdutos*sizeof(char*)+(sizeof(char*))> fil[aux4].cp[ind].cp2[keyC].capacityProdutos){
                    
                    fil[aux4].cp[ind].cp2[keyC].produtos=realloc(fil[aux4].cp[ind].cp2[keyC].produtos,fil[aux4].cp[ind].cp2[keyC].capacityProdutos*10);
                    fil[aux4].cp[ind].cp2[keyC].capacityProdutos= fil[aux4].cp[ind].cp2[keyC].capacityProdutos*10;
                  }

               fil[aux4].cp[ind].cp2[keyC].produtos[fil[aux4].cp[ind].cp2[keyC].sizeProdutos]=strdup(aux[1]);
               fil[aux4].cp[ind].cp2[keyC].sizeProdutos++;
               
             }
            
            //lista cheia, realloc
          
            if(tam+1*sizeof(CodigosProduto3)+sizeof(CodigosProduto3)>fil[aux4].cp[ind].cp2[keyC].capacity){
              fil[aux4].cp[ind].cp2[keyC].cp3=realloc(fil[aux4].cp[ind].cp2[keyC].cp3,fil[aux4].cp[ind].cp2[keyC].capacity*10);
              fil[aux4].cp[ind].cp2[keyC].capacity=fil[aux4].cp[ind].cp2[keyC].capacity*10;        
            }
            //preenche lista
            fil[aux4].cp[ind].cp2[keyC].cp3[tam+1].mes=(int)strtol((aux[6]), (char **)NULL, 10);
            fil[aux4].cp[ind].cp2[keyC].cp3[tam+1].codigo=strdup(aux[1]);
            fil[aux4].cp[ind].cp2[keyC].cp3[tam+1].tipo=*aux[4];
            fil[aux4].cp[ind].cp2[keyC].cp3[tam+1].total=(int)strtol((aux[3]), (char **)NULL, 10);
            fil[aux4].cp[ind].cp2[keyC].cp3[tam+1].preco=(double)strtod((aux[2]), (char **)NULL);
            fil[aux4].cp[ind].cp2[keyC].size++;
return fil;

}

// funcao que tem como objetivo receber o modulo de filial e apresentar todos os clientes q compraram nas 3 filiais
Zat_Array* SGVgetClientsOfAllBranches(Filial fil){
  
  Zat_Array* teste = malloc(sizeof(struct Zat_Array));
  teste->result = NULL;
  teste->size = 0;	
  
  int ind=13;
  for(int i=0;i<26;i++){

    for(int j=1000;j<5001;j++){

      if(fil[1].cp[ind].cp2[j].size!=0){

        if((fil[2].cp[ind].cp2[j].size!=0) && (fil[3].cp[ind].cp2[j].size!=0)){
          char str[4];
          char aux[5];
          sprintf(str, "%d", fil[1].cp[ind].cp2[j].key);
          char z = fil[1].cp[ind].key;
          aux[0]=z;
          for(int i=1;i<5;i++) aux[i] = str[i-1];
          teste->result = realloc(teste->result, ((teste->size)+1)* sizeof(char*));
      	  teste->result[teste->size]=strdup(aux);
      	  teste->size++;
    
        }
        
      }

      }
      ind=(ind+1)%NUM_ALPHA;
  }


  return teste;
}

Zat_Array* SGVgetProductBuyers(Filial fil, char* productID, int branch){//DA AQUELE PROBLEMA COM O FICHEIRO DE 3M, SE ESCOLHER FILIAL 1
  
  Zat_Array* teste = malloc(sizeof(struct Zat_Array));
  teste->result = NULL;
  teste->size = 0;
  int ind;
  int f;
  for(ind=0;ind<26;ind++){

    for(int j=1000;j<5001;j++){

        if(fil[branch].cp[ind].cp2[j].flag==1){
        for(int i=1;i<=fil[branch].cp[ind].cp2[j].size;i++){
          f=strcmp(fil[branch].cp[ind].cp2[j].cp3[i].codigo,productID);
          
          if(f==0){
          char str[4];
          char aux[7];
          sprintf(str, "%d", fil[branch].cp[ind].cp2[j].key);
          char z = fil[branch].cp[ind].key;
          aux[0]=z;
          for(int i=1;i<5;i++) aux[i] = str[i-1];
          aux[5]='-';
          aux[6]=fil[branch].cp[ind].cp2[j].cp3[i].tipo;

          teste->result = realloc(teste->result, ((teste->size)+1) * sizeof(char*));
          teste->result[teste->size] = strdup(aux);
          teste->size++;

          break;
          }
          

        }
      
    }
      

    }

  }
  
  return teste;
}


//FUncao que vai buscar a quantidade de produtos que o cliente comprou por mes
Zat_Numeros* SGVgetTotalProductsMonthandBranch(Filial fil, char* cliente){
	
  int letra=cliente[0]%NUM_ALPHA;
  int resto=atoi (str_slice(cliente,1,5));
	int count=0;
  Zat_Numeros* teste = malloc(sizeof(struct Zat_Numeros));
  
	for(int branch=1;branch<4;branch++){

		for(int mesA=1;mesA<=12;mesA++){
     
			if(fil[branch].cp[letra].cp2[resto].flag==1){
        
				for(int i=1;i<=fil[branch].cp[letra].cp2[resto].size;i++){
					
					if(fil[branch].cp[letra].cp2[resto].cp3[i].mes==mesA){
						count+=fil[branch].cp[letra].cp2[resto].cp3[i].total;
           		
					}
        }
          		teste->mat[branch-1][mesA-1]=count;
              count=0;
		}
    else{
              teste->mat[branch-1][mesA-1]=0;
    }
  }
  }
          
	return teste;
}

//funcao que consoante o cliente e o mes, obtem os produtos favoritos do cliente, ordenados, consoante o mes.
Zat_Array2* SGVgetClientFavoriteProducts(Filial fil, char* clienteID,int month){
  int letra=clienteID[0]%NUM_ALPHA;
  int resto=atoi (str_slice(clienteID,1,5));
  int k=0;
  resultados* res=malloc(100*sizeof(struct resultados));
  
  for(int i=1; i<4;i++){

      if(fil[i].cp[letra].cp2[resto].flag==1){
    
        for(int j=1;j<=fil[i].cp[letra].cp2[resto].size;j++){

          if(fil[i].cp[letra].cp2[resto].cp3[j].mes==month){
          res[k].codigo1 = strdup(fil[i].cp[letra].cp2[resto].cp3[j].codigo);
          res[k].total1=(double)fil[i].cp[letra].cp2[resto].cp3[j].total;
          k++;
        }
      }
    }
  }
  if(k==0) return NULL;

  return arranjaArray(res,k);

}

//funcao que, consoante o cliente, obtem os resultados onde o cliente gastou mais dinheiro.
Zat_Array2* SGVgetClientTopProfitProducts(Filial fil, char* clienteID){
  
  int letra=clienteID[0]%NUM_ALPHA;
  int resto=atoi (str_slice(clienteID,1,5));
  int k=0;
  int sizeG=100;
  int capacity=sizeG*sizeof(struct resultados);
  resultados* res=malloc(sizeG*sizeof(struct resultados));

  for(int i=1; i<4;i++){

      if(fil[i].cp[letra].cp2[resto].flag==1){
    
        for(int j=1;j<=fil[i].cp[letra].cp2[resto].size;j++){
            if(k*sizeof(struct resultados)+sizeof(struct resultados)>capacity){
              res=realloc(res,capacity*4);
              capacity=capacity*4;
            }
          
          res[k].codigo1 = strdup(fil[i].cp[letra].cp2[resto].cp3[j].codigo);
          res[k].total1=(fil[i].cp[letra].cp2[resto].cp3[j].preco)*(fil[i].cp[letra].cp2[resto].cp3[j].total);
          k++;
        
      }
    }
  }
  if(k==0) return NULL;

  return arranjaArray(res,k);

}


//funcao de ordenacao
Zat_Array2* arranjaArray(resultados* res, int k){

  Zat_Array2* zatao=malloc(sizeof(struct Zat_Array2));
  zatao->res=malloc(k*sizeof(struct resultados));
  zatao->size=0;
  int flag;
  for(int i=0;i<k;i++){
    flag=0;

    for(int j=0;j<zatao->size;j++){

      if(res[i].codigo1==zatao->res[j]->codigo1){
        zatao->res[j]->total1+=res[i].total1;
        flag=1;
        break;
      }

    }
    if(flag==0){
      zatao->res[zatao->size]=malloc(sizeof(struct resultados));
      zatao->res[zatao->size]->codigo1=res[i].codigo1;
      zatao->res[zatao->size]->total1=res[i].total1;
      zatao->size++;
    }
  }

  float a;
  char* b;
  for (int i = 0; i < zatao->size; i++) 
        {
          
            for (int j = i + 1; j < zatao->size; j++) 
            {
              
                if (zatao->res[i]->total1 < zatao->res[j]->total1) 
                {
                    b = zatao->res[i]->codigo1;
                    a = zatao->res[i]->total1;
                    zatao->res[i]->total1 = zatao->res[j]->total1;
                    zatao->res[i]->codigo1=zatao->res[j]->codigo1;
                    zatao->res[j]->total1 = a;
                    zatao->res[j]->codigo1=b;
                }
            }
        }

  return zatao;

}

// funcao que compoe a query 6, retornando o numero de clientes que nunca compraram
int NinguemCli(Filial f){
int re=0;
for(int i=1;i<4;i++){
    for(int ind=0;ind<26;ind++){

         for(int j=1000;j<5001;j++){
          
            if(f[i].cp[ind].cp2[j].flag==0 && f[i].cp[ind].cp2[j].lista==1){
              re++;
            }

          }
    }
}

  return re;
}


// funcao que compoe a query 11 , retornando o numero de clientes que compraram os N produtos mais vendidos
OnzeP* insereClientes(OnzeP *o,int n,Filial fil){
char* ver=NULL;
int flag1=-1;

   for(int in=0;in<n;in++){
    o[in].sizeC=0;
   ver=strdup(o[in].codigo);
              for(int i=1;i<4;i++){
                   for(int ind=0;ind<26;ind++){

                       for(int j=1000;j<5001;j++){
          
                           if(fil[i].cp[ind].cp2[j].flag==1 && fil[i].cp[ind].cp2[j].lista==1){
                                for(int per=0;per<fil[i].cp[ind].cp2[j].sizeProdutos;per++){
                                 flag1=strcmp(ver,fil[i].cp[ind].cp2[j].produtos[per]);
                                 if(flag1==0){
                                  o[in].sizeC++;
                                  break;
                                }
                          }
            }
   }
}

}
}
return o;
}