#include <iostream>
#include "Heap.hpp"

/**
 * \file main.cpp
 * \brief Heap Implementation
 * \author KEVIN RIVERA
 * \date 27/04/25
 */

bool min(int a, int b) { return a < b; }
bool max(int a, int b) { return a > b; }

int main () {
    Heap<int> heap(min);

    heap.insert(5);
    heap.insert(3);
    heap.insert(30);
    heap.insert(10);
    heap.insert(50);
    heap.insert(20);
    heap.insert(1);

    std::cout << "Original Heap: " << std::endl;
    heap.print();

    heap.remove();
    std::cout << "After removing root: " << std::endl;
    heap.print();

    std::cout << "Root: " << heap.getRoot() << std::endl;
    std::cout << "Size: " << heap.getSize() << std::endl;
    std::cout << "Elements: " << heap.getNumElements() << std::endl;

    std::cout << std::endl;

    // Copy constructor
    Heap heap2(heap);
    std::cout << "Copy constructor: " << std::endl;
    heap2.print();

    // Copy assignment
    Heap<int> heap3(min);
    heap3 = heap;
    std::cout << "Copy assignment: " << std::endl;
    heap3.print();
    
    return 0;
}
