#ifndef VECTOR_HPP
#define VECTOR_HPP

#define MAX_DIM 10

class Vector {
  public:
    Vector();
    Vector(int dim);
    Vector(int dimension, double value);

    void print();
    void getValues();

    friend Vector operator+(Vector v, Vector w);
    friend Vector operator-(Vector v, Vector w);
    friend Vector operator*(Vector v, Vector w);
    friend Vector operator*(const Vector v, double scalar);
    friend Vector operator*(double scalar, const Vector v);

    void setDim(int dim);
    int getDim() const;

  private:
    int dim;
    double components[MAX_DIM];
};

#endif // VECTOR_HPP
