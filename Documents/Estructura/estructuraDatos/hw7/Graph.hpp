#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Node.hpp"

class Graph {
   public:
    Graph();
    ~Graph();
    Graph(const Graph& graph);
    Graph& operator=(const Graph& graph);

    void addNode(char nodeName);
    void addEdge(char nameA, char nameB);
    void removeNode(char nodeName);
    void removeEdge(char nameA, char nameB);

    bool findNode(char nodeName) const;
    bool findEdge(char nameA, char nameB) const;

    void clearNode(char nodeName);
    void clearEdge(char nameA, char nameB);
    void clear();

    void print() const;

    int getNodeCount() const;
    int getEdgeCount() const;
    int getDegree(char nodeName) const;

   private:
    Node* firstNode;
    Node* lastNode;
    int nodeCount;
    int edgeCount;

    Node* findNodeDirection(char nodeName, Node** prevNode = nullptr) const;
};

#endif  // GRAPH_HPP
