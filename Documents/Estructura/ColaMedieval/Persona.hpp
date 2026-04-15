#ifndef PERSONA_HPP
#define PERSONA_HPP

#include <iostream>
#include <string>

class Persona {
public:
    std::string nombre;
    bool noble;
    int attention_time;

    void operator=(const Persona&other){
        nombre = other.nombre; 
        noble = other.noble; 
        attention_time = other.attention_time;
    }

    Persona(std::string nombre = "", int time = 0) {
        this->nombre = nombre;
        this->attention_time = time;
    }

    friend std::ostream& operator<<(std::ostream& os, const Persona& c) {
        os << c.nombre << " "; 
        
        if( c.noble )
            os << " Noble, tiempo de atencion: ";
        else
            os << " Plebeyo, tiempo de atencion: ";

        os << c.attention_time;
        return os;
    }
};

#endif