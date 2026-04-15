#include <iostream>
#include "List.hpp"

int main() {
    List<int> lista;

    std::cout << "¿Lista vacia?: " << lista.its_empty() << std::endl;

    // Agregar elementos
    lista.add_last(10);
    lista.add_last(20);
    lista.add_last(30);
    lista.add_frist(5);

    std::cout << "Lista despues de agregar elementos: ";
    lista.print();

    std::cout << "Tamano: " << lista.get_size() << std::endl;

    // Agregar en posicion
    lista.add_in_pos(15, 2);
    std::cout << "Despues de insertar 15 en pos 2: ";
    lista.print();

    // Obtener elementos
    std::cout << "Primer elemento: " << lista.get_frist() << std::endl;
    std::cout << "Ultimo elemento: " << lista.get_last() << std::endl;
    std::cout << "Elemento en pos 2: " << lista.get_in_pos(2) << std::endl;

    // Buscar
    std::cout << "Buscar 20: " << lista.shearch(20) << std::endl;
    std::cout << "Posicion de 30: " << lista.get_pos(30) << std::endl;

    // Eliminar
    lista.remove_frist();
    std::cout << "Despues de eliminar primero: ";
    lista.print();

    lista.remove_last();
    std::cout << "Despues de eliminar ultimo: ";
    lista.print();

    lista.remove_in_pos(1);
    std::cout << "Despues de eliminar en pos 1: ";
    lista.print();

    // Imprimir reverso
    std::cout << "Lista en reversa: ";
    lista.print_rv();

    // Vaciar lista
    lista.empty();
    std::cout << "Despues de vaciar lista, vacia?: " << lista.its_empty() << std::endl;

    return 0;
}