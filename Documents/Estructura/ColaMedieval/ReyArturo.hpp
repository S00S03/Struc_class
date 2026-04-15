#ifndef REY_ARTURO_HPP
#define REY_ARTURO_HPP

#include <iostream>

#include "Persona.hpp"
#include "Queue.hpp"

class ReyArturo
{
private:
    bool ocupado; 
    int tiempo_restante; 
    Persona actual; 
    Queue<Persona> atendidos; 

public:
    ReyArturo(/* args */);
    ~ReyArturo();

    bool ist_empty();
    void asignarPersona( const Persona&C);
    void avanzarTiempo();
    void imprimirEstado()const;
    void imprimirAtendidos() const;
};

ReyArturo::ReyArturo(/* args */)
{
    ocupado = false;
    tiempo_restante = 0;
}

ReyArturo::~ReyArturo()
{
}

bool ReyArturo::ist_empty(){
    return ocupado;
}

void ReyArturo::asignarPersona(const Persona& c){
    actual = c; 
     
    tiempo_restante = c.attention_time;
    ocupado = true;
}

void ReyArturo::avanzarTiempo() {
    if (ocupado) {
        tiempo_restante--;
        if (tiempo_restante == 0) {
            ocupado = false;
            atendidos.enqueue(actual);
        }
    }
}

void ReyArturo::imprimirEstado() const {
    if (ocupado) {
        std::cout << actual << ", tiempo restante: " << tiempo_restante << "\n";
    } else {
        std::cout << "Rey libre\n";
    }
}

void ReyArturo::imprimirAtendidos()const{
    atendidos.print();
}

#endif