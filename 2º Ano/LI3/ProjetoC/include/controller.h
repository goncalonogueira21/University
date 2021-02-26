#ifndef CONTROLLER
#define CONTROLLER
#include <stdio.h>
#include "view.h"
#include "interface.h"
#include "faturacao.h"

void imprimePaginas(Zat_Array* teste);
void imprimePaginas10(Zat_Array2* teste);
void imprimePaginas12(Zat_Array2* teste);
void imprimePaginas4(Quatro* teste);
void imprimePaginas44(Quatro* teste, int branch);
SGV query1(SGV sgv, int num);
void query2(SGV sgv);
void query3(SGV sgv);
void query4(SGV sgv);
void query5(SGV sgv);
void query7(SGV sgv);
void query6(SGV sgv);
void query8(SGV sgv);
void query9(SGV sgv);
void query10(SGV sgv);
void query11(SGV sgv);
void query12(SGV sgv);
void query13(SGV sgv, int num);
void run();
#endif
