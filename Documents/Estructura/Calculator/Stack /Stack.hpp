#ifndef STACK_HPP_INCLUDE
#define STACK_HPP_INCLUDE

template <typename T> 
class Stack{
    public:
    Stack(/* args */);
    Stack( const Stack &other); 
    Stack operator=(const Stack &other);
    ~Stack();
    
    void add(const T &new_element);
    void remove(); 
    void empty(); 

    T get_Top()const; 
    int get_size()const;

    void print() const;
    bool its_empty() const;

    private:
        int num_element;
        struct element
        {
            T cont;
            element* next;  
        };
        element *top; 
};

#include "Stack.tpp"

#endif