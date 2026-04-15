#include "BTree.hpp"
#include <iostream>
#include <queue>

// --- Public methods ---

// Constructor
template <typename T, int grade>
BTree<T, grade>::BTree() : root(nullptr), totalKeys(0){};

// Destructor
template <typename T, int grade>
BTree<T, grade>::~BTree() {
    clear();
}

// Copy constructor
template <typename T, int grade>
BTree<T, grade>::BTree(const BTree& other) {
    root = copyNode(other.root);
    totalKeys = other.totalKeys;
}

// Operator =
template <typename T, int grade>
BTree<T, grade>& BTree<T, grade>::operator=(const BTree& other) {
    if (this != &other) {
        clear();
        root = copyNode(other.root);
        totalKeys = other.totalKeys;
    }
    return *this;
}

// Inserts a new key
template <typename T, int grade>
void BTree<T, grade>::insert(int key) {
    // Create the root
    if (root == nullptr) {
        root = createNode();
        root->key[0] = key;
        root->numKeys = 1;
    } else {
        // Check if the root is full
        if (root->numKeys == grade - 1) {
            Node* newRoot = createNode();
            newRoot->child[0] = root;
            split(newRoot, 0, root);
            int i = 0;
            if (newRoot->key[0] < key) {
                i++;
            }
            insertNonFull(newRoot->child[i], key);
            root = newRoot;
        } else {
            insertNonFull(root, key);
        }
    }
    totalKeys++;
}

// Removes a key
template <typename T, int grade>
void BTree<T, grade>::remove(int key) {
    if (root == nullptr) return;

    remove(root, key);
    totalKeys--;

    if (root->numKeys == 0) {
        Node* temp = root;
        if (root->child[0] != nullptr) {
            root = root->child[0];
        } else {
            root = nullptr;
        }
        delete temp;
    }
}

// Finds a key
template <typename T, int grade>
bool BTree<T, grade>::search(int key) {
    Node* current = root;

    // Search in what node the key is
    while (current != nullptr) {
        int i = 0;

        while (i < current->numKeys && key > current->key[i]) {
            i++;
        }

        if (i < current->numKeys && key == current->key[i]) {
            return true;
        }

        current = current->child[i];
    }
    return false;
}

// Clear the BTree
template <typename T, int grade>
void BTree<T, grade>::clear() {
    clear(root);
    root = nullptr;
    totalKeys = 0;
}

// Prints the BTree
template <typename T, int grade>
void BTree<T, grade>::printAscending() const {
    printAscending(root);
    std::cout << std::endl;
}

// Prints the BTree
template <typename T, int grade>
void BTree<T, grade>::printDescending() const {
    printDescending(root);
    std::cout << std::endl;
}

// Prints the BTree
template <typename T, int grade>
void BTree<T, grade>::printByLevel() const {
    if (root == nullptr) return;

    std::queue<std::pair<Node*, int>> queue;
    queue.push({root, 0});

    int currentLevel = 0;
    int level = 0;

    std::cout << "Level 0: ";

    while (!queue.empty()) {
        auto [node, level] = queue.front();
        queue.pop();

        // Prints a new line when a new level is reached
        if (level > currentLevel) {
            std::cout << "\nLevel " << level << ": ";
            currentLevel = level;
        }

        // Prints keys in this node
        std::cout << "[";
        for (int i = 0; i < node->numKeys; i++) {
            std::cout << node->key[i] << " ";
        }
        std::cout << "] ";

        // Enqueue children
        for (int i = 0; i < node->numKeys + 1; i++) {
            if (node->child[i] != nullptr) {
                queue.push({node->child[i], level + 1});
            }
        }
    }

    std::cout << std::endl;
}

// Returns the number of keys in the tree
template <typename T, int grade>
int BTree<T, grade>::getNumKeys() const {
    return totalKeys;
}

// --- Private methods ---

