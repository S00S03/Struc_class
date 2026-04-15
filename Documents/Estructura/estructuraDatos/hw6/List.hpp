#ifndef LIST_HPP
#define LIST_HPP

template <typename T>
class List {
  public:
    List();
    List(const List &other);
    List &operator=(const List &other);
    ~List();

    const T &operator[](int position) const;
    T &operator[](int position);

    void addFront(const T value);
    void addBack(T value);
    void addAt(T value, int position);

    void removeFront();
    void removeBack();
    void removeAt(int position);

    // All elements that meet a condition (pointer function)
    void remove(bool (*condition)(T value));

    // All occurrences
    void removeAll(T value);

    // All repeated elements
    void removeAllDuplicates();

    void sort();
    void swapList(List<T> &other);

    void transfer(List<T> &other, bool (*condition)(T value));

    // transfer from an index to another
    // transfer from an interval
    // Get all elements
    void transferInInterval(List<T> &other, int start, int end);
    void transferAllElements(List<T> &other);

    bool find(T value) const;
    int getPositionOf(T value) const;

    void modifyElement(T value, int position);

    bool isEmpty() const;
    void makeEmpty();

    void print() const;
    void printReverse() const;

    T getFront() const;
    T getBack() const;
    T &getElementAt(int position) const;
    int getSize() const;

  private:
    void checkValidPosition(int position) const;
    struct Node {
        T value;
        Node *next;
        Node *prev;

        Node(T value, Node *next = nullptr, Node *prev = nullptr)
            : value(value), next(next), prev(prev) {}
    };

    int numNodes;
    Node *head;
    Node *tail;
};

#include "List.tpp"

#endif // !LIST_HPP
