#ifndef PILA_HPP
#define PILA_HPP
#define MAX_TAM 10
#include <exception>

class Pila
{
    public:
        /** Default constructor */
        Pila();
        void Agregar(char valor);

        void Eliminar();

        int ObtenerTam() const;

        bool EstaVacia() const;

        bool EstaLLena() const;

        char ObtenerTope() const;

        void Vaciar();

        void Imprimir() const;

            class PilaVacia : public std::exception{

            public:
                PilaVacia() throw();
                virtual const char *what() const throw();

            };

            class PilaLlena : public std::exception{

            public:
                PilaLlena() throw();
                virtual const char *what() const throw();

            };




    protected:

    private:
        int tope; //!< Member variable "tope"
        char elemento[MAX_TAM]; //!< Member variable "elemento[MAX]"
};

#endif // PILA_HPP
