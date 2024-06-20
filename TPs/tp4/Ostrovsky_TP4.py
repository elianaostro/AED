from graph import Graph
from tqdm import tqdm
import numpy as np
import time
import random
from collections import deque
import matplotlib.pyplot as plt

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
    
def contar_triangulos(graph):
    start_time = time.time()
    count = 0
    for vertex in tqdm(graph.get_vertexes(),total=len(graph.get_vertexes())):
        for neighbor in graph.get_neighbors(vertex):
            count += len(set(graph.get_neighbors(neighbor)) & set(graph.get_vertexes_from(vertex)))
    print(f"Execution time: {time.time() - start_time}")
    return count

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

def diametro_estimacion_dfs(graph, cantidad_de_muestras):
    start_time = time.time()
    max_distance = 0
    for _ in tqdm(range(cantidad_de_muestras),total=cantidad_de_muestras):
        v1 = random.choice(list(graph.get_vertexes()))
        distances = {v1: 0}
        stack = deque([v1])
        while stack:
            vertex = stack.pop()
            for neighbor in graph.get_neighbors(vertex):
                if neighbor not in distances:
                    distances[neighbor] = distances[vertex] + 1
                    max_distance = max(max_distance, distances[neighbor])
                    stack.append(neighbor)
    total_time = time.time() - start_time
    print(f"Execution time: {total_time}")
    return max_distance
    
def pagerank(graph, iterations=100, damping_factor=0.85, epsilon=1e-6):
    start_time = time.time()
    n = len(graph.get_vertexes())
    ranks = {v: 1.0 / n for v in graph.get_vertexes()}
    for _ in tqdm(range(iterations), total=iterations):
        new_ranks = {}
        for vertex in graph.get_vertexes():
            new_ranks[vertex] = (1 - damping_factor) / n
            for neighbor in graph.get_vertexes_from(vertex):
                new_ranks[vertex] += damping_factor * ranks[neighbor] / len(graph.get_neighbors(neighbor))
        ranks = new_ranks
        if all(abs(ranks[v] - 1.0 / n) < epsilon for v in graph.get_vertexes()):
            break
    print(f"Execution time: {time.time() - start_time}")
    return ranks or {} 

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

def has_cycle_of_size(graph, size, max_time=1000):
    start_time = time.time()
    for start_vertex in graph.get_vertexes():
        visited = set()
        stack = deque([(start_vertex, 1)])
        while stack:
            vertex, count = stack.pop()
            if count == size:
                if start_vertex in graph.get_neighbors(vertex):
                    return True
                else:
                    continue
            visited.add(vertex)
            for neighbor in graph.get_neighbors(vertex):
                if neighbor not in visited:
                    stack.append((neighbor, count + 1))
        if time.time() - start_time > max_time:
            return False
    return False
        
def max_clique(graph):
    start_time = time.time()
    maximo = 1000
    minimo = 0
    max_clique = 0
    while maximo - minimo > 1:
        if has_cycle_of_size(graph, (maximo + minimo) // 2):
            max_clique = (maximo + minimo) // 2
            minimo = max_clique
            print(f"Max clique: {max_clique}")
        else:
            maximo = (maximo + minimo) // 2
    print(f"Execution time: {time.time() - start_time}")
    return max_clique

def ej1():
    components = connected_components(page_graph_bidirectional)
    print(f"Number of connected components: {len(components)}")
    largest_component = max(components, key=len)
    print(f"Size of the largest connected component: {len(largest_component)}")

def ej2():
    print("Podemos obtener todos los caminos minimos en aprox:" ,estimacion_caminos_minimos(page_graph, 100))

def ej3():
    print("La cantidad de triangulos es:",contar_triangulos(page_graph))

def ej4():
    print("El diametro es:",diametro_estimacion(page_graph, 100))

def ej5():
    ranks = pagerank(page_graph)
    sorted_ranks = sorted(ranks.items(), key=lambda x: x[1], reverse=True)[:10]
    for node, rank in sorted_ranks:
        print(f"Node: {node}, PageRank: {rank}")

def ej6():
    print("La circunferencia es:",circunferencia_estimacion(page_graph, 100))

def main():
    ej1()
    ej2()
    ej3()
    ej4()
    ej5()
    ej6()

if __name__ == "__main__":
    main()