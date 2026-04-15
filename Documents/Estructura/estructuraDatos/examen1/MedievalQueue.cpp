#include "MedievalQueue.hpp"
#include <iostream>
#include <stdexcept>

MedievalQueue::MedievalQueue() : numElements(0), numPlebeyos(0), numNobles(0) {
    Elements = new std::string[100];
}

// destructor
MedievalQueue::~MedievalQueue() { delete[] Elements; }
// copy constructor
MedievalQueue::MedievalQueue(const MedievalQueue &other)
    : numElements(other.numElements), numNobles(other.numNobles),
      numPlebeyos(other.numPlebeyos) {
    Elements = new std::string[100];
    for (int i = 0; i < numElements; i++) {
        Elements[i] = other.Elements[i];
    }
}

// Add a new person to the queue
void MedievalQueue::enqueue(std::string person, bool isNoble) {
    if (isNoble) {
        // This fixes the 1st plebeyo not appearing by moving the nobles
        for (int i = numElements; i > numNobles; i--) {
            Elements[i] = Elements[i - 1];
        }
        Elements[numNobles] = person;
        numNobles++;
    } else {
        Elements[numElements] = person;
        numPlebeyos++;
    }
    numElements++;
}
void MedievalQueue::dequeue() {
    if (isEmpty()) {
        throw std::invalid_argument("The queue is empty");
    }
    numElements--;
    for (int i = 0; i < numElements; i++) {
        Elements[i] = Elements[i + 1];
    }
}

// Get first element
std::string MedievalQueue::front() const { return Elements[0]; }

bool MedievalQueue::isEmpty() const {
    if (numElements == 0) {
        return true;
    } else {
        return false;
    }
}

void MedievalQueue::print() const {
    for (int i = 0; i < numElements; i++) {
        std::cout << Elements[i] << std::endl;
    }
}

// debugging 1stplebeyo
// void MedievalQueue::getPosition(int position) const {
//     std::cout << Elements[position] << std::endl;
// }

int MedievalQueue::getNumNobles() const { return numNobles; }
int MedievalQueue::getNumPlebeyos() const { return numPlebeyos; }
