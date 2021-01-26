/**
 @file estado.h
 @authors Carlos Afonso A82529, Gonçalo Nogueira A86617 e João Neves A81366
 @version 1.0

 Ficheiro onde estão definidos os tipos das funções do 'estado.c'
 */


#ifndef PROJ_ESTADO_H
#define PROJ_ESTADO_H
#define FALSE 0
#define TRUE 1


/**
estado.h
Definição do estado i.e. tabuleiro. Representação matricial do tabuleiro.
*/


// definição de valores possiveis no tabuleiro
typedef enum {VAZIA, VALOR_X, VALOR_O,JOGAVEL, AJUDA} VALOR;

/**
Estrutura que armazena o estado do jogo
*/
typedef struct estado {

    VALOR peca; // peça do jogador que vai jogar!
    VALOR grelha[8][8];
    char modo; // modo em que se está a jogar! 0-> manual, 1-> contra computador
} ESTADO;


/**
 Estrutura que define a lista ligada
 */
typedef struct lista {
    ESTADO esta; // contem um ESTADO
    struct lista *next; // apontador para o proximo ESTADO da lista ligada
}*LISTA;


ESTADO clearE (ESTADO e );
ESTADO ajuda(int x,int y, ESTADO e);
void printa(ESTADO);
ESTADO inicia_jogo(ESTADO e,char c);
ESTADO estado_inicial(ESTADO);
void printNoFicheiro(ESTADO e, char *cmd);
ESTADO meteP (int l,int c,ESTADO e);
ESTADO atualiza_peca (ESTADO);
ESTADO mostra_posicoes(ESTADO);
int posicaojogavel(int i,int j,ESTADO);
ESTADO convert(int i,int j,ESTADO e);
char mostravenc(ESTADO);
int posicaoJog (ESTADO e);
void score (ESTADO e);
void getComando(char *comando);
int pode_jogar(char *cmd);
int conv(char *cmd, int a);
void getFicheiro(char *cmd);
ESTADO leFicheiro(char *cmd,ESTADO e);
void inserir (LISTA *a, ESTADO e);
ESTADO daPenult(LISTA *a);
int retL(int x);
void printamodo(ESTADO e);
int retC(int x);
int maxScorePos(ESTADO e);
#endif //PROJ_ESTADO_H