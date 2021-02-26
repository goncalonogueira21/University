#include "../include/controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

//função para criar navegador para querys 2, 5 e 9
void imprimePaginas(Zat_Array* teste){
    char key = '+';
    int nmrpag;
    int index=0;
    int h=0;
   	int t = teste->size;
    nmrpag = t/30;
    if(t%30) nmrpag++;
    while(key!='q'){
            if(key == '+'){
            	printClear();
            	for(int i = 0; i < 30 && index<t; i++){
           			printCodigo(teste->result[index]);
            		index++;
        	}
        	h++;
        	printRodapeInfo(h, nmrpag, index, t);
        	printRodapeTeclas();
    	}
        else if(key == '-'){
            if(index > 30){
                printClear();
                if(h==nmrpag && t%30!=0) index-=30+t%30;
                else index-=60;

                for(int i = 0; i < 30 && index<t; i++){
               		printCodigo(teste->result[index]);
                	index++;
            }	
            h--;  
        }
        printRodapeInfo(h, nmrpag, index, t);
        printRodapeTeclas();
    }
    key = getchar();
	}
}

//função para criar navegador para query 4 quando se pretende apresentar resultados totais
void imprimePaginas4(Quatro* teste){
    char key = '+';
    int nmrpag;
    int index=0;
    int h=0;
    int t = teste->total;
    nmrpag = t/30;
    if(t%30) nmrpag++;
    while(key!='q'){
            if(key == '+'){
                printClear();
                for(int i = 0; i < 30 && index<t; i++){
                    printCodigo(teste->codt[index]);
                    index++;
            }
            h++;
            printRodapeInfo(h, nmrpag, index, t);
            printRodapeTeclas();
        }
        else if(key == '-'){
            if(index > 30){
                printClear();
                if(h==nmrpag && t%30!=0) index-=30+t%30;
                else index-=60;

                for(int i = 0; i < 30 && index<t; i++){
                    printCodigo(teste->codt[index]);
                    index++;
            }   
            h--;  
        }
        printRodapeInfo(h, nmrpag, index, t);
        printRodapeTeclas();
    }
    key = getchar();
    }
}

//função para criar navegador para query 4 quando se pretende apresentar resultados por filial
void imprimePaginas44(Quatro* teste, int branch){
    char key = '+';
    int nmrpag;
    int index=0;
    int h=0;
    int t = teste->f[branch].fi;
    nmrpag = t/30;
    if(t%30) nmrpag++;
    while(key!='q'){
            if(key == '+'){
                printClear();
                for(int i = 0; i < 30 && index<t; i++){
                    printCodigo(teste->f[branch].cod[index]);
                    index++;
            }
            h++;
            printRodapeInfo(h, nmrpag, index, t);
            printRodapeTeclas();
        }
        else if(key == '-'){
            if(index > 30){
                printClear();
                if(h==nmrpag && t%30!=0) index-=30+t%30;
                else index-=60;

                for(int i = 0; i < 30 && index<t; i++){
                    printCodigo(teste->f[branch].cod[index]);
                    index++;
            }   
            h--;  
        }
        printRodapeInfo(h, nmrpag, index, t);
        printRodapeTeclas();
    }
    key = getchar();
    }
}


//função para criar navegador para query 10
void imprimePaginas10(Zat_Array2* teste){
    char key = '+';
    int nmrpag;
    int index=0;
    int h=0;
   	int t = teste->size;
    nmrpag = t/30;
    if(t%30) nmrpag++;
    while(key!='q'){
            if(key == '+'){
            	printClear();
            	for(int i = 0; i < 30 && index<t; i++){
           			printCodigoProduto(teste->res[index]->codigo1);
           	 		printQntdProduto((int)teste->res[index]->total1);
            		index++;
        	}
        	h++;
        	printRodapeInfo(h, nmrpag, index, t);
        	printRodapeTeclas();
    	}
        else if(key == '-'){
            if(index > 30){
                printClear();
                if(h==nmrpag && t%30!=0) index-=30+t%30;
                else index-=60;

                for(int i = 0; i < 30 && index<t; i++){
               		printCodigoProduto(teste->res[index]->codigo1);
           	 		printQntdProduto((int)teste->res[index]->total1);
                	index++;
            }	
            h--;  
        }
        printRodapeInfo(h, nmrpag, index, t);
        printRodapeTeclas();
    }
    key = getchar();
	}
}

