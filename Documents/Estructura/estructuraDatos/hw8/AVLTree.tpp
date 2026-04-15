#include <queue>
#include <iostream>
#include "AVLTree.hpp"

// --- PUBLIC METHODS ---

template <typename T>
AVLTree<T>::AVLTree() : nodeCount(0), root(nullptr) {}

template <typename T>
AVLTree<T>::~AVLTree() {
    clear();
}

template <typename T>
AVLTree<T>::AVLTree(const AVLTree& other) : nodeCount(0), root(nullptr) {
    if (other.root) {
        root = copy(other.root);
        nodeCount = other.nodeCount;
    }
}

template <typename T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree& other) {
    if (this != &other) {
        clear();
        if (other.root) {
            root = copy(other.root);
            nodeCount = other.nodeCount;
        }
    }
    return *this;
}

// Inserts a new node
template <typename T>
void AVLTree<T>::insert(const T& value) {
    root = insert(root, value);
}

// Removes a node
template <typename T>
void AVLTree<T>::remove(const T& value) {
    root = remove(root, value);
}

// Searches for a node
template <typename T>
bool AVLTree<T>::search(const T& value) const {
    return search(root, value) != nullptr;
}

// Prints the tree inorder
template <typename T>
void AVLTree<T>::printAscending() const {
    inorder(root);
    std::cout << std::endl;
}

template <typename T>
void AVLTree<T>::printDescending() const {
    descending(root);
    std::cout << std::endl;
}

template <typename T>
void AVLTree<T>::printByHeight() const {
    levelOrder(root);
    std::cout << std::endl;
}

template <typename T>
int AVLTree<T>::getNodeCount() const {
    return nodeCount;
}

template <typename T>
int AVLTree<T>::getHeight(typename AVLTree<T>::Node* node) const {
    return node ? node->height : 0;
}

template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::getRoot() const {
    return root;
}

template <typename T>
void AVLTree<T>::clear() {
    clear(root);
    root = nullptr;
    nodeCount = 0;
}

// --- PRIVATE METHODS ---

template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::insert(Node* node, const T& value) {
    if (!node) {
        nodeCount++;
        return new Node(value);
    }

    if (value < node->value) node->left = insert(node->left, value);
    else if (value > node->value) node->right = insert(node->right, value);
    else return node;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    node->balance = getHeight(node->left) - getHeight(node->right);

    if (node->balance > 1 && value < node->left->value)
        return rotateRight(node);
    if (node->balance < -1 && value > node->right->value)
        return rotateLeft(node);
    if (node->balance > 1 && value > node->left->value) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (node->balance < -1 && value < node->right->value) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::remove(Node* node, const T& value) {
    if (!node) return node;

    if (value < node->value) node->left = remove(node->left, value);
    else if (value > node->value) node->right = remove(node->right, value);
    else {
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            delete node;
            node = temp;
            nodeCount--;
        } else {
            Node* temp = findMin(node->right);
            node->value = temp->value;
            node->right = remove(node->right, temp->value);
        }
    }

    if (!node) return node;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    node->balance = getHeight(node->left) - getHeight(node->right);

    if (node->balance > 1 && node->left->balance >= 0) return rotateRight(node);
    if (node->balance > 1 && node->left->balance < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (node->balance < -1 && node->right->balance <= 0)
        return rotateLeft(node);
    if (node->balance < -1 && node->right->balance > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::search(Node* node,
                                              const T& value) const {
    if (!node) return nullptr;
    if (value == node->value) return node;
    if (value < node->value) return search(node->left, value);
    return search(node->right, value);
}

template <typename T>
void AVLTree<T>::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::findMin(Node* node) const {
    while (node->left) node = node->left;
    return node;
}

// Inorder
template <typename T>
void AVLTree<T>::inorder(Node* node) const {
    if (!node) return;
    inorder(node->left);
    std::cout << node->value << " ";
    inorder(node->right);
}

// Descending
template <typename T>
void AVLTree<T>::descending(Node* node) const {
    if (!node) return;
    descending(node->right);
    std::cout << node->value << " ";
    descending(node->left);
}

// Level
template <typename T>
void AVLTree<T>::levelOrder(Node* node) const {
    if (!node) return;
    std::queue<Node*> q;
    q.push(node);
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        std::cout << current->value << " ";
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
}

// Copies the tree
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::copy(const Node* source) {
    if (!source) return nullptr;

    Node* newRoot = new Node(source->value);
    std::queue<std::pair<const Node*, Node*>> q;
    q.push({source, newRoot});

    while (!q.empty()) {
        auto [src, dest] = q.front();
        q.pop();

        if (src->left) {
            dest->left = new Node(src->left->value);
            q.push({src->left, dest->left});
        }
        if (src->right) {
            dest->right = new Node(src->right->value);
            q.push({src->right, dest->right});
        }

        dest->height = src->height;
    }

    return newRoot;
}

// --- ROTATIONS ---

template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}
