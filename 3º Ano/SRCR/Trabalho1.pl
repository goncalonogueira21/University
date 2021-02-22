%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% SIST. REPR. CONHECIMENTO E RACIOCINIO - MiEI/3
% => a86617 Gonçalo Nogueira
% => Carlos Afonso
% => Joao Pedro
% => Pedro Lima
% => Joao Gomes

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% SICStus PROLOG: Declaracoes iniciais

:- set_prolog_flag( discontiguous_warnings,off ).
:- set_prolog_flag( single_var_warnings,off ).
:- set_prolog_flag( unknown,fail ).


%-----------------------------------------------------------------------------
% SICStus PROLOG: definicoes iniciais

:- op( 900, xfy,'::' ).
:- dynamic adjudicante/4.
:- dynamic adjudicataria/4.
:- dynamic contrato/9.
:- dynamic incNIF/1.
:- dynamic incMorada/1.
:- dynamic incValor/1.
:- dynamic incPrazo/1.
:- dynamic imprecisoCusto/3.
:- dynamic nuloInterditoVal/1.
% ----------------------------- CONHECIMENTO POSITIVO -------------------------------- %


% adjudicante: #IdAd, Nome, Nif, Morada ↝{𝕍,𝔽,𝔻}
adjudicante(1, Municipio_de_Braga, 506901173, 'Braga').
adjudicante(2, Teatro_Circo_de_Braga, 500463964, 'Braga').
adjudicante(3, Universidade_do_Minho, 502011378, 'Braga').
adjudicante(4, Centro_Hospitalar_do_Alto_Ave, 508080827, 'Guimarães').
adjudicante(5, Tribunal_Constitucional, 600014193, 'Lisboa').
adjudicante(7, Direcao_Geral_da_Saúde, 600037100, 'Lisboa').
adjudicante(8, Universidade_do_Porto,  501413197, 'Porto').
adjudicante(9, Instituto_Nacional_de_Estatistica, 502237490, 'Lisboa').
adjudicante(10, Municipio_de_Fafe, 506841561, 'Fafe').


% adjudicataria: #IdAda, Nome, Nif, Morada↝{𝕍,𝔽,𝔻}
adjudicataria(1, Soserfis_Contabilidade_Fiscalidade_Gestao_Empresarial_Lda, 502021209, 'Braga').
adjudicataria(2, Bragaconta_Gestao_Empresarial_Lda, 509689930, 'Braga'). 
adjudicataria(3, Fafware_Informatica_Unipessoal_Lda, 509861415, 'Fafe'). 
adjudicataria(4, Sempreluz_Canalizacoes_E_Electricidade_Lda, 500313628, 'Coimbra'). 
adjudicataria(5, Pausa_Simpatica_Lda, 514226854, 'Matosinhos'). 
adjudicataria(6, Enigmalecrim_Lda, 515912794, 'Faro'). 
adjudicataria(7, Atrevomeasorte_Lda, 513899545, 'Braga'). 
adjudicataria(8, Everything_Is_New_Lda, 507903480, 'Lisboa'). 
adjudicataria(9, Diligente_Plano_Unipessoal_Lda, 515785113, 'Aveiro'). 
adjudicataria(10, Faftir_Transportes_Lda, 505404737, 'Fafe'). 



%contrato: #IdAd, #IdAda, TipoDeContrato, TipoDeProcedimento, Descrição, Valor, Prazo, Local, Data↝{𝕍,𝔽,𝔻}
contrato(1,2, 'Aquisição de serviços', 'Consulta Previa', 'Consultoria', 20000, 100, 'Braga', (24,3,2020)).
contrato(3,1, 'Aquisição de serviços', 'Ajuste Direto', 'Assessoria jurídica', 1999, 90, 'Braga', (30,3,2020)).
contrato(10,10, 'Aquisição de serviços', 'Concurso Publico', 'Transporte de mercadoria', 1500, 60, 'Fafe', (24,4,2020)).
contrato(4,3, 'Aquisição de bens', 'Ajuste direto', 'Compra de material informatico', 4000, 30, 'Guimarães', (21,2,2020)).


% ------------------------- CONHECIMENTO NEGATIVO ---------------------------- %

