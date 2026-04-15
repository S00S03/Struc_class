#include "List.hpp"
#include <iostream>

List::List() {
    numNodes = 0;
    head = nullptr;
    tail = nullptr;
}
List::~List() {
    Node *current = head;
    while (current != nullptr) {
        Node *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    numNodes = 0;
}

void List::add(int value) {
    Node *newNode = new Node(value);

    // Empty List
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    // Insert at the beginning
    else if (value <= head->value) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    // Insert at the end
    else if (value <= tail->value) {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    // Insert in the middle
    else {
        Node *current = head;
        while (current->next != nullptr && current->next->value < value) {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->prev = current;
        if (newNode->next != nullptr) {
            newNode->next->prev = newNode;
        }
        current->next = newNode;
    }
    numNodes++;
    // sort();
}

void List::remove() {
    if (head == nullptr) {
        return;
    }
    Node *tmp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete tmp;
    numNodes--;
}

// void List::sort() const {
//     if (numNodes < 1) return;
//
//     for (Node *i = head; i != nullptr; i = i->next) {
//         for (Node *j = i->next; j != nullptr; j = j->next) {
//             if (i->value > j->value) {
//                 std::swap(i->value, j->value);
//             }
//         }
//     }
// }

void List::print() const {
    Node *current = head;
    while (current != nullptr) {
        std::cout << current->value;
        if (current->next != nullptr) {
            std::cout << " -> ";
        }
        current = current->next;
    }
    std::cout << std::endl;
}

void List::printReverse() const {
    Node *current = tail;
    while (current != nullptr) {
        std::cout << current->value;
        if (current->prev != nullptr) {
            std::cout << " -> ";
        }
        current = current->prev;
    }
    std::cout << std::endl;
}
