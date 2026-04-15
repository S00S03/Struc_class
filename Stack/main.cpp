/**
 * @file main.cpp
 * @brief Pruebas completas de la clase Stack.
 * 
 * Se prueba con:
 *  - Stack<int>
 *  - Stack<std::string>
 *  - Stack< Stack<int> >
 * 
 * Autores:
 *  Axel Daniel Arredondo Benites
 *  Galindo Miranda Luis
 */

#include <iostream>
#include <string>
#include "Stack.hpp"

int main() {

    /* ============================================================
       PRUEBA 1: STACK<int>
       ============================================================ */
    std::cout << "========== STACK<int> ==========\n";

    Stack<int> s_int;
    s_int.push(1);
    s_int.push(2);
    s_int.push(3);

    s_int.print();
    std::cout << "Top: " << s_int.top() << "\n\n";


    /* ============================================================
       PRUEBA 2: STACK<string>
       ============================================================ */
    std::cout << "========== STACK<string> ==========\n";

    Stack<std::string> s_str;
    s_str.push("Uno");
    s_str.push("Dos");
    s_str.push("Tres");

    s_str.print();
    std::cout << "Top: " << s_str.top() << "\n\n";


    /* ============================================================
       PRUEBA 3: STACK< STACK<int> >
       ============================================================ */
    std::cout << "========== STACK< STACK<int> > ==========\n";

    // Crear dos pilas internas
    Stack<int> inner1;
    inner1.push(10);
    inner1.push(20);

    Stack<int> inner2;
    inner2.push(100);
    inner2.push(200);

    // Pila de pilas
    Stack< Stack<int> > stack_of_stacks;

    stack_of_stacks.push(inner1);
    stack_of_stacks.push(inner2);

    std::cout << "\nMostrando pila superior (inner2):\n";
    stack_of_stacks.top().print();

    stack_of_stacks.pop();

    std::cout << "\nDespues de pop, nueva pila superior (inner1):\n";
    stack_of_stacks.top().print();

    return 0;
}