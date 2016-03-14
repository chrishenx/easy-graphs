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

#include "list.h"
#include <cstddef>
#include <sstream>
#include <iostream>

namespace easy_graphs {

  template<typename VertexType, typename EdgeType>
  std::ostream& operator<<(std::ostream& os,
    const Vertex<VertexType, EdgeType>& vertex);

  template<class T>
  class NeighborVertex;

  template<class T>
  class Graph;

  template<class T>
  class Vertex {
    friend class NeighborVertex<T>;
    friend class Graph<T>;
  public:
      Vertex(const T& _id, size_t index = 0) : id(_id) {
      // std::cout << "Vertex default constructor" << std::endl;
      this->index = index;
    }

    Vertex(const Vertex& other) : id(other.id), neighbors(other.neighbors) {
      index = other.index;
      // std::cout << "Vertex copy constructor" << std::endl;
    }
    
    Vertex(Vertex&& other) 
        : id(std::move(other.id)), neighbors(std::move(other.neighbors)) {
      index = other.index;
      // std::cout << "Vertex move constructor" << std::endl;
    }

    const T& getId() const {
      return id;
    }

    bool operator==(const Vertex& other) const {
      return id == other.id;
    }
    
    bool operator==(const T& other_id) const {
      return id == other_id;
    }

    bool operator<(const Vertex& other) const {
      return distance < other.distance;
    }

    bool operator>(const Vertex& other) const {
      return distance > other.distance;
    }

    std::string str() const {
      std::stringstream os;
      os << id << "    ";
      for (const NeighborVertex<T>& neighbor : neighbors) {
        os << "->  " << neighbor.str() << "   ";
      }
      return os.str();
    }

  private:
    T id;
    size_t index;
    bool visited = false;
    size_t distance = INT32_MAX;
    Vertex* parent = nullptr;
    List<NeighbourVertex<T>> neighbors;
  };

  // easy_graphs namespace end
}

#endif // VERTEX_H
