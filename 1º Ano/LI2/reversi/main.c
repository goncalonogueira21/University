/**
 @file main.c
 @authors Carlos Afonso A82529, Gonçalo Nogueira A86617 e João Neves A81366
 @version 1.0

 Ficheiro onde se encontra a função "main" do programa utilizando as funções definidas em "estado.c"
 */


#include <stdio.h>
#include "estado.h"
#include <stdlib.h>


int main() {
    int l,c;// linhas e colunas
    int flag=1;
    char linha[1024]; // vetor para armazenar os caracteres lidos dos comando introduzidos
    int flag3=0;
    linha[0]='a';
    ESTADO e = {0}; // Estado inicial a NULL
    char venc1 ='a';
    LISTA b=0; // Inicializa a lista a vazio para as ajudas
    LISTA *z=&b;
    e = estado_inicial(e); // Inicializa o estado do jogo
    printf("Bem vindo, escolhe o que queres fazer\n");
    printf("N <peca>- Novo Jogo\n");
    printf("E <peca>- Escrever Ficheiro\n");
    printf("L <ficheiro>- Ler Ficheiro\n");
    printf("A - Jogar contra Bot\n");
    printf("S - Ajuda\n");
    printf("P - Passar a vez da jogada\n");
    printf("U - Para fazer undo\n");
    printf("J - Sugestao de jogada\n");
    printf("Q - Sair \n");

    ESTADO solucao= {0}; // Inicializa um ESTADO onde guardamos as jogadas possiveis a cada atualização
    int flag2=0;
    int scoreH=0;
    int flagJOGO=1;
    int jogoBot=0;
    int botjogou=0; // Inicialização do bot ter jogado
    ESTADO help= {0}; // Inicialização do ESTADO para as ajudas


    while(linha[0]!='Q' && flagJOGO) {

        if (jogoBot) {
            e.modo='1';
              if (botjogou){
                  gets(linha);
                  getComando(linha);
              }
                else linha[0]='A';
        } else {

        gets(linha);
        getComando(linha);
        if(linha[0]=='N') e.modo='0';

    }
        switch (linha[0]) {
            case 'N':

                if (linha[1] == 'x' || linha[1] == 'X' || linha[1] == 'o' || linha[1] == 'O') {


                    e = estado_inicial(e); // Inicializa ESTADO
                    e = inicia_jogo(e, linha[1]); // Vê qual a peça a ser jogada primeiro
                    inserir(z, e);  // insere o ESTADO na lista ligada
                    solucao = mostra_posicoes(e);
                    printamodo(e);// Imprime o modo de jogo introduzido e a peça a ser jogada
                    printa(e);// Da print ao 'Tabuleiro'
                    score(e); //Da print ao score do jgo


                } else {
                    printf("Erro: escolha O ou X\n");

                }
                break;
            case 'S':
                printamodo(e);
                printa(solucao);// Da print ao tabuleiro do estado onde se guarda as possiveís posições para se jogar
                score(e);

                break;

            case 'J':

                if (pode_jogar(linha) == 0) {
                    l = conv(linha, 1);
                    c = conv(linha, 2);

                      if (posicaojogavel(l, c, solucao)) {
                        e = meteP(l, c, e);
                        e = convert(l, c, e);
                        e = atualiza_peca(e);
                        inserir(z, e);
                        botjogou=0;
                        printamodo(e);
                        printa(e);
                        score(e);
                        solucao = mostra_posicoes(e);
                    } else {
                        printf("Invalido. Prime S para ajuda\n");
                        printamodo(e);
                        printa(e);
                        score(e);
                    }

                } else {
                    printf("Invalido\n");
                    printamodo(e);
                    printa(e);
                    score(e);
                }

                break;

            case 'E':
                getFicheiro(linha); // Retira o nome do ficheiro
                printNoFicheiro(e, linha); // Escreve no ficheiro
                printamodo(e);
                printa(e);
                break;

            case 'L':
                getFicheiro(linha);
                e=leFicheiro(linha,e);// Le o ficheiro para o ESTADO
                printa(e);
                score(e);
                solucao = mostra_posicoes(e);
                inserir(z, e); // insere o ESTADO lido na coluna
                break;

            case 'H':
                scoreH = maxScorePos(solucao);//Coloca na variavel a posição onde a jogada dá mais score
                int linhass = retL(scoreH);
                int colunass = retC(scoreH);
                help = e;
                e= ajuda(linhass, colunass, e);
                printamodo(e);
                printa(e);
                score(e);
                e = help;
                break;

            case 'U':
                e = daPenult(&b);// Atualiza o ESTADO para o anterior
                printamodo(e);
                printa(e);
                score(e);
                solucao = (mostra_posicoes(e));// Atualiza também o ESTADO das soluções
                break;

            case  'A':
                if (flag3) flag2=1; // flag que passa a jogada caso o utilizador pressione O como sendo o 1 a jogar
                if (flag) { // flag que testa se o modo automatico ja se inicializou ou nao
                    if (linha[1] == 'x' || linha[1] == 'X' || linha[1] == 'o' || linha[1] == 'O') {
                        printamodo(e);
                        e = estado_inicial(e);
                        e = inicia_jogo(e, linha[1]);
                        inserir(z, e);
                        solucao = mostra_posicoes(e);

                        if (e.peca == VALOR_X ) {
                            flag2 = 1;
                        } else {

                            flag=0;
                            flag3=1;
                            botjogou=1;
                            e= atualiza_peca(e);
                            inserir(z, e);
                            printamodo(e);
                            printa(e);
                            score(e);
                            solucao=mostra_posicoes(e);
                        }

                        jogoBot=1; // inicializa a flag para o jogo automatico

                    } else {
                        printf("Erro: escolha O ou X\n");

                    }
                }


                if (flag2) { // flag que mediante a inicializacao do jogo automatico deixa jogar o bot, se for a sua vez

                    flag = 0;
                    int scoreJ = maxScorePos(solucao);
                    botjogou=1;

                    int linhas = retL(scoreJ);
                    int coluna = retC(scoreJ);

                    e = meteP(linhas, coluna, e);
                    e = convert(linhas, coluna, e);
                    e = atualiza_peca(e);
                    inserir(z, e);
                    printamodo(e);
                    printa(e);
                    score(e);
                    solucao = mostra_posicoes(e);

                }
                break;


            case 'P' :
                e=atualiza_peca(e);// muda a peça no ESTADO para a outra
                inserir(z, e);
                botjogou=0;
                printamodo(e);
                printa(e);
                score(e);
                solucao = mostra_posicoes(e);

                break;
            default:
                printf("comando invalido\n");
                break;


        }


         flagJOGO = posicaoJog(mostra_posicoes(e));


    }

    venc1 = mostravenc(e); // Indica a peça vencedora
        printf("\no seu jogo acabou\n");
        printf("o vencedor e...... %c", venc1);




return 0;
}