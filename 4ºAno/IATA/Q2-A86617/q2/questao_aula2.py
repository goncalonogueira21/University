import csv
import networkx as nx

# importar a biblioteca matplotlib.pyplot
import matplotlib.pyplot as plt
import collections

from more_itertools import unique_everseen

# open the file

in_file=csv.reader(open('lista_arestas.txt','r'))

g=nx.Graph()
listaux=[]
for line in in_file:
    g.add_edge(line[0],line[1],weight=int(line[2]),conf=int(line[3]))
    listaux.append(line[0])

listaux=list(unique_everseen(listaux))

plt.figure(figsize=(5,5))
nx.draw_networkx(g)
plt.show()


# Distribuição de grau
degree_sequence = sorted([d for n, d in g.degree()], reverse=True)  # degree sequence
degreeCount = collections.Counter(degree_sequence)
deg, cnt = zip(*degreeCount.items())

fig, ax = plt.subplots()
plt.bar(deg, cnt, width=0.80, color="b")

plt.title("Degree Histogram")
plt.ylabel("Count")
plt.xlabel("Degree")
ax.set_xticks([d + 0.4 for d in deg])
ax.set_xticklabels(deg)

# draw graph in inset
plt.axes([0.4, 0.4, 0.5, 0.5])
Gcc = g.subgraph(sorted(nx.connected_components(g), key=len, reverse=True)[0])
plt.axis("off")
plt.show()



# diametro
print("Diâmetro do grafo")
print(nx.diameter(g))


# medidas de distâncias

#distância (menor distância e o seu comprimento)
print(" Comprimento do caminho mais curto entre todos os nodos")
list1 = list(nx.all_pairs_dijkstra_path_length(g))
i = 0
while i < len(list1):
    print(list1[i])
    i += 1



# eccentricity (a maior distância entre um nodo e todos os outros)
print("Maior distancia entre cada nodo e todos os outros")
index = 0
while index < len(listaux):
    print(listaux[index])
    print(nx.eccentricity(g,listaux[index]))
    index += 1

# medidas de centralidade

# centralidade do grau (o número de conecções de um grau para todos os outros)
print("Centralidade do grau")
print(nx.degree_centrality(g))

# eigenvector centrality (o quão importante é um nodo em função de quão bem conectado está)
print("Eigenvector")
print(nx.eigenvector_centrality(g))


# closeness centralidade (importância de um nodo em função da sua proximidade com os outros da rede)
print("closeness centralidade")
print(nx.closeness_centrality(g))

# betweeness centralidade (quantifica quantas vezes um nodo aparece nos caminhos mais curtos entre dois nodos)
print("Betweeness centralidade")
print(nx.betweenness_centrality(g))


pos = nx.spring_layout(g)
betCent = nx.betweenness_centrality(g, normalized=True, endpoints=True)
node_color = [20000.0 * g.degree(v) for v in g]
node_size =  [v * 10000 for v in betCent.values()]
plt.figure(figsize=(10,10))
nx.draw_networkx(g, pos=pos, with_labels=True, node_color=node_color, node_size=node_size )
plt.axis('off')
plt.show()
