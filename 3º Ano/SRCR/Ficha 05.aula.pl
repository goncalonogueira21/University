%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% SIST. REPR. CONHECIMENTO E RACIOCINIO - MiEI/3

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Invariantes

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% SICStus PROLOG: Declaracoes iniciais

:- set_prolog_flag( discontiguous_warnings,off ).
:- set_prolog_flag( single_var_warnings,off ).
:- set_prolog_flag( unknown,fail ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% SICStus PROLOG: definicoes iniciais

:- op( 900,xfy,'::' ).
:- dynamic filho/2.
:- dynamic pai/2.
:- dynamic idade/2.

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado filho: Filho,Pai -> {V,F}

filho( joao,jose ).
filho( jose,manuel ).
filho( carlos,jose ).
filho(carlos,maria).
%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado idade: Pessoa,Idade -> {V,F}

idade( joao,21,m).
idade( jose,42,m ).
idade( manuel,63,m ).
idade( carlos,19,m ).
idade(maria, 43,f).
idade(marco,23,m).
%--------------------------------- - - - - - - - - - -  -  -  -  -   -

descendente( D,A,1 ) :-
    filho( D,A ).
descendente( D,A, G  ) :-
    filho( D,X ),
    descendente( X,A,N ),
	G is N+1.

avo( A,D ) :-
    descendente( D,A,2 ).

pai(A,D) :-
    descendente(D,A,1).


%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Invariante Estrutural:  nao permitir a insercao de conhecimento
%                         repetido

+filho( F,P ) :: (solucoes( (F,P),(filho( F,P )),S ),
                  comprimento( S,N ), 
				  N == 1  ).

% Invariante Referencial: nao admitir mais do que 2 progenitores
%                         para um mesmo individuo

+filho( F,P ) :: (solucoes( (Ps),(filho( F,Ps )),S ),
                  comprimento( S,N ), 
                  N =< 2  ).

% Invariante Referencial: nao e' possivel remover filhos para
%                         os quais exista registo de idade

-filho( F,P ) :: (solucoes( (F),( idade( F,I ) ),S ),
                  comprimento( S,N ), 
                  N == 0  ).

%inv email
+pai( A,D ) :: (solucoes( (G),( idade( F,I,G ) ),S ),comprimento( S,N ), N == 2 ).

%4-----
+avo(A,N)::(findall((A,N),(filho(N,X),filho(X,A)),Lista),length(Lista,1)).

%9----
+avo(A,N)::(solucoes(   (As),(avo(As,N)) ,S),  comprimento(S,N1),   N1=<4).



%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensão do predicado que permite a evolucao do conhecimento

evolucao( Termo ) :-
    solucoes( Invariante, +Termo::Invariante,Lista ),
    insercao( Termo ),
    teste( Lista ). 

insercao( Termo ) :-
    assert( Termo ).
insercao( Termo ) :-
    retract( Termo ), !,fail.
	
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
% Extensao do meta-predicado nao: Questao -> {V,F}

nao( Questao ) :-
    Questao, !, fail.
nao( Questao ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -

solucoes( X,Y,Z ) :-
    findall( X,Y,Z ).

comprimento( S,N ) :-
    length( S,N ).
