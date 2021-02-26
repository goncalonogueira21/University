#ifndef VIEW
#define VIEW
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "faturacao.h"




void printMenu();
void printClear();
void printOpNdisponivel();
void printPrecisaCarregar();
void printaPagina(char** v,int index);
void printRodapeTeclas();
void printRodapeInfo(int h, int nmrpag, int index, int t);
void printLetraInvalida();
void printVoltarAoMenu();
void printMenuQ2();
void printMenuQ3();
void printMenuQ5();
void printMenuQ4();
void printMenuQ6();
void printMenuQ7();
void printMenuQ8();
void printMenuQ9();
void printMenuQ10();
void printMenuQ11();
void printMenuQ12();
void printMenuQ13();
void printCliente();
void printPergFilial();
void printCodigo(char* p);
void printLimite();
void printMesInvalido();
void printPergProduto();
void printMesFinal();
void printMVendas(int mesI,int mesF,int vendas);
void printMFaturado(int mesI,int mesF,double faturado);
void printTotalFaturado2modos(float tfn,float tfp);
void printTotalVendas2modos(int tvn,int tvp);
void printParagrafos();
void printInfoInvalida();
void printTouF();
void printFilial(int filial);
void printTabela(int a[3][12]);
void printTabela11(OnzeP* teste, int limit);
void printClienteNExiste();
void printProdutoNExiste();
void printNComprouMes();
void carregaLogoV2();
void printCodigoProduto(char* p);
void printQntdProduto(int q);
void printPrecoProduto(float p);
void printTotCliNComprou(int c);
void printTotProdNComprou(int p);
void printTime(time_t end,time_t start);
void printaBikes();
void printPergFicheiro();
void printInfo(int lidas,int validadas,int num);
#endif