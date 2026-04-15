/**
 * @file main.cpp
 * @brief Simulación de banco con cola circular y 3 cajas.
 * 
 * @author Axel Daniel Arredondo Benites
 * @author Galindo Miranda Luis
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include <cstdlib>
#include <string>

#include "Queue.hpp"
#include "Caja.hpp"

std::string nombres[] = {
    "Montserrat", "Sandra", "Axel", "Daniel",
    "Eliot", "Kamila", "Kevin", "Manuel"
};

std::string apellidos[] = {
    "Arce", "Jauregui", "Arredondo", "Benites",
    "Mendez", "Espinoza", "Juarez", "Peru"
};

/// Genera nombre aleatorio
std::string generarNombre() {
    return nombres[rand() % 8] + " " + apellidos[rand() % 8];
}

int main() {

    srand(time(0));

    int tiempo_total = rand() % 121 + 120;
    int reloj = 0;

    Queue<Client> cola;
    Caja cajas[3];

    while (reloj <= tiempo_total) {

        std::cout << "Tiempo: " << reloj << "\n";

        /// Llegada aleatoria de clientes
        if (rand() % 2 == 0) {
            Client c(generarNombre(), rand() % 10 + 1);
            cola.enqueue(c);
        }

        /// Procesamiento de cajas
        for (int i = 0; i < 3; i++) {

            cajas[i].avanzarTiempo();

            if (!cajas[i].estaOcupada() && !cola.empty()) {
                Client c = cola.front();
                cola.dequeue();
                cajas[i].asignarCliente(c);
            }
        }

        std::cout << "Cola: ";
        cola.print();
        std::cout << "\n";

        for (int i = 0; i < 3; i++) {
            cajas[i].imprimirEstado(i);
        }

        std::cout << "----------------------\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        reloj++;
    }

    std::cout << "\n=== RESULTADOS ===\n";

    for (int i = 0; i < 3; i++) {
        cajas[i].imprimirAtendidos(i);
    }

    std::cout << "Clientes en cola final: ";
    cola.print();
    std::cout << "\n";

    return 0;
}