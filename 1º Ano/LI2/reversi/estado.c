/**
 @file estado.c
 @authors Carlos Afonso A82529, Gonçalo Nogueira A86617 e João Neves A81366
 @version 1.0

 Ficheiro onde se encontram todas as funções para o programa e para o jogo funcionar
 */
#include <stdio.h>
#include <stdlib.h>
#include "estado.h"


/**
 * Esta função devolve 1 se a posição for jogável e 0 se a posição não for jogável
 * @param ESTADO e
 * @return 1 ou 0
 */
int posicaoJog (ESTADO e){
    int flag =0;
    int i,j;

    for ( i = 0; i < 8; i++) {
        for ( j = 0; j < 8; j++) {
            if (e.grelha[i][j] == JOGAVEL) flag = 1;

        }
    }
    return flag;
}

/**
 * Esta função devolve a peça que está no ESTADO atual para ser jogada
 * @param ESTADO e
 * @return char valor
 */
char conv_modo(ESTADO e){
    if(e.peca==VALOR_X) return 'X';
    else return 'O';
}

/**
 * Esta função transforma caracteres em inteiros (so pode ser de 0 a 7) ou se for diferente retorna 10
 * @param char *cmd, comando introduzido
 * @param int a,indice
 * @return int
 */
int conv(char *cmd, int a){
    if(cmd[a]=='0') return 0;
    if(cmd[a]=='1') return 1;
    if(cmd[a]=='2') return 2;
    if(cmd[a]=='3') return 3;
    if(cmd[a]=='4') return 4;
    if(cmd[a]=='5') return 5;
    if(cmd[a]=='6') return 6;
    if(cmd[a]=='7') return 7;
    else return 10;
}

/**
 * Esta função retorna 0 se o comando para jogar for numa posição válida ou 1 se não for
 * @param char *cmd, comando introduzido
 * @return 0 ou 1
 */
int pode_jogar(char *cmd){
    int a = conv(cmd,1);
    int b = conv(cmd,2);
    if((a>=0 && a<8) && (b>=0 && b<8)) return 0;
    else return 1;
}


/**
 * Esta função retira os espaços dos comandos introduzidos deixando os caracteres
 * @param char *jogada, comando
 */
void getComando(char *jogada){

    int i=0;
    int j=0;
    for(i=0;jogada[i];i++){
        if (jogada[i]!=' '){
            jogada[j]=jogada[i];
            j++;
        }
    }
}

/**
 * Esta funçao coloca no ESTADO a peça que começa a jogar primeiro
 * @param ESTADO e
 * @param char i, peça inicial do jogo
 * @return
 */
ESTADO inicia_jogo(ESTADO e,char i){


    if (i=='x' || i=='X') e.peca=VALOR_X;
    if (i=='o'|| i=='O') e.peca=VALOR_O;
    return e;
}

/**
 * Esta função imprime o modo de jogo
 * @param ESTADO e,atual
 */
void printamodo(ESTADO e){

    char a = conv_modo(e);
    if(e.modo=='0') {
        printf("M %c\n", a);
    }else printf("A %c\n", a);
}

/**
 * Esta função imprime o ESTADO do jogo(Tabuleiro)
 * @param ESTADO e, atual
 */
void printa(ESTADO e)
{
    char c = ' ';

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch (e.grelha[i][j]) {
                case VALOR_O: {
                    c = 'O';

                    break;
                }
                case VALOR_X: {
                    c = 'X';
                    break;
                }
                case VAZIA: {
                    c = '-';
                    break;
                }
                case JOGAVEL:{
                    c= '*';
                    break;
                }
                case AJUDA:{
                    c='?';
                }
            }
            printf("%c ", c);

        }
        printf("\n");
    }

}

/**
 * Esta função devolve o ESTADO inicial oolocando as peças inicias do jogo
 * nas posições iniciais
 * @param ESTADO e,atual
 * @return ESTADO e,inicial
 */
