/**
  The MIT License (MIT)

  Copyright (c) 2016 Christian González León

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
  
	Contact the author: chrishendrix24@gmail.com
*/

#ifndef NEIGHBOUR_VERTEX_H
#define NEIGHBOUR_VERTEX_H

#include <ostream>
#include <iostream>

namespace easy_graphs {
  template<typename VertexType, typename EdgeType>
  class Vertex;

  template<typename VertexType, typename EdgeType>
  class Graph;

  template<typename VertexType, typename EdgeType>
  class NeighbourVertex;

  template<typename VertexType, typename EdgeType>
  std::ostream& operator<<(std::ostream& os,
    const NeighbourVertex<VertexType, EdgeType>& neighbour);


  // neighbour 

  template<typename VertexType, typename EdgeType>
  class NeighbourVertex {
    friend class Graph < VertexType, EdgeType > ;
    friend class Vertex < VertexType, EdgeType > ;
    friend std::ostream& operator<<<VertexType, EdgeType>(std::ostream& os,
      const NeighbourVertex& neighbour);
  public:
    NeighbourVertex() = default;
    NeighbourVertex(Vertex<VertexType, EdgeType>* const vertex, const EdgeType& weight)
      : vertex(vertex), weight(weight) {}
    NeighbourVertex(const NeighbourVertex& other)
      : vertex(other.vertex), weight(other.weight) {}
    NeighbourVertex(NeighbourVertex&& other)
      : vertex(other.vertex), weight(std::move(other.weight)) {}
    NeighbourVertex& operator=(const NeighbourVertex& other) {
      if (this != &other) {
        vertex = other.vertex;
        weight = other.weight;
      }
      return *this;
    }
    NeighbourVertex& operator=(NeighbourVertex&& other) {
      if (this != &other) {
        vertex = other.vertex;
        weight = std::move(other.weight);
      }
      return *this;
    }
  private:
    Vertex<VertexType, EdgeType>* vertex = nullptr;
    EdgeType weight;
  };

  template<typename VertexType, typename EdgeType>
  std::ostream& operator<<(std::ostream& os,
    const NeighbourVertex<VertexType, EdgeType>& neighbour) {
    os << neighbour.vertex->getId() << " | " << neighbour.weight;
    return os;
  }

  // easy_graphs namespace std
}

#endif // NEIGHBOUR_VERTEX_H
