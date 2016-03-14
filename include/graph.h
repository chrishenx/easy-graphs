#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <algorithm>
#include <ostream>
#include <sstream>
#include <cstddef>

#include "vertex.h"
#include "neighbor_vertex.h"

enum class GraphDrawingMode {
    DEFAULT,
    SHOW_DISTANCES
};

typedef std::vector<std::vector<int>> AdjacencyMatrix;

template<class T>
class Graph {
 public:
    // Constructors

  /*
    Copy constructor
    Complexity: Linear on the number of other.vertices plus 
                the number of neighbors of each vertex in other.vertices
   */
  Graph(const Graph& other);
  /*
    Move constructor
    Complexity : Constant - Yeah!
   */
  Graph(Graph&& other);
  /*
    Initializer constructor: Defines the characteristics of the graph
    @param weighted Especifies if the graph is weighted
    @param directed Especifies if the graph is directed
    @param vertices_ids (optional) Initial vertices of the graph  
   */
	Graph(bool weighted, bool directed, 
        const std::initializer_list<T>& vertices_ids = {});
  /*
    Copy assign
    Complexity : Linear on the number of other.vertices plus 
                 the number of neighbors of each vertex in other.vertices
                 plus the cost of clean up the current adjacency matrix
   */
  Graph& operator=(const Graph& other);
  /*
    Move assign
    Complexity : Cost of clean up the current adjacency matrix
   */
  Graph& operator=(Graph&& other);
  
  // Methods for modifying the graph:

  bool newVertex(const T& vertex_id);
  bool deleteVertex(const T& vertex_id);
  bool newEdge(const T& source_id, const T& target_id, int weight = 1);
  bool deleteEdge(const T& source_id, const T& target_id);

  /*
    Deletes all the neighbour vertices of the given vertex 
    Complexity : Cost of a linear seach through the vertices plus
                 the number of neighbors to destroy 
   */
  bool clearVertex(const T& vertex_id) {
    return clearVertex(Vertex<T>(vertex_id));
  }

  /*
    Deletes every vertex in the graph
    All vertex has its own list of neighbors which are destroied also
   */
  void clearAll() {
    vertices.clear();
    degree = 0;
  }

  /* 
    Method to read an adjacency matrix wich has to have the same rank as
    the degree of the graph
   */
  bool readAdjacencyMatrix(const AdjacencyMatrix& adjacencyMatrix);

  /*
    Method to obtain the adjacancy matrix of the current graph
    The order in which appear the elements of the matrix, is the order
    in which are the element in the adjacency list
   */
  AdjacencyMatrix obtainAdjacencyMatrix();

  // Useful method to obtaing the dot description of the graph 
  std::string dotRepr(GraphDrawingMode drawing_mode = 
          GraphDrawingMode::DEFAULT) const;

  // The returned string contains all vertices followed by their neighbors
  std::string str() const {
    std::ostringstream ss;
    for (const Vertex<T>& vertex : vertices) {
        ss << vertex.str() << std::endl;
    }
    return ss.str();
  }
  
  Graph bfs(const T& root_id) {
    Graph resulting_tree(false, true);
    auto it = getIteratorOf(root_id);
    if (it != end(vertices)) {
      bfs(&(*it), resulting_tree);
    }
    return resulting_tree;
  }

  Graph dfs(const T& root_id) {
    Graph resulting_tree(false, true);
    auto it = getIteratorOf(root_id);
    if (it != end(vertices)) {
      dfs(&(*it), resulting_tree);
    }
    return resulting_tree;
  }

  Graph prim(const T& root_id) {
    Graph min_expansion_tree(true, true);
    auto it = getIteratorOf(root_id);
    if (it != end(vertices)) {
      prim(&(*it), min_expansion_tree);
    }
    return min_expansion_tree;
  }

  void dijkstra(const T& source_id) {
    auto it = getIteratorOf(source_id);
    if (it != end(vertices)) {
      resetVerticesFields();
      dijkstra(&(*it));
    }
  }

  List<T> dijkstra(const T& source_id, const T& target_id, int& distance) {
    auto s_it = getIteratorOf(source_id);
    auto t_it = getIteratorOf(target_id);
    if (s_it != end(vertices) and t_it != end(vertices)) {
      resetVerticesFields();
      List<T> path;
      distance = dijkstra(&(*s_it), &(*t_it), path);
      return path;
    }
    distance = -2; // source_id or target_id do not exist
    return {};
  }

