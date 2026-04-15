#ifndef HEAP_HPP
#define HEAP_HPP

#include <functional>

template <typename T>
class Heap {
   public:
    Heap(std::function<bool(const T &, const T &)> compare);
    ~Heap();
    Heap(const Heap &other);
    Heap &operator=(const Heap &other);

    void insert(T value);
    void remove();

    bool empty() const;
    void clear();

    void print() const;

    T getRoot() const;
    int getNumElements() const;
    int getSize() const;

   private:
    void resize();
    void pushDown(int i);
    void pushUp(int i);

    int size;
    int last;
    T *elements;

    std::function<bool(const T &, const T &)> compare;
};

#include "Heap.tpp"

#endif  // HEAP_HPP
