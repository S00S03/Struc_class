#include "SimpleList.hpp"

#include <iostream>

int main () {
    SimpleList list;
    list.addFirst(4);
    list.addFirst(2);
    list.addFirst(5);

    // std::cout << list.getPositionOf(5) << std::endl;

    list.print();

    return 0;
}
