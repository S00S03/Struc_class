#include <iostream>
#include "vector.hpp"

int main() {
    Vector v(3, 1); // Llamada automatica al constructor
    Vector w(3, 3);
    v.print();
    w.print();

    Vector z = v + w;
    Vector x = v - w;
    Vector y = v * w;
    Vector u = v * 2;
    Vector b = 2 * v;

    std::cout << "Suma: " << std::endl;
    z.print();

    std::cout << "Resta: " <<  std::endl;
    x.print();

    std::cout << "Multiplicacion: " << std::endl;
    y.print();

    std::cout << "Multiplicacion por escalar: " << std::endl;
    u.print();

    std::cout << "Multiplicacion por escalar: " << std::endl;
    b.print();

    return 0;
}
