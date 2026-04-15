#ifndef LIST_HPP
#define LIST_HPP

class List {
  public:
    List();
    List(const List &other);
    List &operator=(const List &other);
    ~List();

    void addHead(int value);
    void removeHead();
    void removeAt(int position);

    bool isEmpty() const;
    void makeEmpty();

    void print() const;
    void printReverse() const;
    void printConnections() const;

    int getFront() const;
    int getBack() const;
    int getElementAt(int position) const;
    int getSize() const;

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
};

#endif // !LIST_HPP

