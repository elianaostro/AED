# from graph import Graph
from tqdm import tqdm
import numpy as np
import time
import random
from collections import deque, defaultdict
import matplotlib.pyplot as plt

from typing import Optional, Any, List

class Graph:
    """
    Graph class using defaultdict
    """
    def __init__(self):
        self._graph = defaultdict(lambda: {'data': None, 'neighbors': {}, 'from': set()})

    def add_vertex(self, vertex: str, data: Optional[Any]=None) -> None:
        """
        Adds a vertex to the graph
        :param vertex: the vertex name
        :param data: data associated with the vertex
        """
        self._graph[vertex]['data'] = data

    def add_edge(self, vertex1: str, vertex2: str, data: Optional[Any]=None) -> None:
        """
        Adds an edge to the graph
        :param vertex1: vertex1 key
        :param vertex2: vertex2 key
        :param data: the data associated with the edge
        """
        if not self.vertex_exists(vertex1) or not self.vertex_exists(vertex2):
            raise ValueError("The vertices do not exist")
        self._graph[vertex1]['neighbors'][vertex2] = data
        self._graph[vertex2]['from'].add(vertex1)

    def get_neighbors(self, vertex) -> List[str]:
        """
        Get the list of vertex neighbors
        :param vertex: the vertex to query
        :return: the list of neighbor vertices
        """
        return list(self._graph[vertex]['neighbors'].keys())

    def get_vertex_data(self, vertex: str) -> Optional[Any]:
        """
        Gets vertex associated data
        :param vertex: the vertex name
        :return: the vertex data
        """
        return self._graph[vertex]['data']

    def get_edge_data(self, vertex1: str, vertex2: str) -> Optional[Any]:
        """
        Gets the edge data between two vertices
        :param vertex1: the first vertex name
        :param vertex2: the second vertex name
        :return: the edge data
        """
        if self.edge_exists(vertex1, vertex2):
            return self._graph[vertex1]['neighbors'][vertex2]
        raise ValueError("The edge does not exist")

    def print_graph(self) -> None:
        """
        Prints the graph
        """
        for vertex, data in self._graph.items():
            print("Vertex:", vertex)
            print("Data:", data['data'])
            print("Neighbors:", data['neighbors'])
            print("")

    def vertex_exists(self, vertex: str) -> bool:
        """
        Checks if a vertex exists in the graph
        :param vertex: the vertex name
        :return: boolean indicating existence
        """
        return vertex in self._graph

    def edge_exists(self, vertex1: str, vertex2: str) -> bool:
        """
        Checks if an edge exists between two vertices
        :param vertex1: the first vertex name
        :param vertex2: the second vertex name
        :return: boolean indicating existence
        """
        return vertex1 in self._graph and vertex2 in self._graph[vertex1]['neighbors']

    def get_vertexes(self) -> set:
        """
        Gets the set of all vertices in the graph
        :return: set of vertices
        """
        return set(self._graph.keys())

    def get_vertexes_from(self, vertex: str) -> set:
        """
        Gets the set of vertices directly connected from a given vertex
        :param vertex: the vertex name
        :return: set of vertices
        """
        return self._graph[vertex]['from']

    def get_degree(self, vertex: str) -> int:
        """
        Gets the degree of a vertex (number of neighbors)
        :param vertex: the vertex name
        :return: the degree of the vertex
        """
        return len(self._graph[vertex]['neighbors'])
      
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
    visited = set()
    components = []
    for vertex in tqdm(graph.get_vertexes(),total=len(graph.get_vertexes())):
        if vertex not in visited:
            component = dfs(graph, vertex)
            visited.update(component)
            components.append(component)
    return components