//função para criar navegador para query 12
void imprimePaginas12(Zat_Array2* teste){
    char key = '+';
    int nmrpag;
    int index=0;
    int h=0;
    int t = teste->size;
    nmrpag = t/30;
    if(t%30) nmrpag++;
    while(key!='q'){
            if(key == '+'){
                printClear();
                for(int i = 0; i < 30 && index<t; i++){
                    printCodigoProduto(teste->res[index]->codigo1);
                    printPrecoProduto(teste->res[index]->total1);
                    index++;
            }
            h++;
            printRodapeInfo(h, nmrpag, index, t);
            printRodapeTeclas();
        }
        else if(key == '-'){
            if(index > 30){
                printClear();
                if(h==nmrpag && t%30!=0) index-=30+t%30;
                else index-=60;

                for(int i = 0; i < 30 && index<t; i++){
                    printCodigoProduto(teste->res[index]->codigo1);
                    printPrecoProduto(teste->res[index]->total1);
                    index++;
            }   
            h--;  
        }
        printRodapeInfo(h, nmrpag, index, t);
        printRodapeTeclas();
    }
    key = getchar();
    }
}


void query2(SGV sgv){
    printClear();
    char letter;
    carregaLogoV2();
    printMenuQ2();
    scanf(" %c",&letter);
        if(letter >=97 && letter <= 122) letter-=32; //letra minuscula
         else if(letter < 65 || letter > 90) {
            printLetraInvalida();
            getchar();
            getchar();
            printClear();
            return;
        }
    Zat_Array* teste=getProductsStartedByLetter(sgv,letter);
    imprimePaginas(teste);
    printVoltarAoMenu();
    getchar();
    getchar();
    printClear();
    free(teste);
}





void query3(SGV sgv){
    int mes,filial,totalVendasN,totalVendasP;
    double totalFaturadoN,totalFaturadoP;
    char tipo;
    char* productID;
    productID=malloc(5*sizeof(char));
    carregaLogoV2();
    printClear();
    printMenuQ3();
    scanf("%d",&mes);
     if(mes<1 || mes >12){
        printMesInvalido();
        printVoltarAoMenu();
        getchar();
        getchar();
        printClear();
        return;
    }
    printPergProduto();
    scanf(" %s", productID);
    if(checkProduto(productID,sgv)==0){
        printProdutoNExiste();
        printVoltarAoMenu();
        getchar();
        getchar();
        printClear();
        return;
    }
    Tres* teste=getProductSalesAndProfit(sgv,productID,mes);
    printTouF();
    scanf(" %c", &tipo);
     if (tipo==84||tipo==116){ //total
        totalFaturadoN=teste[1].fatN+teste[2].fatN+teste[3].fatN;
        totalFaturadoP=teste[1].fatP+teste[2].fatP+teste[3].fatP;
        totalVendasN=teste[1].vendaN+teste[2].vendaN+teste[3].vendaN;
        totalVendasP=teste[1].vendaP+teste[2].vendaP+teste[3].vendaP;
        
        printTotalFaturado2modos(totalFaturadoN,totalFaturadoP);
        printTotalVendas2modos(totalVendasN,totalVendasP);
        printVoltarAoMenu();
        getchar();
        getchar();
        printClear();
        return;
    }
     else if (tipo==70||tipo==102){ //filial
        for(filial=1;filial<=3;filial++){
            printFilial(filial);
            printTotalFaturado2modos(teste[filial].fatN,teste[filial].fatP);
            printTotalVendas2modos(teste[filial].vendaN,teste[filial].vendaP);
            printParagrafos();
        }
        printVoltarAoMenu();
        getchar();
        getchar();
        printClear();
        return;
    }
    else {
        printInfoInvalida();
        printVoltarAoMenu();
        getchar();
        getchar();
        printClear();
    }
    free(teste);
    free(productID);
}