// Creates a new node
template <typename T, int grade>
typename BTree<T, grade>::Node* BTree<T, grade>::createNode() const {
    Node* node = new Node;
    node->numKeys = 0;

    for (int i = 0; i < grade + 1; i++) {
        node->child[i] = nullptr;
    }
    return node;
}

// Copies and returns a node
template <typename T, int grade>
typename BTree<T, grade>::Node* BTree<T, grade>::copyNode(Node* node) const {
    if (node == nullptr) return nullptr;

    Node* newNode = createNode();
    // Copy numkeys
    newNode->numKeys = node->numKeys;

    // Copy keys
    for (int i = 0; i < node->numKeys; i++) {
        newNode->key[i] = node->key[i];
    }

    // Copy children
    for (int i = 0; i < node->numKeys + 1; i++) {
        newNode->child[i] = copyNode(node->child[i]);
    }
    return newNode;
}

// Splits a node
template <typename T, int grade>
void BTree<T, grade>::split(Node* parent, int i, Node* child) {
    Node* newChild = createNode();
    int mid = (grade - 1) / 2;

    // Copy mid key
    T midKey = child->key[mid];

    // Copy half of keys
    newChild->numKeys = child->numKeys - mid - 1;
    for (int j = 0; j < newChild->numKeys; j++) {
        newChild->key[j] = child->key[j + mid + 1];
    }

    // Copy children if not leaf
    if (child->child[0] != nullptr) {
        for (int j = 0; j <= newChild->numKeys; j++) {
            newChild->child[j] = child->child[j + mid + 1];
        }
    }

    // Update numKeys
    child->numKeys = mid;

    // Move keys
    for (int j = parent->numKeys; j > i; j--) {
        parent->key[j] = parent->key[j - 1];
        parent->child[j + 1] = parent->child[j];
    }

    // Insert mid key into parent
    parent->key[i] = midKey;
    parent->child[i + 1] = newChild;
    parent->numKeys++;
}

// Merges two nodes
template <typename T, int grade>
void BTree<T, grade>::merge(Node* parent, int i, Node* child) {
    int mid = (grade - 1) / 2;

    Node* sibling = parent->child[i + 1];

    child->key[mid] = parent->key[i];

    for (int j = 0; j < sibling->numKeys; j++) {
        // maybe change
        child->key[j + mid + 1] = sibling->key[j];
    }

    if (sibling->child[0] != nullptr) {
        for (int j = 0; j <= sibling->numKeys; j++) {
            child->child[j + mid + 1] = sibling->child[j];
        }
    }

    child->numKeys += sibling->numKeys + 1;

    for (int j = i + 1; j < parent->numKeys; j++) {
        parent->key[j - 1] = parent->key[j];
        parent->child[j] = parent->child[j + 1];
    }

    parent->numKeys--;
    delete sibling;
}

template <typename T, int grade>
void BTree<T, grade>::insertNonFull(Node* node, int key) {
    int i = node->numKeys - 1;

    if (node->child[0] == nullptr) {
        // Leaf node
        while (i >= 0 && key < node->key[i]) {
            node->key[i + 1] = node->key[i];
            i--;
        }
        node->key[i + 1] = key;
        node->numKeys++;
    } else {
        // Internal node
        while (i >= 0 && key < node->key[i]) {
            i--;
        }
        i++;

        // If child is full
        if (node->child[i]->numKeys == grade - 1) {
            split(node, i, node->child[i]);
            if (key > node->key[i]) {
                i++;
            }
        }
        insertNonFull(node->child[i], key);
    }
}

