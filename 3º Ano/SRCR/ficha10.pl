%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% SIST. REPR. CONHECIMENTO E RACIOCINIO - MiEI/3

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Programacao em logica 
% Grafos Pesados(Ficha 10)

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% SICStus PROLOG: Declaracoes iniciais

:- set_prolog_flag( discontiguous_warnings,off ).
:- set_prolog_flag( single_var_warnings,off ).
:- set_prolog_flag( unknown,fail ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -

g( grafo([madrid, cordoba, sevilla, jaen, granada, huelva, cadiz],
  [aresta(huelva, sevilla, a49, 94),
   aresta(sevilla, cadiz,ap4, 125),
   aresta(sevilla, granada, a92, 256),
   aresta(granada, jaen,a44, 97),
   aresta(sevilla, cordoba, a4, 138),
   aresta(jaen,madrid, a4, 335),
   aresta(cordoba, madrid, a4, 400)]
 )).