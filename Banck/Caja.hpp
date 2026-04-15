#ifndef CAJA_HPP
#define CAJA_HPP

#include <iostream>
#include <vector>
#include <string>
#include "Client.hpp"

class Caja {
private:
    bool ocupada;
    int tiempo_restante;
    Client cliente_actual;
    std::vector<std::string> atendidos;

public:
    Caja() {
        ocupada = false;
        tiempo_restante = 0;
    }

    bool estaOcupada() const {
        return ocupada;
    }

    void asignarCliente(const Client& c) {
        cliente_actual = c;
        tiempo_restante = c.attention_time;
        ocupada = true;
    }

    void avanzarTiempo() {
        if (ocupada) {
            tiempo_restante--;
            if (tiempo_restante == 0) {
                ocupada = false;
                atendidos.push_back(cliente_actual.nombre);
            }
        }
    }

    void imprimirEstado(int i) const {
        if (ocupada) {
            std::cout << "Caja " << i << ": "
                      << cliente_actual.nombre
                      << " (" << tiempo_restante << ")\n";
        } else {
            std::cout << "Caja " << i << ": Libre\n";
        }
    }

    void imprimirAtendidos(int i) const {
        std::cout << "~~Caja " << i << "~~ atendio: \n";
        for (const auto& nombre : atendidos)
            std::cout << nombre << "\n";
    }
};

#endif