template <typename T, int grade>
void BTree<T, grade>::remove(Node* node, int key) {
    int idx = 0;
    while (idx < node->numKeys && node->key[idx] < key) idx++;

    // Key in node
    if (idx < node->numKeys && node->key[idx] == key) {
        // Internal node
        if (node->child[idx] != nullptr) {
            Node* predChild = node->child[idx];
            Node* succChild = node->child[idx + 1];

            // Check if pred or succ has at least (grade + 1 / 2) keys
            if (predChild->numKeys >= (grade + 1) / 2) {
                T pred = predChild->key[predChild->numKeys - 1];
                node->key[idx] = pred;
                remove(predChild, pred);
            } else if (succChild->numKeys >= (grade + 1) / 2) {
                T succ = succChild->key[0];
                node->key[idx] = succ;
                remove(succChild, succ);
            } else {
                merge(node, idx, predChild);
                remove(predChild, key);
            }
        } else {
            // Leaf node
            for (int i = idx + 1; i < node->numKeys; i++) {
                node->key[i - 1] = node->key[i];
            }
            node->numKeys--;
        }
    } else {
        // Key not in node
        if (node->child[idx] == nullptr) {
            return;
        }

        Node* child = node->child[idx];

        if (child->numKeys < (grade + 1) / 2) {
            Node* leftSibling;
            if (idx > 0) {
                leftSibling = node->child[idx - 1];
            } else {
                leftSibling = nullptr;
            }

            Node* rightSibling;
            if (idx < node->numKeys) {
                rightSibling = node->child[idx + 1];
            } else {
                rightSibling = nullptr;
            }

            // Try to borrow from left
            if (leftSibling && leftSibling->numKeys >= (grade + 1) / 2) {
                for (int i = child->numKeys; i > 0; --i)
                    child->key[i] = child->key[i - 1];
                if (child->child[0]) {
                    for (int i = child->numKeys + 1; i > 0; --i)
                        child->child[i] = child->child[i - 1];
                }
                child->key[0] = node->key[idx - 1];
                if (leftSibling->child[0])
                    child->child[0] = leftSibling->child[leftSibling->numKeys];
                node->key[idx - 1] = leftSibling->key[leftSibling->numKeys - 1];
                leftSibling->numKeys--;
                child->numKeys++;
            }
            // Borrow from right
            else if (rightSibling && rightSibling->numKeys >= (grade + 1) / 2) {
                child->key[child->numKeys] = node->key[idx];
                if (rightSibling->child[0])
                    child->child[child->numKeys + 1] = rightSibling->child[0];
                node->key[idx] = rightSibling->key[0];
                for (int i = 1; i < rightSibling->numKeys; ++i)
                    rightSibling->key[i - 1] = rightSibling->key[i];
                if (rightSibling->child[0]) {
                    for (int i = 1; i <= rightSibling->numKeys; ++i)
                        rightSibling->child[i - 1] = rightSibling->child[i];
                }
                rightSibling->numKeys--;
                child->numKeys++;
            }
            // Merge with sibling
            else {
                if (rightSibling) {
                    merge(node, idx, child);
                    remove(child, key);
                    return;
                } else if (leftSibling) {
                    merge(node, idx - 1, leftSibling);
                    remove(leftSibling, key);
                    return;
                }
            }
        }

        remove(child, key);
    }
}

// Prints the BTree from left to right
template <typename T, int grade>
void BTree<T, grade>::printAscending(Node* node) const {
    if (node == nullptr) return;

    for (int i = 0; i < node->numKeys; i++) {
        // Left child
        printAscending(node->child[i]);
        std::cout << node->key[i] << " ";
    }

    // Right child
    printAscending(node->child[node->numKeys]);
}

// Prints the BTree from right to left
template <typename T, int grade>
void BTree<T, grade>::printDescending(Node* node) const {
    if (node == nullptr) return;

    for (int i = node->numKeys; i >= 0; i--) {
        // Right child
        if (i < node->numKeys) {
            std::cout << node->key[i] << " ";
        }
        // Left child
        printDescending(node->child[i]);
    }
}

template <typename T, int grade>
void BTree<T, grade>::clear(Node* node) {
    if (node == nullptr) return;

    for (int i = 0; i <= node->numKeys; i++) {
        clear(node->child[i]);
    }
    delete node;
}
