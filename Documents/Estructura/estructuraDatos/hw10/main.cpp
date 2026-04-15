#include "BTree.hpp"

/**
 * \file main.cpp
 * \brief BTree Implementation
 * \author KEVIN RIVERA
 * \date 04/05/25
 */

int main() {
    BTree<int, 4> bst;

    // int data[] = {10, 12, 30, 7, 17, 25, 1, 2};

    // std::vector<int> values = {50, 30, 70, 40, 20, 60, 80, 10, 90, 55, 35};
    std::vector<int> values = {1,2,5,3};
    for (int key : values) {
        bst.insert(key);
        std::cout << "After inserting " << key << ":\n";
        bst.printByLevel();
        std::cout << "-------------------\n";
    }

    std::cout << "Inorder traversal: ";
    bst.printAscending();

    // BTree<int> tree;
    // tree.insert(7);
    // tree.insert(5);
    // tree.insert(9);
    // tree.insert(4);
    // tree.insert(6);
    // tree.insert(8);
    // tree.insert(10);
    // tree.insert(11);
    // tree.insert(12);
    // tree.insert(13);
    // tree.insert(14);
    // tree.insert(15);
    // tree.insert(16);
    // tree.insert(17);
    // tree.insert(18);
    //
    // std::cout << "Original tree" << std::endl;
    // tree.printByLevel();
    //
    // std::cout << "Removing 9" << std::endl;
    // tree.remove(9);
    // tree.printByLevel();
    //
    // std::cout << "Adding 1" << std::endl;
    // tree.insert(1);
    // tree.printByLevel();
    //
    // std::cout << "Adding 2" << std::endl;
    // tree.insert(2);
    // tree.printByLevel();
    //
    // std::cout << "Adding 3" << std::endl;
    // tree.insert(3);
    // tree.printByLevel();
    //
    //
    // std::cout << std::endl;
    //
    // std::cout << "Search 4: " << tree.search(4) << std::endl;
    //
    // std::cout << "Number of total keys in the tree: " << tree.getNumKeys()
    //           << std::endl;
    //
    // std::cout << std::endl;
    //
    // BTree tree2(tree);
    // std::cout << "Copy of tree 1 (Copy constructor, printed Ascending)"
    //           << std::endl;
    // tree2.printAscending();
    //
    // BTree<int> tree3;
    // tree3 = tree;
    // std::cout << "Copy of tree 1 (Copy assignment, printed Descending)"
    //           << std::endl;
    // tree3.printDescending();
    //
    // std::cout << std::endl;
    //
    // std::cout << "Clearing the last tree" << std::endl;
    // tree3.clear();
    // std::cout << "Tree 3 (now empty):" << std::endl;
    // tree3.printByLevel();

    return 0;
}
