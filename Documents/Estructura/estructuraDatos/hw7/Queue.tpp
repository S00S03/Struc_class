#include <iostream>
#include <stdexcept>

#include "Queue.hpp"

template <typename T>
Queue<T>::Queue() {
    numElements = 0;
    Elements = new T[100];
}
// Copy constructor
template <typename T>
Queue<T>::Queue(const Queue &other) {
    numElements = other.numElements;
    Elements = new T[100];
    for (int i = 0; i < numElements; i++) {
        Elements[i] = other.Elements[i];
    }
}

template <typename T>
Queue<T>::~Queue() {
    delete[] Elements;
    Elements = nullptr;
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue &other) {
    if (this != &other) {
        delete[] Elements;
        numElements = other.numElements;
        Elements = new T[100];
        for (int i = 0; i < numElements; i++) {
            Elements[i] = other.Elements[i];
        }
    }
    return *this;
}

// Inserts an element at the end of the queue
template <typename T>
void Queue<T>::enqueue(T element) {
    Elements[numElements] = element;
    numElements++;
}

// Removes the first element of the queue
template <typename T>
void Queue<T>::dequeue() {
    if (isEmpty()) {
        throw std::invalid_argument("Queue is empty");
    }
    numElements--;
    if (numElements > 1) {
        for (int i = 0; i < numElements; i++) {
            Elements[i] = Elements[i + 1];
        }
    } else {
        Elements[numElements] = 0;
    }
}

template <typename T>
bool Queue<T>::isEmpty() const {
    return numElements == 0;
}

template <typename T>
void Queue<T>::makeEmpty() {
    numElements = 0;
}

template <typename T>
void Queue<T>::print() const {
    for (int i = 0; i < numElements; i++) {
        std::cout << Elements[i];
        if (i < numElements-1) {
            std::cout << "<-";
        }
    }
    std::cout << std::endl;
}

template <typename T>
T Queue<T>::getFront() const {
    return Elements[0];
}

template <typename T>
T Queue<T>::getBack() const {
    return Elements[numElements - 1];
}

template <typename T>
int Queue<T>::getNumElements() const {
    return numElements;
}

