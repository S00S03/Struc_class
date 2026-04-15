#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>
#include <iostream>
#include <stdexcept>

/**
 * @brief Clase plantilla que implementa una pila (Stack) dinámica.
 * 
 * Implementa una estructura LIFO (Last In, First Out).
 * La memoria se gestiona dinámicamente y se redimensiona automáticamente
 * cuando se alcanza la capacidad máxima.
 * 
 * @tparam T Tipo de dato almacenado en la pila.
 */
template <typename T>
class Stack
{   
    public:

        /**
         * @brief Constructor por defecto.
         * Inicializa la pila con capacidad inicial de 10 elementos.
         */
        Stack();

        /**
         * @brief Constructor de copia.
         * @param other Objeto Stack a copiar.
         */
        Stack(const Stack &other);

        /**
         * @brief Destructor.
         * Libera la memoria dinámica utilizada por la pila.
         */
        ~Stack();
        
        /**
         * @brief Operador de asignación.
         * @param other Objeto Stack a copiar.
         * @return Referencia al objeto actual.
         */
        Stack& operator=(const Stack &other);

        /**
         * @brief Inserta un nuevo elemento en la cima de la pila.
         * @param new_element Elemento a insertar.
         */
        void push(const T &new_element);

        /**
         * @brief Elimina el elemento superior de la pila.
         */
        void pop();

        /**
         * @brief Obtiene el número de elementos almacenados.
         * @return Cantidad de elementos en la pila.
         */
        int size() const;

        /**
         * @brief Verifica si la pila está vacía.
         * @return true si está vacía.
         * @return false si contiene elementos.
         */
        bool empty() const;

        /**
         * @brief Vacía completamente la pila.
         */
        void empty_Stack();

        /**
         * @brief Devuelve el elemento en la cima.
         * @return Elemento superior.
         * @throws std::out_of_range si la pila está vacía.
         */
        T top() const;

        /**
         * @brief Imprime el contenido de la pila.
         */
        void print() const;
        
    private:

        /**
         * @brief Verifica si la pila alcanzó su capacidad máxima.
         * @return true si está llena.
         */
        bool full() const;

        /**
         * @brief Duplica la capacidad de la pila.
         */
        void redim();
        
        size_t capacity;   ///< Capacidad máxima actual
        int num_element;   ///< Índice del último elemento
        T* stack;          ///< Arreglo dinámico que almacena los datos
};

/* ================= IMPLEMENTACIÓN ================= */

template <typename T>
Stack<T>::Stack() {
    num_element = -1;
    capacity = 10;
    stack = new T[capacity];
}

template <typename T>
Stack<T>::Stack(const Stack &other) {
    capacity = other.capacity;
    num_element = other.num_element;
    stack = new T[capacity];

    for (int i = 0; i <= num_element; i++) {
        stack[i] = other.stack[i];
    }
}

template <typename T>
Stack<T>::~Stack() {
    delete[] stack;
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack &other) {
    if (this != &other) {
        delete[] stack;

        capacity = other.capacity;
        num_element = other.num_element;
        stack = new T[capacity];

        for (int i = 0; i <= num_element; i++) {
            stack[i] = other.stack[i];
        }
    }
    return *this;
}

template <typename T>
void Stack<T>::push(const T &new_element) {
    if (full()) {
        redim();
    }

    num_element++;
    stack[num_element] = new_element;
}

template <typename T>
void Stack<T>::redim() {
    capacity *= 2;
    T *new_stack = new T[capacity];

    for (int i = 0; i <= num_element; i++) {
        new_stack[i] = stack[i];
    }

    delete[] stack;
    stack = new_stack;
}

template <typename T>
void Stack<T>::pop() {
    if (empty()) {
        std::cout << "La pila esta vacia no le puedes quitar nada";
        return;
    }
    --num_element;
}

template <typename T>
int Stack<T>::size() const {
    return num_element + 1;
}

template <typename T>
bool Stack<T>::empty() const {
    return num_element == -1;
}

template <typename T>
void Stack<T>::empty_Stack() {
    num_element = -1;
}

template <typename T>
T Stack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("Stack vacia");
    }
    return stack[num_element];
}

template <typename T>
bool Stack<T>::full() const {
    return num_element == capacity - 1;
}

template <typename T>
void Stack<T>::print() const {
    if (empty()) {
        std::cout << "Pila vacia que vas a imprimir\n";
        return;
    }

    std::cout << "Elements for stack: ";
    for (int i = num_element; i >= 0; --i) {
        std::cout << " [" << i << "] = " << stack[i];
    }
    std::cout << std::endl;
}

#endif