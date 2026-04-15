#include "Stack.hpp"
#include <iostream>

template <typename T> Stack<T>::Stack(): num_element(0), top(nullptr){}

template <typename T> Stack<T>::~Stack(){
    element *aux = new element; 

    while(top != nullptr){
        aux = top;
        top = top->next;
        delete aux;
    }
}

template <typename T> void Stack<T>::add(const T &new_element){
   element *aux = new element; 
   
   aux->cont = new_element; 
   aux->next = top;
   
   top = aux;

   num_element++;
}

template <typename T>
void Stack<T>::remove(){

    if(top == nullptr)
        throw "Pila vacia";

    element* aux = top;

    top = top->next;

    delete aux;

    num_element--;
}

template <typename T> void Stack<T>::empty(){
    
    while(top != nullptr){
       this->remove();
    }
}


template <typename T> T Stack<T>::get_Top()const{
    if(num_element == 0) throw "Pila vacia"; 
    return top->cont; 
}

template <typename T> int Stack<T>::get_size()const{
    return num_element; 
}

template <typename T> void Stack<T>::print()const{
    
    element* aux = top; 

    while ( aux != nullptr)
    {
        std::cout << aux->cont << " ";
        aux = aux->next;
    }
    
}
template <typename T> bool Stack<T>::its_empty() const{
    return top == nullptr;
}