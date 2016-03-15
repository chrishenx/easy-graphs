#ifndef NEIGHBOR_VERTEX_H
#define NEIGHBOR_VERTEX_H

#include <sstream>
#include <iostream>

namespace easy_graphs {
  template<class T>
  class Vertex;

  template<class T>
  class Graph;

  // neighbour 

  template<class T>
  class NeighborVertex {
      friend class Graph<T>;
      friend class Vertex<T>;
  public:
    NeighborVertex(const NeighborVertex& other) : vertex(other.vertex) {
      weight = other.weight;
    }

    bool operator==(const NeighborVertex& other) {
      return vertex == other.vertex;
    }

  private:
    NeighborVertex(Vertex<T>* const v, int weight = 1) : vertex(v) {
      this->weight = weight;
    }

    Vertex<T>* const vertex;
    int weight;
  };  
  
}

#endif // NEIGHBOR_VERTEX_H
