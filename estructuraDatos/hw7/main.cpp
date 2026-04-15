#include "Graph.hpp"
#include "Stack.hpp"
#include "Queue.hpp"

/**
 * \file main.cpp
 * \brief Fleury's Algorithm Implementation
 * \author KEVIN RIVERA
 * \date 23/03/2025
 */

void fleuryAlgorithm(Graph& g, char startNode) {
    // 1.
    Stack<char> stack;
    Queue<char> queue;

    char v_c = startNode;
    char v_p = startNode;

    queue.enqueue(v_c);
    stack.push(v_p);

    // 2.
    while (g.getDegree(v_c) != 0 && g.getDegree(v_p) != 0) {
        // 2. (a)
        if (g.getDegree(v_c) > 0) {
            char nextNode = '\0';
            bool found = false;

            for (char k = 'A'; k <= 'Z'; k++) {
                if (g.findEdge(v_c, k)) {
                    if (!found || g.getDegree(k) > 1) {
                        nextNode = k;
                        found = true;
                    }
                }
            }

            if (nextNode != '\0') {
                g.removeEdge(v_c, nextNode);
                queue.enqueue(nextNode);
                v_c = nextNode;
            }
        }
        // 2. (b)
        else if (g.getDegree(v_p) == 1) {
            for (char k = 'A'; k <= 'Z'; k++) {
                if (g.findEdge(v_p, k)) {
                    g.removeEdge(v_p, k);
                    queue.enqueue(k);
                    v_p = k;
                    break;
                }
            }
        }
    }

    std::cout << "Fleury Algorithm: ";
    // 3.
    while (!queue.isEmpty()) {
        std::cout << queue.getFront() << " ";
        queue.dequeue();
    }

    while (!stack.isEmpty()) {
        std::cout << stack.top() << " ";
        stack.pop();
    }
    std::cout << std::endl;
}

int main() {
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

    std::cout << "Initializing Fleury Algorithm" << std::endl;
    fleuryAlgorithm(g, 'A');

    return 0;
}