ESTADO estado_inicial(ESTADO e){
    e=clearE(e);

    e.grelha[3][4] = VALOR_X;
    e.grelha[4][3] = VALOR_X;
    e.grelha[3][3] = VALOR_O;
    e.grelha[4][4] = VALOR_O;



 return e;
}



/**
 * Esta funçao lê o ESTADO escrito num ficheiro e coloca-o no ESTADO atual do jogo
 * @param nome do ficheiro
 */
ESTADO leFicheiro(char *cmd,ESTADO e) {
    int i = 0;
    int j = 0;
    int l = 8, c = 8;
    char m[9][8];
    FILE *fp = fopen(cmd, "r"); // read mode

    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            fscanf(fp, " %c", &m[i][j]);


        }
    }
    fclose(fp);

    for (i = 0; i < l; ++i) {
        for (j = 0; j < c; ++j) {
            if (m[i][j] == '_') e.grelha[i][j] = VAZIA;
            if (m[i][j] == 'X') e.grelha[i][j] = VALOR_X;
            if (m[i][j] == 'O') e.grelha[i][j] = VALOR_O;


        }
    }

    printf("\nFicheiro Aberto\n\n");
    return e;
}




/**
 *
 * @param nome do ficheiro
 */

void getFicheiro(char *cmd){

    int j=0;
    for(int i=1;cmd[i];i++){
        cmd[j]=cmd[i];
        j++;
    }
    cmd[j-1]='\0';
}

/**
 * Esta função imprime num ficheiro pretendido  o ESTADO do jogo
 * @param ESTADO e,atual
 * @param nome do ficheiro (.txt)
 */
void printNoFicheiro(ESTADO e, char *cmd) {
    int i = 0, j = 0;

    FILE *f = fopen(cmd, "wb");

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (e.grelha[i][j] == VAZIA) fprintf(f, "-");
            if (e.grelha[i][j] == VALOR_O) fprintf(f, "O");
            if (e.grelha[i][j] == VALOR_X) fprintf(f, "X");

        }
        fprintf(f, "\n");
    }

    fclose(f);


    printf("\n");
}




/**
 * Esta função recebe a linha e coluna da jogada e altera o ESTADO do jogo
 * colocando a peça a ser jogada na posição pretendida
 * @param int l, linha da jogada pretendida
 * @param int c, coluna da jogada pretendida
 * @param ESTADO e antes da jogada ser realizada
 * @return ESTADO atualizado
 */
ESTADO meteP (int l,int c,ESTADO e){

    int i,j;



          for (i = 0; i < 8; i++) {
              for (j = 0; j < 8; j++) {
                  if (i == l && j == c ) e.grelha[i][j] = e.peca;
              }
          }

    return e;
}


/**
 * Esta função altera a vez da peça a ser jogada do ESTADO
 * @param ESTADO e, atual
 * @return ESTADO e atualizado
 */
ESTADO atualiza_peca(ESTADO e) {
    if (e.peca == VALOR_X) {
        e.peca = VALOR_O;
        return e;
    } else {
        e.peca = VALOR_X;
        return e;
    }
}

/**
 * Esta função recebe um ESTADO e conforme as suas peças devolve o ESTADO
 * atualizado com as posições jogaveis
 * @param ESTADO e, atual
 * @return ESTADO e,com posições jogaveis
 */
