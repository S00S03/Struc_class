/**
 * @file Matrix.cpp
 * @brief Implementación de la clase Matrix
 *
 * La clase Matrix permite la creación y manipulación de matrices dinámicas
 * de números reales. Implementa operaciones básicas como suma, resta,
 * multiplicación (escalar y matricial), transpuesta e inversa.
 *
 * @author Arredondo Benites Axel Daniel
 * @author Luis Enrrique Galindo Miranda
 * @date 9 de febrero
 */

#include "Matrix.hpp"
#include <iostream>

/**
 * @brief Sobrecarga del operador << para imprimir la matriz
 * @param output Flujo de salida
 * @param m Matriz a imprimir
 * @return Referencia al flujo de salida
 */
std::ostream &operator<<(std::ostream &output, Matrix &m){
    for(int i = 0; i < m.m_Row; i++){
        for(int j = 0; j< m.m_Column; j++){
            output << m.m_comp[i][j] << " ";
        }
        output << "\n";
    }
    return output;
}

/**
 * @brief Sobrecarga del operador >> para ingresar los valores de la matriz
 * @param input Flujo de entrada
 * @param m Matriz a llenar
 * @return Referencia al flujo de entrada
 */
std::istream &operator>>(std::istream &input, Matrix &m){
    for(int i = 0; i < m.m_Row; i++){
        for(int j = 0; j< m.m_Column; j++){
            std::cout << "component [" << i << "][" << j << "]: ";
            input >> m.m_comp[i][j];
        }
    }
    return input;
}

/**
 * @brief Constructor que inicializa una matriz con filas y columnas
 * @param Row Número de filas
 * @param Column Número de columnas
 */
Matrix::Matrix(const unsigned int &Row, const unsigned int &Column){
    m_Row = Row;
    m_Column = Column;

    m_comp = new double*[m_Row];
    for (int i = 0; i < m_Row; i++){
        m_comp[i] = new double[m_Column];
    }

    Matrix_Default();
}

/**
 * @brief Constructor de copia
 * @param Other Matriz a copiar
 */
Matrix::Matrix(const Matrix &Other){
    m_Column = Other.m_Column;
    m_Row = Other.m_Row;

    m_comp = new double*[m_Row];
    for (int i = 0; i < m_Row; i++){
        m_comp[i] = new double[m_Column];
    }

    for (int i = 0; i < m_Row; i++){
        for (int j = 0; j < m_Column; j++){
            m_comp[i][j] = Other.m_comp[i][j];
        }
    }
}

/**
 * @brief Destructor de la clase Matrix
 */
Matrix::~Matrix(){
    for (size_t i = 0; i < m_Row; i++){
        delete[] m_comp[i];
    }
    delete[] m_comp;
}

/**
 * @brief Sobrecarga del operador de asignación
 * @param Other Matriz a asignar
 * @return Referencia al objeto actual
 */
Matrix& Matrix::operator=(const Matrix &Other){

    if (this == &Other)
        return *this;

    for (int i = 0; i < m_Row; i++){
        delete[] m_comp[i];
    }
    delete[] m_comp;

    m_Row = Other.m_Row;
    m_Column = Other.m_Column;

    m_comp = new double*[m_Row];
    for (int i = 0; i < m_Row; i++){
        m_comp[i] = new double[m_Column];
    }

    for (int i = 0; i < m_Row; i++){
        for (int j = 0; j < m_Column; j++){
            m_comp[i][j] = Other.m_comp[i][j];
        }
    }

    return *this;
}

/**
 * @brief Suma de matrices
 * @param Other Matriz a sumar
 * @return Resultado de la suma
 */
Matrix Matrix::operator+(const Matrix &Other) const{
    if (m_Column != Other.m_Column || m_Row != Other.m_Row)
        throw "No tienen las mismas dimenciones";

    Matrix m(m_Row, m_Column);
    for (int i = 0; i < m.m_Row; i++){
        for (int j = 0; j < m.m_Column; j++){
            m.m_comp[i][j] = m_comp[i][j] + Other.m_comp[i][j];
        }
    }
    return m;
}

/**
 * @brief Resta de matrices
 * @param Other Matriz a restar
 * @return Resultado de la resta
 */
