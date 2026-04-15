#include "BStarTree.hpp"
#include <iostream>

int main() {
    BStarTree bst;

    // int data[] = {10, 15, 17, 19, 20, 30, 40, 18};
    //
    // for (int val : data) {
    //     std::cout << "--------------" << std::endl;
    //     std::cout << "Inserting: " << val << std::endl;
    //     std::cin >> b;
    //     bst.insert(val);
    //     std::cout << std::endl;
    //     bst.printByLevel();
    // }

    int b;
    while(true) {
        std::cout << "--------------" << std::endl;
        std::cout << "Insert a value: ";
        std::cin >> b;
        bst.insert(b);
        std::cout << std::endl;
        bst.printByLevel();
    }

    return 0;
}
