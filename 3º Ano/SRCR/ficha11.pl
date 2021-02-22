%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% SIST. REPR. CONHECIMENTO E RACIOCINIO - MiEI/3

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Programacão em logica 
% Resolução de problemas de pesquisa Não Informada (Ficha 11)

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% SICStus PROLOG: Declaracoes iniciais

:- set_prolog_flag( discontiguous_warnings,off ).
:- set_prolog_flag( single_var_warnings,off ).
:- set_prolog_flag( unknown,fail ).

%---------------------------------  dados do problema ---------

% estado inicial
inicial(jarros(0, 0)).

% estados finais
final(jarros(4, _)).
final(jarros(_, 4)).

% transições possíveis transicao: Ei x Op x Ef

transicao(jarros(V1, V2), encher(1), jarros(8, V2)):- V1 < 8.
transicao(jarros(V1, V2), encher(2), jarros(V1, 5)):- V2 < 5.

transicao(jarros(V1, V2), encher(1, 2), jarros(NV1, NV2)):- 
	V1 > 0,
	NV1 is max(V1 - 5 + V2, 0), 
	NV1 < V1, 
	NV2 is V2 + V1 - NV1.
transicao(jarros(V1, V2), encher(2, 1), jarros(NV1, NV2)):- 
	V2 > 0,
	NV2 is max(V2 - 8 + V1, 0), 
	NV2 < V2, 
	NV1 is V1 + V2 - NV2.

transicao(jarros(V1, V2), vazio(1), jarros(0, V2)):- V1 > 0.
transicao(jarros(V1, V2), vazio(2), jarros(V1, 0)):- V2 > 0.

%---------------------------------  d) ---------
resolvedf(Solucao):-
	inicial(InicialEstado),
	resolvedf(InicialEstado, [InicialEstado], Solucao).

resolvedf(Estado, _, []):-
	final(Estado),!.

resolvedf(Estado, Historico, [Move |Solucao]):-
	transicao(Estado, Move, Estado1),
	nao(membro(Estado1, Historico)),
	resolvedf(Estado1, [Estado1|Historico], Solucao).	

%--------------------------------- Comparar d) e e) ---------


todos(L):-findall((S,C), (resolvedf(S), length(S,C)), L).

melhor(S, Custo):- findall((S,C), (resolvedf(S), length(S,C)), L), minimo(L,(S,Custo)).

escrever([]).
escrever([(X,Y)|L]):- write(X), write(' - '), write(Y), nl, escrever(L).

minimo([(P,X)],(P,X)).
minimo([(Px,X)|L],(Py,Y)):- minimo(L,(Py,Y)), X>Y. 
minimo([(Px,X)|L],(Px,X)):- minimo(L,(Py,Y)), X=<Y. 

minimo1([X],X).
minimo1([X|L], Y):- minimo1(L,Y), X>Y. 
minimo1([X|L], X):- minimo1(L,Y), X=<Y. 


%---------------------------------  e) ---------

resolvebf(Solucao):-
	inicial(InicialEstado),
	resolvebf([(InicialEstado, [])|Xs]-Xs, [], Solucao).

resolvebf([(Estado, Vs)|_]-_, _, Rs):-
	final(Estado),!, inverso(Vs, Rs).

resolvebf([(Estado, _)|Xs]-Ys, Historico, Solucao):-
	membro(Estado, Historico),!,
	resolvebf(Xs-Ys, Historico, Solucao).

resolvebf([(Estado, Vs)|Xs]-Ys, Historico, Solucao):-
	setof((Move, Estado1), transicao(Estado, Move, Estado1), Ls),
	atualizar(Ls, Vs, [Estado|Historico], Ys-Zs),
	resolvebf(Xs-Zs, [Estado|Historico], Solucao).


atualizar([], _, _, X-X).
atualizar([(_, Estado)|Ls], Vs, Historico, Xs-Ys):-
	membro(Estado, Historico),!,
	atualizar(Ls, Vs, Historico, Xs-Ys).

atualizar([(Move, Estado)|Ls], Vs, Historico, [(Estado, [Move|Vs])|Xs]-Ys):-
	atualizar(Ls, Vs, Historico, Xs-Ys).



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



resolve_aestrela(Nodo,Goal, Caminho/Custo) :-
	estima(Nodo, Estima),
	aestrela([[Nodo]/0/Estima],Goal, InvCaminho/Custo/_),
	inverso(InvCaminho, Caminho).

