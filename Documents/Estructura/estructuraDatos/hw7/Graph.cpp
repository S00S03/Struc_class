#include "Graph.hpp"

#include <iostream>

Graph::Graph()
    : nodeCount(0), edgeCount(0), firstNode(nullptr), lastNode(nullptr) {}

Graph::~Graph() { clear(); }

Graph::Graph(const Graph& g)
    : nodeCount(0), edgeCount(0), firstNode(nullptr), lastNode(nullptr) {
    *this = g;
}

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

void Graph::removeNode(char nodeName) {
    Node* prev = nullptr;
    Node* del = findNodeDirection(nodeName, &prev);
    if (del == nullptr) return;
    edgeCount -= del->clear();
    if (prev == nullptr) {
        firstNode = firstNode->next;
    } else {
        prev->next = del->next;
    }
    if (lastNode == del) {
        lastNode = prev;
    }

    delete del;
    nodeCount--;
}
void Graph::removeEdge(char nodeA, char nodeB) {
    Node* from = findNodeDirection(nodeA);
    if (from == nullptr) return;

    Node* to = findNodeDirection(nodeB);
    if (to == nullptr) return;

    from->removeEdge(to);
    to->removeEdge(from);

    edgeCount--;
}

bool Graph::findNode(char nodeName) const {
    return findNodeDirection(nodeName) != nullptr;
}

bool Graph::findEdge(char nodeA, char nodeB) const {
    Node* from = findNodeDirection(nodeA);
    if (from == nullptr) return false;

    Node* to = findNodeDirection(nodeB);
    if (to == nullptr) return false;

    return from->findEdge(to);
}

void Graph::clear() {
    while (firstNode != nullptr) removeNode(firstNode->name);
}

void Graph::clearNode(char nodeName) {
    Node* del = findNodeDirection(nodeName);
    if (del == nullptr) return;

    removeNode(nodeName);
    edgeCount -= del->clear();
}
void Graph::clearEdge(char nodeA, char NodeB) { removeEdge(nodeA, NodeB); }

void Graph::print() const {
    Node* current = firstNode;

    while (current != nullptr) {
        current->print();
        std::cout << std::endl;

        current = current->next;
    }
}

Node* Graph::findNodeDirection(char nodeName, Node** prevNode) const {
    Node* current = firstNode;

    if (prevNode != nullptr) *prevNode = nullptr;

    while (current != nullptr && current->name != nodeName) {
        if (prevNode != nullptr) *prevNode = current;
        current = current->next;
    }

    return current;
}

int Graph::getNodeCount() const { return nodeCount; }
int Graph::getEdgeCount() const { return edgeCount; }
int Graph::getDegree(char nodeName) const {
    Node* node = findNodeDirection(nodeName);
    if (node == nullptr) throw std::invalid_argument("Node not found");
    return node->degree;
}
