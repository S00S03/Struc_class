#ifndef SIMPLELIST_HPP
#define SIMPLELIST_HPP

class SimpleList {
  public:
    SimpleList();

    void addFirst(int value);
    void addLast(int value);
    void addIn(int value, int position);

    void removeFirst();
    void removeLast();
    void print();
    int getPositionOf(int value);

  private:
    struct Node {
        int value;
        Node *next;

        Node(int value, Node *next = nullptr) {
            this->value = value;
            this->next = next;
        }
    };
    int numNodes;
    Node *head;
};

#endif // !SIMPLELIST_HPP
