#include "BStarTree.hpp"
#include <iostream>
#include <queue>
#include <vector>

// Constructor for BStarTree, Initializes an empty tree
BStarTree::BStarTree() : root(nullptr) {}

// Destructor for BStarTree, deletes all nodes
BStarTree::~BStarTree() { deleteTree(root); }

// Helper function to recursively delete a tree
void BStarTree::deleteTree(Node* node) {
    if (!node) return;

    // Recursively delete all children
    for (int i = 0; i <= node->numKeys; ++i)
        deleteTree(node->children[i]);

    // Delete the current node
    delete node;
}

// Function to insert a key into the tree
void BStarTree::insert(int key) {
    // If the tree is empty, create a new root
    if (!root) {
        root = new Node(true);
        root->keys[0] = key;
        root->numKeys = 1;
    } else {
        // If the tree is full, split the root
        if (root->numKeys == DEGREE - 1) {
            Node* newRoot = new Node(false);
            newRoot->children[0] = root;
            splitAndRedistribute(newRoot, 0, root);
            int i = 0;
            if (newRoot->keys[0] < key) {
                i++;
            }
            insertNonFull(newRoot->children[i], key);
            root = newRoot;
        } else {
            // Insert the key into the tree
            insertNonFull(root, key);
        }
    }
}

// Function to insert a key into a non-full node
void BStarTree::insertNonFull(Node* node, int key) {
    // Start from the rightmost node
    int i = node->numKeys - 1;

    // If the node is a leaf, insert the key
    if (node->isLeaf) {

        // Move keys to make space for the new key
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        // Insert the new key
        node->keys[i + 1] = key;
        node->numKeys++;
    } else {

        // If the node is not a leaf, find the correct child to insert the key
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;

        // If the child node is full, split it
        if (node->children[i]->numKeys == DEGREE - 1) {
            splitAndRedistribute(node, i, node->children[i]);
            if (key > node->keys[i]) {
                i++;
            }
        }

        // Recursively insert the key into the correct child node
        insertNonFull(node->children[i], key);
    }
}

