%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Programacao em logica estendida
% Representacao de conhecimento imperfeito

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% SICStus PROLOG: Declaracoes iniciais

:- set_prolog_flag( discontiguous_warnings,off ).
:- set_prolog_flag( single_var_warnings,off ).
:- set_prolog_flag( unknown,fail ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% SICStus PROLOG: definicoes iniciais

:- op( 900,xfy,'::' ).
:- dynamic jogo/3.



%-------------------------------------------------
% Aplicação do PMF ao predicado Jogo


-jogo( Jogo,Arbitro,Ajudas ) :-
    nao( jogo( Jogo,Arbitro,Ajudas ) ),
    nao( excecao( jogo( Jogo,Arbitro,Ajudas ) ) ).


%--------------------------------- - - - - - - - - - -  -  questão i
jogo( 1,aa,500 ).  

%--------------------------------- - - - - - - - - - -  -  questão ii
% Valor nulo tipo I - Desconhecido

jogo( 2,bb,xpto0123 ).
excecao( jogo( Jogo,Arbitro,Ajudas ) ) :-
    jogo( Jogo,Arbitro,xpto0123 ).

%--------------------------------- - - - - - - - - - -  -  questão iii
% Valor nulo tipo II - Desconhecido tomado de um conjunto de valores

excecao( jogo( 3,cc, 500 ) ).
excecao( jogo( 3,cc, 2500 ) ).
%--------------------------------- - - - - - - - - - -  -  questão iv

excecao( jogo( 4,dd,Ajudas ) ) :-
    Ajudas >= 250, Ajudas =< 750.

%--------------------------------- - - - - - - - - - -  -  questão v
% Valor nulo tipo III - Não permitido

jogo( 5,ee,xpto765 ).
excecao( jogo( Jogo,Arbitro,Ajudas ) ) :-
    jogo( Jogo,Arbitro,xpto765 ).

nulo( xpto765 ).

+jogo( J,A,C ) :: ( solucoes( Ajudas, (jogo( 5,ee,Ajudas ),
                              nao( nulo( Ajudas ) ) ),
                              S ),
                    comprimento( S,N ), N == 0 ).


%--------------------------------- - - - - - - - - - -  -  questão vi
jogo( 6,ff, 250 ).
excecao( jogo( 6,ff, Ajudas) ) :-
    Ajudas >= 5000.
 
%--------------------------------- - - - - - - - - - -  -  questão vii
-jogo( 7,gg, 2500).
jogo(7,gg,xpto321).
excecao( jogo( Jogo,Arbitro,Ajudas ) ) :-
    jogo( Jogo,Arbitro,xpto321).

%--------------------------------- - - - - - - - - - -  -  questão viii



excecao(jogo(8,hh,A)) :- cerca( 1000,X,Y),
                A>=Y, A=<X. 



cerca(X,Sup,Inf):-
    Sup is X*1.25,
    Inf is X*0.75.
%--------------------------------- - - - - - - - - - -  -  questão ix

excecao( jogo( 9,ii,Ajudas ) ) :- mproximo( 3000,Csup,Cinf ), Ajudas >= Cinf, Ajudas =< Csup.

mproximo( X,Sup,Inf ) :- Sup is X * 1.1, Inf is X * 0.9.

%--------------------------------- - - - - - - - - - -  -  questão x
%Invariante

+jogo( J,A,C) :: (solucoes(X, jogo( J,X,C), S),
                    comprimento( S,N), N == 1).


%--------------------------------- - - - - - - - - - -  -  questão xi

+jogo( J,A,C) :: (solucoes(J, jogo( J,A,C), S),
                    comprimento( S,N), N =<3).

%--------------------------------- - - - - - - - - - -  -  questão xii

+jogo( J,A,C) :: solucoes(A, jogo( J,A,C), S), solucoes(A, jogo( J+1,A,C), N),
                 concatenar(S,N,R), comprimento(R,P), P=<1.

%--------------------------------- - - - - - - - - - -  -  -  -  -   -

evolucao( Termo ) :-
    solucoes( Invariante,+Termo::Invariante,Lista ),
    insercao( Termo ),
    teste( Lista ).

insercao( Termo ) :-
    assert( Termo ).
insercao( Termo ) :-
    retract( Termo ),!,fail.

teste( [] ).
teste( [R|LR] ) :-
    R,
    teste( LR ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensão do predicado que permite a involucao do conhecimento

involucao( Termo ) :-
    solucoes( Invariante,-Termo::Invariante,Lista ),
    remocao( Termo ),
    teste( Lista ).

remocao( Termo ) :-
    retract( Termo ).
remocao( Termo ) :-
    assert( Termo ),!,fail.

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do meta-predicado demo: Questao,Resposta -> {V,F}
%                            Resposta = { verdadeiro,falso,desconhecido }

demo( Questao,verdadeiro ) :-
    Questao.
demo( Questao,falso ) :-
    -Questao.
demo( Questao,desconhecido ) :-
    nao( Questao ),
    nao( -Questao ).



%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do meta-predicado nao: Questao -> {V,F}

nao( Questao ) :-
    Questao, !, fail.
nao( Questao ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -

solucoes( X,Y,Z ) :-
    findall( X,Y,Z ).

comprimento( S,N ) :-
    length( S,N ).



pertence( X,[X|L] ).
pertence( X,[Y|L] ) :-
    X \= Y,
    pertence( X,L ).

% Extensão do predicado concatenar : L1,L2,R -> {V,F}
concatenar([],L,L).
concatenar([X|L1],L2,[X|L3]) :- concatenar(L1,L2,L3).