aestrela(Caminhos, Goal, Caminho) :-
	obtem_melhor(Caminhos, Caminho),
	Caminho = [Nodo|_]/_/_,Goal.

aestrela(Caminhos, Goal, SolucaoCaminho) :-
	obtem_melhor(Caminhos, MelhorCaminho),
	seleciona(MelhorCaminho, Caminhos, OutrosCaminhos),
	expande_aestrela(MelhorCaminho, ExpCaminhos),
	append(OutrosCaminhos, ExpCaminhos, NovoCaminhos),
        aestrela(NovoCaminhos, Goal, SolucaoCaminho).		


obtem_melhor([Caminho], Caminho) :- !.

obtem_melhor([Caminho1/Custo1/Est1,_/Custo2/Est2|Caminhos], MelhorCaminho) :-
	Custo1 + Est1 =< Custo2 + Est2, !,
	obtem_melhor([Caminho1/Custo1/Est1|Caminhos], MelhorCaminho).
	
obtem_melhor([_|Caminhos], MelhorCaminho) :- 
	obtem_melhor(Caminhos, MelhorCaminho).

expande_aestrela(Caminho, ExpCaminhos) :-
	findall(NovoCaminho, adjacente(Caminho,NovoCaminho), ExpCaminhos).

adjacente([Nodo|Caminho]/Custo/_, [ProxNodo,Nodo|Caminho]/NovoCusto/Est) :-
	distance(Nodo, ProxNodo, PassoCusto),\+ member(ProxNodo, Caminho),
	NovoCusto is Custo + PassoCusto,
	estima(ProxNodo, Est).


resolvedf(Start, Goal, Final):-
	dfs(Start, Goal, [Start], Path),naoPath(Goal,Path,[],Final).

dfs(Goal, Goal,, [Goal|_], [_]).

dfs(Estado, Goal, Historico, [Ligacao |Path]):-
	connected(Estado,Ligacao),
	nao(membro(Ligacao, Historico)),
	dfs(Ligacao, Goal,[Ligacao|Historico], Path).	


resolvedf(Start, Goal, Final):-
	dfs(Start, [Start], Path),naoPath(Goal,Path,[],Final).

dfs(Goal, [Goal|_], [_]).

dfs(Estado, Historico, [Ligacao |Path]):-
	connected(Estado,Ligacao),
	nao(membro(Ligacao, Historico)),
	dfs(Ligacao, [Ligacao|Historico], Path).



resolvedf(Start, Goal) :-
	empty_stack(Empty_been_list),
	stack(Start, Empty_been_list, Been_list),
	path(Start, Goal, Been_list).

path(Goal, Goal, Been_list) :-
	reverse_print_stack(Been_list).
	
path(State, Goal, Been_list) :-
	connected(State,Next),
	stack(Next, Been_list, New_been_list),
	path(Next, Goal, New_been_list), !.



