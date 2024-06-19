#%% Imports
from graph import Graph
from tqdm import tqdm
import numpy as np
import time
import random
from collections import deque

#%% Cargar Informacion
page_graph = Graph()
page_graph_bidirectional = Graph()

with open('web-Google.txt', 'r') as file:
    for l in file:
        if "# FromNodeId	ToNodeId" in l:
            break
    for l in tqdm(file,total =5105039):
        if not l:
            break
        edge = tuple(int(v.replace("\n", "").replace("\t", "")) for v in l.split("\t"))
        for v in edge:
            if not page_graph.vertex_exists(v):
                page_graph.add_vertex(str(v))
                page_graph_bidirectional.add_vertex(str(v))
        page_graph.add_edge(str(edge[0]), str(edge[1]))
        page_graph_bidirectional.add_edge(str(edge[0]), str(edge[1]))
        page_graph_bidirectional.add_edge(str(edge[1]), str(edge[0]))


#%% ej 1

def bfs(graph, start_vertex):
    visited = set()
    queue = deque([start_vertex])
    while queue:
        vertex = queue.popleft()
        if vertex not in visited:
            visited.add(vertex)
            queue.extend(set(graph.get_neighbors(vertex)) - visited)
    return visited

def dfs(graph, start_vertex):
    visited = set()
    stack = deque([start_vertex])
    while stack:
        vertex = stack.pop()
        if vertex not in visited:
            visited.add(vertex)
            stack.extend(set(graph.get_neighbors(vertex)) - visited)
    return visited

def connected_components(graph):
    start_time = time.time()
    visited = set()
    components = []
    for vertex in tqdm(graph.get_vertexes(),total=len(graph.get_vertexes())):
        if vertex not in visited:
            component = dfs(graph, vertex)
            visited.update(component)
            components.append(component)
    print(f"Execution time: {time.time() - start_time}")
    return components

def ej1():
    components = connected_components(page_graph_bidirectional)
    print(f"Number of connected components: {len(components)}")
    largest_component = max(components, key=len)
    print(f"Size of the largest connected component: {len(largest_component)}")

def estimacion_caminos_minimos(graph, cantidad_de_muestras):
    start_time = time.time()
    for i in tqdm(range(cantidad_de_muestras),total=cantidad_de_muestras):
        v1 = random.choice(list(graph._graph.keys()))
        bfs(graph, v1)
    total_time = time.time() - start_time
    print(f"Execution time: {total_time}")
    hours, rem = divmod((total_time / cantidad_de_muestras * 875713), 3600)
    minutes, seconds = divmod(rem, 60)
    days, hours = divmod(hours, 24)
    return f"{int(days)} dias y {int(hours)}:{int(minutes)}:{int(seconds)}"

def ej2():
    print("Podemos obtener todos los caminos minimos en aprox:" ,estimacion_caminos_minimos(page_graph, 100))

def contar_triangulos(graph):
    start_time = time.time()
    count = 0
    for vertex in tqdm(graph.get_vertexes(),total=len(graph.get_vertexes())):
        for neighbor in graph.get_neighbors(vertex):
            count += len(set(graph.get_neighbors(neighbor)) & set(graph.get_vertexes_from(vertex)))
    print(f"Execution time: {time.time() - start_time}")
    return count

def ej3():
    print("La cantidad de triangulos es:",contar_triangulos(page_graph))

def diametro_estimacion(graph, cantidad_de_muestras):
    start_time = time.time()
    max_distance = 0
    for _ in tqdm(range(cantidad_de_muestras),total=cantidad_de_muestras):
        v1 = random.choice(list(graph.get_vertexes()))
        distances = {v1: 0}
        queue = deque([v1])
        while queue:
            vertex = queue.popleft()
            for neighbor in graph.get_neighbors(vertex):
                if neighbor not in distances:
                    distances[neighbor] = distances[vertex] + 1
                    max_distance = max(max_distance, distances[neighbor])
                    queue.append(neighbor)
    total_time = time.time() - start_time
    print(f"Execution time: {total_time}")
    return max_distance

def ej4():
    print("El diametro es:",diametro_estimacion(page_graph, 100))

def pagerank(graph, iterations, damping_factor):
    start_time = time.time()
    n = len(graph.get_vertexes())
    ranks = {v: 1 / n for v in graph.get_vertexes()}
    for _ in tqdm(range(iterations),total=iterations):
        new_ranks = {}
        for vertex in graph.get_vertexes():
            new_ranks[vertex] = (1 - damping_factor) / n
            for neighbor in graph.get_vertexes_from(vertex):
                new_ranks[vertex] += damping_factor * ranks[neighbor] / len(graph.get_neighbors(neighbor))
        ranks = new_ranks
    print(f"Execution time: {time.time() - start_time}")
    return ranks

def ej5():
    ranks = pagerank(page_graph, 100, 0.85)
    print("PageRank:", ranks)

