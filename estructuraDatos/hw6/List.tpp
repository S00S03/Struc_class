#include <iostream>
#include <stdexcept>
#include <utility>

#include "List.hpp"

template <typename T>
List<T>::List() {
    head = nullptr;
    numNodes = 0;
    tail = nullptr;
}

template <typename T>
List<T>::List(const List &other) {
    head = nullptr;
    tail = nullptr;
    numNodes = 0;

    Node *current = other.head;
    while (current != nullptr) {
        addBack(current->value);
        current = current->next;
    }
}

template <typename T>
List<T> &List<T>::operator=(const List &other) {
    if (this != &other) {
        makeEmpty();

        Node *current = other.head;
        while (current != nullptr) {
            addBack(current->value);
            current = current->next;
        }
    }
    return *this;
}

template <typename T>
List<T>::~List<T>() {
    makeEmpty();
}

template <typename T>
const T &List<T>::operator[](int position) const {
    return getElementAt(position);
}

template <typename T>
T &List<T>::operator[](int position) {
    return getElementAt(position);
}

template <typename T>
void List<T>::addFront(T value) {
    Node *newNode = new Node(value);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    numNodes++;
}

template <typename T>
void List<T>::addBack(T value) {
    Node *newNode = new Node(value);
    if (tail == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    numNodes++;
}

template <typename T>
void List<T>::addAt(T value, int position) {
    // std::cout << "[DEBUG] Adding at position " << position << " with size "
              // << numNodes << std::endl;
    checkValidPosition(position);

    if (position == 0) {
        addFront(value);
        return;
    }

    if (position == numNodes) {
        addBack(value);
        return;
    }

    Node *newNode = new Node(value);
    Node *current = head;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    if (current == nullptr) {
        throw std::invalid_argument("Invalid Position");
    }

    // NewNode -> current.next
    newNode->next = current->next;
    // current <- NewNode
    newNode->prev = current;
    if (current->next != nullptr) {
        // NewNode <- current.next
        current->next->prev = newNode;
    }
    // current -> newNode
    current->next = newNode;
    numNodes++;
}

template <typename T>
void List<T>::removeFront() {
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

template <typename T>
void List<T>::removeBack() {
    if (tail == nullptr) {
        return;
    }
    Node *tmp = tail;
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete tmp;
    numNodes--;
}

template <typename T>
void List<T>::removeAt(int position) {
    checkValidPosition(position);

    if (position == 0) {
        removeFront();
        return;
    }
    if (position == numNodes - 1) {
        removeBack();
        return;
    }

    Node *current = head;
    for (int i = 0; i < position; i++) {
        current = current->next;
    }
    if (current->next != nullptr) {
        current->next->prev = current->prev;
    }
    if (current->prev != nullptr) {
        current->prev->next = current->next;
    }
    delete current;
    numNodes--;
}

template <typename T>
void List<T>::removeAllDuplicates() {
    if (!head || !head->next) return;

    Node *current = head;

    while (current) {
        Node *checker = current->next;
        bool hasDuplicate = false;

        while (checker) {
            Node *nextChecker = checker->next;
            if (checker->value == current->value) {
                hasDuplicate = true;

                if (checker == tail) {
                    removeBack();
                } else {
                    checker->prev->next = checker->next;
                    if (checker->next) {
                        checker->next->prev = checker->prev;
                    }
                    delete checker;
                    numNodes--;
                }
            }
            checker = nextChecker;
        }

        Node *nextCurrent = current->next;
        if (hasDuplicate) {
            if (current == head) {
                removeFront();
            } else if (current == tail) {
                removeBack();
            } else {
                current->prev->next = current->next;
                if (current->next) {
                    current->next->prev = current->prev;
                }
                delete current;
                numNodes--;
            }
        }

        current = nextCurrent;
    }
}

template <typename T>
void List<T>::remove(bool (*condition)(T value)) {
    Node *current = head;
    while (current != nullptr) {
        Node *nextNode = current->next;
        if (condition(current->value)) {
            if (current == head) {
                removeFront();
            } else if (current == tail) {
                removeBack();
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
                numNodes--;
            }
        }
        current = nextNode;
    }
}

template <typename T>
void List<T>::removeAll(T value) {
    Node *current = head;

    while (current != nullptr) {
        if (current->value == value) {
            Node *tmp = current;
            current = current->next;

            if (tmp == head) {
                removeFront();
            } else if (tmp == tail) {
                removeBack();
            } else {
                // removeAt(getPositionOf(value)); // Slower?
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
                delete tmp;
                numNodes--;
            }

        } else {
            current = current->next;
        }
    }
}

template <typename T>
void List<T>::sort() {
    if (numNodes < 1) return;

    for (Node *i = head; i != nullptr; i = i->next) {
        for (Node *j = i->next; j != nullptr; j = j->next) {
            if (i->value > j->value) {
                std::swap(i->value, j->value);
            }
        }
    }
}

template <typename T>
void List<T>::swapList(List<T> &other) {
    if (this == &other) return;

    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(numNodes, other.numNodes);
}

template <typename T>
void List<T>::transferAllElements(List<T> &other) {
    swapList(other); // ?
}

// template <typename T>
// void List<T>::transferInInterval(List<T>& other, int start, int end) {
//     Node* current = head;
//     int position = 0;
//     while (current != nullptr) {
//         if (position >= start && position <= end) {
//             other.addBack(current->value);
//             removeAt(position);
//         }
//         current = current->next;
//         position++;
//     }
// }

template <typename T>
bool List<T>::find(T value) const {
    Node *current = head;
    while (current != nullptr) {
        if (current->value == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename T>
int List<T>::getPositionOf(T value) const {
    if (find(value) == false) {
        return -1;
    }
    int position = 0;
    Node *current = head;
    while (current != nullptr) {
        if (current->value == value) {
            return position;
        }
        current = current->next;
        position++;
    }
    return -1;
}

template <typename T>
void List<T>::modifyElement(T value, int position) {
    Node *current = head;
    for (int i = 0; i < position; i++) {
        current = current->next;
    }
    current->value = value;
}

template <typename T>
bool List<T>::isEmpty() const {
    if (head == nullptr) {
        return true;
    } else {
        return false;
    }
}
template <typename T>
void List<T>::makeEmpty() {
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

template <typename T>
void List<T>::print() const {
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

template <typename T>
void List<T>::printReverse() const {
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

template <typename T>
T List<T>::getFront() const {
    if (head == nullptr) {
        return -1;
    } else {
        return head->value;
    }
}
template <typename T>
T List<T>::getBack() const {
    if (tail == nullptr) {
        return -1;
    } else {
        return tail->value;
    }
}
template <typename T>
T &List<T>::getElementAt(int position) const {
    // std::cout << "[DEBUG] Checking position: " << position
    //           << ", numNodes: " << numNodes
    //           << ", head: " << (head ? "NOT NULL" : "NULL") << std::endl;
    checkValidPosition(position);

    Node *current = head;
    for (int i = 0; i < position; i++) {
        current = current->next;
    }
    return current->value;
}
template <typename T>
int List<T>::getSize() const {
    return numNodes;
}

template <typename T>
void List<T>::checkValidPosition(int position) const {
    if (position < 0 || position >= numNodes || head == nullptr) {
        throw std::invalid_argument("Invalid Position");
    }
}
