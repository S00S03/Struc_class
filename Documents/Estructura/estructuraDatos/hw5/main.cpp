#include <iostream>

#include "List.hpp"

bool isEven(int value) { return value % 2 == 0; }

int main() {
    int *ptr;

    ptr = new int;

    List<int> list;

    List<int> list2;

    List<std::string> list3;

    list2.addBack(1);
    list2.addBack(2);
    list2.addBack(3);

    list.addFront(5);
    list.addFront(6);

    list.addBack(1);
    list.addBack(2);
    list.addBack(2);

    // list.remove(isEven);
    // list.removeAll(2);
    // list.removeAllDuplicates();

    // list.removeAt(3);

    // list.addAt(9, 3);

    // list.modifyElement(3, 2);

    // list.swapList(list2);

    list.sort();

    // list2.print();
    // list.print();
    // std::cout << list.getElementAt(2) << std::endl;

    // list.removeFront();
    // list.removeBack();

    // list.makeEmpty();
    // list.print();
    // list.printReverse();

    list3.addBack("hola");
    list3.addBack("wola");
    list3.addBack("adios");
    list3.addBack("test");

    list3.sort();

    list3.print();
    return 0;
}
