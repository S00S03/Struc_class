#ifndef ORDERED_LIST_HPP
#define ORDERED_LIST_HPP

#include "List.hpp"

template <typename T>
class OrderedList {
  public:
    void add(T value);

    void remove();

    bool find(T value) const;

    void makeEmpty();
    bool isEmpty() const;

    void printAscending() const;
    void printDescending() const;

    OrderedList<T> merge(const List<T> &list1, const List<T> &list2);

  private:
    List<T> list;
};

#include "OrderedList.tpp"

#endif // !ORDERED_LIST_HPP
