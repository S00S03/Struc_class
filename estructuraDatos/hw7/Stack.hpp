#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>

template <typename T> class Stack {
  public:
    Stack();
    Stack(size_t cap);

    Stack(const Stack &stack);
    Stack &operator=(const Stack &other);
    ~Stack();

    void push(const T &value);
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
    T *stack;
    void resize();
    bool isFull() const;
};

#include "Stack.tpp"

#endif // !STACK_HPP
