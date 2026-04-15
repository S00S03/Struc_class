#include <iostream>
#include "Queue.hpp"

int main() {

    Queue<int> q;

    std::cout << "¿Esta vacia? " << q.empty() << std::endl;

    std::cout << "\nAgregando elementos...\n";
    q.add(10);
    q.add(20);
    q.add(30);
    q.add(40);

    std::cout << "Contenido de la cola: ";
    q.print();

    std::cout << "Front: " << q.front() << std::endl;
    std::cout << "Back: " << q.back() << std::endl;

    std::cout << "Size: " << q.size() << std::endl;

    std::cout << "\nSacando un elemento...\n";
    q.out();

    std::cout << "Contenido de la cola: ";
    q.print();

    std::cout << "Front ahora: " << q.front() << std::endl;
    std::cout << "Back ahora: " << q.back() << std::endl;

    std::cout << "Size ahora: " << q.size() << std::endl;

    std::cout << "\nVaciando la cola...\n";
    while(!q.empty()){
        q.out();
        q.print();
    }

    std::cout << "¿Esta vacia? " << q.empty() << std::endl;

    return 0;
}