#include "Node.hpp"

#include <iostream>

Node::Node(char name, Node* next)
    : name(name), next(next), degree(0), first(nullptr), last(nullptr) {}

void Node::addEdge(Node* edge) {
    Edge* newEdge = new Edge(edge);
    degree == 0 ? first = newEdge : last->next = newEdge;
    last = newEdge;
    degree++;
}

void Node::removeEdge(Node* adjacent) {
    Edge *prev, *actual = findDirection(adjacent, &prev);

    if (actual == nullptr) return;

    prev == nullptr ? first = first->next : prev->next = actual->next;

    if (first == nullptr) {
        last = nullptr;
    }
    delete actual;
    degree--;
}

// Delete all edges of the node
int Node::clear() {
    int numEdges = 0;
    Edge* del;

    while (first != nullptr) {
        del = first;

        // Remove Edge that isnt current
        if (first->adjacent != this) {
            first->adjacent->removeEdge(this);
        }

        first = first->next;
        delete del;

        numEdges++;
    }
    last = nullptr;
    degree = 0;

    return numEdges;
}

bool Node::findEdge(Node* adjacent) const {
    return findDirection(adjacent) != nullptr;
}

Edge* Node::findDirection(Node* adjacent, Edge** anterior) const {
    Edge* current = first;

    if (anterior != nullptr) *anterior = nullptr;

    while (current != nullptr && current->adjacent != adjacent) {
        if (anterior != nullptr) *anterior = current;
        current = current->next;
    }

    return current;
}

void Node::print() const {
    std::cout << name << " -> ";
    Edge* current = first;
    while (current != nullptr) {
        std::cout << current->adjacent->name << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