% nao pode ser adjudicante se for adjudicataria
% adjudicante : N -> {V,F,D}
-adjudicante(_, Nome, Nif, Morada) :- adjudicataria(ID, Nome, Nif, Morada).



% adjudicataria : N -> {V,F,D}
-adjudicataria(_, Nome, Nif, Morada) :- adjudicante(ID, Nome, Nif, Morada).


% É falsa a informação de que certos adjudicantes/adjudicatarias tenham um contrato.
-adjudicante(11, Municipio_de_Guimaraes, 505948605 , 'Guimarães').
-adjudicante(12, Universidade_de_Lisboa, 510739024 , 'Lisboa').
-adjudicante(13, Universidade_de_Aveiro, 501461108 , 'Aveiro').


-adjudicataria(11, Kyaia_Solucoes_Informaticas_Lda, 509934870, 'Guimarães').
-adjudicataria(12, Ipj_Texteis_Lda, 502752394, 'Braga').
-adjudicataria(13, Convenient_Flavour_Lda, 514418230, 'Braga').


%nao podem existir contratos neste dia por ser feriado.
-contrato(_, _, _, _, _, _, _, _, (1,1,2020)).


% ------------------------ CONHECIMENTO IMPERFEITO --------------------------- %

% --------- CONHECIMENTO INCERTO

% Adoção do pressuposto do domínio fechado -> adjudicante
-adjudicante(IdAd, Nome, NIF, Morada) :- nao(adjudicante(IdAd, Nome, NIF, Morada)),
                                         nao(excecao(adjudicante(IdAd, Nome, NIF, Morada))).


% Deu entrada uma Entidade adjudicante com nif desconhecido
adjudicante(14, Municipio de Bragança, incNIF1, 'Bragança').
excecao(adjudicante(IdAd, Nome, NIF, Morada)) :- adjudicante(IdAd, Nome, incNIF1, Morada).
incNIF(incNIF1).

% Deu entrada uma Entidade adjudicante com morada desconhecida
adjudicante(15, Instituto do Emprego e da Formação Profissional, I. P., 501442600, incMorada1).
excecao(adjudicante(IdAd, Nome, NIF, Morada)) :- adjudicante(IdAd, Nome, NIF, incMorada1).
incMorada(incMorada1).


% Adoção do pressuposto do domínio fechado -> adjudicatária
-adjudicatária(IdAda, Nome, NIF, Morada) :- nao(adjudicatária(IdAda, Nome, NIF, Morada)),
                                            nao(excecao(adjudicatária(IdAda, Nome, NIF, Morada))).

% Deu entrada uma Entidade adjudicatária com nif desconhecido
adjudicatária(14, Topgim Material Desportivo e Lazer, Lda., incNIF1, 'Sintra').
excecao(adjudicatária(IdAda, Nome, NIF, Morada)) :- adjudicatária(IdAda, Nome, incNIF1, Morada).
incNIF(incNIF1).

% Deu entrada uma Entidade adjudicatária com morada desconhecida
adjudicatária(15, Otis elevadores, Lda., 500069824, incMorada1).
excecao(adjudicatária(IdAd, Nome, NIF, Morada)) :- adjudicatária(IdAd, Nome, NIF, incMorada1).
incMorada(incMorada1).

% Adoção do pressuposto do dominio fechado -> contrato
-contrato(IdAd, IdAda, TipoDeContrato, TipoDeProcedimento, Descricao, Valor, Prazo, Local, Data) :- nao(contrato(IdAd, IdAda, TipoDeContrato, TipoDeProcedimento, Descricao, Valor, Prazo, Local, Data)),
                                                                                                    nao(excecao(contrato(IdAd, IdAda, TipoDeContrato, TipoDeProcedimento, Descricao, Valor, Prazo, Local, Data))).

% O contrato tem um valor desconhecido
contrato(1, 6, 'Aquisição de serviços', 'Consulta Prévia', 'Assessoria jurídica', incValor1, '300 dias', 'Braga',(11-02-2020)).
excecao(contrato(IdAd, IdAda, TipoDeContrato, TipoDeProcedimento, Descricao, Valor, Prazo, Local, Data)) :- contrato(IdAd, IdAda, TipoDeContrato, TipoDeProcedimento, Descricao, incValor1, Prazo, Local, Data)
incValor(incValor1).

