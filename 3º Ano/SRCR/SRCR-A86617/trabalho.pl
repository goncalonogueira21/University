%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% SIST. REPR. CONHECIMENTO E RACIOCINIO - MiEI/3

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Programacão em logica 
% Resolução do trabalho de recurso

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% SICStus PROLOG: Declaracoes iniciais

:- set_prolog_flag( discontiguous_warnings,off ).
:- set_prolog_flag( single_var_warnings,off ).
:- set_prolog_flag( unknown,fail ).

%---------------------------------  dados do problema ---------

%local(ID,'city',lat,lng,'capital','admin','caracteristica').




local(1.0,'Lisboa',38.716667,-9.133333,'Lisboa','primary','Capital do País').
local(2.0,'Picotos',41.192402,-8.619816,'Porto','minor','Sem descricao').
local(3.0,'Braga',41.550323,-8.420052,'Braga','admin','Sé de Braga').
local(5.0,'Setubal',38.533333,-8.9,'Setubal','admin','Serra Arrabida').
local(6.0,'Copeira',40.176915,-8.424018,'Coimbra','minor','Patrimonio Mundial').
local(8.0,'Portimao',37.136636,-8.539796,'Faro','minor','Praia da rocha').
local(9.0,'Evora',38.566667,-7.9,'Evora','admin','Templo romano').
local(10.0,'Aveiro',40.644269,-8.645535,'Aveiro','admin','Ria de Aveiro').
local(11.0,'Leiria',39.747724,-8.804995,'Leiria','admin','Sem descricao').
local(12.0,'Faro',37.019367,-7.932229,'Faro','admin','Sem descricao').
local(13.0,'Beja',38.015064,-7.863227,'Beja','admin','Sem descricao').
local(14.0,'Braganca',41.805817,-6.757189,'Braganca','admin','Sem descricao').
local(15.0,'Castelo_Branco',39.822191,-7.490869,'Castelo_Branco','admin','Sem descricao').
local(16.0,'Guarda',40.537328,-7.265749,'Guarda','admin','Serra da estrela').
local(17.0,'Santarem',39.233333,-8.683333,'Santarem','admin','Convento de cristo').
local(18.0,'Viseu',40.661014,-7.909714,'Viseu','admin','Sem descricao').
local(19.0,'Covilha',40.286011,-7.503961,'Castelo_Branco','minor','Sem descricao').
local(20.0,'Vila_Marim',41.304961,-7.779743,'Vila_Real','minor','Patrimonio Mundial').
local(21.0,'Portalegre',39.297178,-7.430151,'Portalegre','admin','Sem descricao').
local(22.0,'Viana_do_Castelo',41.693234,-8.832869,'Viana_do_Castelo','admin','Sem descricao','Se de viana').
local(25.0,'Lagos',37.101782,-8.674242,'Faro','minor','Grutas').
local(26.0,'Paredes_de_Coura',41.910125,-8.560938,'Viana_do_Castelo','minor','Festival').
local(27.0,'Sao_Joao_da_Pesqueira',41.148051,-7.404888,'Viseu','minor','Sem descricao').
local(28.0,'Sao_Joao_da_Madeira',40.900956,-8.499744,'Aveiro','minor','Sem descricao').
local(29.0,'Fornos_de_Algodres',40.628072,-7.540638,'Guarda','minor','Sem descricao').
local(30.0,'Castelo_de_Paiva',41.063007,-8.264696,'Aveiro','minor','Passadicos de paiva').
local(31.0,'Portel',38.30697,-7.702435,'Evora','minor','Sem descricao').
local(32.0,'Porto',41.149606,-8.610993,'Porto','admin','Torre dos clerigos').
local(33.0,'Serta',39.808461,-8.098829,'Castelo_Branco','minor','Sem descricao').
local(34.0,'Vila_do_Bispo',37.083172,-8.911438,'Faro','minor','Patrimonio Mundial').
local(35.0,'Fronteira',39.056291,-7.648679,'Portalegre','minor','Sem descricao').
local(36.0,'Alfandega_da_Fe',41.343149,-6.961124,'Braganca','minor','Sem descricao').
local(37.0,'Celorico_da_Beira',40.637232,-7.39037,'Guarda','minor','Sem descricao').
local(38.0,'Alcoutim',37.474317,-7.472282,'Faro','minor','Sem descricao').
local(39.0,'Arronches',39.122417,-7.286192,'Portalegre','minor','Sem descricao').
local(40.0,'Amarante',41.272711,-8.082455,'Porto','minor','Sem descricao').
local(41.0,'Tabuaco',41.116147,-7.567934,'Viseu','minor','Sem descricao').
local(42.0,'Gouveia',40.494455,-7.592145,'Guarda','minor','Sem descricao').
local(43.0,'Aguiar_da_Beira',40.817264,-7.544307,'Guarda','minor','Sem descricao').
local(44.0,'Idanha_a_Nova',39.923157,-7.240819,'Castelo_Branco','minor','Patrimonio Mundial').
local(45.0,'Ribeira_de_Pena',41.52147,-7.802372,'Vila_Real','minor','Sem descricao').
local(46.0,'Seia',40.415099,-7.708586,'Guarda','minor','Ponto mais alto de portugal continental').
local(47.0,'Rio_Maior',39.337325,-8.939063,'Santarem','minor','Sem descricao').
local(48.0,'Condeixa_a_Nova',40.115733,-8.498336,'Coimbra','minor','Sem descricao').
local(49.0,'Macao',39.555734,-7.994215,'Santarem','minor','Sem descricao').
local(50.0,'Lousada',41.278223,-8.279926,'Porto','minor','Sem descricao').
local(51.0,'Trancoso',40.783291,-7.350157,'Guarda','minor','Sem descricao').
local(52.0,'Estarreja',40.756482,-8.572074,'Aveiro','minor','Sem descricao').
local(53.0,'Moita',38.650779,-8.990383,'Setubal','minor','Sem descricao').
local(54.0,'Ponte_de_Lima',41.767188,-8.583926,'Viana_do_Castelo','minor','Sem descricao').
local(55.0,'Guimaraes',41.444435,-8.296189,'Braga','minor','Castelo').
local(56.0,'Sobral_de_Monte_Agraco',39.019579,-9.150809,'Lisboa','minor','Sem descricao').
local(57.0,'Seixal',38.64008,-9.101412,'Setubal','minor','Sem descricao').
local(58.0,'Almeirim',39.209028,-8.616426,'Santarem','minor','Sem descricao').
local(59.0,'Cantanhede',40.346708,-8.594195,'Coimbra','minor','Sem descricao').
local(60.0,'Elvas',38.881502,-7.162817,'Portalegre','minor','Sem descricao').
local(61.0,'Ponte_da_Barca',41.804509,-8.415541,'Viana_do_Castelo','minor','Sem descricao').
local(62.0,'Golega',39.40474,-8.48625,'Santarem','minor','Sem descricao').
local(63.0,'Anadia',40.438409,-8.43352,'Aveiro','minor','Vinho').
local(64.0,'Moura',38.140095,-7.44856,'Beja','minor','Sem descricao').
local(65.0,'Avis',39.05391,-7.891556,'Portalegre','minor','Sem descricao').
local(66.0,'Agueda',40.577205,-8.444418,'Aveiro','minor','Sem descricao').
local(67.0,'Valongo',41.195007,-8.51027,'Porto','minor','Sem descricao').
local(68.0,'Caminha',41.874874,-8.837321,'Viana_do_Castelo','minor','Sem descricao').
local(69.0,'Ourique',37.653897,-8.225687,'Beja','minor','Sem descricao').
local(70.0,'Sardoal',39.535994,-8.161413,'Santarem','minor','Sem descricao').
local(71.0,'Vila_do_Conde',41.354811,-8.743397,'Porto','minor','Caxinas').
local(72.0,'Alijo',41.276781,-7.474883,'Vila_Real','minor','Sem descricao').
local(73.0,'Monchique',37.317748,-8.555294,'Faro','minor','Serra de monchique').
local(74.0,'Cabeceiras_de_Basto',41.514312,-7.989415,'Braga','minor','Sem descricao').
local(75.0,'Aljezur',37.319152,-8.803305,'Faro','minor','Sem descricao').
local(76.0,'Castanheira_de_Pêra',40.007169,-8.210484,'Leiria','minor','Sem descricao').
local(77.0,'Melgaco',42.113371,-8.260161,'Viana_do_Castelo','minor','Sem descricao').
local(78.0,'Gaviao',39.464431,-7.934494,'Portalegre','minor','Sem descricao').
local(79.0,'Monforte',39.053297,-7.437582,'Portalegre','minor','Sem descricao').
local(80.0,'Vila_Vicosa',38.777696,-7.417927,'Evora','minor','Sem descricao').
local(81.0,'Almodovar',37.512792,-8.060077,'Beja','minor','Sem descricao').
local(82.0,'Redondo',38.648716,-7.547082,'Evora','minor','Sem descricao').
local(83.0,'Vila_Nova_de_Cerveira',41.941184,-8.742304,'Viana_do_Castelo','minor','Sem descricao').
local(84.0,'Mafra',38.937933,-9.327565,'Lisboa','minor','Convento de mafra').
local(85.0,'Lousa',40.111911,-8.24703,'Coimbra','minor','Sem descricao').
local(86.0,'Amadora',38.759711,-9.239708,'Lisboa','minor','Patrimonio Mundial').
local(87.0,'Pinhel',40.774029,-7.06675,'Guarda','minor','Sem descricao').
local(88.0,'Estremoz',38.844316,-7.585854,'Evora','minor','Sem descricao').
local(89.0,'Penamacor',40.168946,-7.169867,'Castelo_Branco','minor','Sem descricao').
local(90.0,'Penalva_do_Castelo',40.676273,-7.698391,'Viseu','minor','Sem descricao').
local(91.0,'Crato',39.287571,-7.645494,'Portalegre','minor','Sem descricao').
local(92.0,'Nelas',40.532157,-7.851525,'Viseu','minor','Sem descricao').
local(93.0,'Aljustrel',37.877594,-8.165159,'Beja','minor','Sem descricao').
local(94.0,'Esposende',41.536098,-8.782011,'Braga','minor','Sem descricao').
local(95.0,'Alcochete',38.755335,-8.960861,'Setubal','minor','Sem descricao').
local(96.0,'Sever_do_Vouga',40.734588,-8.367219,'Aveiro','minor','Sem descricao').
local(97.0,'Sesimbra',38.444513,-9.101236,'Setubal','minor','Sem descricao').
local(98.0,'Sao_Pedro_do_Sul',40.75537,-8.072646,'Viseu','minor','Sem descricao').
local(99.0,'Lourinha',39.233333,-9.316667,'Lisboa','minor','Patrimonio Mundial').
local(100.0,'Santa_Comba_Dao',40.398559,-8.131601,'Viseu','minor','Sem descricao').
local(101.0,'Entroncamento',39.466667,-8.466667,'Santarem','minor','Sem descricao').
local(102.0,'Armamar',41.107646,-7.691386,'Viseu','minor','Sem descricao').
local(103.0,'Arcos_de_Valdevez',41.848912,-8.410905,'Viana_do_Castelo','minor','Sem descricao').
local(104.0,'Pacos_de_Ferreira',41.276571,-8.376174,'Porto','minor','Capital do movel').
local(105.0,'Fafe',41.454227,-8.167998,'Braga','minor','Justica de fafe').
local(106.0,'Ponte_de_Sor',39.249642,-8.010086,'Portalegre','minor','Sem descricao').
local(107.0,'Moimenta_da_Beira',40.983828,-7.617653,'Viseu','minor','Sem descricao').
local(108.0,'Santa_Marta_de_Penaguiao',41.211161,-7.800111,'Vila_Real','minor','Sem descricao').
local(109.0,'Murca',41.405997,-7.454846,'Vila_Real','minor','Sem descricao').
local(110.0,'Sernancelhe',40.898706,-7.493419,'Viseu','minor','Patrimonio Mundial').
local(111.0,'Vila_Real',41.30062,-7.744129,'Vila_Real','admin','Sem descricao').
local(112.0,'Vinhais',41.835094,-7.005007,'Braganca','minor','Sem descricao').
local(113.0,'Alcacer_do_Sal',38.373258,-8.514436,'Setubal','minor','Sem descricao').
local(114.0,'Ourem',39.641675,-8.591899,'Santarem','minor','Sem descricao').
local(115.0,'Vila_Nova_de_Gaia',41.133633,-8.617421,'Porto','minor','Sem descricao').
local(116.0,'Castelo_de_Vide',39.414713,-7.454021,'Portalegre','minor','Sem descricao').
local(117.0,'Vila_Nova_da_Barquinha',39.45,-8.433333,'Santarem','minor','Sem descricao').
local(118.0,'Loule',37.137722,-8.019684,'Faro','minor','Sem descricao').
local(119.0,'Lamego',41.097407,-7.809907,'Viseu','minor','Sem descricao').
local(120.0,'Alvaiazere',39.822559,-8.379994,'Leiria','minor','Sem descricao').
local(121.0,'Satao',40.741775,-7.732855,'Viseu','minor','Sem descricao').
local(122.0,'Albergaria_a_Velha',40.693185,-8.479936,'Aveiro','minor','Sem descricao').
local(123.0,'Matosinhos',41.18207,-8.689076,'Porto','minor','Sem descricao').
local(124.0,'Alandroal',38.702005,-7.403094,'Evora','minor','Sem descricao').
local(125.0,'Proenca_a_Nova',39.752204,-7.923903,'Castelo_Branco','minor','Patrimonio Mundial').
local(126.0,'Lagoa',37.135349,-8.453188,'Faro','minor','Sem descricao').
local(127.0,'Montijo',38.706747,-8.973885,'Setubal','minor','Sem descricao').
local(128.0,'Felgueiras',41.368058,-8.193961,'Porto','minor','Sem descricao').
local(129.0,'Nazare',39.602891,-9.068355,'Leiria','minor','Canhao da nazare').
local(130.0,'Miranda_do_Corvo',40.09318,-8.332608,'Coimbra','minor','Sem descricao').
local(131.0,'Penedono',40.988749,-7.393859,'Viseu','minor','Sem descricao').
local(132.0,'Vale_de_Cambra',40.849701,-8.393892,'Aveiro','minor','Sem descricao').
local(133.0,'Vila_Flor',41.309043,-7.153784,'Braganca','minor','Sem descricao').
local(134.0,'Figueiro_dos_Vinhos',39.904132,-8.275107,'Leiria','minor','Sem descricao').
local(135.0,'Santiago_do_Cacem',38.016935,-8.69475,'Setubal','minor','Sem descricao').
local(136.0,'Trofa',41.322784,-8.572016,'Porto','minor','Sem descricao').
local(137.0,'Penafiel',41.208348,-8.282847,'Porto','minor','Sem descricao').
local(138.0,'Penacova',40.268837,-8.282374,'Coimbra','minor','Sem descricao').
local(139.0,'Pedrogao_Grande',39.918345,-8.1459,'Leiria','minor','Sem descricao').
local(140.0,'Oleiros',39.918934,-7.913698,'Castelo_Branco','minor','Sem descricao').
local(141.0,'Sousel',38.952894,-7.675286,'Portalegre','minor','Sem descricao').
local(142.0,'Arraiolos',38.723626,-7.984777,'Evora','minor','Tapetes de arraiolos').
local(143.0,'Poiares',40.210256,-8.257464,'Coimbra','minor','Sem descricao').
local(144.0,'Famalicao',41.407967,-8.51978,'Braga','minor','Sem descricao').
local(145.0,'Vila_Verde',41.647294,-8.43715,'Braga','minor','Sem descricao').
local(146.0,'Terras_de_Bouro',41.717691,-8.30888,'Braga','minor','Sem descricao').
local(147.0,'Manteigas',40.402799,-7.539769,'Guarda','minor','Sem descricao').
local(148.0,'Sintra',38.800971,-9.378257,'Lisboa','minor','Palacio de sintra').
local(149.0,'Vizela',41.390962,-8.263888,'Braga','minor','Sem descricao').
local(150.0,'Vila_Velha_de_Rodao',39.666667,-7.7,'Castelo_Branco','minor','Sem descricao').
local(151.0,'Benavente',38.979192,-8.807591,'Santarem','minor','Sem descricao').
local(152.0,'Maia',41.235739,-8.619897,'Porto','minor','Sem descricao').
local(153.0,'Santo_Tirso',41.342567,-8.477456,'Porto','minor','Sem descricao').
local(154.0,'Oeiras',38.691049,-9.310847,'Lisboa','minor','Sem descricao').
local(155.0,'Celorico_de_Basto',41.387141,-8.00101,'Braga','minor','Sem descricao').
local(156.0,'Bombarral',39.267231,-9.157952,'Leiria','minor','Patrimonio Mundial').
local(157.0,'Barreiro',38.663137,-9.072395,'Setubal','minor','Sem descricao').
local(158.0,'Belmonte',40.359303,-7.34869,'Castelo_Branco','minor','Sem descricao').
local(159.0,'Montemor_o_Velho',40.172873,-8.686162,'Coimbra','minor','Sem descricao').
local(160.0,'Espinho',41.007628,-8.641251,'Aveiro','minor','Sem descricao').
local(161.0,'Oliveira_do_Hospital',40.361796,-7.86014,'Coimbra','minor','Sem descricao').
local(162.0,'Oliveira_de_Frades',40.733567,-8.174807,'Viseu','minor','Sem descricao').
local(163.0,'Oliveira_de_Azemeis',40.84101,-8.475554,'Aveiro','minor','Sem descricao').
local(164.0,'Oliveira_do_Bairro',40.514596,-8.493858,'Aveiro','minor','Sem descricao').
local(165.0,'Viana_do_Alentejo',38.33458,-8.004399,'Evora','minor','Sem descricao').
local(166.0,'Carrazeda_de_Anciaes',41.242466,-7.307206,'Braganca','minor','Sem descricao').
local(167.0,'Ovar',40.861753,-8.626014,'Aveiro','minor','Sem descricao').
local(168.0,'Torres_Novas',39.481143,-8.539493,'Santarem','minor','Sem descricao').
local(169.0,'Torres_Vedras',39.091089,-9.258602,'Lisboa','minor','Sem descricao').
local(170.0,'Cartaxo',39.160221,-8.787408,'Santarem','minor','Sem descricao').
local(171.0,'Mangualde',40.604248,-7.76115,'Viseu','minor','Sem descricao').
local(172.0,'Vila_Nova_de_Paiva',40.852907,-7.727911,'Viseu','minor','Sem descricao').
local(173.0,'Paredes',41.204853,-8.33147,'Porto','minor','Sem descricao').
local(174.0,'Vidigueira',38.209949,-7.800504,'Beja','minor','Sem descricao').
local(175.0,'Chamusca',39.35722,-8.48151,'Santarem','minor','Sem descricao').
local(176.0,'Trofa',41.487817,-7.961286,'Braga','minor','Sem descricao').
local(177.0,'Macedo_de_Cavaleiros',41.538161,-6.9611,'Braganca','minor','Sem descricao').
local(178.0,'Resende',41.105822,-7.966497,'Viseu','minor','Sem descricao').
local(179.0,'Povoa_de_Lanhoso',41.577713,-8.268468,'Braga','minor','Sem descricao').
local(180.0,'Feira',40.925348,-8.542769,'Aveiro','minor','Sem descricao').
local(181.0,'Azambuja',39.07029,-8.86822,'Lisboa','minor','Sem descricao').
local(182.0,'Vieira_do_Minho',41.632923,-8.142521,'Braga','minor','Sem descricao').
local(183.0,'Batalha',39.660252,-8.824751,'Leiria','minor','Sem descricao').
local(184.0,'Alcanena',39.459005,-8.668924,'Santarem','minor','Sem descricao').
local(185.0,'Palmela',38.569021,-8.901255,'Setubal','minor','Sem descricao').
local(186.0,'Ferreira_do_Zezere',39.694064,-8.292131,'Santarem','minor','Sem descricao').
local(187.0,'Arouca',40.930568,-8.24488,'Aveiro','minor','Sem descricao').
local(188.0,'Vila_de_Rei',39.67604,-8.145768,'Castelo_Branco','minor','Sem descricao').
local(189.0,'Tomar',39.601987,-8.409242,'Santarem','minor','Sem descricao').
local(190.0,'Tondela',40.516815,-8.080866,'Viseu','minor','Sem descricao').
local(191.0,'Constancia',39.466667,-8.333333,'Santarem','minor','Sem descricao').
local(192.0,'Vila_Pouca_de_Aguiar',41.500176,-7.64383,'Vila_Real','minor','Sem descricao').
local(193.0,'Almada',38.679018,-9.156904,'Setubal','minor','Sem descricao').
local(194.0,'Almeida',40.725672,-6.906137,'Guarda','minor','Sem descricao').
local(195.0,'Alvito',38.256109,-7.991584,'Beja','minor','Sem descricao').
local(196.0,'Soure',40.05989,-8.626053,'Coimbra','minor','Sem descricao').
local(197.0,'Alenquer',39.053151,-9.009282,'Lisboa','minor','Sem descricao').
local(198.0,'Mertola',37.643041,-7.661104,'Beja','minor','Sem descricao').
local(199.0,'Mesao_Frio',41.163167,-7.873534,'Vila_Real','minor','Sem descricao').
local(200.0,'Mourao',38.383562,-7.341888,'Evora','minor','Sem descricao').
local(201.0,'Valpacos',41.607461,-7.310876,'Vila_Real','minor','Sem descricao').
local(202.0,'Pombal',39.916738,-8.628474,'Leiria','minor','Sem descricao').
local(203.0,'Mogadouro',41.340203,-6.711347,'Braganca','minor','Sem descricao').
local(204.0,'Povoa_de_Varzim',41.38344,-8.763637,'Porto','minor','Praca dos touros').
local(205.0,'Baiao',41.162735,-8.034704,'Porto','minor','Sem descricao').
local(206.0,'Mortagua',40.396746,-8.232341,'Viseu','minor','Sem descricao').
local(207.0,'Tabua',40.362074,-8.02936,'Coimbra','minor','Sem descricao').
local(208.0,'Cascais',38.69745,-9.423141,'Lisboa','minor','Sem descricao').
local(209.0,'Barcelos',41.538763,-8.615053,'Braga','minor','Galo de barcelos').
local(210.0,'Boticas',41.689874,-7.665938,'Vila_Real','minor','Sem descricao').
local(211.0,'Sabrosa',41.267017,-7.576007,'Vila_Real','minor','Sem descricao').
local(212.0,'Montalegre',41.823569,-7.789714,'Vila_Real','minor','Sem descricao').
local(213.0,'Gondomar',41.144536,-8.532229,'Porto','minor','Sem descricao').
local(214.0,'Freixo_de_Espada_a_Cinta',41.090327,-6.806478,'Braganca','minor','Sem descricao').
local(215.0,'Mora',38.943515,-8.164337,'Evora','minor','Sem descricao').
local(216.0,'Vendas_Novas',38.677056,-8.457924,'Evora','minor','Sem descricao').
local(217.0,'Vila_Nova_de_Foz_Coa',41.083333,-7.2,'Guarda','minor','Sem descricao').
local(218.0,'Caldas_da_Rainha',39.403255,-9.138387,'Leiria','minor','Sem descricao').
local(219.0,'Marvao',39.393912,-7.376861,'Portalegre','minor','Tunel do marvao').
local(220.0,'Vimioso',41.584726,-6.52767,'Braganca','minor','Sem descricao').
local(221.0,'Odivelas',38.795234,-9.187387,'Lisboa','minor','Sem descricao').
local(222.0,'Odemira',37.598106,-8.638886,'Beja','minor','Sem descricao').
local(223.0,'Peniche',39.357486,-9.380439,'Leiria','minor','Surf').
local(224.0,'Vagos',40.555998,-8.68175,'Aveiro','minor','Sem descricao').
local(225.0,'Marco_de_Canavezes',41.183887,-8.148641,'Porto','minor','Sem descricao').
local(226.0,'Coruche',38.959546,-8.525235,'Santarem','minor','Sem descricao').
local(227.0,'Coimbra',40.205642,-8.419551,'Coimbra','admin','Universidade').
local(228.0,'Barrancos',38.134462,-6.976042,'Beja','minor','Sem descricao').
local(229.0,'Montemor_o_Novo',38.648117,-8.214549,'Evora','minor','Sem descricao').
local(230.0,'Meda',40.966352,-7.261634,'Guarda','minor','Sem descricao').
local(231.0,'obidos',39.360551,-9.156696,'Leiria','minor','Sem descricao').
local(232.0,'Gois',40.157353,-8.110067,'Coimbra','minor','Sem descricao').
local(233.0,'Reguengos_de_Monsaraz',38.425293,-7.534945,'Evora','minor','Sem descricao').
local(234.0,'Torre_de_Moncorvo',41.174537,-7.05364,'Braganca','minor','Sem descricao').
local(235.0,'Murtosa',40.736948,-8.637697,'Aveiro','minor','Sem descricao').
local(236.0,'Alcobaca',39.552233,-8.977495,'Leiria','minor','Sem descricao').
local(237.0,'Figueira_da_Foz',40.150852,-8.861786,'Coimbra','minor','Sem descricao').
local(238.0,'Figueira_de_Castelo_Rodrigo',40.892619,-6.963502,'Guarda','minor','Sem descricao').
local(239.0,'Abrantes',39.466667,-8.2,'Santarem','minor','Sem descricao').
local(240.0,'Arruda_dos_Vinhos',38.984106,-9.077463,'Lisboa','minor','Sem descricao').
local(241.0,'Fundao',40.140247,-7.501348,'Castelo_Branco','minor','Sem descricao').
local(242.0,'Tarouca',41.014444,-7.781432,'Viseu','minor','Sem descricao').
local(243.0,'Ilhavo',40.599896,-8.667325,'Aveiro','minor','Sem descricao').
local(244.0,'Alpiarca',39.257116,-8.581866,'Santarem','minor','Sem descricao').
local(245.0,'Albufeira',37.090205,-8.25079,'Faro','minor','Sem descricao').
local(246.0,'Penela',40.033333,-8.383333,'Coimbra','minor','Sem descricao').
local(247.0,'Valenca',42.03104,-8.645953,'Viana_do_Castelo','minor','Sem descricao').
local(248.0,'Amares',41.630907,-8.351166,'Braga','minor','Sem descricao').
local(249.0,'Sao_Bras_de_Alportel',37.1531,-7.887515,'Faro','minor','Sem descricao').
local(250.0,'Pampilhosa_da_Serra',40.046198,-7.951824,'Coimbra','minor','Sem descricao').
local(251.0,'Tavira',37.127338,-7.648609,'Faro','minor','Sem descricao').
local(252.0,'Nisa',39.514989,-7.649077,'Portalegre','minor','Sem descricao').
local(253.0,'Alter_do_Chao',39.198712,-7.658298,'Portalegre','minor','Sem descricao').
local(254.0,'Castro_Verde',37.698282,-8.085812,'Beja','minor','Sem descricao').
local(255.0,'Mealhada',40.378063,-8.449912,'Aveiro','minor','Sem descricao').
local(256.0,'Cuba',38.165436,-7.892402,'Beja','minor','Sem descricao').
local(257.0,'Vouzela',40.723613,-8.112833,'Viseu','minor','Sem descricao').
local(258.0,'Vila_Franca_de_Xira',38.955249,-8.98966,'Lisboa','minor','Sem descricao').
local(259.0,'Marinha_Grande',39.747691,-8.932284,'Leiria','minor','Sem descricao').
local(260.0,'Cinfaes',41.071969,-8.089991,'Viseu','minor','Sem descricao').
local(261.0,'Borba',38.80553,-7.45465,'Evora','minor','Sem descricao').
local(262.0,'Mira',40.428924,-8.737462,'Coimbra','minor','Sem descricao').
local(263.0,'Silves',37.189213,-8.438217,'Faro','minor','Sem descricao').
local(264.0,'Grandola',38.177181,-8.566746,'Setubal','minor','Sem descricao').
local(265.0,'Campo_Maior',39.017742,-7.064967,'Portalegre','minor','Sem descricao').
local(266.0,'Ferreira_do_Alentejo',38.05,-8.033333,'Beja','minor','Sem descricao').
local(267.0,'Miranda_do_Douro',41.496921,-6.273077,'Braganca','minor','Sem descricao').
local(268.0,'Mirandela',41.487385,-7.186949,'Braganca','minor','Sem descricao').
local(269.0,'Chaves',41.740186,-7.468789,'Vila_Real','minor','Sem descricao').
local(270.0,'Sines',37.956215,-8.869788,'Setubal','minor','Sem descricao').
local(271.0,'Mondim_de_Basto',41.411566,-7.954414,'Vila_Real','minor','Sem descricao').
local(272.0,'Moncao',42.078471,-8.481452,'Viana_do_Castelo','minor','Sem descricao').
local(273.0,'Castro_Marim',37.220683,-7.4435,'Faro','minor','Sem descricao').
local(274.0,'Castro_Daire',40.898399,-7.933805,'Viseu','minor','Sem descricao').
local(275.0,'Arganil',40.218261,-8.054029,'Coimbra','minor','Sem descricao').
local(276.0,'Olhao',37.0286,-7.841101,'Faro','minor','Sem descricao').
local(277.0,'Cadaval',39.242977,-9.103271,'Lisboa','minor','Sem descricao').
local(278.0,'Loures',38.829082,-9.168106,'Lisboa','minor','Sem descricao').
local(279.0,'Salvaterra_de_Magos',39.027881,-8.793502,'Santarem','minor','Sem descricao').
local(280.0,'Peso_da_Regua',41.164912,-7.787034,'Vila_Real','minor','Sem descricao').
local(281.0,'Serpa',37.945811,-7.597537,'Beja','minor','Sem descricao').
local(282.0,'Sabugal',40.351267,-7.091036,'Guarda','minor','Sem descricao').
local(283.0,'Ansiao',39.911774,-8.435683,'Leiria','minor','Sem descricao').
local(284.0,'Vila_Real_de_Santo_Antonio',37.194999,-7.417658,'Faro','minor','Sem descricao').
local(285.0,'Porto_de_Mos',39.601911,-8.818389,'Leiria','minor','Sem descricao').

