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

#ifndef NEIGHBOR_VERTEX_H
#define NEIGHBOR_VERTEX_H

#include <ostream>

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

  // easy_graphs namespace std
}

#endif // NEIGHBOR_VERTEX_H