def estimacion_caminos_minimos(graph, cantidad_de_muestras):
    start_time = time.time()
    for i in tqdm(range(cantidad_de_muestras),total=cantidad_de_muestras):
        v1 = random.choice(list(graph._graph.keys()))
        bfs(graph, v1)
    total_time = time.time() - start_time
    hours, rem = divmod((total_time / cantidad_de_muestras * 875713), 3600)
    minutes, seconds = divmod(rem, 60)
    days, hours = divmod(hours, 24)
    return total_time, f"{int(days)} dias y {int(hours)}:{int(minutes)}:{int(seconds)}"
    
def contar_triangulos(graph):
    count = 0
    for vertex in tqdm(graph.get_vertexes(),total=len(graph.get_vertexes())):
        for neighbor in graph.get_neighbors(vertex):
            count += len(set(graph.get_neighbors(neighbor)) & set(graph.get_vertexes_from(vertex)))
    return count

def diametro_estimacion(graph, cantidad_de_muestras):
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
    return max_distance
   
def pagerank(graph, iterations=100, damping_factor=0.85, epsilon=1e-6):
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
    return ranks or {} 

def has_cycle_of_size(graph, size, sample_size=100, max_time=120):
    start_time = time.time()
    vertices = random.sample(list(graph.get_vertexes()), sample_size)
    for start_vertex in tqdm(vertices, total=sample_size):
        if time.time() - start_time > max_time:
            return False
        stack = deque([(start_vertex, start_vertex, 1)])  # (current_vertex, previous_vertex, count)
        visited = set([start_vertex])
        while stack:
            current_vertex, previous_vertex, count = stack.pop()
            if count == size:
                if start_vertex in graph.get_neighbors(current_vertex):
                    return True
                continue
            for neighbor in graph.get_neighbors(current_vertex):
                if time.time() - start_time > max_time:
                    return False
                if neighbor != previous_vertex:
                    if count + 1 == size and start_vertex in graph.get_neighbors(neighbor):
                        return True
                    if neighbor not in visited:
                        visited.add(neighbor)
                        stack.append((neighbor, current_vertex, count + 1))
    return False

def max_cycle(graph, max_time_per_cycle=120):
    vertices = graph.get_vertexes()
    max_cycle_length = 0
    start_time = time.time()
    
    def binary_search_time(low, high):
        nonlocal max_cycle_length
        if low > high:
            return
        mid = (low + high) // 2
        if has_cycle_of_size(graph, mid, max_time=max_time_per_cycle):
            max_cycle_length = max(max_cycle_length, mid)
            binary_search_time(mid + 1, high)
        else:
            binary_search_time(low, mid - 1)
    
    binary_search_time(2, len(vertices))
    return max_cycle_length

def ej1():
    start_time = time.time()
    components = connected_components(page_graph_bidirectional)
    print(f"Execution time: {time.time() - start_time}")
    print(f"Number of connected components: {len(components)}")
    largest_component = max(components, key=len)
    print(f"Size of the largest connected component: {len(largest_component)}")

def ej2():
    total_time, time_to_complete = estimacion_caminos_minimos(page_graph, 100)
    print("Tiempo tardado en obtener todos los caminos minimos desde 100 nodos:",total_time,"segundos")
    print("Podemos obtener todos los caminos minimos en aprox:",time_to_complete)

def ej3():
    start_time = time.time()
    triangles_count = contar_triangulos(page_graph)
    print(f"Execution time: {time.time() - start_time}")
    print("La cantidad de triangulos es:",triangles_count)

def ej4():
    start_time = time.time()
    estimated_diameter = diametro_estimacion(page_graph, 100)
    print(f"Execution time: {time.time() - start_time}")
    print("El diametro es:",estimated_diameter)

def ej5():
    start_time = time.time()
    ranks = pagerank(page_graph)
    print(f"Execution time: {time.time() - start_time}")
    sorted_ranks = sorted(ranks.items(), key=lambda x: x[1], reverse=True)[:10]
    for node, rank in sorted_ranks:
        print(f"Node: {node}, PageRank: {rank}")