-- 50 moradas
INSERT INTO morada 
		(`Rua`,`Localidade`,`Código-Postal`)
	VALUES 
        ("Avenida de Melo","9311","Faro"),
        ("Travessa Wilson Lopes, 3, 6º Esq.","4149","Oliveira de Azeméis"),
        ("Av. St. Victória Gomes, nº 41","7034","Sacavém"),
        ("Travessa São. Gustavo","4409-932", "Pinhel"),
        ("Travessa Esteves, 8","7390-152", "Porto Santo"),
        ("Avenida São. Vicente, 895", "3905-812", "Santa Comba Dão"),
        ("R. de Machado, 1, 3º Eq.", "5044-155", "São João da Madeira"), 
        ("R. de Maia, 9","5605-252", "Caldas da Rainha"),
        ("Largo St. Francisca Antunes, 23", "4515-822", "Vila Real de Santo António"),
        ("R. de Correia, nº 4, 9º Esq.","1485","Felgueiras"),
        ("Rua St. Luís Leite, 1","8244","Gondomar"),
        ("Av. de Guerreiro, 6, 49º Eq.", "4301" ,"Guimarães"),
        ("Largo Pinheiro, nº 35, 75º Esq.","6229-615" ,"Esposende"),
        ("Avenida Fabiana Sousa","8281" ,"Braga"),
        ("Avenida de Amorim, 6, 82º Eq.","3259" ,"Mealhada"),
        ("R. de Anjos, 70, 14º Eq.","1369-950" ,"Moura"),
        ("Largo Miranda, nº 4, 2º Dir.","6510" ,"Porto Santo"),
        ("Largo Adriana Cardoso, nº 764, 2º Dr.","7284-266" ,"Agualva-Cacém"),
        ("Largo São. Cláudia","4720" ,"Queluz"),
        ("Av. Bruno Figueiredo, nº 476","2375" ,"Odivelas"),
        ("Avenida São. Marcos","8711-200" ,"Vila do Conde"),
        ("Avenida Kyara Marques, 1, 3º Dir.","5184" ,"Póvoa de Varzim"),
        ("Rua de Freitas, nº 3, 6º Esq.","2284" ,"Valbom"),
        ("Av. de Torres, 3","8351-260" ,"Oliveira do Hospital"),
        ("Rua Henrique Magalhães, nº 47", "7449" ,"Felgueiras"),
        ("Largo São. Vicente, nº 64, 5º Eq.","7455","Anadia"),
        ("R. de Lopes, nº 22, Bl. 2","8069","Viana do Castelo"),
        ("Av. Henriques","1014-200","Porto"),
        ("Av. St. Yasmin Nascimento","7974","Alcobaça"),
        ("Avenida Júlia Santos, 71","4791-961","Valongo"),
        ("Largo de Nunes, 54","4950","Valpaços"),
        ("Largo Branco","9010-937","Agualva-Cacém"),
        ("Avenida Rui Martins, 1, 6º Dr.","4435","Rio Maior"),
        ("Av. Francisco Carvalho, 5, Bloco 7","3779-433","Almada"),
        ("Largo São. Alícia, nº 7","2640","Vendas Novas"),
        ("Travessa de Soares, nº 646, 46º Eq.","1895-692","Vila Real"),
        ("Largo Henriques, 2","7939-870","Covilhã"),
        ("Largo Sá, nº 78","4301","Gondomar"),
        ("Travessa Clara Loureiro, 32","8494-504","Évora"),
        ("Largo São. Isabela","2604-421","Mirandela"),
        ("Av. Mariana Pinho, 85","2091-309","Esposende"),
        ("R. de Barbosa","5125","Funchal"),
        ("Travessa de Lourenço, nº 328","4370","Leiria"),
        ("Avenida Jesus","5824-001","Queluz"),
        ("Av. São. Kyara","3475-353","Loulé"),
        ("Largo São. Vera, nº 1","2485","Vila Nova de Foz Côa"),
        ("Av. São. Sofia","8354-434","Angra do Heroísmo"),
        ("Travessa St. Emanuel Gomes, 2, Bloco 8","7914","Marinha Grande"),
        ("Av. Batista","1575","Entroncamento"),
        ("Avenida São. Telmo, 4","6714","Moura");

-- 10 carros
INSERT INTO carro
		(`Matricula`,`Marca`,`Modelo`,`Ano`)
	VALUES
        ('XA-91-BE','Hyundai', 'Tiburon', 2006),
        ('PO-25-GT','Dodge', 'Durango', 1998),
        ('KJ-41-SD','Mitsubishi', 'Galant', 1995),
        ('NB-70-GH','Isuzu', 'Hombre Space', 1997),
        ('VP-62-CQ','Acura', 'RL', 2007),
        ('DR-84-HN','GMC', 'Sierra 3500', 2002),
        ('TH-67-FR','GMC', 'Yukon XL 2500', 2011),
        ('JI-50-NK','Mazda', 'MX-6', 1989),
        ('QA-18-QL','Pontiac', 'Montana', 2004),
        ('CF-49-LA','Maybach', 'Landaulet', 2010);

