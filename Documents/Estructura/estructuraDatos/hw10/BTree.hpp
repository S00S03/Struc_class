#ifndef BTREE_HPP
#define BTREE_HPP

template <typename T, int grade = 5>
class BTree {
   private:
    struct Node {
        T key[grade];
        Node* child[grade + 1];
        int numKeys;
    };

    Node* root;
    int totalKeys;

    Node* createNode() const;
    Node* copyNode(Node* node) const;
    void merge(Node* parent, int i, Node* child);
    void split(Node* parent, int i, Node* child);

    void insertNonFull(Node* node, int key);
    void remove(Node* node, int key);

    void printAscending(Node* node) const;
    void printDescending(Node* node) const;
    void clear(Node* node);

   public:
    BTree();
    ~BTree();
    BTree(const BTree& other);
    BTree& operator=(const BTree& other);

    void insert(int key);
    void remove(int key);
    bool search(int key);

    void printAscending() const;
    void printDescending() const;
    void printByLevel() const;

    void clear();

    int getNumKeys() const;
};

#include "BTree.tpp"

#endif  // BTREE_HPP
