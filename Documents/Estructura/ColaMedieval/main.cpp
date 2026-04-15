/**
 * @file main.cpp
 * 
 * @author Axel Daniel Arredondo Benites
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include <cstdlib>
#include <string>

#include "Queue.hpp"
#include "ColaMedieval.hpp"
#include "ReyArturo.hpp"

std::string nombres_n[] = {
    "Montserrat", "Sandra", "Axel", "Daniel",
    "Eliot", "Kamila", "Kevin", "Manuel"
};

std::string apellidos_n[] = {
    "Arce", "Jauregui", "Arredondo", "Benites",
    "Mendez", "Espinoza"
};

std::string nombres_p[] = {
    "pedro", "juan", "pepe", "quico",
    "chuy", "ramiro", "kamilo", "carlos", "mario", 
    "cantinflas", "pablo", "joshu", "cabezuco", "patricio",
    "catatu", "ioio"
};

std::string apellidos_p[] = {
    "Garcia", "Rodriguez", "Martinez", "Hernandez", "Lopez", "Gonzalez",
    "Perez", "Sanchez", "Ramirez", "Torres", "Flores", "Morales",
    "Vazquez", "Castillo", "Guzman", "Salazar", "Villanueva", "Montalvo"
};

/// Genera nombre aleatorio
std::string generarNombre_n() {
    return nombres_n[rand() % 8] + " " + apellidos_n[rand() % 8];
}

std::string generarNombre_p(){
    return nombres_n[rand() % 16] + " " + apellidos_n[rand() % 18];
}

int main() {

    srand(time(0));

    int tiempo_total = rand() % 121 + 120;
    int reloj = 0;

    Queue<Persona> atendidos;
    ColaMedieval cola;
    ReyArturo rey;

    while (reloj <= tiempo_total) {

        std::cout << "Tiempo: " << reloj << "\n";

        /// Llegada aleatoria de clientes
        if (rand() % 2 == 0) {
            bool noble = rand()%2 == 0; 
            int time = rand() % 10 + 1;

            if (noble)
                cola.add(noble, generarNombre_n(), time);
            else 
                cola.add(noble, generarNombre_p(), time);
        }

        rey.avanzarTiempo();

        if (!rey.ist_empty() && !cola.its_empty()) {
            Persona c = cola.get_frist();
            cola.remove_element();
            rey.asignarPersona(c);
        }

        std::cout << "en espera: ";
        cola.print();
        std::cout << "\n";

        std::cout << "Atendiendo :\n";
        rey.imprimirEstado();

        std::cout << "----------------------\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        reloj++;
        system("clear");
    }

    std::cout << "\n=== RESULTADOS ===\n";

    
    rey.imprimirAtendidos();

    std::cout << "Clientes en cola final: ";
    cola.print();
    std::cout << "\n";

    return 0;
}