% O contrato tem um prazo desconhecido
contrato(10, 3, 'Aquisição de serviços', 'Ajuste Direto Regime Geral', 'Assessoria jurídica', 13 599, incPrazo1, 'Fafe', (02-02-2020)).
excecao(contrato(IdAd, IdAda, TipoDeContrato, TipoDeProcedimento, Descricao, Valor, Prazo, Local, Data)) :- contrato(IdAd, IdAda, TipoDeContrato, TipoDeProcedimento, Descricao, Valor, incPrazo1, Local, Data)
incPrazo(incPrazo1).

% --------- CONHECIMENTO IMPRECISO

% O valor do contrato X encontra-se entre 5000 e 6000 euros
excecao(contrato(3, 9, 'Aquisição de serviços', 'Ajuste Direto Regime Geral', 'Assessoria jurídica', X, '500 dias', 'Braga', (21-01-2020))) :- X > 5000, X < 6000.
imprecisoCusto(3,9,(21-01-2020)).


% --------- CONHECIMENTO INTERDITO




% Por questões de confidencialidade não se pode saber:
%         - valor
nuloInterditoVal(nuloValor1).
excecao(contrato(IdAd, IdAda, TipoDeContrato, TipoDeProcedimento, Descricao, Valor, Prazo, Local, Data)) :- contrato(IdAd, IdAda, TipoDeContrato, TipoDeProcedimento, Descricao, nuloValor1, Prazo, Local, Data). % Não esquecer de adicionar invariante!
contrato(16, 16, 'Empreitadas de obras públicas', 'Ajuste Direto Regime Geral', 'Reposição do pavimento de valas da rede de água na EN 207-1, em Barrosas St.º Estêvão', nuloValor1, '20 dias', 'Lousada', (15-03-2020)).
+contrato(Id,Id2,TC,TP,D,V,P,L,DT) :: (findall( (Id,Id2,TC,TP,D,V,P,L,DT), (contrato(16, 16, 'Empreitadas de obras públicas', 'Ajuste Direto Regime Geral', 'Reposição do pavimento de valas da rede de água na EN 207-1, em Barrosas St.º Estêvão', Va, '20 dias', 'Lousada', (15-03-2020)),nao(nuloInterditoIda(Va))), S),
                            comprimento(S,N),
                            N==0).


% ------------------------- Construção do Caso Prático ---------------------- 
%
% Registar adjudicantes, adjudicatarias e contratos

% Invariante Estrutural: Não podem existir adjudicantes repetidos (com o mesmo ID).
+adjudicante( IdAd, _, _, _) :: ( integer(IdAd),
                               findall(IdAd, adjudicante(IdAd, Nome, Nif, Morada), S),
                               comprimento( S, N ), N == 1 ).

% Invariante Referencial: Nif valido
+adjudicante( _, _, Nif, _) :: ( integer(Nif),
                                 Nif >= 100000000, Nif =< 999999999).

% Invariante Estrutural: Não podem existir adjudicatarias repetidas (com o mesmo ID).
+adjudicataria( IdAda, _, _, _) :: ( integer(IdAda),
                               findall(IdAda, adjudicataria(IdAda, Nome, Nif, Morada), S),
                               comprimento( S, N ), N == 1 ).


% Invariante Referencial: Nif valido
+adjudicataria( _, _, Nif, _) :: ( integer(Nif),
                                 Nif >= 100000000, Nif =< 999999999).



% Invariante Referencial: Só se pode adicionar um contrato se o adjudicante e a adjudicataria existir.
+contrato(IdAd, IdAda, _, _, _, _, _, _, _) :: ( findall( IdAd, adjudicante(IdAd, Nome, Nif, Morada), L), comprimento(L,S), S == 1,
                                        findall( IdAda, adjudicataria(IdAda, Nome, Nif, Morada), X), comprimento(X,C), C == 1 )


% Invariante Referencial: Só se pode adicionar um contrato se o adjudicante e a adjudicataria existir.
% Nao sei como fazer para ver se é ajuste direto ou nao