-- 10 funcionários
INSERT INTO funcionario
		(`Nome`,`Email`,`Nrº_Telemóvel`,`Nrº_CC`,`Morada_idMorada`)
	VALUES 
        ('Cross Hyder', 'chyder0@eventbrite.com', '963718837', '14400548-5-BD3', 32),
        ('Glen Toop', 'gtoop2@examiner.com', '440408118', '22211126-6-DA7', 15),
        ('Rodrique Stanlake', 'rstanlake1@google.es', '130950123', '69452683-9-JA7', 18),
        ('Jsandye Matthisson', 'jmatthisson3@umich.edu', '96980766', '20506459-9-AK4', 23),
        ('Wolfy St. Leger', 'wst4@163.com', '930838196', '65623610-4-ZO9', 25),
        ('Ronnica Syder', 'rsyder5@aboutads.info', '275542291', '16678492-8-MM4', 12),
        ('Theodosia MacBrearty', 'tmacbrearty6@springer.com', '383861733', '25603015-9-PY8', 24),
        ('Hasheem Dorsey', 'hdorsey7@last.fm', '619977986', '23256551-7-AJ9', 49),
        ('Lane Darrel', 'ldarrel8@alexa.com', '771771880', '93629435-6-NP6', 41),
        ('Geneva McPeice', 'gmcpeice9@macromedia.com', '290321967', '91624409-3-YF7', 17);


-- 5 instrutores
INSERT INTO instrutor
        (`Nome`,`Email`,`Nrº_Telemóvel`,`Nrº_CC`,`Morada_idMorada`)
    VALUES
        ('Conan Rippin', 'crippin0@gov.uk', '451768552', '03133196-2-FD9', 10),
        ('Erwin Broadley', 'ebroadley1@cargocollective.com', '721519945', '23140007-0-QZ9', 29),
        ('Yule MacSorley', 'ymacsorley2@wiley.com', '778241087', '07950159-0-XD8', 11),
        ('Thayne Pollastrone', 'tpollastrone3@fema.gov', '257380119', '51117930-9-IG2', 40),
        ('Kitty Folli', 'kfolli4@twitter.com', '115503587', '75463239-4-KR1', 18);

