#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>
#include <iostream>

template <typename T> class Stack {
  public:
    Stack(size_t cap);

    Stack(const Stack& stack);
    Stack& operator=(const Stack& other);
    ~Stack();

    void push(const T& value);
    T top() const;
    void pop();
    bool isEmpty() const;
    void makeEmpty();

    size_t getSize() const;
    size_t getCapacity() const;
    void print() const;

  private:
    size_t capacity;
    int numElements;
    T* stack;
    void resize();
    bool isFull() const;
};

// Constructor
template <typename T> Stack<T>::Stack(size_t cap) : capacity(cap), numElements(-1) {
    stack = new T[capacity];
}

// Copy Constructor
template <typename T>
Stack<T>::Stack(const Stack& other) : capacity(other.capacity), numElements(other.numElements) {
    stack = new T[capacity];
    for (size_t i = 0; i < numElements; i++) {
        stack[i] = other.stack[i];
    }
}

// Copy Assignment
template <typename T> Stack<T>& Stack<T>::operator=(const Stack& other) {
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

// Add an element to the stack
template <typename T> void Stack<T>::push(const T& value) {
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
template <typename T> bool Stack<T>::isEmpty() const { return numElements == -1; }

// Make the stack empty
template <typename T> void Stack<T>::makeEmpty() { numElements = -1; }

template <typename T> void Stack<T>::resize() {
    capacity *= 2;
    int* newStack = new T[capacity];
    for (int i = 0; i < numElements; i++) {
        newStack[i] = stack[i];
    }
    delete[] stack;
    stack = newStack;
}

// check if the stack is full
template <typename T> bool Stack<T>::isFull() const { return numElements + 1 == capacity; }

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

template <typename T> size_t Stack<T>::getSize() const { return numElements + 1; }
template <typename T> size_t Stack<T>::getCapacity() const { return capacity; }

#endif // !STACK_HPP