// Function to split a chid node and redistribute keys
void BStarTree::splitAndRedistribute(Node*& parent, int index, Node*& child) {
    Node* leftSibling;
    if (index > 0) {
        leftSibling = parent->children[index - 1];
    } else {
        leftSibling = nullptr;
    }

    Node* rightSibling;
    if (index < parent->numKeys) {
        rightSibling = parent->children[index + 1];
    } else {
        rightSibling = nullptr;
    }

    // std::cout << "Right Sibling" << rightSibling->numKeys << std::endl;
    // Try 3-way redistribution with right sibling
    if (rightSibling && rightSibling->numKeys < DEGREE - 1) {
        int totalKeys = child->numKeys + rightSibling->numKeys + 1;
        std::vector<int> combinedKeys(totalKeys);

        // Copy child keys
        for (int i = 0; i < child->numKeys; i++) {
            combinedKeys[i] = child->keys[i];
        }

        // Copy parent separator key
        combinedKeys[child->numKeys] = parent->keys[index];

        // Copy right sibling keys
        for (int i = 0; i < rightSibling->numKeys; i++) {
            combinedKeys[child->numKeys + 1 + i] = rightSibling->keys[i];
        }

        // Redistribute into 3 nodes (including a new one)
        int third = totalKeys / 3;
        int secondThird = 2 * third;

        // ASSIGN KEYS TO CHILD
        child->numKeys = third;
        for (int i = 0; i < child->numKeys; i++) {
            child->keys[i] = combinedKeys[i];
        }

        // ASSIGN KEYS TO RIGHT SIBLING
        rightSibling->numKeys = third - 1;
        for (int i = 0; i < rightSibling->numKeys; i++) {
            rightSibling->keys[i] = combinedKeys[third + 1 + i];
        }

        // ASSIGN KEYS TO NEW CHILD
        Node* newChild = new Node(child->isLeaf);
        newChild->numKeys = totalKeys - secondThird - 1;

        for (int i = 0; i < newChild->numKeys; i++) {
            newChild->keys[i] = combinedKeys[secondThird + 1 + i];
        }

        // Shift parent keys and children
        for (int i = index + 1; i < parent->numKeys; i++) {
            parent->keys[i + 1] = parent->keys[i];
            parent->children[i + 2] = parent->children[i + 1];
        }

        parent->keys[index] = combinedKeys[third];
        parent->keys[index + 1] = combinedKeys[secondThird];
        parent->numKeys++;

        parent->children[index] = child;
        parent->children[index + 1] = rightSibling;
        parent->children[index + 2] = newChild;

    } else if (leftSibling && leftSibling->numKeys < DEGREE - 1) {
        // Similar 3-way redistribution with left sibling

        int totalKeys = leftSibling->numKeys + child->numKeys + 1; // +1 for separator
        std::vector<int> combinedKeys(totalKeys); // Vector to store total keys (size 7)

        // Copy left sibling keys
        for (int i = 0; i < leftSibling->numKeys; i++) {
            combinedKeys[i] = leftSibling->keys[i]; // Store [ 10 15 ] from left sibling
        }

        // Copy parent separator key
        combinedKeys[leftSibling->numKeys] = parent->keys[index - 1]; // Store [ 17 ] from parent

        // Copy child keys
        for (int i = 0; i < child->numKeys; i++) {
            combinedKeys[leftSibling->numKeys + 1 + i] =
                child->keys[i]; // Store [ 19 20 30 40 ] from child
        }

        int third = totalKeys / 3;   // 7 / 3 = 2
        int secondThird = 2 * third; // 2 * 2 = 4

        leftSibling->numKeys = third; // 2
        for (int i = 0; i < third; ++i) {
            leftSibling->keys[i] = combinedKeys[i]; // [ 10 15 ]
        }

        child->numKeys = third - 1; // 2 - 1 = 1

        for (int i = 0; i < child->numKeys; ++i) {
            child->keys[i] = combinedKeys[third + i + 1]; // [ 19 ]
        }

        // Create a new node
        Node* newNode = new Node(child->isLeaf);
        newNode->numKeys = totalKeys - secondThird - 1; // 7 - 4 - 1 = 2
        for (int i = 0; i < newNode->numKeys; ++i) {
            newNode->keys[i] = combinedKeys[secondThird + i + 1]; // [ 30 40 ]
        }

        // Shift parent keys and children
        for (int i = parent->numKeys; i > index - 1; --i) {
            parent->keys[i + 1] = parent->keys[i];
            parent->children[i + 2] = parent->children[i + 1];
        }

        parent->keys[index - 1] = combinedKeys[third];   // [ 17 ]
        parent->keys[index] = combinedKeys[secondThird]; // [ 20 ]
        parent->numKeys++;

        parent->children[index - 1] = leftSibling; // [ 10 15 ]
        parent->children[index] = child;           // [ 19 ]
        parent->children[index + 1] = newNode;     // [ 30 40 ]

    } else {
        // Fallback to basic 2-way split
        // int mid = DEGREE / 2; // mid = 2
        int mid = child->numKeys / 2;

        int middleKey = child->keys[mid]; // middleKey = 5

        Node* newSibling = new Node(child->isLeaf);
        newSibling->numKeys = child->numKeys - mid - 1;

        for (int i = 0; i < newSibling->numKeys; i++) {
            newSibling->keys[i] = child->keys[mid + 1 + i];
        }

        if (!child->isLeaf) {
            for (int i = 0; i <= newSibling->numKeys; i++)
                newSibling->children[i] = child->children[mid + 1 + i];
        }

        child->numKeys = mid;

        for (int i = parent->numKeys; i > index; i--) {
            parent->keys[i] = parent->keys[i - 1];
            parent->children[i + 1] = parent->children[i];
        }

        parent->keys[index] = middleKey;
        parent->children[index + 1] = newSibling;
        parent->numKeys++;
    }
}

void BStarTree::printByLevel() const { printLevelOrder(root); }

void BStarTree::printLevelOrder(Node* node) const {
    if (!node) return;

    std::queue<std::pair<Node*, int>> q;
    q.push({node, 0});
    int currLevel = 0;

    std::cout << "Level 0: ";
    while (!q.empty()) {
        auto [n, level] = q.front();
        q.pop();

        if (level > currLevel) {
            std::cout << "\nLevel " << level << ": ";
            currLevel = level;
        }

        std::cout << "[ ";
        for (int i = 0; i < n->numKeys; i++)
            std::cout << n->keys[i] << " ";
        std::cout << "] ";

        for (int i = 0; i <= n->numKeys; i++) {
            if (n->children[i]) q.push({n->children[i], level + 1});
        }
    }

    std::cout << std::endl;
}

// Función pública de búsqueda
bool BStarTree::search(int key) const { return searchInNode(root, key); }