INSERT INTO aluno
        (`Nome`,`Email`,`Nrº_Telemóvel`,`Nrº_CC`,`NIF`,`Pagamento`,`Morada_idMorada`)
    VALUES ('Micky Gogay', 'mgogay0@nytimes.com', '923567246', '17080320-7-MO8', '647349835', 'S', 1),
        ('Cristian Collihole', 'ccollihole1@umich.edu', '441262229', '22983798-4-TB2', '988694638', 'S', 2),
        ('D''arcy Strettle', 'dstrettle2@amazon.co.uk', '482170658', '46063667-7-NU0', '721683164', 'S', 3),
        ('Kitti Stillmann', 'kstillmann3@aol.com', '906367294', '13227519-1-VP1', '659056684', 'N', 4),
        ('Raul Meijer', 'rmeijer4@smh.com.au', '609595992', '61996042-4-HP9', '543093915', 'N', 5),
        ('Pablo Rocco', 'procco5@wikimedia.org', '607849268', '56017343-4-RL3', '076576641', 'S', 6),
        ('Richy Haggith', 'rhaggith6@businessweek.com', '603285899', '15318326-1-OF9', '607520499', 'S', 7),
        ('Ab Weekly', 'aweekly7@jimdo.com', '849587209', '24900293-1-CZ2', '824639682', 'S', 8),
        ('Dolorita O''Dowd', 'dodowd8@nhs.uk', '133697228', '79593895-3-QI1', '324054688', 'N', 9),
        ('Pacorro Drewry', 'pdrewry9@columbia.edu', '156928705', '16034235-5-KS0', '170816471', 'S', 10),
        ('Gregoire Soloway', 'gsolowaya@weather.com', '333251695', '91654285-7-SS4', '891789845', 'S', 11),
        ('Hymie Zini', 'hzinib@icq.com', '222633669', '34043922-0-GW3', '941610268', 'S', 12),
        ('Randie Tiley', 'rtileyc@go.com', '794549180', '22488319-4-JK4', '824871194', 'S', 13),
        ('Fawn Hearnes', 'fhearnesd@live.com', '753878187', '35423409-7-KO6', '796121852', 'N', 14),
        ('Hendrika Drysdale', 'hdrysdalee@answers.com', '469805112', '84526364-2-HB9', '666736491', 'N', 15),
        ('Hugo Van der Spohr', 'hvanf@comsenz.com', '743984596', '93955649-2-YU8', '456258004', 'N', 16),
        ('Jourdain Arndell', 'jarndellg@livejournal.com', '654375783', '80108864-6-BH0', '331795997', 'S', 17),
        ('Darwin McClintock', 'dmcclintockh@seesaa.net', '123184378', '05740173-3-FR6', '593635176', 'S', 18),
        ('Milli Winscomb', 'mwinscombi@java.com', '972782698', '14519355-3-OM2', '647199524', 'S', 19),
        ('Keslie Fransemai', 'kfransemaij@loc.gov', '252758108', '27540147-4-ID8', '061418250', 'S', 20),
        ('Jere Godber', 'jgodberk@dedecms.com', '567194621', '57897843-4-VF4', '757779161', 'S', 21),
        ('Mamie Moreland', 'mmorelandl@google.cn', '228538364', '61594333-2-ZQ1', '984477183', 'S', 22),
        ('Margery Costar', 'mcostarm@time.com', '835582870', '67917028-6-EQ9', '450578971', 'S', 23),
        ('Godwin Rutt', 'gruttn@reddit.com', '438685890', '04120752-0-YV3', '602668203', 'S', 24),
        ('Afton Mound', 'amoundo@google.es', '354978614', '57261754-8-MR3', '193618453', 'S', 25),
        ('Clerissa Screeton', 'cscreetonp@sphinn.com', '881368022', '87830417-9-BM6', '435632257', 'N', 26),
        ('Olga Razoux', 'orazouxq@msn.com', '282778987', '88327395-2-XJ9', '231391897', 'S', 27),
        ('Denise Del Dello', 'ddelr@etsy.com', '408430883', '77790261-3-QV2', '671128373', 'S', 28),
        ('Ginni Glavin', 'gglavins@godaddy.com', '470983821', '95424396-0-VX9', '099658635', 'S', 29),
        ('Wilfrid Tripett', 'wtripettt@cloudflare.com', '264345406', '72667749-4-MA1', '781918912', 'S', 30),
        ('Rudyard Tumber', 'rtumberu@vk.com', '679909617', '61707615-1-EF3', '163240286', 'N', 31),
        ('Albertina Divill', 'adivillv@addthis.com', '859408360', '91375042-2-ND2', '969249097', 'N', 32),
        ('Adella Zmitruk', 'azmitrukw@webs.com', '566581282', '79880857-7-RV4', '994233230', 'N', 33),
        ('Hartley Grime', 'hgrimex@salon.com', '743740075', '92620654-7-WJ7', '962787146', 'N', 34),
        ('Tannie Bazoche', 'tbazochey@senate.gov', '409172255', '14572184-1-VU9', '867530337', 'S', 35),
        ('Clarabelle Bigg', 'cbiggz@businessinsider.com', '718170678', '79515346-7-BF9', '990292435', 'S', 36),
        ('Horst Aizikovitz', 'haizikovitz10@amazon.de', '898176055', '43564504-3-OY8', '462208983', 'N', 37),
        ('Genia Belcham', 'gbelcham11@uiuc.edu', '732100303', '42074894-0-PZ1', '574161541', 'S', 38),
        ('Jorey Dienes', 'jdienes12@statcounter.com', '279791869', '20272942-4-YO0', '611336892', 'S', 39),
        ('Yovonnda Chander', 'ychander13@wiley.com', '872614232', '12541352-4-UW2', '246964104', 'S', 40),
        ('Dodie MacDearmont', 'dmacdearmont14@sakura.ne.jp', '903606524', '32466849-7-LJ8', '730433608', 'S', 41),
        ('Richard MacIlriach', 'rmacilriach15@comsenz.com', '534626727', '37375101-8-GO7', '966951481', 'S', 42),
        ('Lettie Forgie', 'lforgie16@time.com', '462930547', '56874755-0-SN1', '437866412', 'S', 43),
        ('Toby Cerman', 'tcerman17@multiply.com', '966578796', '05300656-4-SS2', '516985272', 'S', 44),
        ('Torre Vatini', 'tvatini18@bloglines.com', '707632157', '65103115-9-KE6', '783045762', 'S', 45),
        ('Agna Beinke', 'abeinke19@privacy.gov.au', '172352961', '91887944-5-FK1', '314303659', 'S', 46),
        ('Dory Mohan', 'dmohan1a@ycombinator.com', '414879897', '07999972-2-TL4', '033467131', 'N', 47),
        ('Lidia Scroggie', 'lscroggie1b@addthis.com', '832484363', '21438869-6-JO1', '977423141', 'S', 48),
        ('Nealon Eburne', 'neburne1c@google.cn', '921673056', '33361035-7-RP7', '915113226', 'S', 49),
        ('Derby Giorgio', 'dgiorgio1d@yale.edu', '836529930', '65849836-4-BW0', '884779635', 'S', 50);