ESTADO mostra_posicoes(ESTADO e) {
    int i, j;
    int li, ci, lis, cis,dcx,dcy,ecx,ecy,ebx,eby,dbx,dby;
    VALOR oponent;
    if (e.peca == VALOR_O)oponent = VALOR_X;
    else oponent = VALOR_O;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (e.grelha[i][j] == VAZIA) {
                if(e.grelha[i][j+1]==oponent) {
                    //direta

                    for(ci=j+1; e.grelha[i][ci] == oponent && ci<8;ci++) {
                        if (e.grelha[i][ci + 1] == e.peca) {
                            e.grelha[i][j] = JOGAVEL;
                            break;
                        }

                    }
                }


                // esquerda





                for(cis=j-1; e.grelha[i][cis] == oponent && cis>=0;cis--) {
                    if (e.grelha[i][cis - 1] == e.peca) {
                        e.grelha[i][j] = JOGAVEL;
                        break;
                    }

                }



                //cima

                for(li=i-1;e.grelha[li][j] == oponent && li>=0;li--) {
                    if (e.grelha[li - 1][j] == e.peca) {
                        e.grelha[i][j] = JOGAVEL;
                        break;
                    }

                }



                // baixo


                for(lis=i+1;e.grelha[lis][j] == oponent && lis<8;lis++) {
                    if (e.grelha[lis + 1][j] == e.peca) {
                        e.grelha[i][j] = JOGAVEL;
                        break;
                    }

                }


                //diagonal direita cima



                for(dcx=i-1,dcy=j+1;e.grelha[dcx][dcy] == oponent && dcy<8 &&dcx>=0;dcx--,dcy++) {
                    if (e.grelha[dcx - 1][dcy+1] == e.peca) {
                        e.grelha[i][j] = JOGAVEL;
                        break;
                    }

                }


                //diagonal esquerda cima

                for(ecx=i-1,ecy=j-1;e.grelha[ecx][ecy] == oponent && ecx>=0 && ecy>=0;ecx--,ecy--) {
                    if (e.grelha[ecx - 1][ecy-1] == e.peca) {
                        e.grelha[i][j] = JOGAVEL;
                        break;
                    }

                }




                //diagonal direita baixo




                for(ebx=i+1,eby=j+1;e.grelha[ebx][eby] == oponent && ebx<8 && eby<8;ebx++,eby++) {
                    if (e.grelha[ebx + 1][eby +1] == e.peca) {
                        e.grelha[i][j] = JOGAVEL;
                        break;
                    }

                }


                //diagonal esquerda  baixo

                for(dbx=i+1,dby=j-1 ;e.grelha[dbx][dby] == oponent && dbx<8 && dby>=0;dbx++,dby--) {
                    if (e.grelha[dbx + 1][dby-1] == e.peca) {
                        e.grelha[i][j] = JOGAVEL;
                        break;
                    }

                }




            }
        }

    }
    return e;
}

/**
 * Esta função devolve 'FALSE' se a posição da jogada a ser efetuada
 * for numa posição inválido ou 'TRUE' se for valida
 * @param int i, linha da jogada pretendida
 * @param int j, coluna da jogada pretendida
 * @param ESTADO e, estado atual do jogo
 * @return Boolean conforme a jogada é possível ou nao
 */
int posicaojogavel(int i,int j,ESTADO e) {

    if (e.grelha[i][j]!= JOGAVEL) {
        return FALSE;
    } else return TRUE;
}

/**
 * Esta função devove o score da peça atuaal do estado
 * @param ESTADO e
 * @return inteiro com o score da peça no estado atual
 */
int scoreJOG(ESTADO e){
    int countX=0;
    int countO=0;
    int ret=0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if(e.grelha[i][j]==VALOR_X) countX++;
            if(e.grelha[i][j]==VALOR_O) countO++;


        }
    }
    if (e.peca==VALOR_X)  ret = countX;
    else ret =countO;

    return ret;

}

/**
 * Esta funçao recebe um estado e determina a posicao onde o score é maior
 * @param ESTADO e
 * @return a posiçao onde o score é maior
 */


int maxScorePos(ESTADO e){
        ESTADO ant;
        int maxscore=0;
        int maxpos=0;

        ant=e;
        int score=0;
        int count=0;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {

                if (e.grelha[i][j] == JOGAVEL) {


                    e.grelha[i][j] = e.peca;
                    e=convert(i,j,e);

                    score= scoreJOG(e);
                    if(score>maxscore){
                        maxscore=score;
                        maxpos=  count;
                    }



                }
                count++;
                e = ant;


            }
        }


        return maxpos;

    }

