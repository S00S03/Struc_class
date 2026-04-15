#include <iostream>

#include "Matrix.hpp"

using namespace  std;


/// @brief 
/// @return 
int main (){
    Matrix A(3, 3), B(3,3); 
     cout << "Ingrese matriz A:\n";
    cin >> A;

    cout << "Ingrese matriz B:\n";
    //cin >> B;

    cout << "\nA:\n" << A;
    cout << "\nB:\n" << B;

    Matrix aux = A+B;
    cout << "\nSuma:\n" << aux;

    aux = A-B;
    cout << "\nResta:\n" << aux;

    aux = A*B;
    cout << "\nProducto:\n" << aux;

    aux = A.Trans(); 
    cout << "\nTranspuesta de A:\n" << aux;

    aux = A * 2;
    cout << "\nEscalar 2*A:\n" <<aux;

    A.Redim(3, 3);

    aux = A.Inversa();
    cout << "inversa de A: " << aux;
    cout << "\nA redimensionada:\n" << A;

    return 0; 
}