INSERT INTO aula
		(`Data`,`Hora`,`Estado`,`Instrutor_Id`)
     VALUES ("2020-12-05","10:00:00","L",1), -- DIA 1
			("2020-12-05","10:00:00","L",2),
            ("2020-12-05","10:00:00","L",4),               
            ("2020-12-05","11:00:00","L",2),   
            ("2020-12-05","11:00:00","L",4),       
            ("2020-12-05","15:00:00","L",1),                    
            ("2020-12-05","15:00:00","L",5),                 
            ("2020-12-05","16:00:00","L",2),                 
            ("2020-12-05","16:00:00","L",4),      
            ("2020-12-05","17:00:00","L",3),   
            ("2020-12-06","10:00:00","L",1), -- DIA 2
            ("2020-12-06","10:00:00","L",3),   
            ("2020-12-06","10:00:00","L",5),              
            ("2020-12-06","11:00:00","L",4),   
            ("2020-12-06","15:00:00","L",1),   
            ("2020-12-06","15:00:00","L",3),             
            ("2020-12-06","16:00:00","L",3),   
            ("2020-12-06","16:00:00","L",5),           
            ("2020-12-06","17:00:00","L",2),   
            ("2020-12-06","17:00:00","L",4),   
            ("2020-12-07","10:00:00","L",1), -- DIA 3
			("2020-12-07","10:00:00","L",2),              
            ("2020-12-07","10:00:00","L",5),   
            ("2020-12-07","11:00:00","L",3),    
            ("2020-12-07","11:00:00","L",5),     
            ("2020-12-07","15:00:00","L",2),      
            ("2020-12-07","15:00:00","L",5),         
            ("2020-12-07","16:00:00","L",2),     
            ("2020-12-07","16:00:00","L",4),   
            ("2020-12-07","17:00:00","L",1),  
            ("2020-12-07","17:00:00","L",3),     
            ("2020-12-07","17:00:00","L",5),
            ("2020-12-08","10:00:00","L",1), -- DIA 4
			("2020-12-08","10:00:00","L",2), 
            ("2020-12-08","10:00:00","L",4),    
            ("2020-12-08","11:00:00","L",1),   
            ("2020-12-08","11:00:00","L",3),    
            ("2020-12-08","11:00:00","L",5),     
            ("2020-12-08","15:00:00","L",2),   
            ("2020-12-08","15:00:00","L",4),   
            ("2020-12-08","15:00:00","L",5),   
            ("2020-12-08","16:00:00","L",1),   
            ("2020-12-08","16:00:00","L",3),   
            ("2020-12-08","16:00:00","L",5),   
            ("2020-12-08","17:00:00","L",1),  
            ("2020-12-08","17:00:00","L",3),    
            ("2020-12-08","17:00:00","L",5),
            ("2020-12-09","10:00:00","L",1), -- DIA 5
			("2020-12-09","10:00:00","L",2),
            ("2020-12-09","10:00:00","L",4),   
            ("2020-12-09","11:00:00","L",1),    
            ("2020-12-09","11:00:00","L",3),   
            ("2020-12-09","11:00:00","L",5),   
            ("2020-12-09","15:00:00","L",1),   
            ("2020-12-09","15:00:00","L",3),   
            ("2020-12-09","15:00:00","L",4),   
            ("2020-12-09","16:00:00","L",1),   
            ("2020-12-09","16:00:00","L",2),   
            ("2020-12-09","16:00:00","L",4),   
            ("2020-12-09","16:00:00","L",5),   
            ("2020-12-09","17:00:00","L",2),   
            ("2020-12-09","17:00:00","L",3),   
            ("2020-12-09","17:00:00","L",5),
            ("2020-12-10","10:00:00","L",1), -- DIA 6
			("2020-12-10","10:00:00","L",2), 
            ("2020-12-10","10:00:00","L",5),     
            ("2020-12-10","11:00:00","L",2),   
            ("2020-12-10","15:00:00","L",1),   
            ("2020-12-10","15:00:00","L",3),   
            ("2020-12-10","15:00:00","L",5),    
            ("2020-12-10","16:00:00","L",2),    
            ("2020-12-10","16:00:00","L",4),   
            ("2020-12-10","16:00:00","L",5),   
            ("2020-12-10","17:00:00","L",2),   
            ("2020-12-10","17:00:00","L",3),   
            ("2020-12-10","17:00:00","L",5),
            ("2020-12-11","10:00:00","L",1), -- DIA 7
			("2020-12-11","10:00:00","L",2),
            ("2020-12-11","10:00:00","L",3),   
            ("2020-12-11","10:00:00","L",4),   
            ("2020-12-11","10:00:00","L",5),   
            ("2020-12-11","11:00:00","L",1),   
            ("2020-12-11","11:00:00","L",2),   
            ("2020-12-11","11:00:00","L",3),   
            ("2020-12-11","11:00:00","L",4),   
            ("2020-12-11","11:00:00","L",5),   
            ("2020-12-11","15:00:00","L",1),   
            ("2020-12-11","15:00:00","L",2),   
            ("2020-12-11","15:00:00","L",3),   
            ("2020-12-11","15:00:00","L",4),   
            ("2020-12-11","15:00:00","L",5),   
            ("2020-12-11","16:00:00","L",1),   
            ("2020-12-11","16:00:00","L",2),   
            ("2020-12-11","16:00:00","L",3),   
            ("2020-12-11","16:00:00","L",4),   
            ("2020-12-11","16:00:00","L",5),   
            ("2020-12-11","17:00:00","L",1), 
            ("2020-12-11","17:00:00","L",2),   
            ("2020-12-11","17:00:00","L",3),   
            ("2020-12-11","17:00:00","L",4),   
            ("2020-12-11","17:00:00","L",5); 
            
            
            
   
            
