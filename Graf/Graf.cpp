#include <iostream>
#include "Graph.hpp"
using namespace std;

int main()
{
    Graph<string> g;

    cout << "=== Adding nodes ===\n";
    g.add_node("A");
    g.add_node("B");
    g.add_node("C");
    g.add_node("D");

    g.print();

    cout << "\n=== Adding edges ===\n";
    g.add_edge("A", "B");
    g.add_edge("A", "C");
    g.add_edge("B", "D");
    g.add_edge("C", "D");

    g.print();

    cout << "\n=== Check nodes ===\n";
    cout << "Has A: " << g.has_node("A") << endl;
    cout << "Has Z: " << g.has_node("Z") << endl;

    cout << "\n=== Check edges ===\n";
    cout << "A -> B: " << g.has_edge("A", "B") << endl;
    cout << "B -> C: " << g.has_edge("B", "C") << endl;

    cout << "\n=== Degree ===\n";
    cout << "Degree of A: " << g.get_degree("A") << endl;
    cout << "Degree of B: " << g.get_degree("B") << endl;

    cout << "\n=== Remove edge A -> C ===\n";
    g.remove_edge("A", "C");
    g.print();

    cout << "\n=== Remove node B ===\n";
    g.remove_node("B");
    g.print();

    cout << "\n=== Graph info ===\n";
    cout << "Order (nodes): " << g.get_order() << endl;
    cout << "Size (edges): " << g.get_size() << endl;

    cout << "\n=== Clear node C ===\n";
    g.clear_node("C");
    g.print();

    cout << "\n=== Clear all graph ===\n";
    g.clear();
    cout << "Is empty: " << g.is_empty() << endl;

    return 0;
}