void query4(SGV sgv){
    char tipo;
    int branch;
    printClear();
    carregaLogoV2();
    printMenuQ4();
    Quatro* teste=getProductsNeverBought(sgv,1);
    scanf(" %c", &tipo);
    if (tipo==84||tipo==116){ // Total
        imprimePaginas4(teste);
        printVoltarAoMenu();
        getchar();
        getchar();
        printClear();
        return;
    }
     else if (tipo==70||tipo==102){ //filial
        printPergFilial();
        scanf("%d", &branch);
        if(branch==1){
            imprimePaginas44(teste,1);
            printVoltarAoMenu();
            getchar();
            getchar();
            printClear();
            return;
        }
        if(branch==2){
            imprimePaginas44(teste,2);
            printVoltarAoMenu();
            getchar();
            getchar();
            printClear();
            return;
        }
        if(branch==3){
            imprimePaginas44(teste,3);
            printVoltarAoMenu();
            getchar();
            getchar();
            printClear();
            return;
        } 
        else{
            printInfoInvalida();
            printVoltarAoMenu();
            getchar();
            getchar();
            printClear();
            return;
        }   
    }
    else {
        printInfoInvalida();
        printVoltarAoMenu();
        getchar();
        getchar();
    }
    printClear();
    free(teste);
}




void query5(SGV sgv){
    printClear();
    carregaLogoV2();
    printMenuQ5();
    Zat_Array* teste=getClientsOfAllBranches(sgv);
    imprimePaginas(teste);
    printVoltarAoMenu();
    getchar();
    getchar();
    printClear();
    free(teste);
}


void query6(SGV sgv){
    time_t start, end;
    printClear();
    carregaLogoV2();
    printMenuQ6();
    start = time(NULL);
    Seis* teste=getClientsAndProductsNeverBoughtCount(sgv);
    end = time(NULL);
    printTotCliNComprou(teste->nC);
    printTotProdNComprou(teste->nP);
    printTime(end,start);
    printVoltarAoMenu();
    getchar();
    getchar();
    printClear();
    free(teste);
    return;
}


void query7(SGV sgv){
    time_t start, end;
    char* clienteID;
    Zat_Numeros* tabela;
    clienteID=malloc(5*sizeof(char));
    printClear();
    carregaLogoV2();
    printMenuQ7();
    scanf(" %s", clienteID);
    if(checkCliente(clienteID,sgv)==0){
        printClienteNExiste();
        printVoltarAoMenu();
        getchar();
        getchar();
        printClear();
        return;
    }
    start = time(NULL);
    tabela=getTotalProductsBoughtByClient(sgv,clienteID);
    int a[3][12];
    for(int i=0; i<3; i++){
    	for(int j=0;j<12;j++){
  		a[i][j]=tabela->mat[i][j];
   	 	}
	}
    printTabela(a);
    end = time(NULL);
    printTime(end,start);
    printVoltarAoMenu();
    getchar();
    getchar();
    printClear();
    free(tabela);
    free(clienteID);
}

void query8(SGV sgv){
    time_t start, end;
    int mesI,mesF;
    printClear();
    carregaLogoV2();
    printMenuQ8();
    scanf("%d",&mesI);
    printMesFinal();
    scanf("%d",&mesF);
    if((mesI<1 || mesI >12) || (mesF<1 || mesF >12) || (mesF-mesI<0)){
        printMesInvalido();
        printVoltarAoMenu();
        getchar();
        getchar();
        printClear();
        return;
    }
    start = time(NULL);
    Oito* teste=getSalesAndProfit(sgv,mesI,mesF);
    end = time(NULL);
    printMVendas(mesI,mesF,teste->vendas);
    printMFaturado(mesI,mesF,teste->totFat);
    printTime(end,start);
    printVoltarAoMenu();
    getchar();
    getchar();
    printClear();

free(teste);

}


void query9(SGV sgv){
    time_t start, end;
    printClear();
    carregaLogoV2();
    printMenuQ9();
    char* productID;
    productID=malloc(5*sizeof(char));
    scanf(" %s", productID);
    if(checkProduto(productID,sgv)==0){
        printProdutoNExiste();
        printVoltarAoMenu();
        getchar();
        getchar();
        printClear();
        return;
    }
    printPergFilial();
    int branch;
    scanf("%d", &branch);
    start = time(NULL);
    Zat_Array* teste = getProductBuyers(sgv, productID, branch);
    end = time(NULL);
    imprimePaginas(teste);
    printTime(end,start);
    printVoltarAoMenu();
    getchar();
    getchar();
    printClear();
        free(productID);
        free(teste);
}


