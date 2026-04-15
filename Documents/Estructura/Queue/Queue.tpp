#include "Queue.hpp"
#include <iostream>

template <typename T> bool Queue<T>::empty() const{
    if (num_element == 0) return true;
    return false; 
}

template <typename T> int Queue<T>::size() const{
    return num_element;
}

template <typename T> T Queue<T>::front() const{
    if(empty()) throw "Its empty"; 
    return frist->cont; 
}

template <typename T> T Queue<T>::back() const{
    if(empty()) throw "Its empty";
    return last->cont; 
}

template <typename T> void Queue <T>::print()const{
    
    if(empty()){
        std::cout << "Queue empty\n";
        return;
    }

    list *aux = frist; 

    do{
        std :: cout << aux->cont << " "; 
        aux = aux->next;
    }while (aux != frist);
    
    std::cout << std::endl;
}