def circunferencia_estimacion(graph, cantidad_de_muestras):
    start_time = time.time()
    max_distance = 0
    for _ in tqdm(range(cantidad_de_muestras),total=cantidad_de_muestras):
        v1 = random.choice(list(graph.get_vertexes()))
        distances = {v1: 0}
        queue = deque([v1])
        while queue:
            vertex = queue.popleft()
            for neighbor in graph.get_neighbors(vertex):
                if neighbor not in distances:
                    distances[neighbor] = distances[vertex] + 1
                    max_distance = max(max_distance, distances[neighbor])
                    queue.append(neighbor)
    total_time = time.time() - start_time
    print(f"Execution time: {total_time}")
    return max_distance

def ej6():
    print("La circunferencia es:",circunferencia_estimacion(page_graph, 100))

def bfs_until_level(graph, start_vertex, level):
    visited = set()
    queue = deque([(start_vertex, 0)])
    while queue:
        vertex, current_level = queue.popleft()
        if vertex not in visited:
            visited.add(vertex)
            if current_level < level:
                queue.extend((neighbor, current_level + 1) for neighbor in graph.get_neighbors(vertex))
    return visited

def poligonos_k_lados(graph, k):
    start_time = time.time()
    count = 0
    for vertex in tqdm(graph.get_vertexes(),total=len(graph.get_vertexes())):
        for neighbor in graph.get_neighbors(vertex):
            for neighbor2 in graph.get_neighbors(neighbor):
                if vertex in graph.get_neighbors(neighbor2):
                    count += 1
    print(f"Execution time: {time.time() - start_time}")
    return count

def coeficiente_clustering(graph):
    start_time = time.time()
    clustering = {}
    for vertex in tqdm(graph.get_vertexes(),total=len(graph.get_vertexes())):
        neighbors = graph.get_neighbors(vertex)
        if len(neighbors) < 2:
            clustering[vertex] = 0
        else:
            triangles = 0
            for neighbor in neighbors:
                for neighbor2 in graph.get_neighbors(neighbor):
                    if vertex in graph.get_neighbors(neighbor2):
                        triangles += 1
            clustering[vertex] = triangles / (len(neighbors) * (len(neighbors) - 1))
    print(f"Execution time: {time.time() - start_time}")
    return clustering

def betweenness_centrality(graph):
    start_time = time.time()
    betweenness = {v: 0 for v in graph.get_vertexes()}
    for vertex in tqdm(graph.get_vertexes(),total=len(graph.get_vertexes())):
        for vertex2 in graph.get_vertexes():
            if vertex != vertex2:
                paths = 0
                for neighbor in graph.get_neighbors(vertex):
                    if vertex2 in bfs_until_level(graph, neighbor, 2):
                        paths += 1
                betweenness[vertex] += paths / len(graph.get_vertexes())
    print(f"Execution time: {time.time() - start_time}")
    return betweenness

def ej_extra1():
    print("Cantidad de poligonos de 3 lados:",poligonos_k_lados(page_graph, 3))

def ej_extra2():
    clustering = coeficiente_clustering(page_graph)
    print("Coeficiente de clustering:", clustering)

def ej_extra3():
    betweenness = betweenness_centrality(page_graph)
    print("Betweenness centrality:", betweenness)


#%%
def main():
    print("1) ¿Cuál es el tamaño de la componente conexa más grande? ¿Cuántas componentes conexas hay?")
    ej1()
    print("2) Calcular el camino mínimo de todos con todos. ¿En cuanto tiempo lo puede hacer?¿Qué orden tiene el algoritmo? En caso de no alcanzarle el tiempo, estime cuanto tiempo le llevaría.")
    ej2()
    print("3) En un grafo un triángulo es una conexión entre 3 vértices A, B y C donde:\nA está conectado con B\nB está conectado con C\nC está conectado con A\n¿Cuántos triángulos tiene el grafo?")
    ej3()
    print("4) Utilice el punto 2 para calcular el diámetro del grafo.")
    ej4()
    print("5) Google inventó un algoritmo llamado PageRank que le permitía saber qué páginas eran más confiables según que tanto eran referenciadas. PageRank consiste en hacer muchos random walks a lo largo del grafo y contar cuántas veces aparece cada vértice. Los vértices que más aparecen son los de mayor PageRank. Calcule el PageRank de los vértices del grafo.")
    ej5()
    print("6) La circunferencia del grafo es el largo del ciclo más largo. ¿Cuál es la circunferencia del grafo?")
    ej6()
    
    print("Puntos extra:")
    print("1) Programe una función genérica que extendiendo la definición del triángulo calcule la cantidad de polígonos de K lados. Haga un gráfico para mostrar la cantidad de polígonos por cantidad de lados, estimando aquellos que no pueda calcular.")
    
    print("2) Calcule el coeficiente de clustering del grafo")
    print("3) Utilizando el punto 2, ¿cuál es el vértice con más betweenness centrality?")
        

if __name__ == "__main__":
    main()
  
# %%
