% SIST. REPR. CONHECIMENTO E RACIOCIONIO - MiEI/3
%--------------------------------- - - - - - - - - - -  -  -  -  -   -

% Ficheiro que contém a base de conhecimento.
:- include('trabalho.pl').

% SICStus PROLOG: Declaracoes iniciais
:- set_prolog_flag(toplevel_print_options, [quoted(true), portrayed(true), max_depth(0)]).
:- set_prolog_flag( discontiguous_warnings,off ).
:- set_prolog_flag( single_var_warnings,off ).
:- set_prolog_flag( unknown,fail ).
:- use_module(library(lists)).

%----------------------------------Calcular um trajeto possível entre duas cidades----------------------------------------

resolvebf(Start, Goal, Final) :- bfs([Start], Goal, [], Path),naoPath(Goal,Path,[],Final).

bfs([Goal|_], Goal, Visited, [Goal|Visited]).                                                       %quando chegamos ao destino
bfs([Start|Rest], Goal, Visited, Path) :- findall(Prox, (connected(Start, Prox),
                                                        \+ membro(Prox, Visited),                      %verifica se o proximo local ainda nao foi visitado
                                                        \+ membro(Prox, Rest)), Seguintes),            %coloca em seguintes os locais possiveis
														sort(Seguintes, Ordered),                      %ordenar
														append(Rest, Ordered, Next),                   %meter no fim
                                                        bfs(Next, Goal, [Start|Visited], Path).        %volta a correr o algoritmo mas o que antes era start agora é o proximo local que chegamos,
                                                        											   % a queue esta updated


naoPath(Start, [], Adj, [Start|Adj]).
naoPath(Start, [First|Path], Bounded, Final) :- connected(Start, First) -> naoPath(First, Path, [Start|Bounded], Final);naoPath(Start, Path, Bounded, Final).











%------------------------pesquisa em profundidade-------------------------------------------






resolvedf(Start, Goal, Final):-
	dfs(Start, Goal, [Start], Final).

dfs(Goal,Goal,A,Z):- inverso(A,Z).

dfs(Estado, Goal, Historico, Path):-
	connected(Estado,Next),
	nao(membro(Next, Historico)),
	dfs(Next, Goal,[Next|Historico], Path).	



%-----------------Escolher  uma  ou  mais  cidades  intermédias  por  onde  o  percurso  deverá obrigatoriamente passar-----------------------



resolvebfIntermediarias(Start,Goal,City1,City2,Final):-resolvebf(Start,City1,Final1),resolvebf(City1,City2,Final2),resolvebf(City2,Goal,Final3),
														append(Final1,Final2,Final4),append(Final4,Final3,Final5),remove_duplicates(Final5,Final).





%----------------------------Escolher um percurso que passe apenas por cidades “minor”----------------------------------------------

resolvebf1(Start, Goal, Zat, Final) :- bfs1([Start], Goal, [], Zat, Path),naoPath(Goal,Path,[],Final).

bfs1([Goal|_], Goal, Visited, Zat, [Goal|Visited]).                                                          %quando chegamos ao destino
bfs1([Start|Rest], Goal, Visited, Zat, Path) :- findall(Prox,(connected(Start, Prox),
                                                        \+ membro(Prox, Visited),                      %verifica se o proximo local ainda nao foi visitado
                                                        \+ membro(Prox, Rest),
                                                       	hasZat(Zat,Prox)),Seguintes),                         % verifica se local é minor                                   
														sort(Seguintes, Ordered),                      %ordenar
														append(Rest, Ordered, Next),                   %meter no fim
                                                        bfs1(Next, Goal, [Start|Visited], Zat ,Path).        %volta a correr o algoritmo mas o que antes era start agora é o proximo local que chegamos, a queue esta updated






hasZat(Zat,Prox):- local(_,Prox,_,_,_,Zat,_).


%--------------------------------Excluir uma ou mais caracteristicas de cidades para um percurso------------------------------------------

resolvebf2(Start, Goal, Zat, Final) :- bfs2([Start], Goal, [], Zat, Path),naoPath(Goal,Path,[],Final).

bfs2([Goal|_], Goal, Visited, Zat, [Goal|Visited]).                                                    %quando chegamos ao destino
bfs2([Start|Rest], Goal, Visited, Zat, Path) :- findall(Prox,(connected(Start, Prox),
                                                        \+ membro(Prox, Visited),                      %verifica se o proximo local ainda nao foi visitado
                                                        \+ membro(Prox, Rest),
                                                       	\+ hasDesc(Zat,Prox)),Seguintes),                       %verifica se local nao tem caraterística                                 
														sort(Seguintes, Ordered),                      %ordenar
														append(Rest, Ordered, Next),                   %meter no fim
                                                        bfs2(Next, Goal, [Start|Visited], Zat ,Path).        %volta a correr o algoritmo mas o que antes era start agora é o proximo local que chegamos, a queue esta updated






hasDesc(Zat,Prox):- local(_,Prox,_,_,_,_,Zat).


%--------------------------------Selecionar apenas cidades,com uma determinada caraterística,para um determinado trajeto;------------------------------------------

resolvebf3(Start, Goal, Zat, Final) :- bfs3([Start], Goal, [], Zat, Path),naoPath(Goal,Path,[],Final).

bfs3([Goal|_], Goal, Visited, Zat, [Goal|Visited]).                                                    %quando chegamos ao destino
bfs3([Start|Rest], Goal, Visited, Zat, Path) :- findall(Prox,(connected(Start, Prox),
                                                        \+ membro(Prox, Visited),                      %verifica se o proximo local ainda nao foi visitado
                                                        \+ membro(Prox, Rest),
                                                       	 hasDesc(Zat,Prox)),Seguintes),                          %verifica se local tem caraterística                                  
														sort(Seguintes, Ordered),                      %ordenar
														append(Rest, Ordered, Next),                   %meter no fim
                                                        bfs3(Next, Goal, [Start|Visited], Zat ,Path).        %volta a correr o algoritmo mas o que antes era start agora é o proximo local que chegamos, a queue esta updated