INSERT INTO aula 
		(`Data`,`Hora`,`Estado`,`Instrutor_Id`,`Carro_Matricula`,`Funcionario_id`,`Aluno_id`)
	VALUES ("2020-12-05","10:00:00","M",3,"XA-91-BE",2,14),
("2020-12-05","10:00:00","M",5,"DR-84-HN",1,15),
("2020-12-05","11:00:00","M",1,"QA-18-QL",2,11),
("2020-12-05","11:00:00","M",3,"KJ-41-SD",4,22),
("2020-12-05","11:00:00","M",5,"TH-67-FR",5,21),
("2020-12-05","15:00:00","M",2,"NB-70-GH",2,25),
("2020-12-05","15:00:00","M",3,"VP-62-CQ",1,17),
("2020-12-05","15:00:00","M",4,"CF-49-LA",4,2), 
("2020-12-05","16:00:00","M",1,"DR-84-HN",2,1),
("2020-12-05","16:00:00","M",3,"KJ-41-SD",1,5), 
("2020-12-05","16:00:00","M",5,"PO-25-GT",5,3),
("2020-12-05","17:00:00","M",1,"XA-91-BE",4,8),
("2020-12-05","17:00:00","M",2,"KJ-41-SD",2,6),
("2020-12-05","17:00:00","M",4,"NB-70-GH",2,24),
("2020-12-05","17:00:00","M",5,"PO-25-GT",1,30),
("2020-12-06","10:00:00","M",2,"CF-49-LA",4,27),
("2020-12-06","10:00:00","M",4,"KJ-41-SD",5,29),
("2020-12-06","11:00:00","M",1,"NB-70-GH",1,41),
("2020-12-06","11:00:00","M",2,"PO-25-GT",2,45),
("2020-12-06","11:00:00","M",3,"TH-67-FR",5,46),
("2020-12-06","11:00:00","M",5,"DR-84-HN",3,20),
("2020-12-06","15:00:00","M",2,"JI-50-NK",1,10),
("2020-12-06","15:00:00","M",4,"PO-25-GT",1,6),
("2020-12-06","15:00:00","M",5,"QA-18-QL",4,8),
("2020-12-06","16:00:00","M",1,"XA-91-BE",2,14),
("2020-12-06","16:00:00","M",2,"PO-25-GT",5,25),
("2020-12-06","16:00:00","M",4,"CF-49-LA",2,31),
("2020-12-06","17:00:00","M",1,"DR-84-HN",1,26),
("2020-12-06","17:00:00","M",3,"CF-49-LA",5,28),
("2020-12-06","17:00:00","M",5,"PO-25-GT",2,34),
("2020-12-07","10:00:00","M",3,"QA-18-QL",4,29),
("2020-12-07","10:00:00","M",4,"XA-91-BE",5,19),
("2020-12-07","11:00:00","M",1,"CF-49-LA",2,16),
("2020-12-07","11:00:00","M",2,"PO-25-GT",4,15),
("2020-12-07","11:00:00","M",4,"DR-84-HN",3,13),
("2020-12-07","15:00:00","M",1,"TH-67-FR",1,11),
("2020-12-07","15:00:00","M",3,"NB-70-GH",2,18),
("2020-12-07","15:00:00","M",4,"QA-18-QL",1,24),
("2020-12-07","16:00:00","M",1,"JI-50-NK",4,21),
("2020-12-07","16:00:00","M",3,"CF-49-LA",2,25),
("2020-12-07","16:00:00","M",5,"PO-25-GT",4,27),
("2020-12-07","17:00:00","M",2,"KJ-41-SD",5,4),
("2020-12-07","17:00:00","M",4,"DR-84-HN",1,2),
("2020-12-08","10:00:00","M",3,"PO-25-GT",3,7),
("2020-12-08","10:00:00","M",5,"QA-18-QL",1,8),
("2020-12-08","11:00:00","M",2,"",2,9),
("2020-12-08","11:00:00","M",4,"CF-49-LA",4,10),
("2020-12-08","15:00:00","M",1,"XA-91-BE",5,11),
("2020-12-08","15:00:00","M",3,"TH-67-FR",5,15),
("2020-12-08","16:00:00","M",2,"CF-49-LA",1,21),
("2020-12-08","16:00:00","M",4,"DR-84-HN",2,16),
("2020-12-08","17:00:00","M",2,"TH-67-FR",2,19),
("2020-12-08","17:00:00","M",4,"NB-70-GH",4,22),
("2020-12-09","10:00:00","M",3,"KJ-41-SD",2,16),
("2020-12-09","10:00:00","M",5,"CF-49-LA",1,14),
("2020-12-09","11:00:00","M",2,"JI-50-NK",4,2),
("2020-12-09","11:00:00","M",4,"PO-25-GT",5,6),
("2020-12-09","15:00:00","M",2,"KJ-41-SD",3,4),
("2020-12-09","15:00:00","M",5,"DR-84-HN",2,7),
("2020-12-09","16:00:00","M",3,"CF-49-LA",1,9),
("2020-12-09","17:00:00","M",1,"QA-18-QL",5,13),
("2020-12-09","17:00:00","M",4,"TH-67-FR",3,21),
("2020-12-10","10:00:00","M",3,"DR-84-HN",1,23),
("2020-12-10","10:00:00","M",4,"TH-67-FR",2,22),
("2020-12-10","11:00:00","M",1,"CF-49-LA",3,11),
("2020-12-10","11:00:00","M",3,"DR-84-HN",5,15),
("2020-12-10","11:00:00","M",4,"XA-91-BE",3,17),
("2020-12-10","11:00:00","M",5,"TH-67-FR",2,20),
("2020-12-10","15:00:00","M",2,"CF-49-LA",5,14),
("2020-12-10","15:00:00","M",4,"QA-18-QL",3,18),
("2020-12-10","16:00:00","M",1,"PO-25-GT",2,23),
("2020-12-10","16:00:00","M",3,"QA-18-QL",1,4),
("2020-12-10","17:00:00","M",1,"CF-49-LA",1,7),
("2020-12-10","17:00:00","M",4,"DR-84-HN",2,3),
("2020-12-11","10:00:00","M",3,"NB-70-GH",3,1),
("2020-12-11","10:00:00","M",5,"QA-18-QL",4,9),
("2020-12-11","11:00:00","M",2,"KJ-41-SD",2,17),
("2020-12-11","11:00:00","M",4,"CF-49-LA",5,21),
("2020-12-11","11:00:00","M",5,"XA-91-BE",2,27),
("2020-12-11","15:00:00","M",2,"TH-67-FR",1,24),
("2020-12-11","15:00:00","M",3,"JI-50-NK",3,17),
("2020-12-11","16:00:00","M",1,"DR-84-HN",2,19), 
("2020-12-11","16:00:00","M",3,"KJ-41-SD",4,20),
("2020-12-11","16:00:00","M",5,"PO-25-GT",1,10),
("2020-12-11","17:00:00","M",4,"NB-70-GH",4,9);
