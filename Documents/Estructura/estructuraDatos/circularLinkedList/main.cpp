#include "List.hpp"
int main () {
    List list;

    list.addHead(4);
    list.addHead(6);
    list.addHead(8);
    list.addHead(11);

    list.print();
    list.printConnections();

    list.removeAt(0);

    list.print();
    list.printConnections();
    
    return 0;
}
