%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% SIST. REPR. CONHECIMENTO E RACIOCINIO - MiEI/3




%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% SICStus PROLOG: Declaracoes iniciais

:- set_prolog_flag( discontiguous_warnings,off ).
:- set_prolog_flag( single_var_warnings,off ).
:- set_prolog_flag( unknown,fail ).


%------------------------------------------------------
%1


%------------------------------------------------------
%3




%-------------------------------------------------------
%4

%---------------------------------------------------------------
%6




%-------------------------------------------------------------- 
%7
mdc( X,Y,R ) :- X>Y, X1 is X-Y, mdc(X1,Y,R).
mdc(X,Y,R) :- Y>X, Y1 is Y-X, mdc(X,Y1,R).
mdc(X,X,X).

%-------------------------------------------------------------- 
%9
fibonacci(0,0).
fibonacci(1,1).
fibonacci(N,R):- N1 is N-1,
                 N2 is N-2,
                 fibonacci(N1,R1),
                 fibonacci(N2,R2),
                 R is R1 + R2 .


