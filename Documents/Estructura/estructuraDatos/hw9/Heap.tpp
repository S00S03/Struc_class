#include "Heap.hpp"
#include <iostream>

// --- Public methods ---

// Constructor
template <typename T>
Heap<T>::Heap(std::function<bool(const T&, const T&)> compare)
    : size(5), last(-1), compare(compare) {
    elements = new T[size];
}

// Destructor
template <typename T>
Heap<T>::~Heap() {
    delete[] elements;
}

// Copy constructor
template <typename T>
Heap<T>::Heap(const Heap& other) {
    size = other.size;
    last = other.last;
    elements = new T[size];
    for (int i = 0; i < size; i++) {
        elements[i] = other.elements[i];
    }
}

// Operator =
template <typename T>
Heap<T>& Heap<T>::operator=(const Heap& other) {
    if (this != &other) {
        clear();
        size = other.size;
        last = other.last;
        elements = new T[size];
        for (int i = 0; i < size; i++) {
            elements[i] = other.elements[i];
        }
    }
    return *this;
}

// Inserts a new element
template <typename T>
void Heap<T>::insert(T value) {
    if (last == size - 1) {
        resize();
    }
    last++;
    elements[last] = value;
    pushUp(last);
}

// Removes the root
template <typename T>
void Heap<T>::remove() {
    if (empty()) {
        throw std::runtime_error("The heap is empty");
    }
    elements[0] = elements[last];
    last--;
    pushDown(0);
}

// Checks if the heap is empty
template <typename T>
bool Heap<T>::empty() const {
    return last == -1;
}

// Clears the heap
template <typename T>
void Heap<T>::clear() {
    last = -1;
}

// Prints the heap
template <typename T>
void Heap<T>::print() const {
    if (empty()) {
        std::cout << "The heap is empty" << std::endl;
        return;
    }
    for (int i = 0; i <= last; i++) {
        std::cout << elements[i] << " ";
    }
    std::cout << std::endl;
}

// Returns the root
template <typename T>
T Heap<T>::getRoot() const {
    if (empty()) {
        throw std::runtime_error("The heap is empty");
    }
    return elements[0];
}

// Returns the number of elements
template <typename T>
int Heap<T>::getNumElements() const {
    return last + 1;
}

// Returns the size
template <typename T>
int Heap<T>::getSize() const {
    return size;
}

// --- Private methods ---

// Resizes the heap
template <typename T>
void Heap<T>::resize() {
    size *= 2;
    T* newElements = new T[size];
    for (int i = 0; i <= last; i++) {
        newElements[i] = elements[i];
    }
    delete[] elements;
    elements = newElements;
}

// Pushes the element down
template <typename T>
void Heap<T>::pushDown(int i) {
    int child;
    while ((child = 2 * i + 1) <= last) {
        int right = child + 1;
        if (right <= last && compare(elements[right], elements[child])) {
            child = right;
        }
        if (compare(elements[child], elements[i])) {
            std::swap(elements[i], elements[child]);
            i = child;
        } else {
            break;
        }
    }
}

// Pushes the element up
template <typename T>
void Heap<T>::pushUp(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (compare(elements[i], elements[parent])) {
            std::swap(elements[i], elements[parent]);
            i = parent;
        } else {
            break;
        }
    }
}
