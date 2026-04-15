#ifndef QUEUE_HPP
#define QUEUE_HPP

template <typename T>
class Queue{
    public:
    Queue(/* args */);
    ~Queue();

    void add(const T& new_element); 
    void out();

    bool empty() const; 

    T front() const; 
    T back()const; 

    int size() const; 
    void print() const; 

    private:
        int num_element;
        struct list
        {
            T cont; 
            list* next; 
        };
        list* frist;
        list* last; 
        
};

template <typename T>
Queue<T>::Queue()
{ 
    frist = nullptr;
    last = nullptr;
    num_element = 0;
}

template <typename T>
Queue<T>::~Queue()
{   
while(!empty()){
        out();
    }
    
}

template <typename T> void Queue<T>::add( const T &new_element){
    ++num_element; 
      
    if(num_element == 1) {
        frist = new list(); 
        frist->cont= new_element;
        frist->next = last;
        last = frist;
        return; 
    }

    list*aux = new list(); 

    aux->cont = new_element; 
    aux->next = frist; 

    last->next = aux;
    last = aux;
}

template <typename T>
void Queue<T>::out(){

    if(frist == nullptr)
        throw "The frist is empty";

    if(frist == last){
        delete frist;
        frist = nullptr;
        last = nullptr;
        num_element = 0;
        return;
    }

    list *aux = frist->next;
    delete frist;

    frist = aux;
    last->next = frist;

    --num_element;
}

#include "Queue.tpp"

#endif