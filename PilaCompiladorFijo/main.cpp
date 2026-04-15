#include <iostream>
#include "Pila.hpp"

using namespace std;

int main()
{
    try{
        Pila p;

        p.Imprimir();
        cout << endl;

        p.Agregar('e');
        p.Imprimir();
        cout << endl;


        p.Agregar('n');
        p.Imprimir();
        cout << endl;

        p.Agregar('e');
        p.Imprimir();
        cout << endl;

        p.Agregar('p');
        p.Imprimir();
        cout << endl;

        p.Agregar('p');
        p.Imprimir();
        cout << endl;

        p.Agregar('p');
        p.Imprimir();
        cout << endl;



        while ( p.ObtenerTam() != 0)
          {
            p.Eliminar();
            p.Imprimir();
            cout<<endl;
          }

          cout << "El valor del tope es: " << p.ObtenerTope() << endl;





    }catch(const char *error){

        cerr << "error: "<< error << endl;

        }catch(Pila::PilaVacia &error){
            cerr<<"Error en la pila: "<< error.what();
        }catch(Pila::PilaLlena &error){
            cerr<<"Error en la pila: "<< error.what();
        }catch(exception &error){
            cerr<<"Error: " << error.what();
        }catch(...){
            cerr << "No se que fue";
            }




    return 0;
}
