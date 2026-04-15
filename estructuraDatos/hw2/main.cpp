#include "Stack.hpp"

#include <iostream>

int main () {
    Stack<int> intStack(5);

    for (int i = 0; i < 5; i++) {
        std::cout << "Pushing " << i + 1 << std::endl;
        intStack.push(i + 1);
    }

    std::cout << "Stack content: " << std::endl;
    intStack.print();

    std::cout << "Size: " << intStack.getSize() << std::endl;
    std::cout << "Capacity: " << intStack.getCapacity() << std::endl;

    std::cout << "Top Element: " << intStack.top() << std::endl;

    // for (int i = 0; i < intStack.getCapacity(); i++) {
    //     std::cout << "Removing: " << intStack.top() << std::endl;
    //     intStack.pop();
    // }

    if (intStack.isEmpty()) {
        std::cout << "Stack is empty" << std::endl;
    } else {
        std::cout << "Stack is not empty" << std::endl;
        
    }

    Stack<int> copyStack = intStack;

    copyStack.print();

    return 0;
}
