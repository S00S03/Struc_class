#include "Graph.hpp"
#include <iostream>


int main () {
    Graph g;

    g.addNode('A');
    g.addNode('B');
    g.addNode('C');
    g.addNode('D');
    g.addEdge('A', 'B');
    g.addEdge('A', 'D');
    g.addEdge('B', 'C');
    g.addEdge('B', 'D');
    g.addEdge('C', 'D');

    g.print();


    return 0;
}
