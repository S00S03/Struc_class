#include "SimpleList.hpp"

#include <iostream>

SimpleList::SimpleList() {
    head = nullptr;
    numNodes = 0;
}

void SimpleList::addFirst(int value) {
    Node *newNode = new Node(value);
    newNode->next = head;
    head = newNode;
}

void SimpleList::addLast(int value) {
    Node *newNode = new Node(value);
    // head is the first node
    if (head == nullptr) {
        head = newNode;
    } else {
        Node *visited = head;
        // travel to the last node
        while (visited->next != nullptr) {
            visited = visited->next;
        }
        visited->next = newNode;
    }
    numNodes++;
}

// void SimpleList::addIn(int value, int position) {
//     Node *newNode = new Node(value);
//     Node *visited = head;
//     for (int i = 0; i < position; i++) {
//         visited = visited->next;
//     }
//     visited = newNode;
// }

void SimpleList::removeFirst() {
    if (head == nullptr) return;
    Node *temp = head;
    head = head->next;
    delete temp;
}

void SimpleList::removeLast() {}

int SimpleList::getPositionOf(int value) {
    int position = 0;
    Node *visited = head;
    // why here is only visited and not visited->next ?
    while (visited != nullptr && visited->value != value) {
        visited = visited->next;
        position++;
    }
    return position;
}

void SimpleList::print() {
    Node *visited = head;
    while (visited != nullptr) {
        std::cout << visited->value;
        if (visited->next != nullptr) {
            std::cout << " -> ";
        }
        visited = visited->next;
    }
    std::cout << std::endl;
}
