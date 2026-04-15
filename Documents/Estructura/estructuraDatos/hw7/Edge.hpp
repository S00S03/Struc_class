#ifndef EDGE_HPP
#define EDGE_HPP

struct Node;

struct Edge {
    char name1;
    char name2;
    Node* adjacent;
    Edge* next;

    Edge(Node* adjacent) : adjacent(adjacent), next(nullptr) {}
};
#endif // EDGE_HPP

