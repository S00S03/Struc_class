#ifndef COLAMEDIEVAL_HPP
#define    COLAMEDIEVAL_HPP

#include <string>

#include "Queue.hpp"
#include "Persona.hpp"

class ColaMedieval
{
private:
    Queue<Persona> noble; 
    Queue<Persona> plebeyo; 

public:
    ColaMedieval();
    ColaMedieval(const ColaMedieval& other);
    ~ColaMedieval();

    void add(bool ist_noble, std::string nombre, int time_attencion);

    void remove_element(); 

    Persona get_frist() const;
    Persona get_last() const;
    
    int get_n_nobles() const;
    int get_n_plebeyos() const;
    int get_poblacion() const; 
    
    bool its_empty()const; 

    void empty();
    void print()const;

};

ColaMedieval::ColaMedieval(/* args */){}

ColaMedieval::~ColaMedieval()
{
    noble.~Queue(); 
    plebeyo.~Queue(); 
}

void ColaMedieval::add(bool its_noble, std::string nombre, int time_attencion){
    Persona aux;
    aux.nombre = nombre; 
    aux.noble = its_noble;
    aux.attention_time= time_attencion ; 
    
    if (its_noble){ 
        noble.enqueue(aux);
        return;
    }
    
    plebeyo.enqueue(aux);
    
}

void ColaMedieval::remove_element() {
    if(!noble.empty()){
        noble.dequeue();
        return;
    }
    
    plebeyo.dequeue();
}

Persona ColaMedieval::get_frist() const{
    if( noble.empty()) {
        return plebeyo.front(); 
    }
    
    return noble.front();
}

Persona ColaMedieval::get_last() const{
    if( plebeyo.empty()) {
        return noble.back(); 
    }
    
    return plebeyo.back();
}

 int ColaMedieval::get_n_nobles() const{
    return noble.size();
 }
    
 int ColaMedieval::get_n_plebeyos() const{
    return plebeyo.size();
 }
   
 int  ColaMedieval::get_poblacion() const{
    return noble.size() + plebeyo.size();
 }
    
bool ColaMedieval::its_empty() const {
    return (get_poblacion() == 0);
}

void ColaMedieval::empty() {
    noble.empty(); 
    plebeyo.empty();
}

void ColaMedieval::print()const{
    noble.print();
    plebeyo.print(); 
}



#endif