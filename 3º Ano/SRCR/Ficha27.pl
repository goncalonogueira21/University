%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% SIST. REPR. CONHECIMENTO E RACIOCINIO - MiEI/3




%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% SICStus PROLOG: Declaracoes iniciais

:- set_prolog_flag( discontiguous_warnings,off ).
:- set_prolog_flag( single_var_warnings,off ).
:- set_prolog_flag( unknown,fail ).


%------------------------------------------------------
%1
soma(X,Y,R) :- 
	R is X+Y.

%------------------------------------------------------
%3
%[H|T]

somaC([],0).
somaC([X|Y],N) :-
	somaC(Y,R), N is X+R. 


%-------------------------------------------------------
%4
fun(adicao,X,Y,R) :-
	R is X+Y.
	 
fun(subtracao,X,Y,R) :- 
	R is X-Y.

fun(multiplicacao,X,Y,R) :- 
	R is X*Y.

fun(divisao,X,Y,R) :- 
	Y\=0, R is X/Y.

%---------------------------------------------------------------
%6


maior(X,Y,X) :- X>Y.
maior(X,Y,Y) :- X=<Y.

%-------------------------------------------------------------- 
%7



