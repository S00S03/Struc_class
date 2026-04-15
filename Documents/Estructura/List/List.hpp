#ifndef LIST_HPP
#define LIST_HPP

/**
 * @brief Clase plantilla que implementa una lista doblemente enlazada circular
 * 
 * @tparam T Tipo de dato que almacenará la lista
 * 
 * @author Galindo
 * @author Arredondo
 */
template <typename T>
class List
{
    public:

    /**
     * @brief Constructor por defecto
     */
    List();

    /**
     * @brief Constructor de copia
     * @param other Lista a copiar
     */
    List(const List& other);

    /**
     * @brief Sobrecarga del operador de asignación
     * @param other Lista a asignar
     * @return Referencia a la lista actual
     */
    List& operator=(const List &other);

    /**
     * @brief Destructor
     */
    ~List();
    
    /**
     * @brief Obtiene el tamaño de la lista
     * @return Número de elementos
     */
    int get_size() const; 

    /**
     * @brief Verifica si la lista está vacía
     * @return true si está vacía
     */
    bool its_empty() const; 
    
    /**
     * @brief Agrega un elemento al final
     * @param adding Elemento a insertar
     */
    void add_last(const T& adding); 

    /**
     * @brief Agrega un elemento al inicio
     * @param adding Elemento a insertar
     */
    void add_frist(const T& adding); 

    /**
     * @brief Inserta un elemento en una posición específica
     * @param adding Elemento a insertar
     * @param pos Posición
     */
    void add_in_pos(const T& adding, const int &pos); 
    
    /**
     * @brief Vacía la lista
     */
    void empty();

    /**
     * @brief Elimina el primer elemento
     */
    void remove_frist();

    /**
     * @brief Elimina el último elemento
     */
    void remove_last(); 

    /**
     * @brief Elimina un elemento en una posición específica
     * @param pos Posición
     */
    void remove_in_pos(const int& pos);
    
    /**
     * @brief Busca un elemento en la lista
     * @param ele Elemento a buscar
     * @return true si existe
     */
    bool shearch(const T& ele) const; 

    /**
     * @brief Obtiene la posición de un elemento
     * @param pos Elemento a buscar
     * @return Posición o -1 si no existe
     */
    int get_pos(const T& pos) const; 
    
    /**
     * @brief Obtiene el primer elemento
     * @return Elemento
     */
    T get_frist() const; 

    /**
     * @brief Obtiene el último elemento
     * @return Elemento
     */
    T get_last() const; 

    /**
     * @brief Obtiene un elemento en una posición
     * @param pos Posición
     * @return Elemento
     */
    T get_in_pos(const int &pos) const;
    
    /**
     * @brief Imprime la lista de inicio a fin
     */
    void print() const;

    /**
     * @brief Imprime la lista en orden inverso
     */
    void print_rv() const;
    
    /**
     * @brief Nodo de la lista
     */
    struct Element
    {
        T cont;              ///< Contenido del nodo
        Element *next;       ///< Puntero al siguiente nodo
        Element *previous;   ///< Puntero al nodo anterior
    };
    
    private:
    int size;        ///< Tamaño de la lista
    Element *frist;  ///< Primer nodo
    Element *last;   ///< Último nodo
};

#include "List.tpp"

#endif