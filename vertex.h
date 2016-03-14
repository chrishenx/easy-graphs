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

#ifndef VERTEX_H
#define VERTEX_H

#include <unordered_map>
#include <cstdint>
#include <ostream>

namespace easy_graphs {
  template<typename VertexType, typename EdgeType>
  class Vertex;

  template<typename VertexType, typename EdgeType>
  class NeighbourVertex;

  template<typename VertexType, typename EdgeType>
  std::ostream& operator<<(std::ostream& os,
    const Vertex<VertexType, EdgeType>& vertex);

  template<typename VertexType, typename EdgeType>
  class Graph;


  template<typename VertexType, typename EdgeType>
  class Vertex {
    friend class Graph < VertexType, EdgeType > ;
    friend class NeighbourVertex < VertexType, EdgeType > ;
    friend std::ostream& operator<<<VertexType, EdgeType>(std::ostream& os,
      const Vertex& vertex);
  public:
    Vertex() = default;
    Vertex(const VertexType& id, int index = 0) : id(id), index(index) {}
    Vertex(const Vertex& other) : id(other.id), neighbours(other.neighbours) {
      index = other.index;
    }
    Vertex(Vertex&& other)
      : id(std::move(other.id)), neighbours(std::move(other.neighbours)) {
      index = other.index;
    }
    Vertex& operator=(const Vertex& other) {
      if (this != &other) {
        index = other.index;
        neighbours = other.neighbours;
        id = other.id;
      }
      return *this;
    }
    Vertex& operator=(Vertex&& other) {
      if (this != &other) {
        index = other.index;
        neighbours = std::move(other.neighbours);
        id = std::move(other.id);
      }
      return *this;
    }
    const VertexType& getId() const {
      return id;
    }
    bool operator<(const Vertex& other) const { return distance < other.distance; }
    bool operator>(const Vertex& other) const { return distance > other.distance; }

  private:
    VertexType id;
    int index;
    bool visited = false;
    int distance = INT32_MAX;
    Vertex* parent = nullptr;
    std::unordered_map < Vertex<VertexType, EdgeType>*,
      NeighbourVertex < VertexType, EdgeType >> neighbours;
  };

  template<typename VertexType, typename EdgeType>
  std::ostream& operator<<(std::ostream& os,
    const Vertex<VertexType, EdgeType>& vertex) {
    os << vertex.id << "    ";
    for (const auto& pair : vertex.neighbours) {
      os << "->  " << pair.second << "   ";
    }
    return os;
  }

  // easy_graphs namespace end
}

#endif // VERTEX_H
