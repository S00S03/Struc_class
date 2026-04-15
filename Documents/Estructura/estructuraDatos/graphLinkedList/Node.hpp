#ifndef NODE_HPP
#define NODE_HPP

#include "Edge.hpp"

struct Node {
    char name;
    int degree;
    Edge *first, *last;
    Node* next;

    Node(char name, Node* next = nullptr);

    void addEdge(Node* edge);
    void removeEdge(Node* edge);
    int clear();

    bool findEdge(Node* edge) const;

    void print() const;

    Edge* findDirection(Node* adjacent, Edge** anterior = nullptr) const;

};

#endif  // NODE_HPP