/**
 * Devolve a linha da posiçao encontrada com o melhor score
 * @param int x onde o 'x' é a posição obtida na função maxScorePos
 * @return a linha onde essa posição está
 */
int retL(int x){
    int conta=0;
    int flag=1;
    int i;
    int j;
    for ( i = 0; i < 8 && flag; i++) {
        for ( j = 0; j < 8 && flag; j++) {

            if (conta == x) flag=0;
            else conta++;


        }


    }


    return i-1;
}


/**
 * Devolve a coluna da posiçao encontrada com o melhor score
 * @param int x onde o 'x' é a posição obtida na função maxScorePos
 * @return a coluna onde essa posição está
 */

int retC(int x) {
    int conta = 0;
    int flag = 1;
    int i,j;

    for ( i = 0; i < 8 && flag; i++) {
        for ( j = 0; j < 8 && flag; j++) {
            if (conta == x) flag = 0;

            else conta++;
        }
    }
    return (j-1);

}








/**
 * Esta função converte as peças entre a peça do utilizador e a jogada efetuada
 * para que essa direção fique com as peças todas do  utilizador
 * @param int i é a linha da jogada efetuada
 * @param int j é a coluna da jogada efetuada
 * @param ESTADO e é o estado atual do jogo
 * @return Estado e
 */

ESTADO convert(int i,int j,ESTADO e) {
    int li, ci, es, di;
    int dcx, dcy, ecx, ecy, ebx, eby, dbx, dby;

    VALOR oponent;
    if (e.peca == VALOR_O)oponent = VALOR_X;
    else oponent = VALOR_O;

    //baixo
    int lis=i+1;
    int flagB=0;
    while (e.grelha[lis][j]==oponent){
        if(e.grelha[lis+1][j]==e.peca) flagB=1;
        lis++;
    }

    for (li = i + 1; li < 8 && e.grelha[li][j] == oponent && flagB; li++) {

        e.grelha[li][j] = e.peca;


    }

    //esquerda
    int cis=j-1;
    int flagE=0;
    while (e.grelha[i][cis]==oponent){
        if(e.grelha[i][cis-1]==e.peca) flagE=1;
        cis--;
    }




    for (ci = j - 1; ci >= 0 && e.grelha[i][ci] == oponent && flagE; ci--) {

        e.grelha[i][ci] = e.peca;


    }

    //cima
    int ess=i-1;
    int flagC=0;
    while (e.grelha[ess][j]==oponent){
        if(e.grelha[ess-1][j]==e.peca) flagC=1;
        ess--;
    }


    for (es = i - 1; es >= 0 && e.grelha[es][j] == oponent && flagC; es--) {

        e.grelha[es][j] = e.peca;


    }

    //direita
    int dis=j+1;
    int flagD=0;
    while (e.grelha[i][dis]==oponent){
        if(e.grelha[i][dis+1]==e.peca) flagD=1;
        dis++;
    }



    for (di = j + 1; di < 8 && e.grelha[i][di] == oponent && flagD; di++) {

        e.grelha[i][di] = e.peca;


    }


    // direita cima
    int aa=i-1;
    int bb = j+1;
    int flagDC=0;
    while (e.grelha[aa][bb]==oponent){
        if(e.grelha[aa-1][bb+1]==e.peca) flagDC=1;
        bb++;
        aa--;
    }



    for (dcx = i - 1, dcy = j + 1; dcx >= 0 && dcy < 8 && e.grelha[dcx][dcy] == oponent && flagDC; dcx--, dcy++) {
        e.grelha[dcx][dcy] = e.peca;
    }


    //  esquerda cima

    int cc=i-1;
    int dd = j-1;
    int flagEC=0;
    while (e.grelha[cc][dd]==oponent){
        if(e.grelha[cc-1][dd-1]==e.peca) flagEC=1;
        cc--;
        dd--;
    }




    for (ecx = i - 1, ecy = j - 1; ecx >= 0 && ecy >= 0 && e.grelha[ecx][ecy] == oponent && flagEC; ecx--, ecy--) {

        e.grelha[ecx][ecy] = e.peca;
    }


    // direita baixo
    int ee=i+1;
    int ff = j+1;
    int flagDB=0;
    while (e.grelha[ee][ff]==oponent){
        if(e.grelha[ee+1][ff+1]==e.peca) flagDB=1;
        ee++;
        ff++;
    }






    for(dbx=i+1,dby=j+1; dbx<8 && dby<8 && e.grelha[dbx][dby]==oponent && flagDB;dbx++,dby++) {
        e.grelha[dbx][dby]=e.peca;
    }


    // esquerda baixo

    int gg=i+1;
    int hh = j-1;
    int flagEB=0;
    while (e.grelha[gg][hh]==oponent){
        if(e.grelha[gg+1][hh-1]==e.peca) flagEB=1;
        gg++;
        hh--;
    }





    for(ebx=i+1,eby=j-1; ebx<8 && eby>=0 && e.grelha[ebx][eby]==oponent && flagEB ;ebx++,eby--) {
        e.grelha[ebx][eby]=e.peca;
    }

    return e;
}


