from graph import Graph
from tqdm import tqdm
import numpy as np
import time
import random
from collections import deque, defaultdict
import matplotlib.pyplot as plt

from typing import Optional, Any, List


class Graph:
    """
    Graph class
    """
    def __init__(self):
        self._graph = {}

    def add_vertex(self, vertex: str, data: Optional[Any]=None) -> None:
        """
        Adds a vertex to the graph
        :param vertex: the vertex name
        :param data: data associated with the vertex
        """
        if vertex not in self._graph:
            self._graph[vertex] = {'data': data, 'neighbors': {}, 'to': set(), 'from': set()}

    def add_edge(self, vertex1: str, vertex2: str, data: Optional[Any]=None) -> None:
        """
        Adds an edge to the graph
        :param vertex1: vertex1 key
        :param vertex2: vertex2 key
        :param data: the data associated with the vertex
        """
        if not vertex1 in self._graph or not vertex2 in self._graph:
            raise ValueError("The vertexes do not exist")
        self._graph[vertex1]['neighbors'][vertex2] = data
        self._graph[vertex1]['to'].add(vertex2)
        self._graph[vertex2]['from'].add(vertex1)

    def get_neighbors(self, vertex) -> List[str]:
        """
        Get the list of vertex neighbors
        :param vertex: the vertex to query
        :return: the list of neighbor vertexes
        """
        if vertex in self._graph:
            return self._graph[vertex]['to']
        else:
            return []

    def get_vertex_data(self, vertex: str) -> Optional[Any]:
        """
        Gets  vertex associated data
        :param vertex: the vertex name
        :return: the vertex data
        """
        if self.vertex_exists(vertex):
            return self._graph[vertex]['data']
        else:
            return None

    def get_edge_data(self, vertex1: str, vertex2: str) -> Optional[Any]:
        """
        Gets the vertexes edge data
        :param vertex1: the vertex1 name
        :param vertex2: the vertex2 name
        :return: vertexes edge data
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
        If contains a vertex
        :param vertex: the vertex name
        :return: boolean
        """
        return vertex in self._graph

    def edge_exists(self, vertex1: str, vertex2: str) -> bool:
        """
        If contains an edge
        :param vertex1: the vertex1 name
        :param vertex2: the vertex2 name
        :return: boolean
        """
        return vertex1 in self._graph and vertex2 in self._graph[vertex1]['neighbors']

    def get_vertexes(self) -> set:
        """
        Gets the list of vertexes
        :return: the list of vertexes
        """
        return set(self._graph.keys())
    
    def get_vertexes_from(self, vertex: str) -> set:
        """
        Gets the list of vertexes from a vertex
        :param vertex: the vertex name
        :return: the list of vertexes
        """
        return self._graph[vertex]['from']
    
    def get_degree(self, vertex: str) -> int:
        """
        Gets the degree of a vertex
        :param vertex: the vertex name
        :return: the degree of the vertex
        """
        return len(self._graph[vertex]['neighbors'])
         
    def bfs(self, start_vertex):
        visited = set()
        queue = deque([start_vertex])
        while queue:
            vertex = queue.popleft()
            if vertex not in visited:
                visited.add(vertex)
                queue.extend(self.get_neighbors(vertex) - visited)
        return visited

    def dfs(self, start_vertex):
        visited = set()
        stack = deque([start_vertex])
        while stack:
            vertex = stack.pop()
            if vertex not in visited:
                visited.add(vertex)
                stack.extend(self.get_neighbors(vertex) - visited)
        return visited

    def connected_components(self):
        visited = set()
        components = []
        for vertex in tqdm(self.get_vertexes(),total=len(self.get_vertexes())):
            if vertex not in visited:
                component = self.dfs(vertex)
                visited.update(component)
                components.append(component)
        return components

    def estimacion_caminos_minimos(self, cantidad_de_muestras):
        start_time = time.time()
        for i in tqdm(range(cantidad_de_muestras),total=cantidad_de_muestras):
            v1 = random.choice(list(self._graph.keys()))
            self.bfs(v1)
        total_time = time.time() - start_time
        hours, rem = divmod((total_time / cantidad_de_muestras * 875713), 3600)
        minutes, seconds = divmod(rem, 60)
        days, hours = divmod(hours, 24)
        return total_time, f"{int(days)} dias y {int(hours)}:{int(minutes)}:{int(seconds)}"
        
    def contar_triangulos(self):
        count = 0
        for vertex in tqdm(self.get_vertexes(),total=len(self.get_vertexes())):
            for neighbor in self.get_neighbors(vertex):
                count += len(self.get_neighbors(neighbor) & self.get_vertexes_from(vertex))
        return count

    def diametro_estimacion(self, cantidad_de_muestras):
        max_distance = 0
        for _ in tqdm(range(cantidad_de_muestras),total=cantidad_de_muestras):
            v1 = random.choice(self.get_vertexes())
            distances = {v1: 0}
            queue = deque([v1])
            while queue:
                vertex = queue.popleft()
                for neighbor in self.get_neighbors(vertex):
                    if neighbor not in distances:
                        distances[neighbor] = distances[vertex] + 1
                        max_distance = max(max_distance, distances[neighbor])
                        queue.append(neighbor)
        return max_distance
   
    def pagerank(self, iterations=100, damping_factor=0.85, epsilon=1e-6):
        n = len(self.get_vertexes())
        ranks = {v: 1.0 / n for v in self.get_vertexes()}
        for _ in tqdm(range(iterations), total=iterations):
            new_ranks = {}
            for vertex in self.get_vertexes():
                new_ranks[vertex] = (1 - damping_factor) / n
                for neighbor in self.get_vertexes_from(vertex):
                    new_ranks[vertex] += damping_factor * ranks[neighbor] / self.get_degree(neighbor)
            ranks = new_ranks
            if all(abs(ranks[v] - 1.0 / n) < epsilon for v in self.get_vertexes()):
                break
        return ranks or {} 

    def has_cycle_of_size(self, size, sample_size=50, max_time=120):
        start_time = time.time()
        vertices = random.sample(list(self.get_vertexes()), sample_size)
        for start_vertex in tqdm(vertices, total=sample_size):
            if time.time() - start_time > max_time:
                return False
            stack = deque([(start_vertex, start_vertex, 1)])  # (current_vertex, previous_vertex, count)
            while stack:
                current_vertex, previous_vertex, count = stack.pop()
                if count == size:
                    if start_vertex in self.get_neighbors(current_vertex):
                        return True
                    continue
                for neighbor in self.get_neighbors(current_vertex):
                    if time.time - start_time > max_time:
                        return False
                    if neighbor != previous_vertex:
                        if count + 1 == size and start_vertex in self.get_neighbors(neighbor):
                            return True
                        stack.append((neighbor, current_vertex, count + 1))
        return False

    def max_cycle(self, max_time_per_cycle=120):
        vertices = self.get_vertexes()
        num_vertices = len(vertices)
        max_cycle_length = 0
        
        def binary_search_time(low, high):
            nonlocal max_cycle_length
            while low <= high:
                mid = (low + high) // 2
                if self.has_cycle_of_size(mid, max_time=max_time_per_cycle):
                    max_cycle_length = mid
                    low = mid + 1
                else:
                    high = mid - 1
        
        binary_search_time(2, min(num_vertices, 1000))  # Limitar la búsqueda a un tamaño razonable
        return max_cycle_length
    
    def aprox_count_polygon_k_sides(self, start_vertex, k, max_time_per_cycle=120):
        start_time = time.time()
        count = 0
        stack = [(start_vertex, [start_vertex])]
        while stack:
            current_vertex, path = stack.pop()
            neighbors = self.get_neighbors(current_vertex)
            if len(path) == k - 1:
                count += len(neighbors & self.get_vertexes_from(start_vertex) - set(path))
                continue
            for neighbor in neighbors:
                if time.time() - start_time > max_time_per_cycle:
                    return count
                if neighbor not in path:
                    stack.append((neighbor, path + [neighbor]))
        return count

    def count_polygons_for_k(self, k, sample_size=50):
        vertices = random.sample(list(self.get_vertexes()), sample_size)
        count = 0
        start_time = time.time()
        for start_vertex in tqdm(vertices, desc=f'Counting polygons for k={k}', leave=False):
            count += self.aprox_count_polygon_k_sides(start_vertex, k)
            if time.time() - start_time > 120:
                break
        return count / sample_size

    def estimate_growth_rate(self, sample_size=50):
        lower_bound = 3
        upper_bound = 13000
        iteration_count = 0
        prev_mid_count = None

        while iteration_count < 10:
            mid_point = (lower_bound + upper_bound) // 2
            lower_count = self.count_polygons_for_k(lower_bound, sample_size)
            mid_count = self.count_polygons_for_k(mid_point, sample_size)
            upper_count = self.count_polygons_for_k(upper_bound, sample_size)

            if prev_mid_count is not None and abs(prev_mid_count - mid_count) < 1:
                break
            prev_mid_count = mid_count

            if abs(lower_count - mid_count) > abs(upper_count - mid_count):
                upper_bound = mid_point
            else:
                lower_bound = mid_point

            iteration_count += 1

        growth_rate = []
        for k in tqdm(range(lower_bound, upper_bound + 1, max(1, (upper_bound - lower_bound) // 100)), desc='Estimating growth rate'):
            growth_rate.append(self.count_polygons_for_k(k, sample_size))

        return growth_rate, lower_bound, upper_bound

    def plot_growth_rate(self):
        growth_rate, lower_bound, upper_bound = self.estimate_growth_rate()
        plt.plot(range(lower_bound, upper_bound + 1, max(1, (upper_bound - lower_bound) // 100)), growth_rate)
        plt.xlabel("Number of sides")
        plt.ylabel("Number of polygons")
        plt.show()

    def clustering_coefficient_local(self, v):
        neighbors = self.get_neighbors(v)
        if len(neighbors) < 2:
            return 0.0
        links = 0
        for i, neighbor in enumerate(neighbors):
            for neighbor2 in neighbors[i+1:]:
                if neighbor2 in self.get_neighbors(neighbor):
                    links += 1
        return 2 * links / (len(neighbors) * (len(neighbors) - 1))

    def clustering_coefficient(self):
        clustering_coeffs = [self.clustering_coefficient_local(v) for v in self.get_vertexes()]
        return sum(clustering_coeffs) / len(clustering_coeffs)

    def betweenness_centrality(self, sample_size=100):
        vertices = random.sample(self.get_vertexes(), sample_size)
        betweenness = defaultdict(float)

        for s in tqdm(vertices, total=len(vertices)):
            stack = []
            predecessors = defaultdict(list)
            sigma = defaultdict(float)
            sigma[s] = 1.0
            distance = defaultdict(lambda: -1)
            distance[s] = 0
            queue = deque([s])

            while queue:
                v = queue.popleft()
                stack.append(v)
                for w in self.get_neighbors(v):
                    if distance[w] < 0:
                        queue.append(w)
                        distance[w] = distance[v] + 1
                    if distance[w] == distance[v] + 1:
                        sigma[w] += sigma[v]
                        predecessors[w].append(v)

            delta = defaultdict(float)
            while stack:
                w = stack.pop()
                for v in predecessors[w]:
                    delta[v] += (sigma[v] / sigma[w]) * (1 + delta[w])
                if w != s:
                    betweenness[w] += delta[w]

        for v in betweenness:
            betweenness[v] /= 2.0

        return max(betweenness, key=betweenness.get)
   
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


def ej1():
    start_time = time.time()
    components = page_graph_bidirectional.connected_components()
    print(f"Execution time: {time.time() - start_time}")
    print(f"Number of connected components: {len(components)}")
    largest_component = max(components, key=len)
    print(f"Size of the largest connected component: {len(largest_component)}")

def ej2():
    total_time, time_to_complete = page_graph.estimacion_caminos_minimos(100)
    print("Tiempo tardado en obtener todos los caminos minimos desde 100 nodos:",total_time,"segundos")
    print("Podemos obtener todos los caminos minimos en aprox:",time_to_complete)

def ej3():
    start_time = time.time()
    triangles_count = page_graph.contar_triangulos()
    print(f"Execution time: {time.time() - start_time}")
    print("La cantidad de triangulos es:",triangles_count)

def ej4():
    start_time = time.time()
    estimated_diameter = page_graph.diametro_estimacion(100)
    print(f"Execution time: {time.time() - start_time}")
    print("El diametro es:",estimated_diameter)

def ej5():
    start_time = time.time()
    ranks = page_graph.pagerank()
    print(f"Execution time: {time.time() - start_time}")
    sorted_ranks = sorted(ranks.items(), key=lambda x: x[1], reverse=True)[:10]
    for node, rank in sorted_ranks:
        print(f"Node: {node}, PageRank: {rank}")

def ej6():
    start_time = time.time()
    largest_cycle = page_graph.max_cycle()
    print(f"Execution time: {time.time() - start_time}")
    print("El tamaño maximo de la ciclo es:",largest_cycle)

def ej_extra1():
    start_time = time.time()
    page_graph.plot_growth_rate()
    print(f"Execution time: {time.time() - start_time}")

def ej_extra2():
    start_time = time.time()
    clustering = page_graph.clustering_coefficient()
    print(f"Execution time: {time.time() - start_time}")
    print("El coeficiente de clustering es:",clustering)

def ej_extra3():
    start_time = time.time()
    betweenness = page_graph.betweenness_centrality()
    print(f"Execution time: {time.time() - start_time}")
    print("El nodo con mayor betweenness centrality es:",betweenness)


def main():
    # ej1()
    # ej2()
    # ej3()
    # ej4()
    # ej5()
    ej6()

    ej_extra1()
    # ej_extra2()
    # ej_extra3()
    

if __name__ == "__main__":
    main()