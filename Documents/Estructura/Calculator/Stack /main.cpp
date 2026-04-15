#include <iostream>

#include "Stack.hpp"

int main (){

    Stack<int> pilita;
    for ( int i = 0; i < 10; ++i){
        pilita.add(i); 
    }

    pilita.print();
    
    return 0; 
}