Matrix Matrix::operator-(const Matrix &Other) const{
    if (m_Column != Other.m_Column || m_Row != Other.m_Row)
        throw "No tienen las mismas dimenciones";

    Matrix m(m_Row, m_Column);
    for (int i = 0; i < m.m_Row; i++){
        for (int j = 0; j < m.m_Column; j++){
            m.m_comp[i][j] = m_comp[i][j] - Other.m_comp[i][j];
        }
    }
    return m;
}

/**
 * @brief Multiplicación de matrices
 * @param Other Matriz multiplicadora
 * @return Resultado de la multiplicación
 */
Matrix Matrix::operator*(const Matrix &Other) const{
    if (m_Column != Other.m_Row)
        throw "No tienen las mismas dimenciones";

    Matrix m(m_Row, Other.m_Column);
    m.Matrix_Default();

    for (int i = 0; i < m_Row; i++){
        for (int j = 0; j < Other.m_Column; j++){
            for (int k = 0; k < m_Column; k++){
                m.m_comp[i][j] += m_comp[i][k] * Other.m_comp[k][j];
            }
        }
    }
    return m;
}

/**
 * @brief Multiplicación escalar
 * @param Scalar Escalar
 * @return Matriz resultante
 */
Matrix Matrix::operator*(const double &Scalar) const{
    Matrix m(m_Row, m_Column);
    for (int i = 0; i < m.m_Row; i++){
        for (int j = 0; j < m.m_Column; j++){
            m.m_comp[i][j] = m_comp[i][j] * Scalar;
        }
    }
    return m;
}

/**
 * @brief Acceso a una fila de la matriz
 * @param i Índice de la fila
 * @return Puntero a la fila
 */
double* Matrix::operator[](int i) const{
    if (i < 0 || i > m_Row)
        throw "Indices fuera de rango";
    return m_comp[i];
}

/**
 * @brief Redimensiona la matriz a un tamaño mayor
 * @param new_Rows Nuevas filas
 * @param new_Colums Nuevas columnas
 */
void Matrix::Redim(const unsigned int &new_Rows, const unsigned int &new_Colums){
    Matrix aux(new_Rows, new_Colums);

    for (int i = 0; i < m_Row; i++){
        for (int j = 0; j < m_Column; j++){
            aux[i][j] = m_comp[i][j];
        }
    }

    *this = aux;
}

/**
 * @brief Imprime la matriz (uso de depuración)
 */
void Matrix::print(){
    for(int i = 0; i < m_Row; i++){
        for(int j = 0; j < m_Column; j++){
            std::cout << m_comp[i][j] << " ";
        }
        std::cout << "\n";
    }
}

/**
 * @brief Calcula la transpuesta de la matriz
 * @return Matriz transpuesta
 */
Matrix Matrix::Trans(){
    Matrix aux(m_Column, m_Row);

    for (int i = 0; i < m_Row; i++){
        for (int j = 0; j < m_Column; j++){
            aux.m_comp[j][i] = m_comp[i][j];
        }
    }
    return aux;
}

/**
 * @brief Calcula la inversa de la matriz usando Gauss-Jordan
 * @return Matriz inversa
 */
Matrix Matrix::Inversa(){
    if (m_Row != m_Column)
        throw "La matriz no es cuadrada";

    int n = m_Row;
    Matrix aug(n, 2 * n);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            aug.m_comp[i][j] = m_comp[i][j];
            aug.m_comp[i][j + n] = (i == j) ? 1.0 : 0.0;
        }
    }

    for (int i = 0; i < n; i++){
        double pivote = aug.m_comp[i][i];
        if (pivote == 0)
            throw "La matriz no es invertible";

        for (int j = 0; j < 2 * n; j++)
            aug.m_comp[i][j] /= pivote;

        for (int k = 0; k < n; k++){
            if (k == i) continue;
            double factor = aug.m_comp[k][i];
            for (int j = 0; j < 2 * n; j++){
                aug.m_comp[k][j] -= factor * aug.m_comp[i][j];
            }
        }
    }

    Matrix inv(n, n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            inv.m_comp[i][j] = aug.m_comp[i][j + n];
        }
    }
    return inv;
}

/**
 * @brief Inicializa la matriz con ceros
 */
void Matrix::Matrix_Default(){
    for(int i = 0; i < m_Row; i++){
        for(int j = 0; j < m_Column; j++){
            m_comp[i][j] = 0;
        }
    }
}
