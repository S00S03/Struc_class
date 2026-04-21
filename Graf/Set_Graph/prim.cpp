#include "Graph.hpp"
#include <iostream>
using namespace std;

int main()
{
    Graph<string> g;

    cout << "=== Creating graph ===\n";

    g.add_node("A");
    g.add_node("B");
    g.add_node("C");
    g.add_node("D");
    g.add_node("E");

    g.add_edge("A", "B", 1);
    g.add_edge("A", "C", 5);
    g.add_edge("B", "C", 2);
    g.add_edge("B", "D", 4);
    g.add_edge("C", "D", 3);
    g.add_edge("C", "E", 6);
    g.add_edge("D", "E", 7);

    cout << "\n=== Original Graph ===\n";
    g.print();

    cout << "\nNodes: " << g.get_order() << endl;
    cout << "Edges: " << g.get_size() << endl;

    cout << "\n=== Running Prim from A ===\n";
    Graph<string> mst = g.prim("A");

    cout << "\n=== Minimum Spanning Tree ===\n";
    mst.print();

    return 0;
}