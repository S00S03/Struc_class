#include "List.hpp"
#include <iostream>

List::List() {
    numNodes = 0;
    head = nullptr;
}

List::List(const List &other) {
    numNodes = 0;
    head = nullptr;
    Node *current = other.head;
    if (current) {
        do {
            addHead(current->value);
            current = current->next;
        } while (current != other.head);
    }
}

List &List::operator=(const List &other) {
    if (this != &other) {
        makeEmpty();
        Node *current = other.head;
        if (current) {
            do {
                addHead(current->value);
                current = current->next;
            } while (current != other.head);
        }
    }
    return *this;
}

List::~List() {
    makeEmpty();
}

void List::addHead(int value) {
    Node *newNode = new Node(value);
    if (!head) {
        head = newNode;
        head->next = head;
        head->prev = head;
    } else {
        Node *tail = head->prev;
        newNode->next = head;
        newNode->prev = tail;
        tail->next = newNode;
        head->prev = newNode;
        head = newNode;
    }
    numNodes++;
}

void List::removeHead() {
    if (!head) return;
    
    if (head->next == head) {
        delete head;
        head = nullptr;
    } else {
        Node *tail = head->prev;
        Node *newHead = head->next;
        tail->next = newHead;
        newHead->prev = tail;
        delete head;
        head = newHead;
    }
    numNodes--;
}

void List::removeAt(int position) {
    if (!head || position < 0 || position >= numNodes) {
        throw std::out_of_range("Invalid position");
        return; 
    }

    for (int i = 0; i < position; i++) {
        head = head->next;
    }

    removeHead();
}

bool List::isEmpty() const { return numNodes == 0; }

void List::makeEmpty() {
    while (!isEmpty()) {
        removeHead();
    }
}

void List::print() const {
    if (!head) return;
    Node *current = head;
    do {
        std::cout << current->value;
        if (current->next != head) {
            std::cout << " -> ";
        }
        current = current->next;
    } while (current != head);
    std::cout << std::endl;
}

void List::printReverse() const {
    if (!head) return;
    Node *current = head->prev;
    do {
        std::cout << current->value;
        if (current->prev != head->prev) {
            std::cout << " <- ";
        }
        current = current->prev;
    } while (current != head->prev);
    std::cout << std::endl;
}

void List::printConnections() const {
    if (!head) {
        std::cout << "List is empty." << std::endl;
        return;
    }

    Node *current = head;
    do {
        std::cout << "[ " << current->value << " | prev: " 
                  << (current->prev ? std::to_string(current->prev->value) : "NULL") 
                  << " | next: " 
                  << (current->next ? std::to_string(current->next->value) : "NULL") 
                  << " ]" << std::endl;
        current = current->next;
    } while (current != head);
}


int List::getFront() const { return head ? head->value : -1; }

int List::getBack() const { return head ? head->prev->value : -1; }

int List::getSize() const { return numNodes; }

int List::getElementAt(int position) const {
    if (!head || position < 0 || position >= numNodes) return -1;
    Node *current = head;
    for (int i = 0; i < position; ++i) {
        current = current->next;
    }
    return current->value;
}

