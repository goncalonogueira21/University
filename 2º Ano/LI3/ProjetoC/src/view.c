#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/view.h"
#include <time.h>

//funcoes relativas ao viewer.
void printMenu(){
        carregaLogoV2();
        printf("|--------------------------------------MENU----------------------------------------------|\n\n");
        printf("1- Carregar ficheiros para SGV \n");
        printf("2- Determinar a lista e o total de produtos cujo código se inicia por uma dada letra\n");
        printf("3- Dado um mês e um código de produto determinar e apresentar o número total de vendas e o total faturado com esse produto\n");
        printf("4- Determinar a lista ordenada dos códigos dos produtos que ninguém comprou\n");
        printf("5- Determinar a lista ordenada de códigos de clientes que realizaram compras em todas a filiais\n");
        printf("6- Determinar o número de clientes registados que não realizaram compras e o número de produtos que ninguém comprou\n");
        printf("7- Dado um código de cliente criar uma tabela com o número total de produtos comprados mês a mês\n");
        printf("8- Dado um intervalo de meses determinar o total de vendas registadas e o total faturado\n");
        printf("9- Dado um código de produto e uma filial determinar os códigos dos clientes que o compraram\n");
        printf("10- Dado um código de cliente e um mês determinar a lista de códigos de produtos que mais comprou por quantidade\n");
        printf("11- Criar uma lista nos N produtos mais vendidos em todo o ano\n");
        printf("12- Dado um código de cliente determinar quais os códigos dos N produtos em que gastou mais dinheiro durante o ano\n");
        printf("13- Apresentar resultados de leitura do ficheiros da query 1\n");
        printf("\nEscolha uma query ou 0 para sair: ");
}

void printClear(){

    printf("\033c");
}

void printOpNdisponivel(){ printf("Não disponível!\n");}    

void printPrecisaCarregar(){printf("Precisa de carregar os ficheiros!\n");}

void printaPagina(char** v,int index){ 
   	printf("  %s  \n", v[index]);
     }
void printRodapeTeclas(){printf("\'+\' para próximo, \'-\' para anterior, \'q\' para sair\n");}

void printRodapeInfo(int h, int nmrpag, int index, int t){
    printf("Página: %d de %d | Lidos: %d de %d |\n",h, nmrpag, index, t);
}

void printLetraInvalida(){
    printf("Letra inválida!\n");
    printf("(Prima ENTER para voltar ao menu)\n");
}

 

void printVoltarAoMenu(){printf("\n(Prima ENTER para voltar ao menu)\n");} 


void printMenuQ2(){
        printf("\n|-------------------------------------Query 2--------------------------------------------|\n\n");
        printf("Letra: ");
}


void printMenuQ3(){
        printf("|-------------------------------------Query 3--------------------------------------------|\n\n");
        printf("Mês: ");
}

void printMenuQ4(){
        printf("|-------------------------------------Query 4--------------------------------------------|\n\n");
        printTouF();
}



void printMenuQ5(){
        printf("\n|-------------------------------------Query 5--------------------------------------------|\n\n");
}

void printMenuQ6(){
        printf("\n|-------------------------------------Query 6--------------------------------------------|\n\n");
}

void printMenuQ7(){
        printf("\n|-------------------------------------Query 7--------------------------------------------|\n\n");
        printf("Codigo cliente: ");
}

void printMenuQ8(){
        printf("\n|-------------------------------------Query 8--------------------------------------------|\n\n");
        printf("Mês Inicial:");
}


void printMenuQ9(){
        printf("\n|-------------------------------------Query 9--------------------------------------------|\n\n");
        printf("Codigo do produto: ");
}


void printMenuQ10(){
        printf("\n|-------------------------------------Query 10-------------------------------------------|\n\n");
        printf("Mês:");
}

void printMenuQ11(){
        printf("\n|-------------------------------------Query 11-------------------------------------------|\n\n");
        printf("Numero de produtos pretendidos: ");
}

void printMenuQ12(){
        printf("\n|-------------------------------------Query 12-------------------------------------------|\n\n");
        printf("Codigo cliente:");
}

void printMenuQ13(){
        printf("\n|-------------------------------------Query 13-------------------------------------------|\n\n");
}

void printMesInvalido(){
	printf("Mês inválido!\n");
}


void printMVendas(int mesI,int mesF,int vendas){
        printf("Total de unidades vendidas entre o mês %d e o mês %d é: %d\n", mesI,mesF,vendas);
}

void printMFaturado(int mesI,int mesF,double faturado){
         printf("Total faturado entre o mês %d e o mês %d é: %f\n", mesI,mesF,faturado);
}


void printLimite(){
	printf("Indique limite:");
}

void printCliente(){
	printf("Cliente:");
}