  List<std::string> bfs_animation(const T& root_id) {
    List<std::string> animation;
    auto it = getIteratorOf(root_id);
    if (it != end(vertices)) {
      bfs_animation(&(*it), animation);
    }
    return animation;
  }

  List<std::string> dfs_animation(const T& root_id) {
    List<std::string> animation;
    auto it = getIteratorOf(root_id);
    if (it != end(vertices)) {
      dfs_animation(&(*it), animation);
    }
    return animation;
  }

  List<std::string> dijkstra_animation(const T& source_id) {
    List<std::string> animation;
    auto it = getIteratorOf(source_id);
    if (it != end(vertices)) {
      resetVerticesFields();
      dijkstra_animation(&(*it), animation);
    }
    return animation;
  }

private:
  // bool newVertex(const Vertex<T>& vertex);
  // bool newEdge(const Vertex<T>& source, const Vertex<T>& target, int weight = 1);
  // bool deleteVertex(const Vertex<T>& vertex);
  // bool deleteEdge(const Vertex<T>& source, const Vertex<T>& target);
  bool clearVertex(const Vertex<T>& vertex);
  void resetVerticesFields();
  void reconstructPath(Vertex<T>* current, Vertex<T>* source, 
                       List<T>& path) const; // path most be empty
  
  void bfs(Vertex<T>* root, Graph& resulting_tree);
  void dfs(Vertex<T>* root, Graph& resulting_tree);
  void prim(Vertex<T>* root, Graph& min_expansion_tree);
  void dijkstra(Vertex<T>* source);
  int dijkstra(Vertex<T>* source, Vertex<T>* target, List<T>& path);

  void bfs_animation(Vertex<T>* root, List<std::string>& animation);
  void dfs_animation(Vertex<T>* root, List<std::string>& animation);
  void dijkstra_animation(Vertex<T>* source, List<std::string>& animation);

  typename List<Vertex<T>>::Iterator getIteratorOf(const T& vertex_id) const;
  
  bool weighted;
  bool directed;
  List<Vertex<T>> vertices; // Adjancecy list 
  size_t degree = 0;
};

// ----------------- IMPLEMENTATION --------------------


#include "heap.h"

#include <iostream> // TODO Delete after testing

template <typename T>
class Graph;

template <typename T>
Graph<T>::Graph(bool weighted, bool directed,
                const std::initializer_list<T>& vertices_ids) {
    degree = vertices_ids.size();
    int i = 0;
    for (const T& id : vertices_ids) {
        vertices.append(Vertex<T>(id, i));
        i++;
    }
    degree = vertices.getLength();
    this->weighted = weighted;
    this->directed = directed;
}

template <typename T>
Graph<T>::Graph(const Graph<T>& other) : vertices(other.vertices) {
    weighted = other.weighted;
    directed = other.directed;
    degree = other.degree;
    std::cout << "Graph copy constructor" << std::endl;
}

template <typename T>
Graph<T>::Graph(Graph<T>&& other) : vertices(std::move(other.vertices)) {
    weighted = other.weighted;
    directed = other.directed;
    degree = other.degree;
    other.degree = 0;
    std::cout << "Graph move constructor" << std::endl;
}

template <typename T>
Graph<T>& Graph<T>::operator=(const Graph& other) {
    if (this != &other) {
        vertices = other.vertices;
        weighted = other.weighted;
        directed = other.directed;
        degree = other.degree;
        std::cout << "Graph copy assignation" << std::endl;
    }
    return *this;
}

template <typename T>
Graph<T>& Graph<T>::operator=(Graph&& other) {
    if (this != &other) {
        vertices = std::move(other.vertices);
        weighted = other.weighted;
        directed = other.directed;
        degree = other.degree;
        other.degree = 0;
        std::cout << "Graph move assignation" << std::endl;
    }
    return *this;
}

template <typename T>
bool Graph<T>::newVertex(const T& vertex_id) {
    auto it = getIteratorOf(vertex_id);
    if (it == end(vertices)) { // the vertex is added if it isn't inside the vector
        vertices.append(Vertex<T>(vertex_id, degree));
        degree++;
        return true;
    }
    return false;
}