ligacao('Boticas','Figueira_da_Foz').
ligacao('Rio_Maior','Vila_Nova_de_Gaia').
ligacao('Setubal','Vila_Nova_de_Cerveira').
ligacao('Mondim_de_Basto','Vila_Nova_de_Foz_Coa').
ligacao('Agueda','Vila_Nova_da_Barquinha').
ligacao('Santa_Marta_de_Penaguiao','Trancoso').
ligacao('Vila_Verde','Gois').
ligacao('Vila_Velha_de_Rodao','Chaves').
ligacao('Vila_do_Conde','Celorico_da_Beira').
ligacao('Arruda_dos_Vinhos','Alter_do_Chao').
ligacao('Copeira','Santa_Comba_Dao').
ligacao('Vila_Flor','Sines').
ligacao('Montemor_o_Novo','Valongo').
ligacao('Vieira_do_Minho','Elvas').
ligacao('Santarem','Alcanena').
ligacao('Pacos_de_Ferreira','Sabugal').
ligacao('Proenca_a_Nova','Tabua').
ligacao('Pombal','Amadora').
ligacao('Sao_Pedro_do_Sul','Macedo_de_Cavaleiros').
ligacao('Tabua','Arcos_de_Valdevez').
ligacao('Oliveira_do_Bairro','Olhao').
ligacao('Paredes_de_Coura','Castelo_de_Vide').
ligacao('Mondim_de_Basto','Sabrosa').
ligacao('Fafe','Ponte_da_Barca').
ligacao('Pinhel','Satao').
ligacao('Fronteira','Penela').
ligacao('Sever_do_Vouga','Penamacor').
ligacao('Sao_Joao_da_Madeira','Mafra').
ligacao('Anadia','Maia').
ligacao('Azambuja','Famalicao').
ligacao('Anadia','Vouzela').
ligacao('Ferreira_do_Alentejo','Beja').
ligacao('Reguengos_de_Monsaraz','Mesao_Frio').
ligacao('Loule','Alcochete').
ligacao('Aveiro','Seia').
ligacao('Golega','Castro_Daire').
ligacao('Lagos','Almeida').
ligacao('Sao_Joao_da_Madeira','Paredes').
ligacao('Serpa','Caminha').
ligacao('Cascais','Vila_Real_de_Santo_Antonio').
ligacao('Leiria','Cantanhede').
ligacao('Cascais','Idanha_a_Nova').
ligacao('Odemira','Alcoutim').
ligacao('Mora','Vila_Real').
ligacao('Pampilhosa_da_Serra','Ponte_de_Sor').
ligacao('Serpa','Tondela').
ligacao('Sobral_de_Monte_Agraco','Moura').
ligacao('Moncao','Loures').
ligacao('Loule','Campo_Maior').
ligacao('Pedrogao_Grande','Serta').
ligacao('Tarouca','Figueiro_dos_Vinhos').
ligacao('Constancia','Tavira').
ligacao('Castanheira_de_Pêra','Entroncamento').
ligacao('Espinho','Idanha_a_Nova').
ligacao('Estremoz','Cartaxo').
ligacao('Peso_da_Regua','Vila_do_Conde').
ligacao('Sabrosa','Barcelos').
ligacao('Castro_Marim','Sobral_de_Monte_Agraco').
ligacao('Melgaco','Estremoz').
ligacao('Alenquer','Pedrogao_Grande').
ligacao('Beja','Figueiro_dos_Vinhos').
ligacao('Coimbra','Covilha').
ligacao('Caldas_da_Rainha','Tavira').
ligacao('Santa_Marta_de_Penaguiao','Cuba').
ligacao('Vila_Nova_de_Gaia','Portel').
ligacao('Poiares','Vizela').
ligacao('Aveiro','Castelo_de_Vide').
ligacao('Abrantes','Pombal').
ligacao('Murtosa','Evora').
ligacao('Campo_Maior','Seia').
ligacao('Mafra','Vieira_do_Minho').
ligacao('Nisa','Santarem').
ligacao('Guarda','Poiares').
ligacao('Santo_Tirso','Espinho').
ligacao('Miranda_do_Douro','Castanheira_de_Pêra').
ligacao('Ferreira_do_Zezere','Monforte').
ligacao('Arraiolos','Castelo_de_Vide').
ligacao('Alcanena','Vila_Nova_de_Gaia').
ligacao('Moura','Castelo_de_Paiva').
ligacao('Castro_Daire','Armamar').
ligacao('Coimbra','Gaviao').
ligacao('Seia','Golega').
ligacao('Povoa_de_Varzim','Gouveia').
ligacao('Torre_de_Moncorvo','Aveiro').
ligacao('Penalva_do_Castelo','Oliveira_de_Azemeis').
ligacao('Mangualde','Ponte_da_Barca').
ligacao('Leiria','Sao_Joao_da_Pesqueira').
ligacao('Chaves','Penafiel').
ligacao('Arganil','Serpa').
ligacao('Alpiarca','Alcanena').
ligacao('Povoa_de_Lanhoso','Marvao').
ligacao('Aveiro','Mondim_de_Basto').
ligacao('Chaves','Estarreja').
ligacao('Paredes_de_Coura','Benavente').
ligacao('Esposende','Picotos').
ligacao('Monchique','Serpa').
ligacao('Azambuja','Mogadouro').
ligacao('Valongo','Salvaterra_de_Magos').
ligacao('Caldas_da_Rainha','Olhao').
ligacao('Idanha_a_Nova','Castro_Daire').
ligacao('Porto','Idanha_a_Nova').
ligacao('Oliveira_do_Hospital','Nazare').
ligacao('Lisboa','Aguiar_da_Beira').
ligacao('Vila_Flor','Redondo').
ligacao('Almeida','Monforte').
ligacao('Vendas_Novas','Caldas_da_Rainha').
ligacao('Aljustrel','Vila_Nova_de_Paiva').
ligacao('Beja','Penafiel').
ligacao('Torres_Vedras','Povoa_de_Lanhoso').
ligacao('Oliveira_do_Bairro','Vila_Nova_de_Cerveira').
ligacao('Fundao','Felgueiras').
ligacao('Santo_Tirso','Silves').
ligacao('Reguengos_de_Monsaraz','Vale_de_Cambra').
ligacao('Crato','Portel').
ligacao('Penamacor','Trofa').
ligacao('Esposende','Arouca').
ligacao('Torres_Vedras','Vendas_Novas').
ligacao('Redondo','Peso_da_Regua').
ligacao('Resende','Celorico_da_Beira').
ligacao('Aguiar_da_Beira','Entroncamento').
ligacao('Evora','Viana_do_Alentejo').
ligacao('Albufeira','Ponte_da_Barca').
ligacao('Cabeceiras_de_Basto','Sever_do_Vouga').
ligacao('Avis','Albergaria_a_Velha').
ligacao('Sao_Bras_de_Alportel','Mortagua').
ligacao('Proenca_a_Nova','Sines').
ligacao('Sobral_de_Monte_Agraco','Resende').
ligacao('Terras_de_Bouro','Anadia').
ligacao('Almodovar','Mortagua').
ligacao('Oleiros','Campo_Maior').
ligacao('Vila_Nova_de_Gaia','Castelo_Branco').
ligacao('Gois','Palmela').
ligacao('Peniche','Mortagua').
ligacao('Tavira','Marinha_Grande').
ligacao('Leiria','Pedrogao_Grande').
ligacao('Porto','Viana_do_Alentejo').
ligacao('Coruche','Trofa').
ligacao('Fundao','Arganil').
ligacao('Valenca','Sousel').
ligacao('Ourem','Ferreira_do_Alentejo').
ligacao('Fafe','Lisboa').
ligacao('Lamego','Gois').
ligacao('Marco_de_Canavezes','Valongo').
ligacao('Mangualde','Fafe').
ligacao('Sobral_de_Monte_Agraco','Borba').
ligacao('Pombal','Poiares').
ligacao('Avis','Tabua').
ligacao('Gondomar','Estremoz').
ligacao('Cantanhede','Viana_do_Alentejo').
ligacao('Mora','Esposende').
ligacao('Alcoutim','Lisboa').
ligacao('Sardoal','Arronches').
ligacao('Boticas','Condeixa_a_Nova').
ligacao('Valongo','Penamacor').
ligacao('Faro','Moimenta_da_Beira').
ligacao('Vila_Pouca_de_Aguiar','Gouveia').
ligacao('Moimenta_da_Beira','Aguiar_da_Beira').
ligacao('Boticas','Alvito').
ligacao('Oliveira_de_Frades','Pampilhosa_da_Serra').
ligacao('Silves','Resende').
ligacao('Fafe','Sines').
ligacao('Agueda','Vimioso').
ligacao('Vila_Vicosa','Lousada').
ligacao('Santa_Marta_de_Penaguiao','Vizela').
ligacao('Aguiar_da_Beira','Povoa_de_Varzim').
ligacao('Azambuja','Batalha').
ligacao('Palmela','Batalha').
ligacao('Braga','Palmela').
ligacao('Barcelos','Albufeira').
ligacao('Boticas','Sabrosa').
ligacao('Lousada','Trancoso').
ligacao('Moita','Odivelas').
ligacao('Pinhel','Barrancos').
ligacao('Abrantes','Almeirim').
ligacao('Poiares','Cartaxo').
ligacao('Monchique','Esposende').
ligacao('Borba','Trofa').
ligacao('Peniche','Arronches').
ligacao('Elvas','Almada').
ligacao('Obidos','Cadaval').
ligacao('Ilhavo','Odemira').
ligacao('Cartaxo','Estarreja').
ligacao('Vinhais','Penacova').
ligacao('Mealhada','Moita').
ligacao('Armamar','Penedono').
ligacao('Tomar','Caminha').
ligacao('Sabugal','Vouzela').
ligacao('Odivelas','Fafe').
ligacao('Sintra','Redondo').
ligacao('Monchique','Esposende').
ligacao('Manteigas','Montalegre').
ligacao('Arronches','Pinhel').
ligacao('Oleiros','Cadaval').
ligacao('Valongo','Nisa').
ligacao('Picotos','Manteigas').
ligacao('Guarda','Vimioso').
ligacao('Odemira','Penedono').
ligacao('Maia','Cascais').
ligacao('Vinhais','Alcanena').
ligacao('Portalegre','Penacova').
ligacao('Borba','Tavira').
ligacao('Ovar','Tomar').
ligacao('Arraiolos','Arouca').
ligacao('Chaves','Murtosa').
ligacao('Penamacor','Arronches').
ligacao('Sines','Ovar').
ligacao('Cuba','Mirandela').
ligacao('Montijo','Avis').
ligacao('Almada','Portel').
ligacao('Almada','Guarda').
ligacao('Coruche','Amares').
ligacao('Manteigas','Amadora').
ligacao('Nisa','Borba').
ligacao('Entroncamento','Pombal').
ligacao('Barreiro','Arronches').
ligacao('Cuba','Armamar').
ligacao('Sintra','Mogadouro').
ligacao('Arganil','Estremoz').
ligacao('Pinhel','Alcanena').
ligacao('Chaves','Albufeira').
ligacao('Braga','Braganca').
ligacao('Felgueiras','Moita').
ligacao('Amares','Ovar').
ligacao('Vizela','Albufeira').


