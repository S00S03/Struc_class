#ifndef LIST_HPP
#define LIST_HPP

class List {
  public:
    List();
    ~List();

    void add(int value);
    void remove();

    void sort() const;

    void print() const;
    void printReverse() const;

  private:
    struct Node {
        int value;
        Node *next;
        Node *prev;

        Node(int value, Node *next = nullptr, Node *prev = nullptr)
            : value(value), next(next), prev(prev) {}
    };
    int numNodes;
    Node *head;
    Node *tail;
};

#endif // !LIST_HPP