void printPergFilial(){
	printf("Qual a filial?\n");
}

void printPergProduto(){
    printf("Produto: ");
}

void printMesFinal(){
    printf("Mês final:");
}


void printTotalFaturado2modos(float tfn,float tfp){
     printf("Total faturado modo Normal: %.2f\nTotal faturado modo Promoção: %.2f\n",tfn,tfp);
}

void printTotalVendas2modos(int tvn,int tvp){
    printf("Total de vendas em modo Normal: %d\nTotal de vendas em modo Promoção %d\n",tvn,tvp);
}

void printParagrafos(){printf("\n\n");}


void printInfoInvalida(){printf("informação inválida\n");}

void printFilial(int filial){
    printf("\nFilial %d\n", filial);
}


void printTouF(){
    printf("Pretende apresentar resultados totais (T) ou por filial (F)\n");
}

void printTabela(int a[3][12]){
    printf("\n____________________________________________________________________________________________________________________________________________\n");
    printf("        |                                                                                                                                   |\n");
    printf("  MES   |     1    |     2    |     3    |     4    |     5    |     6    |     7    |     8    |     9    |    10    |    11    |    12    |\n");
    printf("________|___________________________________________________________________________________________________________________________________|\n");
    for(int i=0;i<3;i++){
        printf("Filial %d|   %4d   |   %4d   |   %4d   |   %4d   |   %4d   |   %4d   |   %4d   |   %4d   |   %4d   |   %4d   |   %4d   |   %4d   |\n",i+1, a[i][0], a[i][1], a[i][2],a[i][3],a[i][4],a[i][5], a[i][6],a[i][7],a[i][8],a[i][9], a[i][10],a[i][11]);
        }
    printf("________|___________________________________________________________________________________________________________________________________|\n");
}


void printTabela11(OnzeP* teste, int limit){
    printf("\n___________________________________________________\n");
    printf("            |                                       |\n");
    printf("            | Filial1    Filial2   Filial3   Total  |\n");
    printf("____________|_______________________________________|\n");
    for (int i = 0; i < limit; i++){
        printf("Produto: %s                                     |\n",teste[i].codigo);
        printf("Nº clientes: %8d    %7d %9d %7d  |\n",teste[i].print->vf1,teste[i].print->vf2,teste[i].print->vf3,teste[i].print->vtotal);
        printf("Nº compras:  %8d    %7d %9d %7d  |\n",teste[i].print->uf1,teste[i].print->uf2,teste[i].print->uf3,teste[i].unid);
        printf("____________________________________________________|\n");
    }
}


void printClienteNExiste(){
    printf("Cliente nao existe\n");
}

void printProdutoNExiste(){
	printf("O produto nao existe\n");
}

void printNComprouMes(){
	printf("Nao comprou produtos nesse mes\n");
}

void printCodigoProduto(char* p){
	printf("Produto %s - ",p);
}

void printQntdProduto(int q){
	printf(" quantidade:  %d\n ",q);
}

void printPrecoProduto(float p){
    printf(" preco: %f\n", p);
}

void printCodigo(char* p){
	printf("%s\n", p);
}

void printTotCliNComprou(int c){
     printf("Total de clientes que não fizeram compras: %d\n", c);
}

void printTotProdNComprou(int p){
     printf("Total de produtos não comprados: %d\n", p);
}


void printTime(time_t end,time_t start){
    printf("\nTempo de execucao da query : %2f \n", difftime(end, start));
}

void carregaLogoV2(){
	printf("******************************************************************************************\n");
	printf("*                                                                                        *\n");
	printf("*                                                                                        *\n");
	printf("*                            $$$$$$        $$$$$$       $$     $$                        *\n");
	printf("*                           $$            $$    $$      $$     $$                        *\n");
	printf("*                           $$            $$             $$   $$                         *\n");
	printf("*                            $$$$$$       $$  $$$$       $$   $$                         *\n");
	printf("*                                 $$      $$    $$        $$ $$                          *\n");
	printf("*                                 $$      $$    $$         $$$                           *\n");
	printf("*                            $$$$$$        $$$$$$           $                            *\n");
	printf("*                                                                                        *\n");
	printf("*                                                                                        *\n");
	printf("*                                                                                        *\n");
	printf("******************************************************************************************\n");

}


void printaBikes(){
    printf("Nao existe a quantidade de vendas desejada, por favor 1 ,3 ou 5 \n");
}

void printPergFicheiro(){
    printf("\nQual o ficheiro que quer abrir?\n");
}

void printInfo(int lidas,int validadas,int num){
    printf("\nNR linhas lidas: %d\nNR linhas validadas : %d \nFicheiros lidos: FIcheiro clientes, ficheiro produtos, ficheiro %dVendas\n",lidas,validadas,num );
}