void query10(SGV sgv){
    time_t start, end;
    int mes;
    char* clienteID;
    clienteID=malloc(5*sizeof(char));
    printClear();
    carregaLogoV2();
    printMenuQ10();
    scanf("%d",&mes);
    if(mes<1 || mes >12){
        printMesInvalido();
        printVoltarAoMenu();
        getchar();
        getchar();
        printClear();
        return;
    }
    printCliente();
    scanf(" %s",clienteID);
    if(checkCliente(clienteID,sgv)==0){
        printClienteNExiste();
        printVoltarAoMenu();
        getchar();
        getchar();
        printClear();
        return;
    }
    start = time(NULL);
    Zat_Array2* teste=getClientFavoriteProducts(sgv, clienteID, mes);
    end = time(NULL);
    if(teste==NULL) printNComprouMes();
    else {
         imprimePaginas10(teste);
        }
        printTime(end,start);
        printVoltarAoMenu();
        getchar();
        getchar();
        printClear();
        free(teste);
        free(clienteID);
        return;
       
}


void query11(SGV sgv){
	time_t start, end;
	int limit;
	printClear();
	carregaLogoV2();
	printMenuQ11();
	scanf("%d", &limit);
	start = time(NULL);
	OnzeP* teste=getTopSelledProducts(sgv,limit);
	end = time(NULL);
	printTabela11(teste,limit);
	printTime(end,start);
    printVoltarAoMenu();
    getchar();
    getchar();
    printClear();
    

    return;
}




void query12(SGV sgv){
	time_t start, end;
    printClear();
    carregaLogoV2();
    printMenuQ12();
    char* clientID;
    clientID=malloc(5*sizeof(char));
    scanf(" %s", clientID);
    if(checkCliente(clientID,sgv)==0){
        printClienteNExiste();
        printVoltarAoMenu();
        getchar();
        getchar();
        printClear();
        return;
    }
    int limit;
    printLimite();
    scanf("%d", &limit);
    start = time(NULL);
    Zat_Array2* teste = getClientTopProfitProducts(sgv, clientID, limit);
    end = time(NULL);
    if(teste==NULL) printNComprouMes();
    else{
        imprimePaginas12(teste);
        }
        printTime(end,start);
        printVoltarAoMenu();
        getchar();
        getchar();
        printClear();
        free(teste);
        free(clientID);
        return;

}

 void query13(SGV sgv, int num){
    int lidas = getlidas(sgv);
    int validadas = getValidas(sgv);
    printClear();
    printMenuQ13();
    printInfo(lidas,validadas,num);
    printVoltarAoMenu();
    getchar();
    getchar();
    printClear();
    return;
}


SGV query1(SGV sgv, int num){
    printClear();
    if(num==1){
        sgv =loadSGVFromFiles(sgv,"./docs/Clientes.txt","./docs/Produtos.txt","./docs/Vendas_1M.txt");
    }else if(num==3){
        sgv =loadSGVFromFiles(sgv,"./docs/Clientes.txt","./docs/Produtos.txt","./docs/Vendas_3M.txt");
    }else if (num==5){
        sgv =loadSGVFromFiles(sgv,"./docs/Clientes.txt","./docs/Produtos.txt","./docs/Vendas_5M.txt");
    }else {
        printOpNdisponivel();
        printaBikes();
    }
    return sgv;
}

void run(){

    int op=-1,carregado=0, num;

        SGV sgv=initSGV();

    while(op!=0){
        printClear();
        printMenu();
        scanf("%d",&op);
        if(op==1) {
        	printClear();
            if(carregado==0) {
            printPergFicheiro();
            scanf("%d", &num);
            sgv=query1(sgv,num);
            carregado=1;
        }
        else{
           printClear();
        }

    }
        else if(op==2 && carregado) query2(sgv);
        else if(op==3 && carregado) query3(sgv);
        else if(op==4 && carregado) query4(sgv);
        else if(op==5 && carregado) query5(sgv); 
        else if(op==6 && carregado) query6(sgv);
        else if(op==7 && carregado) query7(sgv);
        else if(op==8 && carregado) query8(sgv);
        else if(op==9 && carregado) query9(sgv);
        else if(op==10 && carregado) query10(sgv);
        else if(op==11 && carregado) query11(sgv);
        else if(op==12 && carregado) query12(sgv);
        else if(op==13 && carregado) query13(sgv, num);

        else if(!carregado && op){
         printPrecisaCarregar();
         getchar(); 
         getchar();
        }
        else if(op!=0){
            getchar();
            getchar();
        }
    }
    printClear();
    destroySGV(sgv);
}