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

#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <ostream>

namespace easy_graphs {
  
template <class T>
class List;

/**
 * @class Node
 * @brief Nodo de una lista doblemente enlazada.
 * @details Alamacena:
 *          - Un apuntador a un nodo siguiente, si existe, claro.
 *			- Un apuntador a un nodo previo, si existe, claro.
 *          - Un dato/valor, es decir, la informaci�n del nodo.
 * @author Gonz�lez Le�n Christian (chrishenx)
 * @date 09/10/2014
 * @version 1.0
 * @see List
 */
template <class T>
class Node {
	friend class List<T>;
 public:
	Node(const T& val, Node* previous = nullptr, Node* next = nullptr)
		: value(val) {
		this->previous = previous;
		this->next = next;
	}
  Node(T&& val, Node* previous = nullptr, Node* next = nullptr)
		: value(std::move(val)) {
		this->previous = previous;
		this->next = next;
	}
 private:
	T value;
	Node* previous;
	Node* next;
};

/**
 * @class List A double-linked list
 * Allows to:
 * - Constructing a list with a initializer_list object.
 * - Constructing a list with a value repeated n times.
 * - Adding a value at the end.
 * - Adding a list at the end.
 * - Adding a value n times at the end.
 * - Adding a value at the beginning.
 * - Adding a list at the beginning
 * - Adding a value n times at the beginning.
 * - Inserting a value in any position of the list.
 * - Removing the first element.
 * - Removing the last element.
 * - Removing a value in any position.
 * - Acceding to any element.
 * - Concatenating to lists.
 * - Investing the list
 * - Checking if a value is in the list.
 * - Iterating the list with Iterators to obtain a efficient iteration.
 * @author Christian González León (chrishenx)
 * @date 09/10/2014
 */

template <typename T>
class List {
 public:
	class Iterator;

	/**
	 * @brief It constructs an empty list.
	 * @since Version 1.0
	 */
	List() {}
	
  /**
	 * @brief Construye una lista con n elementos con un determinado valor.
	 * @details Complejidad: O(n) -> n = times
	 * @param value Valor inicial de los elementos.
	 * @param times Número de elementos.
	 * @see append(const T&)
   * @see append(T&&)
	 */
	List(const T& value, int times);

	/**
	 * @brief Constructor copia
	 * @details Complejidad: O(n) -> n = número de la lista other.
	 * @param other Lista que será copiada en *this.
	 * @since Version 1.0
	 * @see append(const List&)
	 */
	List(const List& other) { append(other); }

	/**
	 * @brief Constructor para operaciones de movimiento.
	 * @details Complejidad: O(1)
	 * @param other Lista a ser movida a *this.
	 * @details Complejidad
	 * @since Version 1.0
	 * @see append(const List&)
	 * @see clear()
	 */
	List(List&& other);

	/**
	 * @brief Constructor que inicializa la lista con una lista de inicialización.
	 * @details Complejidad : O(n) -> n = número de elementos de la lista de inicialización.
	 * @param il Lista de inicialización.
	 * @since Version 1.0
	 * @see append(const List&)
	 */
	List(std::initializer_list<T> il);

	/**
	 * @brief Limpia todos los elementos de la lista\n:
     * 		  No hay fugas de memoria.
	 * @details Complejidad: O(n) -> n = número de elementos a eliminar de la lista.
	 * @since Version 1.0
	 * @see clear()
	 */
	~List() { clear(); }

	/**
	 * @brief Sobre-escribe la lista con otra lista.
	 * @details Complejidad: O(na + nb) -> na = elementos de *this, nb = elementos de other.
	 * @param other Lista para sobre-escribir a *this.
	 * @since Version 1.0
	 * @see clear()
	 * @see append(const List&)
	 * @see operator=(List&&)
	 */
	List& operator=(const List& other);

	/**
	 * @brief Sobre-escribe la lista con otra lista. Especializado en operaciones de movimiento.
	 * @details Complejidad: O(n) -> n = elementos a eliminar the *this
	 * @param other Lista para sobre-escribir a *this.
	 * @since Version 1.0
	 * @see clear()
	 * @see operator=(const List&)
	 */
	List& operator=(List&& other);

