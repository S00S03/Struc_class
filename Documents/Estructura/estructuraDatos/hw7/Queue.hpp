#ifndef QUEUE_HPP
#define QUEUE_HPP

template <typename T>
class Queue {
  public:
    // Constructor
    Queue();
    // copy constructor
    Queue(const Queue &other);
    // destructor
    ~Queue();
    // operator=
    Queue<T> &operator=(const Queue &other);

    void enqueue(T element);
    void dequeue();

    bool isEmpty() const;
    void makeEmpty();

    void print() const;

    T getFront() const;
    T getBack() const;
    int getNumElements() const;

  private:
    int numElements;
    T *Elements;
};

#include "Queue.tpp"

#endif // !QUEUE_HPP