template <typename T>
bool Graph<T>::deleteVertex(const T& vertex_id) {
    auto vertex_it = getIteratorOf(vertex_id);
    if (vertex_it != end(vertices)) {
        int k = 0;
        for (auto it = begin(vertices); it != end(vertices); it++, k++) {
            it->neighbors.remove_one(NeighborVertex<T>(&(*vertex_it)));
            it->index = k;
            if (k == vertex_it->index) k--;
        }
        vertices.erase(vertex_it);
        degree--;
    }
    return false;
}

template <typename T>
bool Graph<T>::newEdge(const T& source_id, const T& target_id, int weight) {
    auto source_it = getIteratorOf(source_id);
    auto target_it = getIteratorOf(target_id);
    if (source_it != end(vertices) and target_it != end(vertices)) {
        source_it->neighbors.append(NeighborVertex<T>(&(*target_it), weight));
        if (!directed) {
            target_it->neighbors.append(NeighborVertex<T>(&(*source_it), weight));
        }
        return true;
    }
    return false;
}

template <typename T>
bool Graph<T>::deleteEdge(const T& source_id, const T& target_id) {
    auto s_it = vertices.getIteratorOf(source_id);
    auto t_it = vertices.getIteratorOf(target_id);
    if (s_it != end(vertices) and t_it != end(vertices)) {
        s_it->neighbors.remove_one(NeighborVertex<T>(&(*t_it)));
        if (!directed) {
            t_it->neighbors.remove_one(NeighborVertex<T>(&(*s_it)));
        }
        return true;
    }
    return false;
}

template <typename T>
bool Graph<T>::clearVertex(const Vertex<T>& vertex) {
    auto it = vertices.getIteratorOf(vertex);
    if (it != end(vertices)) {
        it->neighbors.clear();
        return true;
    }
    return false;
}

template <typename T>
void Graph<T>::resetVerticesFields() {
    for (Vertex<T>& vertex : vertices) {
        vertex.visited = false;
        vertex.distance = INT32_MAX;
        vertex.parent = nullptr;
    }
}

template <typename T>
void Graph<T>::reconstructPath(Vertex<T>* current, Vertex<T>* source,
                               List<T>& path) const {
    while (current != source) {
        path.push_first(current->id);
        current = current->parent;
    }
    path.push_first(current->id);
}

template<class T>
bool Graph<T>::readAdjacencyMatrix(const AdjacencyMatrix& adjacencyMatrix) {
    int degree = adjacencyMatrix.size();
    if (degree != this->degree) {
        return false; // Degree of the matrix and degree of the graph most be equal
    }
    for (const std::vector<int>& row : adjacencyMatrix) {
        if (row.size() != degree) {
            return false; // The matrix is not squared
        }
    }
    // At this point the matrix accomplish the requirements
    int i = 0;
    for (Vertex<T>& vertex: vertices) {
        if (!vertex.neighbors.isEmpty()) {
            vertex.neighbors.clear();
        }
        for (int j = 0; j < degree; j++) {
            if (adjacencyMatrix[i][j] != 0) {
                vertex.neighbors.append(
                                         NeighborVertex<T>(&vertices[j], adjacencyMatrix[i][j])
                                         );
            }
        }
        i++;
    }
    return true;
}

template <class T>
AdjacencyMatrix Graph<T>::obtainAdjacencyMatrix() {
    AdjacencyMatrix adjacencyMatrix;
    for (int i = 0; i < degree; i++) {
        auto it = begin(vertices[i].neighbors);
        if (it == end(vertices[i - 1].neighbors)) { // The vertex hasn't neighbors
            adjacencyMatrix.push_back(std::vector<int>(degree, 0));
        } else {
            adjacencyMatrix.push_back(std::vector<int>());
            for (int j = 0, index = it->vertex->index; j < degree; j++) {
                if (j != index) {
                    adjacencyMatrix[i].push_back(0);
                } else {
                    adjacencyMatrix[i].push_back(weighted ? it->weight : 1);
                    it++;
                    if (it != end(vertices[i].neighbors))  {
                        index = it->vertex->index;
                    }
                }
            }
        }
    }
    return adjacencyMatrix;
}

