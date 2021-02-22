#importar a biblioteca
import networkx as nx

# importar a biblioteca matplotlib.pyplot
import matplotlib.pyplot as plt

#criar um grafo simétrico não direcionado
G_symmetric = nx.Graph()

G_symmetric.add_edge('Rodrigo',  'Laura')
G_symmetric.add_edge('Rodrigo',  'Marco')
G_symmetric.add_edge('Rodrigo',  'Rui')
G_symmetric.add_edge('Rodrigo',  'Marta')
G_symmetric.add_edge('Laura',   'Marta')
G_symmetric.add_edge('Marta','Marco')
G_symmetric.add_edge('Jorge',  'Rui')
G_symmetric.add_edge('Jorge',  'Rodrigo')

#print(nx.info(G_symmetric))

# plt.figure(figsize=(5,5))
# nx.draw_networkx(G_symmetric);
# plt.show()

#criar um grafo não simétrico não-direcionado
G_asymmetric = nx.DiGraph()
G_asymmetric.add_edge('A','B')
G_asymmetric.add_edge('A','D')
G_asymmetric.add_edge('C','A')
G_asymmetric.add_edge('D','E')

# plt.figure(figsize=(5,5))
# nx.spring_layout(G_asymmetric)
# nx.draw_networkx(G_asymmetric)
# plt.show()

#criar um grafo pesado, peso == número de projectos
G_weighted = nx.Graph()

G_weighted.add_edge('Rodrigo',  'Laura', weight=25)
G_weighted.add_edge('Rodrigo',  'Marco', weight=8)
G_weighted.add_edge('Rodrigo',  'Rui', weight=11)
G_weighted.add_edge('Rodrigo',  'Marta',weight=1)
G_weighted.add_edge('Laura',   'Marta',weight=1)
G_weighted.add_edge('Marta','Marco',weight=1)
G_weighted.add_edge('Jorge',  'Rui',weight=8)
G_weighted.add_edge('Jorge',  'Rodrigo',weight=4)

# elarge = [(u, v) for (u, v, d) in G_weighted.edges(data=True) if d['weight'] > 8]
# esmall = [(u, v) for (u, v, d) in G_weighted.edges(data=True) if d['weight'] <= 8]
#
# pos = nx.circular_layout(G_weighted)  # posições para todos os nodos
#
# # nodos
# nx.draw_networkx_nodes(G_weighted, pos, node_size=700)
#
# # arestas
# nx.draw_networkx_edges(G_weighted, pos, edgelist=elarge,width=6)
# nx.draw_networkx_edges(G_weighted, pos, edgelist=esmall,width=6, alpha=0.5, edge_color='b', style='dashed')
#
# # labels
# nx.draw_networkx_labels(G_weighted, pos, font_size=20, font_family='sans-serif')
#
# plt.axis('off')
# plt.show();

#clustering coefficient usando nx.clustering(Graph, Node) -> 0.867
#print(nx.clustering(G_symmetric,'Marta'))

#print(nx.average_clustering(G_symmetric))

#medidas de distâncias

#grau -> marta trabalhou com 3 colegas
#print(nx.degree(G_symmetric, 'Marta'))


#distância (menor distância e o seu comprimento)
#print(nx.shortest_path(G_symmetric, 'Marta', 'Rui'))
#print(nx.shortest_path_length(G_symmetric, 'Marta', 'Rui'))


#bfs (a distância de um nodo para todos os outros)
#S = nx.bfs_tree(G_symmetric, 'Rodrigo')
#nx.draw_networkx(S)
#plt.axis('on')
#plt.show()

#eccentricy (a maior distância entre um nodo e todos os outros)
#print(nx.eccentricity(G_symmetric,'Marta'))

#medidas de centralidade

#centralidade do grau (o número de conecções de um grau para todos os outros)
#print(nx.degree_centrality(G_symmetric))

#eigenvector centrality (o quão importante é um nodo em função de quão bem conectado está)
#print(nx.eigenvector_centrality(G_symmetric))

#closeness centralidade (importância de um nodo em função da sua proximidade com os outros da rede)
#print(nx.closeness_centrality(G_symmetric))

#betweeness centralidade (quantifica quantas vezes um nodo aparece nos caminhos mais curtos entre dois nodos)
#print(nx.betweenness_centrality(G_symmetric))

#pos = nx.spring_layout(G_symmetric)
#betCent = nx.betweenness_centrality(G_symmetric, normalized=True, endpoints=True)
#node_color = [20000.0 * G_symmetric.degree(v) for v in G_symmetric]
#node_size =  [v * 10000 for v in betCent.values()]
#plt.figure(figsize=(10,10))
#nx.draw_networkx(G_symmetric, pos=pos, with_labels=True,
#                 node_color=node_color,
#                 node_size=node_size )
#plt.axis('off');
#plt.show()