#include "Matrix.hpp"

#include <cmath>
#include <iostream>

// Hecho por Kevin Eduardo Rivera Osuna

// TODO: 
// - Inverse of a Matrix (Gauss-Jordan, Det != 0, n x n)

int main() {
    // int rows, columns;

    // std::cout << "Enter the number of rows: ";
    // std::cin >> rows;
    // std::cout << "Enter the number of columns: ";
    // std::cin >> columns;
    // Matrix matrix(rows, columns);
    // matrix.print();

    std::cout << "Matrix m1: " << std::endl;
    Matrix m1(3, 2);
    m1.set(0, 0, 5);
    m1.set(1, 0, 5);
    m1.set(2, 0, 2);

    m1.set(0, 1, 2);
    m1.set(1, 1, 2);
    m1.set(2, 1, 5);

    std::cout << m1 << std::endl;


    std::cout << "Matrix m2: " << std::endl;
    Matrix m2(2, 3);
    m2.set(0, 0, 3);
    m2.set(0, 1, 2);
    m2.set(0, 2, 1);

    m2.set(1, 0, 2);
    m2.set(1, 1, 3);
    m2.set(1, 2, 5);


    std::cout << m2 << std::endl;

    std::cout << "Copy of m1: " << std::endl;
    Matrix m1Copy = m1;
    std::cout << m1Copy << std::endl;

    std::cout << "Sum of m2 and m1: " << std::endl;
    Matrix mSum = m2 + m1;
    std::cout << mSum << std::endl;


    std::cout << "Substraction of m2 and m2: " << std::endl;
    Matrix mSub = m2 - m2;
    std::cout << mSub << std::endl;

    m1.resize(2, 5);
    m2.resize(5, 2);

    std::cout << "Multiplication of m2 and m1: " << std::endl;
    Matrix mMult = m1 * m2;
    std::cout << mMult << std::endl;


    std::cout << "Multiplication of m2 and a scalar: " << std::endl;
    Matrix mScalarMult = m2 * 3;
    std::cout << mScalarMult << std::endl;

    std::cout << "Commutative Scalar Product: " << std::endl;
    Matrix mCommutative = 3 * m2;
    std::cout << mCommutative << std::endl;


    std::cout << "Transpose of m2: " << std::endl;
    Matrix mTranspose = m2.transpose();
    std::cout << mTranspose << std::endl;


    std::cout << "Redimension of m1: " << std::endl;

    m1.resize(4, 3);
    std::cout << m1 << std::endl;


    std::cin >> m1;
    std::cout << m1 << std::endl;

    return 0;
}
