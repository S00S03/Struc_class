#include <iostream>
#include "vector.hpp"

Vector::Vector() : dim(0) {}

Vector::Vector(int dimension) : dim(dimension) {
    if (dimension < 1 || dimension > MAX_DIM) {
        throw "Dimension fuera de rango";
    }
    for (int i = 0; i < dim; ++i) {
        components[i] = 0.0;
    }
}

Vector::Vector(int dimension, double value) : dim(dimension) {
    if (dimension < 1 || dimension > MAX_DIM) {
        throw "Dimension fuera de rango";
    }
    for (int i = 0; i < dim; ++i) {
        components[i] = value;
    }
}

Vector operator+(const Vector v, const Vector w) {
    if (v.dim != w.dim) {
        throw "Dimensiones incompatibles para la suma";
    }
    Vector result(v.dim);
    for (int i = 0; i < v.dim; ++i) {
        result.components[i] = v.components[i] + w.components[i];
    }
    return result;
}

Vector operator-(const Vector v, const Vector w) {
    if (v.dim != w.dim) {
        throw "Dimensiones incompatibles para la suma";
    }
    Vector result(v.dim);
    for (int i = 0; i < v.dim; ++i) {
        result.components[i] = v.components[i] - w.components[i];
    }
    return result;
}

Vector operator*(const Vector v, const Vector w) {
    if (v.dim != w.dim) {
        throw "Dimensiones incompatibles para la suma";
    }
    Vector result(v.dim);
    for (int i = 0; i < v.dim; ++i) {
        result.components[i] = v.components[i] * w.components[i];
    }
    return result;
}

Vector operator*(const Vector v, double scalar) {
    Vector result(v.dim);
    for (int i = 0; i < v.dim; ++i) {
        result.components[i] = v.components[i] * scalar;
    }
    return result;
}

Vector operator*(double scalar, const Vector v) {
    Vector result(v.dim);
    for (int i = 0; i < v.dim; ++i) {
        result.components[i] = v.components[i] * scalar;
    }
    return result;
}

// INSTEAD OF THIS YOU CAN DO THE ABOVE
// Vector Vector::operator+(Vector v) {
//     if (dim != v.dim) {
//         throw "Dimensiones incompatibles para la suma";
//     }
//     Vector result(dim);
//     for (int i = 0; i < dim; ++i) {
//         result.components[i] = components[i] + v.components[i];
//     }
//     return result;
// }

// Vector Vector::operator-(Vector v) {
//     if (dim != v.dim) {
//         throw "Dimensiones incompatibles para la suma";
//     }
//     Vector result(dim);
//     for (int i = 0; i < dim; ++i) {
//         result.components[i] = components[i] - v.components[i];
//     }
//     return result;
// }

// Vector Vector::operator*(Vector v) {
//     if (dim != v.dim) {
//         throw "Dimensiones incompatibles para la suma";
//     }
//     Vector result(dim);
//     for (int i = 0; i < dim; ++i) {
//         result.components[i] = components[i] * v.components[i];
//     }
//     return result;
// }

void Vector::getValues() {
    std::cout << "Introduce los componentss del vector:" << std::endl;
    for (int i = 0; i < dim; ++i) {
        std::cout << "Componente " << (i + 1) << ": ";
        std::cin >> components[i];
    }
}

void Vector::print() {
    std::cout << "[";
    for (int i = 0; i < dim; ++i) {
        std::cout << components[i];
        if (i < dim - 1)
            std::cout << ", ";
    }
    std::cout << "]";
    std::cout << std::endl;
}

void Vector::setDim(int dimension) {
    if (dimension < 1 || dimension > MAX_DIM) {
        throw "Dimension fuera de rango";
    }
    dim = dimension;
}

int Vector::getDim() const { return dim; }
