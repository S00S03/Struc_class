#include "Graph.hpp"

#include <iostream>

// Constructor
Graph::Graph()
    : nodeCount(0), edgeCount(0), firstNode(nullptr), lastNode(nullptr) {}

// Destructor
Graph::~Graph() { clear(); }

// Copy constructor
Graph::Graph(const Graph& g)
    : nodeCount(0), edgeCount(0), firstNode(nullptr), lastNode(nullptr) {
    *this = g;
}

// Copy assignment
Graph& Graph::operator=(const Graph& graph) {
    if (this == &graph) {
        return *this;
    }
    clear();

    Node* currentNode = graph.firstNode;
    while (currentNode != nullptr) {
        this->addNode(currentNode->name);
        currentNode = currentNode->next;
    }

    currentNode = firstNode;
    Edge* currentEdge;
    while (currentNode != nullptr) {
        currentEdge = currentNode->first;
        while (currentEdge != nullptr) {
            if (!findEdge(currentNode->name, currentEdge->adjacent->name)) {
                this->addEdge(currentNode->name, currentEdge->adjacent->name);
            }
            currentEdge = currentEdge->next;
        }
        currentNode = currentNode->next;
    }

    // copy graph g
    return *this;
}

// Adds a new node
void Graph::addNode(char name) {
    Node* newNode = new Node(name);

    if (nodeCount == 0) {
        firstNode = newNode;
    } else {
        lastNode->next = newNode;
    }

    lastNode = newNode;
    nodeCount++;
}

// Adds a new edge
void Graph::addEdge(char fromNode, char toNode) {
    Node* from = findNodeDirection(fromNode);
    if (from == nullptr) return;

    Node* to = findNodeDirection(toNode);
    if (to == nullptr) return;

    // Add edge from -> to
    from->addEdge(to);

    // Add edge from <- to
    to->addEdge(from);

    edgeCount++;
}

// Removes a node
void Graph::removeNode(char nodeName) {
    Node* prev = nullptr;
    Node* del = findNodeDirection(nodeName);
    if (del == nullptr) return;
    edgeCount -= del->clear();

    prev == nullptr ? firstNode = firstNode->next : prev->next = del->next;

    if (firstNode == nullptr) lastNode = nullptr;

    delete del;
    nodeCount--;
}

// Removes an edge
void Graph::removeEdge(char nodeA, char nodeB) {
    Node* from = findNodeDirection(nodeA);
    if (from == nullptr) return;

    Node* to = findNodeDirection(nodeB);
    if (to == nullptr) return;

    from->removeEdge(to);
    to->removeEdge(from);

    edgeCount--;
}

// Finds a node
bool Graph::findNode(char nodeName) const {
    return findNodeDirection(nodeName) != nullptr;
}

// Finds an edge
bool Graph::findEdge(char nodeA, char nodeB) const {
    Node* from = findNodeDirection(nodeA);
    if (from == nullptr) return false;

    Node* to = findNodeDirection(nodeB);
    if (to == nullptr) return false;

    return from->findEdge(to);
}

// Clears the graph
void Graph::clear() {
    while (firstNode != nullptr) removeNode(firstNode->name);
}

// Clears a node
void Graph::clearNode(char nodeName) {
    Node* del = findNodeDirection(nodeName);
    if (del == nullptr) return;

    removeNode(nodeName);
    edgeCount -= del->clear();
}

// Clears an edge
void Graph::clearEdge(char nodeA, char NodeB) { removeEdge(nodeA, NodeB); }


// Prints the graph
void Graph::print() const {
    Node* current = firstNode;

    while (current != nullptr) {
        current->print();
        std::cout << std::endl;

        current = current->next;
    }
}

// Finds a node direction
Node* Graph::findNodeDirection(char nodeName, Node** prevNode) const {
    Node* current = firstNode;

    if (prevNode != nullptr) *prevNode = nullptr;

    while (current != nullptr && current->name != nodeName) {
        if (prevNode != nullptr) *prevNode = current;
        current = current->next;
    }

    return current;
}

// Returns the node count
int Graph::getNodeCount() const { return nodeCount; }

// Returns the edge count
int Graph::getEdgeCount() const { return edgeCount; }

// Returns the degree
int Graph::getDegree(char nodeName) const {
    Node* node = findNodeDirection(nodeName);
    if (node == nullptr) throw std::invalid_argument("Node not found");
    return node->degree;
}
