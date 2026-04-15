#include "OrderedList.hpp"

int main () {
    List<int> list;
    list.addFront(1);
    list.addFront(2);

    List<int> list2;
    list2.addFront(3);
    list2.addFront(4);

    list.print();
    list2.print();

    OrderedList<int> mergedList;
    mergedList = mergedList.merge(list, list2);
    mergedList.printAscending();
    mergedList.printDescending();



    return 0;
}
