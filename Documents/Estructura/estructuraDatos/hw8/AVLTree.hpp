#ifndef AVLTree_HPP
#define AVLTree_HPP

template <typename T>
class AVLTree {
   private:
    struct Node {
        T value;
        int height;
        int balance;

        Node* left;
        Node* right;

        Node(const T& val)
            : value(val), height(1), balance(0), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int nodeCount;

    Node* insert(Node* node, const T& value);
    Node* remove(Node* node, const T& value);
    Node* search(Node* node, const T& value) const;

    void inorder(Node* node) const;
    void descending(Node* node) const;
    void levelOrder(Node* node) const;

    Node* copy(const Node* source);
    Node* findMin(Node* node) const;

    void clear(Node* node);

    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);

   public:
    AVLTree();
    ~AVLTree();
    AVLTree(const AVLTree& other);
    AVLTree& operator=(const AVLTree& other);

    void insert(const T& value);
    void remove(const T& value);
    bool search(const T& value) const;

    void printAscending() const;
    void printDescending() const;
    void printByHeight() const;

    void clear();

    int getNodeCount() const;
    int getHeight(Node* node) const;
    Node* getRoot() const;
};

#include "AVLTree.tpp"

#endif  // AVLTree_HPP