	/**
	 * @brief Inserta un elemento al final de la lista
	 * @details Complejidad: O(1)
	 * @param value Valor del elemento a insertar.
	 * @since Version 1.0
	 * @see append(const T&, int)
	 * @see append(const List&)
	 */
	void append(const T& value);
  void append(T&& value);

	/**
	 * @brief Inserta un elemento al final de la lista n veces
	 * @details Complejidad: O(n) -> n = times
	 * @param value Valor del elemento a insertar.
	 * @param times Número de veces a insertar value.
	 * @since Version 1.0
	 * @see append(const T&)
	 * @see append(const List&)
	 */
	void append(const T& value, int times);

	/**
	 * @brief Inserta, al final, los valores de una lista.
	 * @details Complejidad: O(n) -> n = número de elementos de other
	 * @param other Lista a insertar al final.
	 * @see append(const T&)
	 * @see append(const T&, int)
	 */
	void append(const List& other);

	/**
	 * @brief Inserta un valor al inicio de la lista.
	 * @details Complejidad: O(1)
	 * @param value Valor del elemento a insertar.
	 * @since Version 1.0
	 * @see push_first(const T&, int)
	 * @see push_first(const List&)
	 */
	void push_first(const T& value);
  void push_first(T&& value);

	/**
	 * @brief Inserta un valor al inicio de la lista n veces.
	 * @details Complejidad: O(n) -> n = times
	 * @param value Valor del elemento a insertar.
	 * @param times Número de copias de value.
	 * @since Version 1.0
	 * @see push_first(const T&)
	 * @see push_first(const List&)
	 */
	void push_first(const T& value, int times);

	/**
	 * @brief Inserta una lista al inicio.
	 * @details Complejidad: O(n) -> n = número de elementos de other.
	 * @param other Lista a insertar.
	 * @since Version 1.0
	 * @see push_first(const T&)
	 * @see push_first(const T&, int)
	 */
	void push_first(const List& other);

	/**
	 * @brief Inserta un valor en la lista mediante un indice.
	 * @details Complejidad:
	 *        Peor de lo casos  - O(n/2) -> n = número de elementos la lista
	 *	      Mejor de los casos - O(1)
	 *        Si el indice esta fuera de los límites, no se insertará el elemento.
	 * @param pos Indice/posición donde se desee que se posicione value.
	 * @param value Valor del elemento a insertar.
	 * @return Si el índice no esta fuera de los límites de la lista, true, de lo contrario, false.
	 * @since Version 1.0
	 * @see getNode(int)
	 * @see append(const T&)
	 * @see push_first(const T&)
	 */
	bool insert(int pos, const T& value);

	/**
	 * @brief Remueve todos lo elementos de la lista con un determinado valor.
	 * @details Complejidad: O(n) -> n = número de elementos la lista.
	 * @return Si se eliminó por lo menos un elemento en la lista, true, de lo contrario, false.
	 * @param value Valor que se quiere eliminar de la lista.
	 * @since Version 1.0
	 */
	bool remove(const T& value);

	bool remove_one(const T& value);

	/**
	 * @brief Remueve el último elemento de la lista.
	 * @details Complejidad: O(1)
	 * @return Si hay por lo menos un elemento para eliminar, true, de lo contrario, false.
	 * @since Version 1.0
	 * @see pop_first()
	 */
	bool pop();

    /**
	 * @brief Remueve el primer elemento de la lista.
	 * @details Complejidad: O(1)
	 * @return Si hay por lo menos un elemento para eliminar, true, de lo contrario, false.
	 * @since Version 1.0
	 * @see pop()
	 */
	bool pop_first();

	/**
	 * @brief Remueve algún elimento de la lista mediante un índice.
	 * @details Complejidad:
	 *        Peor de lo casos  - O(n/2) -> n = número de elementos la lista
	 *	      Mejor de los casos - O(1)
	 *        Si el indice esta fuera de los límites, no se eliminará el elemento.
	 * @param pos Posición/índice del elemento a eliminar
	 * @return Si se eliminó el elemento, true, de lo contrario, false.
	 * @since Version 1.0
	 * @see erase(Iterator)
	 * @see rerase(Iterator)
	 */
	bool erase(int pos);

