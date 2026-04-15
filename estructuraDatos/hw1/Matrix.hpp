#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <ostream>

class Matrix {
    friend std::ostream &operator<<(std::ostream &output, const Matrix& m);
    friend std::istream &operator>>(std::istream &input, Matrix& m);
    friend Matrix operator*(double escalar, const Matrix m);

public:
    // Constructor 2 param
    explicit Matrix(int rows, int columns);

    // Destructor
    ~Matrix();

    // Copy constructor
    Matrix(const Matrix& other);

    // Operator overload
    Matrix& operator=(const Matrix& other);

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;

    // Matrix multiplication
    Matrix operator*(const Matrix& other) const;
    // Scalar multiplication
    Matrix operator*(double scalar) const;

    Matrix transpose() const;
    Matrix inverse() const;

    void resize(int newRows, int newColumns);

    void print() const;
    void set(int row, int column, double value) const;

private:
    int rows, columns;
    double** data;

};

#endif // !MATRIX_HPP
