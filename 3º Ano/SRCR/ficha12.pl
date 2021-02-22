%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% SIST. REPR. CONHECIMENTO E RACIOCINIO - MiEI/3

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Programacão em logica 
% Resolução de problemas de pesquisa  Informada (Ficha 10)

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% SICStus PROLOG: Declaracoes iniciais

:- set_prolog_flag( discontiguous_warnings,off ).
:- set_prolog_flag( single_var_warnings,off ).
:- set_prolog_flag( unknown,fail ).

%---------------------------------  dados do problema ---------

move(s, a, 2).
move(a, b, 2).
move(b, c, 2).
move(c, d, 3).
move(d, t, 3).
move(s, e, 2).
move(e, f, 5).
move(f, g, 2).
move(g, t, 2).

move(b,f,2).

estima(a, 5).
estima(b, 4).
estima(c, 4).
estima(d, 3).
estima(e, 7).
estima(f, 4).
estima(g, 2).
estima(s, 10).
estima(t, 0).

goal(t).











%---------------------------------  profundidadeprimeiro com custo ---------

resolve_pp_c(Nodo, [Nodo|Caminho], C) :-
	profundidadeprimeiro(Nodo, Caminho, C).

profundidadeprimeiro(Nodo, [], 0) :-
	goal(Nodo).

profundidadeprimeiro(Nodo, [ProxNodo|Caminho], C) :-
	adjacente(Nodo, ProxNodo, C1),
	profundidadeprimeiro(ProxNodo, Caminho, C2), C is C1 + C2.	

adjacente(Nodo, ProxNodo, C) :- 
	move(Nodo, ProxNodo, C).





todos(L):-findall((S,C), (resolvedf(S), length(S,C)), L).

melhor(N, S, Custo):- findall((SS, CC), resolve_pp_c(N, SS, CC),L), minimo(L,(S,Custo)).

escrever([]).
escrever([(X,Y)|L]):- write(X), write(' - '), write(Y), nl, escrever(L).

minimo([(P,X)],(P,X)).
minimo([(Px,X)|L],(Py,Y)):- minimo(L,(Py,Y)), X>Y. 
minimo([(Px,X)|L],(Px,X)):- minimo(L,(Py,Y)), X=<Y. 

minimo1([X],X).
minimo1([X|L], Y):- minimo1(L,Y), X>Y. 
minimo1([X|L], X):- minimo1(L,Y), X=<Y. 


%---------------------------------  A* ---------

resolve_aestrela(Nodo, Caminho/Custo) :-
	estima(Nodo, Estima),
	aestrela([[Nodo]/0/Estima], InvCaminho/Custo/_),
	inverso(InvCaminho, Caminho).

aestrela(Caminhos, Caminho) :-
	obtem_melhor(Caminhos, Caminho),
	Caminho = [Nodo|_]/_/_,goal(Nodo).

aestrela(Caminhos, SolucaoCaminho) :-
	obtem_melhor(Caminhos, MelhorCaminho),
	seleciona(MelhorCaminho, Caminhos, OutrosCaminhos),
	expande_aestrela(MelhorCaminho, ExpCaminhos),
	append(OutrosCaminhos, ExpCaminhos, NovoCaminhos),
        aestrela(NovoCaminhos, SolucaoCaminho).		


obtem_melhor([Caminho], Caminho) :- !.

obtem_melhor([Caminho1/Custo1/Est1,_/Custo2/Est2|Caminhos], MelhorCaminho) :-
	Custo1 + Est1 =< Custo2 + Est2, !,
	obtem_melhor([Caminho1/Custo1/Est1|Caminhos], MelhorCaminho).
	
obtem_melhor([_|Caminhos], MelhorCaminho) :- 
	obtem_melhor(Caminhos, MelhorCaminho).

expande_aestrela(Caminho, ExpCaminhos) :-
	findall(NovoCaminho, adjacente(Caminho,NovoCaminho), ExpCaminhos).

adjacente([Nodo|Caminho]/Custo/_, [ProxNodo,Nodo|Caminho]/NovoCusto/Est) :-
	move(Nodo, ProxNodo, PassoCusto),\+ member(ProxNodo, Caminho),
	NovoCusto is Custo + PassoCusto,
	estima(ProxNodo, Est).
%---------------------------------  Guloso ---------


resolve_guloso(Nodo, Caminho/Custo) :-
	estima(Nodo, Estima),
	aguloso([[Nodo]/0/Estima], InvCaminho/Custo/_),
	inverso(InvCaminho, Caminho).

aguloso(Caminhos, Caminho) :-
	obtem_melhorGuloso(Caminhos, Caminho),
	Caminho = [Nodo|_]/_/_,goal(Nodo).

aguloso(Caminhos, SolucaoCaminho) :-
	obtem_melhorGuloso(Caminhos, MelhorCaminho),
	seleciona(MelhorCaminho, Caminhos, OutrosCaminhos),
	expande_guloso(MelhorCaminho, ExpCaminhos),
	append(OutrosCaminhos, ExpCaminhos, NovoCaminhos),
        aestrela(NovoCaminhos, SolucaoCaminho).	


obtem_melhorGuloso([Caminho], Caminho) :- !.

obtem_melhorGuloso([Caminho1/Custo1/Est1,_/Custo2/Est2|Caminhos], MelhorCaminho) :-
	Est1 =<  Est2, !,
	obtem_melhorGuloso([Caminho1/Custo1/Est1|Caminhos], MelhorCaminho).
	
obtem_melhorGuloso([_|Caminhos], MelhorCaminho) :- 
	obtem_melhorGuloso(Caminhos, MelhorCaminho).

expande_guloso(Caminho, ExpCaminhos) :-
	findall(NovoCaminho, adjacenteguloso(Caminho,NovoCaminho), ExpCaminhos).

adjacenteguloso([Nodo|Caminho]/_/Est, [ProxNodo,Nodo|Caminho]/Custo/NovaEst) :-
	estima(ProxNodo, PassoEst),\+ member(ProxNodo, Caminho),
	NovaEst is Est + PassoEst,
	move(Nodo,ProxNodo,Custo).

%---------------------------------  predicados auxiliares ---------




membro(X, [X|_]).
membro(X, [_|Xs]):-
	membro(X, Xs).

membros([], _).
membros([X|Xs], Members):-
	membro(X, Members),
	membros(Xs, Members).



nao( Questao ) :-
    Questao, !, fail.
nao( Questao ).	

escrever([]).
escrever([X|L]):- write(X), nl, escrever(L). 

inverso(Xs, Ys):-
	inverso(Xs, [], Ys).

inverso([], Xs, Xs).
inverso([X|Xs],Ys, Zs):-
	inverso(Xs, [X|Ys], Zs).

seleciona(E, [E|Xs], Xs).
seleciona(E, [X|Xs], [X|Ys]) :- seleciona(E, Xs, Ys).