// Función auxiliar de búsqueda en un nodo
bool BStarTree::searchInNode(Node* node, int key) const {
    if (!node) return false;

    // Busca en el nodo si la clave está entre las claves del nodo
    int i = 0;
    while (i < node->numKeys && key > node->keys[i]) {
        i++;
    }

    // Si encontramos la clave
    if (i < node->numKeys && key == node->keys[i]) {
        return true;
    }

    // Si no es una hoja, buscamos en el hijo correspondiente
    if (!node->isLeaf) {
        return searchInNode(node->children[i], key);
    }

    return false; // Si no es hoja y no encontramos la clave
}

// Método público para eliminar una clave
void BStarTree::remove(int key) {
    if (!root) {
        std::cout << "El árbol está vacío\n";
        return;
    }

    remove(root, key);

    // Si el nodo raíz queda sin claves después de la eliminación,
    // hacer que su primer hijo sea la nueva raíz si existe
    if (root->numKeys == 0) {
        Node* temp = root;
        if (root->isLeaf) {
            root = nullptr;
        } else {
            root = root->children[0];
        }
        delete temp;
    }
}

// Función principal para eliminar una clave
void BStarTree::remove(Node* node, int key) {
    int index = 0;
    while (index < node->numKeys && key > node->keys[index]) {
        index++;
    }

    // Caso 1: La clave está en este nodo
    if (index < node->numKeys && node->keys[index] == key) {
        if (node->isLeaf) {
            removeFromLeaf(node, index);
        } else {
            removeFromNonLeaf(node, index);
        }
    } else {
        // Caso 2: La clave no está en este nodo
        if (node->isLeaf) {
            std::cout << "La clave " << key << " no existe en el árbol\n";
            return;
        }

        // Verificar si la clave está en el último hijo
        bool isLastChild = (index == node->numKeys);

        // Si el hijo donde debe estar la clave tiene menos claves de las necesarias, llenarlo
        if (node->children[index]->numKeys < (DEGREE + 1) / 2) {
            fill(node, index);
        }

        // Si el último hijo fue fusionado, debe haber disminuido en 1
        if (isLastChild && index > node->numKeys) {
            remove(node->children[index - 1], key);
        } else {
            remove(node->children[index], key);
        }
    }
}

// Eliminar una clave de un nodo hoja
void BStarTree::removeFromLeaf(Node* node, int index) {
    for (int i = index + 1; i < node->numKeys; ++i) {
        node->keys[i - 1] = node->keys[i];
    }
    node->numKeys--;
}

// Eliminar una clave de un nodo no hoja
void BStarTree::removeFromNonLeaf(Node* node, int index) {
    int key = node->keys[index];

    // Caso 3a: El hijo anterior tiene suficientes claves
    if (node->children[index]->numKeys >= (DEGREE + 1) / 2) {
        int predecessor = getPredecessor(node, index);
        node->keys[index] = predecessor;
        remove(node->children[index], predecessor);
    }
    // Caso 3b: El hijo siguiente tiene suficientes claves
    else if (node->children[index + 1]->numKeys >= (DEGREE + 1) / 2) {
        int successor = getSuccessor(node, index);
        node->keys[index] = successor;
        remove(node->children[index + 1], successor);
    }
    // Caso 3c: Fusionar
    else {
        // Corrección: Verificar si estamos en un nodo raíz o no
        if (node == root && node->numKeys == 1) {
            // Caso especial para raíz con solo una clave
            merge(node, index);
            remove(node->children[index], key);
        } else {
            // Caso normal
            merge(node, index);
            remove(node->children[index], key);
        }
    }
}

// Llenar un hijo que tiene menos de (DEGREE + 1)/2 claves
void BStarTree::fill(Node* node, int index) {
    // Corrección: Priorizar redistribución 3:2 específica de B*

    // Primero intentar con el hermano izquierdo
    if (index != 0 && node->children[index - 1]->numKeys > (DEGREE + 1) / 2) {
        borrowFromPrev(node, index);
    }
    // Luego con el hermano derecho
    else if (index != node->numKeys && node->children[index + 1]->numKeys > (DEGREE + 1) / 2) {
        borrowFromNext(node, index);
    }
    // Finalmente fusionar
    else {
        if (index != node->numKeys) {
            merge(node, index);
        } else {
            merge(node, index - 1);
        }
    }
}

