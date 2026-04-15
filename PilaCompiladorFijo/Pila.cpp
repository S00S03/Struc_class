/*
Nombre del archivo:
Descripcion:
Autor: Erik Alexander Castro Barraza
Fecha:
*/

#include "Pila.hpp"
#include <iostream>


Pila::Pila()
{
    tope=-1;
    //ctor
}

//****************************************************************
void Pila::Agregar(char valor)
{
    if (EstaLLena())throw PilaLlena();
    elemento[++tope]= valor;
}

//****************************************************************
void Pila::Eliminar()
{
    if (EstaVacia()) throw PilaVacia();
    --tope;
}
//****************************************************************
int Pila::ObtenerTam() const
{
    return tope + 1;
}
//****************************************************************
bool Pila::EstaVacia() const
{
    return tope == -1;
}
//****************************************************************
bool Pila::EstaLLena() const
{
    return tope == MAX_TAM - 1;
}
//****************************************************************
char Pila::ObtenerTope() const
{
    if (EstaVacia()) throw PilaVacia();
    return elemento[tope];
}

//****************************************************************
void Pila::Vaciar()
{
    tope=-1;
}

//****************************************************************
void Pila::Imprimir() const
{
    std::cout<< "Tope ->";
    for(int i=tope; i>=0; --i)
        std::cout << "[" << elemento[i] << "] ";
}

//****************************************************************
// Clase auxiliar de la pila
//****************************************************************
Pila::PilaVacia::PilaVacia() throw() {}
//****************************************************************
const char * Pila::PilaVacia::what() const throw()
{
    return "La pila se encuentra vac\241a";
}
//****************************************************************
Pila::PilaLlena::PilaLlena() throw() {}
//****************************************************************
const char * Pila::PilaLlena::what() const throw()
{
    return "La pila se encuentra llena cablon";
}









