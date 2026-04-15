#include "Stack.hpp"
#include <stdexcept>
#include <iostream>

// Constructor
template <typename T>
Stack<T>::Stack(size_t cap) : capacity(cap), numElements(-1) {
    stack = new T[capacity];
}

template <typename T>
Stack<T>::Stack() : capacity(100), numElements(-1){
    stack = new T[100];
}


// Copy Constructor
template <typename T>
Stack<T>::Stack(const Stack &other)
    : capacity(other.capacity), numElements(other.numElements) {
    stack = new T[capacity];
    for (size_t i = 0; i < numElements; i++) {
        stack[i] = other.stack[i];
    }
}

// Copy Assignment
template <typename T> Stack<T> &Stack<T>::operator=(const Stack &other) {
    if (this != &other) {
        delete[] stack;

        capacity = other.capacity;
        numElements = other.numElements;
        stack = new T[capacity];
        for (size_t i = 0; i < numElements; i++) {
            stack[i] = other.stack[i];
        }
    }
    return *this;
}

// Destructor
template <typename T> Stack<T>::~Stack() { delete[] stack; }

// Add an element to the stack.
template <typename T> void Stack<T>::push(const T &value) {
    if (isFull()) {
        throw std::invalid_argument("Stack is full");
    }
    numElements++;
    stack[numElements] = value;
}

// Remove an element from the stack
template <typename T> void Stack<T>::pop() {
    if (isEmpty()) {
        throw std::invalid_argument("Stack is empty");
    }
    numElements--;
}

// Return the top element
template <typename T> T Stack<T>::top() const { return stack[numElements]; }

// Check if the stack is empty
template <typename T> bool Stack<T>::isEmpty() const {
    return numElements == -1;
}

// Make the stack empty
template <typename T> void Stack<T>::makeEmpty() { numElements = -1; }

template <typename T> void Stack<T>::resize() {
    capacity *= 2;
    int *newStack = new T[capacity];
    for (int i = 0; i < numElements; i++) {
        newStack[i] = stack[i];
    }
    delete[] stack;
    stack = newStack;
}

// check if the stack is full
template <typename T> bool Stack<T>::isFull() const {
    return numElements + 1 == capacity;
}

// Print the stack
template <typename T> void Stack<T>::print() const {
    if (isEmpty()) {
        std::cout << "Stack is empty" << std::endl;
        return;
    }
    for (int i = numElements; i >= 0; i--) {
        std::cout << stack[i] << " ";
    }
    std::cout << std::endl;
}

// Return the size
template <typename T> size_t Stack<T>::getSize() const {
    return numElements + 1;
}
// Return the capacity
template <typename T> size_t Stack<T>::getCapacity() const { return capacity; }
