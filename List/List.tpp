/**
 * @brief Constructor por defecto
 */
template <typename T> 
List<T>::List(): size(0), frist(nullptr), last(nullptr){}

/**
 * @brief Constructor de copia
 */
template <typename T>
List<T>::List(const List& other) : size(0), frist(nullptr), last(nullptr){
    if(other.size == 0)
        return;

    Element* aux = other.frist;

    for(int i = 0; i < other.size; i++){
        add_last(aux->cont);
        aux = aux->next;
    }
}

/**
 * @brief Elimina el primer elemento
 * @throw "Lista vacia" si no hay elementos
 */
template <typename T>
void List<T>::remove_frist(){
    if(size == 0)
        throw "Lista vacia";

    if(size == 1){
        delete frist;
        frist = nullptr;
        last = nullptr;
    }
    else{
        Element* borrar = frist;
        frist = frist->next;

        frist->previous = last;
        last->next = frist;

        delete borrar;
    }

    --size;
}