%
% ------------------------------------------------------------------------ %
%
%                      Remover adjudicantes, adjudicatarias e contratos


% Invariante Estrutural: Só se pode eliminar se existir o ID existir na Base de Conhecimento.
-adjudicante( IdAd, _, _, _) :: ( integer(IdAd),
                               findall(IdAd, adjudicante(IdAd, Nome, Nif, Morada), S),
                               comprimento( S, N ), N == 0 ).

% Invariante Referencial: Só se pode eliminar adjudicante se não existirem contratos com esta entidade.
-adjudicante( IdAd, _, _, _) :: ( findall( IdAd, contrato(IdAd, IdAda, TipoDeContrato, TipoDeProcedimento, Descricao, Valor, Prazo, Local, Data), L),
                                 comprimento( L, N),
                                 N == 0 ).

% Invariante Estrutural: Só se pode eliminar se o ID existir na Base de Conhecimento.
-adjudicataria( IdAda, _, _, _) :: ( integer(IdAda),
                               findall(IdAda, adjudicataria(IdAda, Nome, Nif, Morada), S),
                               comprimento( S, N ), N == 0 ).

% Invariante Referencial: Só se pode eliminar adjudicatarias se não existirem contratos com esta entidade.
-adjudicataria( IdAda, _, _, _) :: ( findall( IdAda, contrato(IdAd, IdAda, TipoDeContrato, TipoDeProcedimento, Descricao, Valor, Prazo, Local, Data), L),
                                 comprimento( L, N),
                                 N == 0 ).









% Não se pode adicionar um excecao se for para conhecimento perfeito.
+excecao(T) :: nao(T).

% -------------------------- Predicados Auxiliares -------------------------- %

% Extensão do Predicado comprimento: ListaElem, Comp -> {V,F}
comprimento([],0).
comprimento([X|L], C) :- comprimento(L, N), C is 1+N.

% Extensão do predicado sum: X, R -> {V, F}, faz o somatório de uma lista.
sum([], 0).
sum([X|L], R) :- sum(L, R1), R is X + R1.

% Extensão do predicado apagaReps: L, R -> {V, F}
% Apaga diversos elementos repetidos numa lista.
apagaReps([], []).
apagaReps([H|T], [H|L]) :- apagaT(H, T, X),
                           apagaReps(X, L).

% Extensão do predicado apagaT: X, L, R -> {V, F}
% Apaga todas as ocorrências repetidas de um elemento numa lista.
apagaT(X, [], []).
apagaT(X,[X|L1],L2) :- apagaT(X,L1,L2).
apagaT(X,[Y|L1],[Y|L2]) :- apagaT(X,L1,L2).

% Extensão do predicado concatenar : L1,L2,R -> {V,F}
concatenar([],L,L).
concatenar([X|L1],L2,[X|L3]) :- concatenar(L1,L2,L3).

% Extensão do predicado concListList: LLs, L -> {V, F}
% Utilizando o predicado auxiliar concatenar, concatena listas dentro de uma lista.
concListList([], []).
concListList([H|T], L) :- concListList(T, L1),
                          concatenar(H, L1, L).

% insercao: T -> {V,F}
insercao(T) :- assert(T).
insercao(T) :- retract(T), !, fail.

% remocao: T -> {V,F}
remocao(T) :- retract(T).
remocao(T) :- assert(T), !, fail.

% teste: L -> {V,F}
teste( [] ).
teste( [I|Is] ) :- I, teste(Is).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Evolução do CONHECIMENTO PERFEITO POSITIVO

% evolucao: T -> {V,F}
evolucao(T) :- findall(I,+T::I,Li),
		       insercao(T),
		       teste(Li).

% involucao: T -> {V,F}
involucao(T) :- T,
                findall(I,-T::I,Li),
                remocao(T),
                teste(Li).


%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Evolução do CONHECIMENTO PERFEITO NEGATIVO
evolucaoNeg(T) :- findall(I,+(-T)::I,Li),
                  teste(Li),
                  assert(-T).

involucaoNeg(T) :- findall(I,+(-T)::I,Li),
                   teste(Li),
                   retract(-T).


%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do meta-predicado demo: Questao,Resposta -> {V,F}
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