%--------------------------------Identificar num determinado percurso qual a cidade com o maior número de ligações------------------------------------------

resolvebf4(Start, Goal, Z):- resolvebf(Start,Goal,Path),findLargest(Path,[],Z).




findLargest([X|Xs],[],Z):-maior(X,F),
						findLargest(Xs,[F],Z).

findLargest([X],Zat,Z):-maior(X,F),
							findLargest([],[F|Zat],Z).

findLargest([],Zat,Z):-quick_sort(Zat,ZatSorted),inverso(ZatSorted,ZatInverted),head(ZatInverted,Z).




maior(X,(CountCity,CountNumber)):- findall(P,connected(X,P),L),length(L,CountNumber),CountCity=X.




	



%-------------------------------Escolher o menor percurso (usando o critério do menor número de cidades percorridas);---------------------------------------



melhor(Start, Goal, Path):- findall(P, (resolvebf(Start,Goal,P)),L), minimo1(L,Path).

minimo1([X],X).
minimo1([X|L], Y):- minimo1(L,Y), X>Y. 
minimo1([X|L], X):- minimo1(L,Y), X=<Y.

%-------------------------------Escolher o percurso mais rápido (usando o critério da distância);------------------------------------------


resolve_aestrela(Nodo,Goal, Caminho/Custo) :-
	distance(Nodo,Goal ,Estima),
	aestrela([[Nodo]/0/Estima], InvCaminho/Custo/_,Goal),
	inverso(InvCaminho, Caminho).

aestrela(Caminhos, Caminho, Goal) :-
	obtem_melhor(Caminhos, Caminho,Goal),
	Caminho = [Goal|_]/_/_.

aestrela(Caminhos, Goal, SolucaoCaminho) :-
	obtem_melhor(Caminhos, MelhorCaminho,SolucaoCaminho),
	seleciona(MelhorCaminho, Caminhos, OutrosCaminhos),
	expande_aestrela(MelhorCaminho, ExpCaminhos,SolucaoCaminho),
	append(OutrosCaminhos, ExpCaminhos, NovoCaminhos),
        aestrela(NovoCaminhos, Goal, SolucaoCaminho).		


obtem_melhor([Caminho], Caminho,SolucaoCaminho) :- !.

obtem_melhor([Caminho1/Custo1/Est1,_/Custo2/Est2|Caminhos], MelhorCaminho,SolucaoCaminho) :-
	Custo1 + Est1 =< Custo2 + Est2, !,
	obtem_melhor([Caminho1/Custo1/Est1|Caminhos], MelhorCaminho,SolucaoCaminho).
	
obtem_melhor([_|Caminhos], MelhorCaminho,SolucaoCaminho) :- 
	obtem_melhor(Caminhos, MelhorCaminho,SolucaoCaminho).

expande_aestrela(Caminho, ExpCaminhos,SolucaoCaminho) :-
	findall(NovoCaminho, adjacente(Caminho,NovoCaminho,SolucaoCaminho), ExpCaminhos).

adjacente([Nodo|Caminho]/Custo/_, [ProxNodo,Nodo|Caminho]/NovoCusto/Est, SolucaoCaminho) :-
			connected(Nodo,ProxNodo),
	distance(Nodo, ProxNodo, PassoCusto),\+ member(ProxNodo, Caminho),
	NovoCusto is Custo + PassoCusto,
	distance(Nodo,ProxNodo,Est).








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

reverse_print_stack(S) :-
	empty_stack(S).
reverse_print_stack(S) :-
	stack(E, Rest, S),
	reverse_print_stack(Rest),
	write(E), nl.

connected(X,Y) :- ligacao(X,Y); ligacao(Y,X).

connected1(X,Y,Z) :- ligacao(X,Y); ligacao(Y,X),
					Z is Y.

distance(N1,N2,D) :- local(_,N1,X1,X2,_,_,_), 
                     local(_,N2,Y1,Y2,_,_,_),
                     D is sqrt((X2-X1)^2 + (Y2-Y1)^2).


remove_duplicates([],[]).

remove_duplicates([H | T], List) :-    
     member(H, T),
     remove_duplicates( T, List).

remove_duplicates([H | T], [H|T1]) :- 
      \+member(H, T),
      remove_duplicates( T, T1).



pivoting(_,[],[],[]).
pivoting((A,B),[(C,D)|T],[(C,D)|L],G):-D>B,pivoting((A,B),T,L,G).
pivoting((A,B),[(C,D)|T],[(C,D)|L],G):-D=B,C>A,pivoting((A,B),T,L,G).
pivoting((A,B),[(C,D)|T],L,[(C,D)|G]):-D<B,pivoting((A,B),T,L,G).
pivoting((A,B),[(C,D)|T],L,[(C,D)|G]):-D=B,C<A,pivoting((A,B),T,L,G).
pivoting((A,B),[(C,D)|T],L,G):-A=C,D=B,pivoting((A,B),T,L,G).


      quick_sort(List,Sorted):-q_sort(List,[],Sorted).
q_sort([],Acc,Acc).
q_sort([H|T],Acc,Sorted):-
    pivoting(H,T,L1,L2),
    q_sort(L1,Acc,Sorted1),q_sort(L2,[H|Sorted1],Sorted).	


seleciona(E, [E|Xs], Xs).
seleciona(E, [X|Xs], [X|Ys]) :- seleciona(E, Xs, Ys).