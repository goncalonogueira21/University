% SIST. REPR. CONHECIMENTO E RACIOCIONIO - MiEI/3
%--------------------------------- - - - - - - - - - -  -  -  -  -   -

% Ficheiro que contém a base de conhecimento.
:- include('trabalho.pl').

% SICStus PROLOG: Declaracoes iniciais
:- set_prolog_flag(toplevel_print_options, [quoted(true), portrayed(true), max_depth(0)]).
:- set_prolog_flag( discontiguous_warnings,off ).
:- set_prolog_flag( single_var_warnings,off ).
:- set_prolog_flag( unknown,fail ).



%--------------------------------------------------------------------------
%---bfs------
resolvebf(Start, Goal, Final) :- bfs([Start], Goal, [], Path), naoPath(Goal, Path, [], Final).

bfs([Goal|_], Goal, Visited, [Goal|Visited]).
bfs([Start|Rest], Goal, Visited, Path) :- findall(Prox,
                                                       (connected(Start, Prox),
                                                        /+ membro(Prox, Visited),
                                                        /+ membro(Prox, Rest)), Seguintes), 
														sort(Seguintes, Ordered),
														append(Rest, Ordered, Next),
                                                        bfs(Next, Goal, [Start|Visited], Path).


naoPath(Start, [], Adj, [Start|Adj]).
naoPath(Start, [First|Path], connected, Final) :- connected(Start, First) -> naoPath(First, Path, [Start|connected], Final);
                                                                                          naoPath(Start, Path, connected, Final).



%---------------------------------  predicados auxiliares ---------


membro(X, [X|_]).
membro(X, [_|Xs]):-
	membro(X, Xs).

membros([], _).
membros([X|Xs], Members):-
	membro(X, Members),
	membros(Xs, Members).


inverso(Xs, Ys):-
	inverso(Xs, [], Ys).

inverso([], Xs, Xs).
inverso([X|Xs],Ys, Zs):-
	inverso(Xs, [X|Ys], Zs).

nao( Questao ) :-
    Questao, !, fail.
nao( Questao ).	

escrever([]).
escrever([X|L]):- write(X), nl, escrever(L). 

connected(X,Y) :- ligacao(X,Y); ligacao(Y,X).