	/**
	 * @brief Remueve el elemento de la lista apuntado por it.
	 * @details Complejidad: O(1)
	 * @param it Iterador apuntando al elemento que se quiere eliminar.
	 * @return Retorna un Iterator apuntando al elemento siguiente del eliminado.
	 *         En caso de que se eliminara el ultimo elemento, se retornará la constante NO_ELEMENT.
	 * @since Version 1.0
	 * @see erase(int)
	 * @see rerase(Iterator)
	 */
	Iterator erase(Iterator it);

	/**
	 * @brief Remueve el elemento de la lista apuntado por it.
	 * @details Complejidad: O(1)
	 * @param it Iterador apuntando al elemento que se quiere eliminar.
	 * @return Retorna un Iterator apuntando al elemento previo del eliminado.
	 *         En caso de que se eliminara el primer elemento, se retornará la constante NO_ELEMENT.
	 * @since Version 1.0
	 * @see erase(int)
	 * @see erase(Iterator)
	 */
	Iterator rerase(Iterator it);

	/**
	 * @brief It deletes all the elements in the list.
	 * @details No memory leaks.\n
	 * Complexity: O(n)
	 * @since Version 1.0
	 * @see pop()
	 */
	void clear();

	/**
	 * @brief It overrides a element in the list.
	 * @details Complexity:
   *	 Worst case: F(n/2) -> O(n)
	 *   Optimal case: F(pos) if pos < n/2.
	 * @param pos Index of the element to override.
	 * @param value Value to set.
	 * @return If the index given is in the list true otherwise false.
	 * @since Version 1.0
	 * @see get(int) const
	 * @see operator[](int)
	 */
	bool set(int pos, const T& value);

	/**
	 * @brief It obtains a reference
	 * @details Complexity:
   *	 Worst case: F(n/2) -> O(n)
	 *   Optimal case: F(pos) -> if pos < n/2
	 * If the index given is not in the list, your program will die!
	 * @param pos Index of the element.
	 * @see set(int, const T&)
	 * @see operator[](int)
	 */
	const T& get(int pos) const;

	/**
	 * @brief It obtains a reference
	 * @details Complexity:
   *	 Worst case: F(n/2) -> O(n)
	 *   Optimal case: F(pos) -> if pos < n/2
	 * If the index given is not in the list, your program will die!
	 * @param pos Index of the element.
	 * @return The element
	 * @see set(int, const T&)
	 * @see get(int) const
	 */
	T& operator[](int pos);

    /**
	 * @brief It obtains a const reference
	 * @details Complexity:
     *	 Worst case: F(n/2) -> O(n)
	 *   Optimal case: F(pos) -> if pos < n/2
	 * If the index given is not in the list, your program will die!
	 * @param pos Index of the element.
	 * @return The element
	 * @see set(int, const T&)
	 * @see get(int) const
	 */
  const T& operator[](int pos) const;

	/**
	 * @brief It inserts a value to the end.
	 * @details Complexity: O(1)
	 * @param value Value of the element to append.
	 * @see append(const T&)
	 * @see operator>>(T&)
	 */
	void operator<<(const T& value) { append(value); }

	/**
	 * @brief It extracts the last element of the list.
	 * @details Complexity: O(1)
	 * @param output Value to override with the value of the las element.
	 * @return If there are elements to extract true otherwise false.
	 * @see pop()
	 * @see operator<<(const T&)
	 */
	bool operator>>(T& output) { 
    output = last->value; 
    return pop();
  }

	/**
	 * @brief It inverts the order of the elements of the list.
	 * @details Complexity: O(n)
	 */
	void reverse();
  
  /**
	 * @brief Returns the list but inverted.
	 * @details Complexity: O(n)
	 */
  List reversed() const;

	/**
	 * @brief It checks if a value is in the list.
	 * @details Complexity:\n
	 * - Worst case: O(n)
	 */
	bool contains(const T& value) const;

	int getLength() const { return length; }

	bool isEmpty() const { return length == 0; }