/**
 *  Esta função da print ao score de cada peça
 * @param ESTADO e
 */

void score (ESTADO e) {

    int x=0;
    int o=0;
    int i, j;


    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (e.grelha[i][j] == VALOR_O) o++;
            if (e.grelha[i][j] == VALOR_X) x++;


        }
    }

    printf("Jogador X:%d   ", x );
    printf("Jogador O:%d   \n", o );
}


/**
 * Esta função insere no fim da lista um novo ESTADO
 * @param LISTA*a
 * @param ESTADO e
 */
void inserir(LISTA *a,ESTADO e) {

    LISTA new;

    new = malloc(sizeof(struct lista));
    new->esta = e;
    new->next = *a;
    *a=new;

}


/**
 * Esta função devolve o penúltimo estado da lista e liberta o espaço
 * de memória do último estado
 * @param LISTA *a
 * @return ESTADO
 */
ESTADO daPenult(LISTA *a) {
    LISTA t;

    if (*a == NULL || ((*a)->next) == NULL)
        printf("error\n");
    else {
        t = *a;
        *a = (*a)->next;
        free(t);


    }
    return ((*a)->esta);


}

/**
 * Esta função altera no estado na posição indicada para 'AJUDA'
 * @param int x, linha da posição
 * @param int y, coluna da posição
 * @param ESTADO e, estado atual do jogo
 * @return ESTADO com a ajuda ja apresentada
 */

ESTADO ajuda(int x,int y, ESTADO e){
   int i,j;

    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if(i==x && j==y) e.grelha[i][j]=AJUDA;
        }
    }
    return e;
}


/**
 * Esta função devolve a peça vencedora de um ESTADO
 * @param ESTADO e
 * @return peça
 */
char mostravenc(ESTADO e) {
    char venc =' ';
    int x = 0;
    int o = 0;
    int i, j;


    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (e.grelha[i][j] == VALOR_O) o++;
            if (e.grelha[i][j] == VALOR_X) x++;


        }
    }

    if(x>o) venc='X';
    if (x<o) venc='O';
    if (x==o) venc='?';

    return venc;
}

/**
 * Esta função recebe um ESTADO e coloca todos valores para vazio
 * @param ESTADO e
 * @return ESTADO e,alterado para os valores todos vazios
 */
ESTADO clearE (ESTADO e ){
  int i,j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {

            e.grelha[i][j] = VAZIA;
        }
    }
return e;
}