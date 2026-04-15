#ifndef MATRIX_HPP_INCLUDE
#define MATRIX_HPP_INCLUDE

#include <iostream>

/**
 * @class Matrix
 * @brief Clase para el manejo de matrices dinámicas de números reales
 *
 * Esta clase permite crear matrices de tamaño dinámico y realizar
 * operaciones básicas como suma, resta, multiplicación, transpuesta
 * e inversa. La memoria es gestionada manualmente mediante punteros.
 *
 * @author Arredondo Benites Axel Daniel
 * @author Luis Enrrique Galindo Miranda
 * @date 9 de febrero
 */
class Matrix
{
    /**
     * @brief Sobrecarga del operador << para imprimir la matriz
     * @param output Flujo de salida
     * @param m Matriz a imprimir
     * @return Referencia al flujo de salida
     */
    friend std::ostream &operator<<(std::ostream &output, Matrix &m);

    /**
     * @brief Sobrecarga del operador >> para ingresar los valores de la matriz
     * @param input Flujo de entrada
     * @param m Matriz a llenar
     * @return Referencia al flujo de entrada
     */
    friend std::istream &operator>>(std::istream &input, Matrix &m);
    
public:
    /**
     * @brief Constructor que inicializa una matriz con filas y columnas
     * @param Row Número de filas
     * @param Column Número de columnas
     */
    Matrix(const unsigned int &Row, const unsigned int &Column);

    /**
     * @brief Constructor de copia
     * @param Other Matriz a copiar
     */
    Matrix(const Matrix &Other);

    /**
     * @brief Destructor de la clase Matrix
     */
    ~Matrix();
    
    /**
     * @brief Sobrecarga del operador de asignación
     * @param Other Matriz a asignar
     * @return Referencia al objeto actual
     */
    Matrix& operator=(const Matrix &Other);

    /**
     * @brief Suma de matrices
     * @param Other Matriz a sumar
     * @return Matriz resultante
     */
    Matrix operator+(const Matrix &Other) const;

    /**
     * @brief Resta de matrices
     * @param Other Matriz a restar
     * @return Matriz resultante
     */
    Matrix operator-(const Matrix &Other) const;

    /**
     * @brief Multiplicación de matrices
     * @param Other Matriz multiplicadora
     * @return Matriz resultante
     */
    Matrix operator*(const Matrix &Other) const;

    /**
     * @brief Multiplicación escalar
     * @param Scalar Escalar
     * @return Matriz resultante
     */
    Matrix operator*(const double &Scalar) const;

    /**
     * @brief Acceso a una fila de la matriz
     * @param i Índice de la fila
     * @return Puntero a la fila
     */
    double* operator[](int i) const;
    
    /**
     * @brief Redimensiona la matriz a un tamaño mayor
     * @param new_Rows Nuevas filas
     * @param new_Colums Nuevas columnas
     */
    void Redim(const unsigned int &new_Rows, const unsigned int &new_Colums);

    /**
     * @brief Calcula la transpuesta de la matriz
     * @return Matriz transpuesta
     */
    Matrix Trans();

    /**
     * @brief Calcula la inversa de la matriz
     * @return Matriz inversa
     */
    Matrix Inversa();
    
private:
    /**
     * @brief Imprime la matriz (uso exclusivo para depuración)
     */
    void print();

    /**
     * @brief Inicializa la matriz con ceros
     */
    void Matrix_Default();

    /// Número de filas
    unsigned int m_Row;

    /// Número de columnas
    unsigned int m_Column;

    /// Puntero doble que almacena los componentes de la matriz
    double **m_comp;
};

#endif