template <class T>
void Graph<T>::bfs(Vertex<T>* root, Graph& resulting_tree) {
    List<Vertex<T>*> queue = {root};
    root->visited = true;
    while (!queue.isEmpty()) {
        Vertex<T>* first = queue[0];
        queue.pop_first();
        for (NeighborVertex<T>& neighbour : first->neighbors) {
            resulting_tree.newVertex(first->id);
            if (!neighbour.vertex->visited) {
                resulting_tree.newVertex(neighbour.vertex->id);
                resulting_tree.newEdge(first->id, neighbour.vertex->id);
                queue.append(neighbour.vertex);
                neighbour.vertex->visited = true;
            }
        }
    }
    resetVerticesFields();
}

template <class T>
void Graph<T>::dfs(Vertex<T>* root, Graph& resulting_tree) {
    List<Vertex<T>*> stack = {root};
    root->visited = true;
    while (!stack.isEmpty()) {
        Vertex<T>* first = stack[stack.getLength() - 1];
        stack.pop();
        for (NeighborVertex<T>& neighbour : first->neighbors) {
            resulting_tree.newVertex(first->id);
            if (!neighbour.vertex->visited) {
                resulting_tree.newVertex(neighbour.vertex->id);
                resulting_tree.newEdge(first->id, neighbour.vertex->id);
                stack.append(neighbour.vertex);
                neighbour.vertex->visited = true;
            }
        }
    }
    resetVerticesFields();
}

template <typename T>
void Graph<T>::prim(Vertex<T>* root, Graph& min_expansion_tree) {
    root->distance = 0;
    MinHeap<Vertex<T>*> min_heap = {root};
    while (not min_heap.isEmpty()) {
        Vertex<T>* best = min_heap.getMin();
        min_heap.pop();
        best->visited = true;
        for (NeighborVertex<T>& neighbour : best->neighbors) {
            if (neighbour.weight < neighbour.vertex->distance and
                not neighbour.vertex->visited) {
                neighbour.vertex->distance = neighbour.weight;
                neighbour.vertex->parent = best;
                min_heap.push(neighbour.vertex);
            }
        }
    }
    for (const Vertex<T>& vertex : vertices) {
        if (vertex.parent != nullptr and vertex.visited) {
            min_expansion_tree.newVertex(vertex.id);
            min_expansion_tree.newVertex(vertex.parent->id);
            min_expansion_tree.newEdge(
                                       vertex.parent->id, vertex.id, vertex.distance
                                       );
        }
    }
    resetVerticesFields();
}

template <typename T>
void Graph<T>::dijkstra(Vertex<T>* source) {
    source->distance = 0;
    MinHeap<Vertex<T>*> min_heap = {source};
    while (not min_heap.isEmpty()) {
        const Vertex<T>* best = min_heap.getMin();
        min_heap.pop();
        for (NeighborVertex<T>& neighbour : best->neighbors) {
            if (neighbour.weight + best->distance < neighbour.vertex->distance) {
                neighbour.vertex->distance = neighbour.weight + best->distance;
                min_heap.push(neighbour.vertex);
            }
        }
    }
}

template <typename T>
int Graph<T>::dijkstra(Vertex<T>* source, Vertex<T>* target, List<T>& path) {
    source->distance = 0;
    MinHeap<Vertex<T>*> min_heap = {source};
    while (not min_heap.isEmpty()) {
        Vertex<T>* best = min_heap.getMin();
        min_heap.pop();
        if (best == target) {
            reconstructPath(best, source, path);
            return best->distance;
        }
        for (NeighborVertex<T>& neighbour : best->neighbors) {
            if (neighbour.weight + best->distance < neighbour.vertex->distance) {
                neighbour.vertex->distance = neighbour.weight + best->distance;
                neighbour.vertex->parent = best;
                min_heap.push(neighbour.vertex);
            }
        }
    }
    return -1; // No path finded
}