// Tomar prestado una clave del hijo anterior
void BStarTree::borrowFromPrev(Node* node, int index) {
    Node* child = node->children[index];
    Node* sibling = node->children[index - 1];

    // Desplazar todas las claves del hijo una posición adelante
    for (int i = child->numKeys - 1; i >= 0; --i) {
        child->keys[i + 1] = child->keys[i];
    }

    // Si no es hoja, desplazar también los punteros de los hijos
    if (!child->isLeaf) {
        for (int i = child->numKeys; i >= 0; --i) {
            child->children[i + 1] = child->children[i];
        }
    }

    // Mover la clave del nodo padre al hijo
    child->keys[0] = node->keys[index - 1];

    // Mover la última clave del hermano al nodo padre
    if (!child->isLeaf) {
        child->children[0] = sibling->children[sibling->numKeys];
    }

    node->keys[index - 1] = sibling->keys[sibling->numKeys - 1];
    child->numKeys++;
    sibling->numKeys--;
}

// Tomar prestado una clave del hijo siguiente
void BStarTree::borrowFromNext(Node* node, int index) {
    Node* child = node->children[index];
    Node* sibling = node->children[index + 1];

    // Mover la clave del nodo padre al hijo
    child->keys[child->numKeys] = node->keys[index];
    child->numKeys++;

    // Mover la primera clave del hermano al nodo padre
    node->keys[index] = sibling->keys[0];

    // Mover el primer hijo del hermano al último hijo del hijo actual
    if (!child->isLeaf) {
        child->children[child->numKeys] = sibling->children[0];
    }

    // Desplazar las claves y punteros del hermano una posición atrás
    for (int i = 1; i < sibling->numKeys; ++i) {
        sibling->keys[i - 1] = sibling->keys[i];
    }

    if (!sibling->isLeaf) {
        for (int i = 1; i <= sibling->numKeys; ++i) {
            sibling->children[i - 1] = sibling->children[i];
        }
    }

    sibling->numKeys--;
}

// Fusionar un nodo con su hermano
void BStarTree::merge(Node* node, int index) {
    Node* child = node->children[index];
    Node* sibling = node->children[index + 1];

    // Corrección: Solo mover la clave del padre si no es raíz especial
    if (!(node == root && node->numKeys == 1)) {
        child->keys[child->numKeys] = node->keys[index];
        child->numKeys++;
    }

    // Copiar claves del hermano
    for (int i = 0; i < sibling->numKeys; ++i) {
        child->keys[child->numKeys + i] = sibling->keys[i];
    }

    // Copiar hijos si no es hoja
    if (!child->isLeaf) {
        for (int i = 0; i <= sibling->numKeys; ++i) {
            child->children[child->numKeys + i] = sibling->children[i];
        }
    }

    // Actualizar contador de claves
    child->numKeys += sibling->numKeys;

    // Eliminar la clave del padre y ajustar
    if (!(node == root && node->numKeys == 1)) {
        for (int i = index + 1; i < node->numKeys; ++i) {
            node->keys[i - 1] = node->keys[i];
        }

        for (int i = index + 2; i <= node->numKeys; ++i) {
            node->children[i - 1] = node->children[i];
        }

        node->numKeys--;
    }

    // Liberar memoria
    delete sibling;
}

// Redistribuir o fusionar nodos (específico para B*)
void BStarTree::redistributeOrMerge(Node* node, int index) {
    // Implementación específica para B* que prioriza redistribución 3:2
    // Esta es una versión simplificada, se puede mejorar

    Node* child = node->children[index];

    // Intentar redistribución con hermanos izquierdo y derecho
    if (index > 0 && node->children[index - 1]->numKeys > (DEGREE + 1) / 2) {
        borrowFromPrev(node, index);
    } else if (index < node->numKeys && node->children[index + 1]->numKeys > (DEGREE + 1) / 2) {
        borrowFromNext(node, index);
    } else {
        // Si no se puede redistribuir, fusionar
        if (index < node->numKeys) {
            merge(node, index);
        } else {
            merge(node, index - 1);
        }
    }
}

// Obtener el predecesor de una clave (mayor clave en el subárbol izquierdo)
int BStarTree::getPredecessor(Node* node, int index) {
    // Moverse al hijo izquierdo del nodo
    Node* current = node->children[index];

    // Seguir por el hijo más a la derecha hasta llegar a una hoja
    while (!current->isLeaf) {
        current = current->children[current->numKeys];
    }

    // Devolver la última clave del nodo hoja
    return current->keys[current->numKeys - 1];
}

// Obtener el sucesor de una clave (menor clave en el subárbol derecho)
int BStarTree::getSuccessor(Node* node, int index) {
    // Moverse al hijo derecho del nodo
    Node* current = node->children[index + 1];

    // Seguir por el hijo más a la izquierda hasta llegar a una hoja
    while (!current->isLeaf) {
        current = current->children[0];
    }

    // Devolver la primera clave del nodo hoja
    return current->keys[0];
}
