#include "AVLTree.hpp"
#include <iostream>

/**
 * \file main.cpp
 * \brief AVLTree Implementation
 * \author KEVIN RIVERA
 * \date 20/04/25
 */


int main() {
    AVLTree<int> tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(25);
    tree.insert(5);
    tree.insert(15);

    std::cout << "In ascending order: ";
    tree.printAscending();

    std::cout << "In descending order: ";
    tree.printDescending();

    std::cout << "Level-order: ";
    tree.printByHeight();

    std::cout << "Height: " << tree.getHeight(tree.getRoot()) << std::endl;
    std::cout << "Node count: " << tree.getNodeCount() << std::endl;

    std::cout << "Removing 20..." << std::endl;
    tree.remove(20);

    std::cout << "Level-order after removal: ";
    tree.printByHeight();

    std::cout << "Searching 15: " << (tree.search(15) ? "Found" : "Not Found") << std::endl;
    std::cout << "Searching 100: " << (tree.search(100) ? "Found" : "Not Found") << std::endl;

    std::cout << "Testing copy constructor..." << std::endl;
    AVLTree<int> treeCopy(tree);
    treeCopy.insert(99);
    std::cout << "Copy tree level-order: ";
    treeCopy.printByHeight();

    std::cout << "Original tree level-order: ";
    tree.printByHeight();

    return 0;
}
