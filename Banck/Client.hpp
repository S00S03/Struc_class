#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <string>

class Client {
public:
    std::string nombre;
    int attention_time;

    Client(std::string nombre = "", int time = 0) {
        this->nombre = nombre;
        this->attention_time = time;
    }

    friend std::ostream& operator<<(std::ostream& os, const Client& c) {
        os << c.nombre << "(" << c.attention_time << ")";
        return os;
    }
};

#endif