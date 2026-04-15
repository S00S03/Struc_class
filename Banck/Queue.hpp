#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
    };

    Node* first;
    Node* last;
    int num_elements;

public:
    Queue() {
        first = last = nullptr;
        num_elements = 0;
    }

    ~Queue() {
        while (!empty())
            dequeue();
    }

    bool empty() const {
        return first == nullptr;
    }

    int size() const {
        return num_elements;
    }

    void enqueue(const T& element) {
        Node* n = new Node{element, nullptr};

        if (empty()) {
            first = last = n;
            n->next = n;
        } else {
            n->next = first;
            last->next = n;
            last = n;
        }

        num_elements++;
    }

    void dequeue() {
        if (empty())
            throw "Queue vacía";

        if (first == last) {
            delete first;
            first = last = nullptr;
        } else {
            Node* temp = first;
            first = first->next;
            last->next = first;
            delete temp;
        }

        num_elements--;
    }

    T front() const {
        if (empty())
            throw "Queue vacía";
        return first->data;
    }

    void print() const {
        if (empty()) {
            std::cout << "[vacía]";
            return;
        }

        Node* temp = first;
        do {
            std::cout << temp->data << " | ";
            temp = temp->next;
        } while (temp != first);
    }
};

#endif