def ej6():
    start_time = time.time()
    largest_cycle = max_cycle(page_graph)
    print(f"Execution time: {time.time() - start_time}")
    print("El tamaño maximo de la ciclo es:",largest_cycle)

#extra
def aprox_count_polygon_k_sides(graph, start_vertex, k, max_time_per_cycle=120):
    start_time = time.time()
    count = 0
    stack = [(start_vertex, [start_vertex])]
    while stack:
        current_vertex, path = stack.pop()
        neighbors = graph.get_neighbors(current_vertex)
        if len(path) == k - 1:
            count += len(set(neighbors) & set(graph.get_vertexes_from(start_vertex)) - set(path))
            continue
        for neighbor in neighbors:
            if neighbor not in path:
                stack.append((neighbor, path + [neighbor]))
        if time.time() - start_time > max_time_per_cycle:
            break
    return count

def estimate_growth_rate(graph,sample_size=100):
    k_values = list(range(3, 11))
    vertices = random.sample(list(graph.get_vertexes()), sample_size)
    growth_rate = []
    for k in k_values:
        count = 0
        start_time = time.time()
        for start_vertex in vertices:
            count += aprox_count_polygon_k_sides(graph, start_vertex, k)
            if time.time() - start_time > 120:
                break
        growth_rate.append(count / sample_size)
    return growth_rate

def plot_growth_rate(graph):
    growth_rate = estimate_growth_rate(graph)
    plt.plot(range(3, 11), growth_rate)
    plt.xlabel("Number of sides")
    plt.ylabel("Number of polygons")
    plt.show()    

def clustering_coefficient_local(graph, v):
    neighbors = list(graph[v]['neighbors'])
    if len(neighbors) < 2:
        return 0.0
    links = 0
    for i, neighbor in enumerate(neighbors):
        for neighbor2 in neighbors[i+1:]:
            if neighbor2 in graph[neighbor]['neighbors']:
                links += 1
    return 2 * links / (len(neighbors) * (len(neighbors) - 1))

def clustering_coefficient(graph):
    clustering_coeffs = [clustering_coefficient_local(graph, v) for v in graph]
    return sum(clustering_coeffs) / len(clustering_coeffs)

def betweenness_centrality(graph):
    betweenness = {v: 0.0 for v in graph}
    nodes = list(graph.keys())

    for s in nodes:
        stack = []
        predecessors = {w: [] for w in graph}
        sigma = {t: 0.0 for t in graph}
        sigma[s] = 1.0
        distance = {t: -1 for t in graph}
        distance[s] = 0
        queue = deque([s])

        while queue:
            v = queue.popleft()
            stack.append(v)
            for w in graph[v]['neighbors']:
                if distance[w] < 0:
                    queue.append(w)
                    distance[w] = distance[v] + 1
                if distance[w] == distance[v] + 1:
                    sigma[w] += sigma[v]
                    predecessors[w].append(v)

        delta = {v: 0.0 for v in graph}
        while stack:
            w = stack.pop()
            for v in predecessors[w]:
                delta[v] += (sigma[v] / sigma[w]) * (1 + delta[w])
            if w != s:
                betweenness[w] += delta[w]

    for v in betweenness:
        betweenness[v] /= 2.0

    return betweenness

def ej_extra():
    # Extra 1
    start_time = time.time()
    plot_growth_rate(page_graph)
    print(f"Execution time: {time.time() - start_time}")

    # Extra 2
    start_time = time.time()
    clustering = clustering_coefficient(page_graph._graph)
    print(f"Execution time: {time.time() - start_time}")
    print("El coeficiente de clustering es:",clustering)

    # Extra 3
    start_time = time.time()
    betweenness = betweenness_centrality(page_graph._graph)
    print(f"Execution time: {time.time() - start_time}")
    print("El nodo con mayor betweenness centrality es:",betweenness)


def main():
    # ej1()
    # ej2()
    # ej3()
    # ej4()
    # ej5()
    # ej6()

    ej_extra()
    

if __name__ == "__main__":
    main()