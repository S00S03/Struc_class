#include "Expression.hpp"

#include <iostream>

int main () {
    std::string infix = "(1 + 2 / 3 * (4 + 5) - 6)";

    Expression e(infix);

    // Expression f;

    // f.evaluate();

    e.print();

    std::cout << e.evaluate() << std::endl;


    return 0;
}
