#include "Matrix.hpp"

#include <iostream>
#include <stdexcept>

// Constructor 2 param
Matrix::Matrix(int rows, int columns) : rows(rows), columns(columns) {
    if (rows <= 0 || columns <= 0) {
        throw std::invalid_argument("Dimension must be higher than 0");
    }
    data = new double *[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new double[columns];
    }
}

// Destructor
Matrix::~Matrix() {
    for (int i = 0; i < rows; i++) {
        delete[] data[i];
    }
    delete[] data;
}

// Copy constructor
Matrix::Matrix(const Matrix &other) : rows(other.rows), columns(other.columns) {
    data = new double *[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new double[columns];
        for (int j = 0; j < columns; j++) {
            data[i][j] = other.data[i][j];
        }
    }
}

// Equal
Matrix &Matrix::operator=(const Matrix &other) {
    // Delete memory
    for (int i = 0; i < rows; i++) {
        delete[] data[i];
    }
    delete[] data;

    rows = other.rows;
    columns = other.columns;
    data = new double *[rows];

    for (int i = 0; i < rows; i++) {
        data[i] = new double[columns];
        for (int j = 0; j < columns; j++) {
            data[i][j] = other.data[i][j];
        }
    }

    return *this;
}

// Sum
Matrix Matrix::operator+(const Matrix &other) const {
    Matrix m(rows, columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            m.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return m;
}

// Sub
Matrix Matrix::operator-(const Matrix &other) const {
    Matrix m(rows, columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            m.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return m;
}

// Multiply
Matrix Matrix::operator*(const Matrix &other) const {
    if (columns != other.rows) {
        throw std::invalid_argument(
            "Matrix Dimensions do not match for mutiplication");
    }
    Matrix m(rows, other.columns);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.columns; j++) {
            m.data[i][j] = 0;
            for (int k = 0; k < columns; k++) {
                m.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return m;
}

// Scalar Multiplication
Matrix Matrix::operator*(double scalar) const {
    Matrix m(rows, columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            m.data[i][j] = data[i][j] * scalar;
        }
    }
    return m;
}

Matrix Matrix::transpose() const {
    Matrix m(columns, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            m.data[j][i] = data[i][j];
        }
    }
    return m;
}

// Gauss Jordan too long
// Matrix Matrix::inverse() const {
//     return;
// }

void Matrix::resize(int newRows, int newColumns) {
    if (newRows < rows || newColumns < columns) {
        throw std::invalid_argument(
            "New dimension must be greater or equal to current dimension");
    }

    Matrix temp(newRows, newColumns);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            temp.data[i][j] = data[i][j];
        }
    }

    *this = temp;
}

std::ostream &operator<<(std::ostream &output, const Matrix &m) {
    // output << "(";
    for (int i = 0; i < m.rows; ++i) {
        if (i > 0)
            output << std::endl;
        for (int j = 0; j < m.columns; j++) {
            output << m.data[i][j];
            if (j < m.columns - 1)
                output << ", ";
        }
    }
    // output << ")";
    return output;
}

std::istream &operator>>(std::istream &input, Matrix &m) {
    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.columns; j++) {
            std::cout << "Component " << "[" << i + 1 << "]" << "[" << j + 1 << "]" << ": ";
            input >> m.data[i][j];
        }
    }
    return input;
}

Matrix operator*(double escalar, const Matrix m) {
    Matrix mult(m.rows, m.columns);
    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.columns; j++) {
            mult.data[i][j] = m.data[i][j] * escalar;
        }
    }
    return mult;
}

// *****************************
//            UTILS
// *****************************
// No longer needed
void Matrix::print() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Matrix::set(int row, int column, double value) const {
    if (row >= rows || column >= columns) {
        throw std::invalid_argument("Invalid position");
    }
    data[row][column] = value;
}