	/// @return Iterator to the first position of the list.
	Iterator begin() const { return first; }

	/// @return Iterator to NO_ELEMENT
	const Iterator& end() const { return NO_ELEMENT; }

	///	@return Iterator to the last position of the list
	Iterator rbegin() const { return last; }

	
	/// @return Iterator to NO_ELEMENT
	const Iterator& rend() const { return NO_ELEMENT; }

  /// @return Iterator to value, if value is not in the list it returns NO_ELEMENT
	Iterator getIteratorOf(const T& value) const;
 private:
	int length = 0;
	Node<T> * first = nullptr;
	Node<T> * last = nullptr;

	/**
	 * @brief Pointer to some element on the list.
	 * @details Complexity:\n
	 * - Worst case: F(n/2) -> O(n)
	 * - Optimal case: O(1)
	 * @param pos index of the node.
	 * @return Node<T>*
	 */
	Node<T>* getNode(int pos);
  void append(Node<T>* new_node); // Supposing *node is already in memory
  void push_first(Node<T>* new_node); // Supposing *node is already in memory
 public:
	static const Iterator NO_ELEMENT; /// Protects of multiples constructions of Iterator objects pointing to nullptr

	/**
	 * @class Iterator
	 * @brief Simulation of a pointer.
	 */
	class Iterator {
		friend class List<T>;
	 public:

		/// @param content Dirección de nodo.
		Iterator(Node<T>* content) { this->content = content; }
    
		// Pre incremento
		Iterator operator++(int) {
			content = content->next;
			return content;
		}

		// Pre decremento
		Iterator operator--(int) {
			content = content->previous;
			return content;
		}

		// Post incremento
		Iterator operator++() {
			Iterator auxiliar = *this;
			content = content->next;
			return auxiliar;
		}

		// Post decremento
		Iterator operator--() {
			Iterator auxiliar = *this;
			content = content->previous;
			return auxiliar;
		}

		/// Operador de indereccion
		T& operator*() { return content->value; }

		/// Operador de desreferencia
		T* operator->() { return &(content->value); }

		bool operator!=(const Iterator& other) { return content != other.content; }

