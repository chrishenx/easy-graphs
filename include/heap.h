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

#ifndef HEAP_H
#define HEAP_H

#include <vector>

namespace easy_graphs {

  template <typename T>
  struct Comparator {
    static bool greater(const T& x, const T& y) {
      return x > y;
    }
    static bool less(const T& x, const T& y) {
      return x < y;
    }
  };

  template <typename T>
  struct Comparator < T* > {
    static bool greater(const T* x, const T* y) {
      return *x > *y;
    }
    static bool less(const T* x, const T* y) {
      return *x < *y;
    }
  };

  template <typename T>
  class MinHeap {
  public:
    MinHeap() {
      container.push_back(T());
    }

    MinHeap(std::initializer_list<T> initialValues) {
      container.reserve(initialValues.size());
      container.push_back(T());
      for (const T& value : initialValues) {
        push(value);
      }
    }

    void push(const T& value) {
      container.push_back(value);
      length++;
      up();
    }

    void pop() {
      container[1] = container[length];
      container.pop_back();
      length--;
      down();
    }

    const T& getMin() const { return container[1]; }

    bool empty() const { return length == 0; }

    int size() const { return length; }

    const std::vector<T>& getContainer() const { return container; }
  private:
    std::vector<T> container;
    int length = 0;

    void up() {
      int child = length;
      while (child / 2 > 0 && isMayor(child / 2, child)) {
        swap(child / 2, child);
        child /= 2;
      }
    }

    void down() {
      int parent = 1;
      while (parent <= length / 2.0) {
        int child = parent * 2;
        if (child < length && isMayor(child, child + 1)) {
          child++; // Right child
        }
        if (isMinor(child, parent)) {
          swap(parent, child);
        }
        else {
          break;
        }
        parent = child;
      }
    }

    void swap(int index1, int index2) {
      std::swap(container[index1], container[index2]);
    }

    // checks if container[index1] is mayor than container[index2] 
    bool isMayor(int index1, int index2) const {
      return Comparator<T>::greater(container[index1], container[index2]);
    }

    // checks if container[index1] is minor than container[index2] 
    bool isMinor(int index1, int index2) const {
      return Comparator<T>::less(container[index1], container[index2]);
    }
  };

  // easy_graphs namespace end
}

#endif // HEAP_H