template <typename T>
void Graph<T>::bfs_animation(Vertex<T>* root, List<std::string>& animation) {
    std::stringstream ss;
    ss << "digraph {\n";
    List<Vertex<T>*> queue = {root};
    root->visited = true;
    ss << "\t\"" << root->id << "\"\n";
    animation.append(ss.str() += '}');
    while (!queue.isEmpty()) {
        Vertex<T>* first = queue[0];
        queue.pop_first();
        for (NeighborVertex<T>& neighbour : first->neighbors) {
            if (!neighbour.vertex->visited) {
                ss << "\t\"" << first->id << "\" -> \"" << neighbour.vertex->id << "\"\n";
                queue.append(neighbour.vertex);
                neighbour.vertex->visited = true;
                animation.append(ss.str() += '}');
            }
        }
    }
    resetVerticesFields();
}

template <class T>
void Graph<T>::dfs_animation(Vertex<T>* root, List<std::string>& animation) {
    List<Vertex<T>*> stack = {root};
    std::stringstream ss;
    ss << "digraph {\n";
    root->visited = true;
    ss << "\t\"" << root->id << "\"\n";
    animation.append(ss.str() += '}');
    while (!stack.isEmpty()) {
        Vertex<T>* first = stack[stack.getLength() - 1];
        stack.pop();
        for (NeighborVertex<T>& neighbour : first->neighbors) {
            if (!neighbour.vertex->visited) {
                ss << "\t\"" << first->id << "\" -> \"" << neighbour.vertex->id << "\"\n";
                stack.append(neighbour.vertex);
                neighbour.vertex->visited = true;
                animation.append(ss.str() += '}');
            }
        }
    }
    resetVerticesFields();
}

template <typename T>
void Graph<T>::dijkstra_animation(Vertex<T>* source,
                                  List<std::string>& animation) {
    source->distance = 0;
    MinHeap<Vertex<T>*> min_heap = {source};
    animation.append(dotRepr(GraphDrawingMode::SHOW_DISTANCES));
    while (not min_heap.isEmpty()) {
        const Vertex<T>* best = min_heap.getMin();
        min_heap.pop();
        for (NeighborVertex<T>& neighbour : best->neighbors) {
            if (neighbour.weight + best->distance < neighbour.vertex->distance) {
                neighbour.vertex->distance = neighbour.weight + best->distance;
                min_heap.push(neighbour.vertex);
                animation.append(dotRepr(GraphDrawingMode::SHOW_DISTANCES));
            }
        }
    }
}

template <typename T> typename List<Vertex<T>>::Iterator
Graph<T>::getIteratorOf(const T& vertex_id) const {
    for (auto it = begin(vertices); it != end(vertices); it++) {
        if (it->id == vertex_id) {
            return it;
        }
    }
    return List<Vertex<T>>::NO_ELEMENT;
}

template <class T>
std::string Graph<T>::dotRepr(GraphDrawingMode drawingMode) const {
    if (degree == 0) return {};
    
    std::stringstream ss;
    ss << (directed ? "digraph " : "strict graph ") << " {\n";
    
    for (const Vertex<T>& vertex : vertices) {
        if (vertex.neighbors.isEmpty()) {
            ss << "\t\"" << vertex.id << "\"" << std::endl;
        } else {
            for (const NeighborVertex<T>& neighbor : vertex.neighbors) {
                // This switch it's so dirty.
                switch (drawingMode) {
                    case GraphDrawingMode::DEFAULT:
                        ss << "\t\"" << vertex.id;
                        ss << (directed ? "\" -> \"" : "\" -- \"") << neighbor.vertex->id << "\"  [";
                        if (weighted) {
                            ss << "taillabel = \"" << neighbor.weight << "\", ";
                        }
                        break;
                    case GraphDrawingMode::SHOW_DISTANCES:
                        ss << "\t\"" << vertex.id << " | ";
                        if (vertex.distance == INT32_MAX) {
                            ss << "inf";
                        } else {
                            ss << vertex.distance;
                        }
                        ss << (directed ? "\" -> \"" : "\" -- \"") << neighbor.vertex->id << " | ";
                        if (neighbor.vertex->distance == INT32_MAX) {
                            ss << "inf";
                        } else {
                            ss << neighbor.vertex->distance;
                        }
                        ss << "\" [";
                        if (weighted) {
                            ss << "taillabel = \"" << neighbor.weight << "\", ";
                        }
                        break;
                }
                ss << "labeldistance = 1.5]" << std::endl;
            }
        }
    }
    ss << "}";
    return ss.str();
}

#endif // GRAPH_H