		bool operator==(const Iterator& other) { return content == other.content; }
	 private:
		Node<T>* content = nullptr; /// Pinter to some node inside the list.
	};
};


// ---------------------------- begin, end, rbegin, rend ----------------------------

// I hate this static instantiation but #C++
template <typename T>
const typename List<T>::Iterator List<T>::NO_ELEMENT = nullptr;

/**
 * @fn List<T>::Iterator begin(const List<T>& list)
 * @brief It does the same that List::begin()
 * @see List::begin()
 */
template <typename T>
typename List<T>::Iterator begin(const List<T>& list) {
	return list.begin();
}

/**
 * @fn List<T>::Iterator end(const List<T>& list)
 * @brief It does the same that List::end()
 * @see List::end()
 */
template <typename T>
typename List<T>::Iterator end(const List<T>& list) {
	return list.end();
}

/**
 * @fn List<T>::Iterator rbegin(const List<T>& list)
 * @brief It does the same that List::rbegin()
 * @see List::rbegin()
 */
template <typename T>
typename List<T>::Iterator rbegin(const List<T>& list) {
	return list.rbegin();
}

/**
 * @fn List<T>::Iterator rend(const List<T>& list)
 * @brief It does the same that List::rend()
 * @see List::rend()
 */
template <typename T>
typename List<T>::Iterator rend(const List<T>& list) {
	return list.rend();
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const List<T>& list) {
  for (const T& value : list) {
    out << value << ' ';
  }
  return out;
}

// ----------------------------------------------------------------------------------
// ---------------------------- Implementation --------------------------------------
// ----------------------------------------------------------------------------------

#include <stdexcept>
#include <iostream>

template <typename T>
class List;

template <typename T>
List<T>::List(const T& value, int times) {
    for (int i = 0; i < length; i++) {
        append(value);
    }
}

template <typename T>
List<T>::List(List<T>&& other) {
    // std::cout << "List move constructor" << std::endl;
    first = other.first;
    last = other.last;
    length = other.length;
    other.first = nullptr;
    other.last = nullptr;
    other.length = 0;
}

template <typename T>
List<T>::List(std::initializer_list<T> il) {
    for (const T& value : il) {
        append(value);
    }
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other) {
    if (this != &other) {
        clear();
        append(other);
    }
    return *this;
}

template <typename T>
List<T>& List<T>::operator=(List<T>&& other) {
    // std::cout << "List move assignment" << std::endl;
    if (this != &other) {
        clear();
        first = other.first;
        last = other.last;
        length = other.length;
        other.first = nullptr;
        other.last = nullptr;
        other.length = 0;
    }
    return *this;
}

template <typename T>
void List<T>::append(Node<T>* new_node) {
    if (length == 0) {
        first = new_node;
        last = new_node;
    } else {
        new_node->next = nullptr;
        new_node->previous = last;
        last->next = new_node;
        last = new_node;
    }
    length++;
}

template <typename T>
void List<T>::append(const T& value) {
    Node<T>* new_node = new Node<T>(value);
    append(new_node);
}

template <typename T>
void List<T>::append(T&& value) {
    Node<T>* new_node = new Node<T>(std::move(value));
    append(new_node);
}


template <typename T>
void List<T>::append(const T& value, int times) {
    for (int i = 0; i < times; i++) {
        append(value);
    }
}

template <typename T>
void List<T>::append(const List<T>& other) {
    for(Node<T>* node = other.first; node != nullptr; node = node->next) {
        append(node->value);
    }
}

template <typename T>
void List<T>::push_first(Node<T>* new_node) {
    if (length == 0) {
        first = new_node;
        last = new_node;
    } else {
        new_node->previous = nullptr;
        new_node->next = first;
        first->previous = new_node;
        first = new_node;
    }
    length++;
}

template <typename T>
void List<T>::push_first(const T& value) {
    Node<T>* new_node = new Node<T>(value);
    push_first(new_node);
}

template <typename T>
void List<T>::push_first(T&& value) {
    Node<T>* new_node = new Node<T>(std::move(value));
    push_first(new_node);
}

template <typename T>
void List<T>::push_first(const T& value, int times) {
    for (int i = 0; i < times; i++) {
        push_first(value);
    }
}

template <typename T>
void List<T>::push_first(const List& other) {
    for(Node<T>* node = other.first; node != nullptr; node = node->next) {
        push_first(node->value);
    }
}

template <typename T>
bool List<T>::insert(int pos, const T& value) {
    if (pos == 0) {
        push_first(value);
    } else if (pos == length - 1) {
        append(value);
    } else {
        Node<T>* node_in_pos = getNode(pos);
        if (not node_in_pos) return false;
        Node<T>* new_node = new Node<T>(value, node_in_pos->previous, node_in_pos);
        node_in_pos->previous->next = new_node;
        node_in_pos->previous = new_node;
        length++;
    }
    return true;
}

template <typename T>
bool List<T>::remove(const T& value) {
    int itemsFound = false;
    for (auto it = Iterator(first); it != NO_ELEMENT; ) {
        if (*it == value) {
            itemsFound = true;
            it = erase(it);
        } else {
            it++;
        }
    }
    return itemsFound;
}

template <typename T>
bool List<T>::remove_one(const T& value) {
    for (auto it = Iterator(first); it != NO_ELEMENT; it++) {
        if (*it == value) {
            it = erase(it);
            return true;
        }
    }
    return false;
}

template <typename T>
bool List<T>::pop() {
    if (length > 0) {
        Node<T>* node_to_delete = last;
        if (length > 1) {
            last->previous->next = nullptr;
            last = last->previous;
        } else {
            last = nullptr;
            first = nullptr;
        }
        delete node_to_delete;
        length--;
        return true;
    }
    return false;
}

template <typename T>
bool List<T>::pop_first() {
    if (length > 0) {
        Node<T>* node_to_delete = first;
        if (length > 1) {
            first->next->previous = nullptr;
            first = first->next;
        } else {
            last = nullptr;
            first = nullptr;
        }
        delete node_to_delete;
        length--;
        return true;
    }
    return false;
}

template <typename T>
bool List<T>::erase(int pos) {
    if (pos == 0) {
        pop_first();
    } else if (pos == length - 1) {
        pop();
    } else {
        Node<T>* node_in_pos = getNode(pos);
        if (not node_in_pos) return false;
        node_in_pos->previous->next = node_in_pos->next;
        node_in_pos->next->previous = node_in_pos->previous;
        delete node_in_pos;
        length--;
    }
    return true;
}

template <typename T>
void List<T>::clear() {
    while (length > 0) {
        pop();
    }
    first = nullptr;
    last = nullptr;
}

template <typename T>
bool List<T>::set(int pos, const T& value) {
    Node<T>* node = getNode(pos);
    if (not node) return false;
    node->value = value;
    return true;
}

template <typename T>
const T& List<T>::get(int pos) const {
    Node<T>* node = getNode(pos);
    return node->value;
}

template <typename T>
T& List<T>::operator[](int pos) {
    Node<T>* node = getNode(pos);
    if (node == nullptr) {
        throw std::out_of_range("Attempting to access to an index out of range");
    }
    return node->value;
}

template <typename T>
const T& List<T>::operator[](int pos) const {
    Node<T>* node = getNode(pos);
    if (node == nullptr) {
        throw std::out_of_range("Attempting to access to an index out of range");
    }
    return node->value;
}

template <typename T>
void List<T>::reverse() {
    if (length > 1) {
        Node<T>* node_to_reverse = first;
        for (int i = 0; i < length; i++) {
            Node<T> * next_node = node_to_reverse->next;
            Node<T> * auxiliar_node = node_to_reverse->previous;
            node_to_reverse->previous = node_to_reverse->next;
            node_to_reverse->next = auxiliar_node;
            node_to_reverse = next_node;
        }
        Node<T>* auxiliar_node = first;
        first = last;
        last = auxiliar_node;
    }
}

template <typename T>
List<T> List<T>::reversed() const {
    List<T> resulting_list;
    for (Node<T>* node = last; node != nullptr; node = node->previous) {
        resulting_list.append(node->value);
    }
    return resulting_list;
}

template <typename T>
bool List<T>::contains(const T& value) const {
    for (Node<T>* node = first; node != nullptr; node = node->next) {
        if (node->value == value) {
            return true;
        }
    }
    return false;
}

template <typename T>
typename List<T>::Iterator List<T>::erase(Iterator it) {
    Node<T>* node = it.content;
    Node<T>* next = node->next;
    if (node != nullptr) {
        if (node->next == nullptr) {
            pop();
            next = nullptr;
        } else if (!node->previous) {
            pop_first();
        } else {
            node->previous->next = node->next;
            node->next->previous = node->previous;
            delete node;
            length--;
        }
        return Iterator(next);
    }
    return NO_ELEMENT;
}

template <typename T>
typename List<T>::Iterator List<T>::rerase(Iterator it) {
    Node<T>* node = it.content;
    Node<T>* previous = node->previous;
    if (node) {
        if (!node->previous) {
            pop_first();
            previous = nullptr;
        } else if (!node->next) {
            pop();
        } else {
            node->previous->next = node->next;
            node->next->previous = node->previous;
            delete node;
            length--;
        }
        return Iterator(previous);
    }
    return NO_ELEMENT;
}

template <typename T>
typename List<T>::Iterator List<T>::getIteratorOf(const T& value) 
const {
    for (auto it = begin(); it != end(); it++) {
        if (*it == value) {
            return it;
        }
    }
    return NO_ELEMENT;
}

template <typename T>
Node<T>* List<T>::getNode(int pos) {
    if (length == 0 or pos < 0 or pos >= length)
        return nullptr;
    int middle = int(length / 2);
    Node<T> * node_to_return = nullptr;
    if (pos <= middle) {
        node_to_return = first;
        for (int i = 0; i < pos; i++) {
            node_to_return = node_to_return->next;
        }
    } else {
        node_to_return = last;
        for (int i = length - 1; i > pos; i--) {
            node_to_return = node_to_return->previous;
        }
    }
    return node_to_return;
}

} // easy_graphs namespace end

#endif // LIST_H
