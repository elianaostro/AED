from graph import Graph
from typing import List

page_graph = Graph()

with open('web-Google.txt', 'r') as file:
    for l in file:
        if "# FromNodeId\tToNodeId" in l:
            break
    for l in file:
        if not l:
            break
        edge = tuple(int(v.replace("\n", "").replace("\t", "")) for v in l.split("\t"))
        for v in edge:
            if not page_graph.vertex_exists(v):
                page_graph.add_vertex(str(v))
        page_graph.add_edge(str(edge[0]), str(edge[1]))

# page_graph.print_graph()

def bfs(graph: Graph, start_vertex: str) -> List[str]:
    """
    Breadth-First Search (BFS) implementation
    :param graph: The graph to search
    :param start_vertex: The starting vertex
    :return: A list of vertices in the order they were visited
    """
    queue = [start_vertex]
    visitados = []
    while queue:
        vertice = queue.pop(0)
        visitados.append(vertice)
        for vecino in graph.get_neighbors(vertice):
            if vecino not in visitados:
                queue.append(vecino)
    return visitados
    
def dfs(graph: Graph, start_vertex: str) -> List[str]:
    """
    Depth-First Search (DFS) implementation
    :param graph: The graph to search
    :param start_vertex: The starting vertex
    :return: A list of vertices in the order they were visited
    """
    stack = [start_vertex]
    visitados = []
    while stack:
        vertice = stack.pop()
        visitados.append(vertice)
        for vecino in graph.get_neighbors(vertice):
            if vecino not in visitados:
                stack.append(vecino)
    return visitados

def shortest_path_bfs(graph: Graph, start: str, end: str) -> List[str]:
    """
    Encuentra el camino más corto entre dos nodos usando BFS
    :param graph: El grafo para buscar
    :param start: El nodo de inicio
    :param end: El nodo de destino
    :return: Una lista de nodos en el camino más corto o un mensaje si no existe un camino
    """
    visited = []
    queue = [[start]]
    if start == end:
        return [start]
    while queue:
        path = queue.pop(0)
        node = path[-1]
        if node not in visited:
            neighbors = graph.get_neighbors(node)
            for neighbor in neighbors:
                new_path = list(path)
                new_path.append(neighbor)
                queue.append(new_path)
                if neighbor == end:
                    return new_path
            visited.append(node)
    return "No existe un camino entre los nodos especificados"

# 1) ¿Cuál es el tamaño de la componente conexa más grande? ¿Cuántas componentes conexas hay?

def largest_connected_component(graph: Graph) -> int:
    """
    Encuentra el tamaño de la componente conexa más grande
    :param graph: El grafo a analizar
    :return: El tamaño de la componente conexa más grande
    """
    visitados = []
    componentes = []
    for v in graph:
        if v not in visitados:
            componente = bfs(graph, v)
            componentes.append(componente)
            visitados.extend(componente)
    return max([len(c) for c in componentes])