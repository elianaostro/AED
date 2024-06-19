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

#%% funciones 1

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
    for vertex in tqdm(graph._graph.keys(),total=875713):
        if vertex not in visited:
            component = dfs(graph, vertex)
            visited.update(component)
            components.append(component)
    print(f"Execution time: {time.time() - start_time}")
    return components
#%% ej 1
components = connected_components(page_graph_bidirectional)
print(f"Number of connected components: {len(components)}")
largest_component = max(components, key=len)
print(f"Size of the largest connected component: {len(largest_component)}")
# %% funciones 2
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
# %% ej 2
print(estimacion_caminos_minimos(page_graph, 10))
# %% funciones 3
def contar_triangulos(graph):
    count = 0
    for vertex in tqdm(graph._graph.keys(),total=len(graph._graph.keys())):
        for neighbor in graph.get_neighbors(vertex):
            for neighbor2 in graph.get_neighbors(neighbor):
                count += graph.edge_exists(neighbor2, vertex)
    return count


# %% ej 3
print(contar_triangulos(page_graph))
# %% ej 4
degrees = [len(page_graph.get_neighbors(vertice)) for vertice in page_graph._graph.keys()]

