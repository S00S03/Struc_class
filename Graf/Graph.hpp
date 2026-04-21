#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
using namespace std;

template <typename T>
struct Edge;

template <typename T>
struct Node
{
    T data;
    int degree;

    Edge<T> *first, *last;
    Node<T> *next;

    Node(T d, Node<T> *n = nullptr);
};

template <typename T>
struct Edge
{
    Node<T> *adjacent;
    Edge<T> *next;

    Edge(Node<T> *adj, Edge<T> *n = nullptr);
};

template <typename T>
class Graph
{
private:
    int num_nodes;
    int num_edges;
    Node<T> *first;
    Node<T> *last;

public:
    Graph();
    ~Graph();

    void add_node(T data);
    void add_edge(T d1, T d2);

    void remove_node(T data);
    void remove_edge(T d1, T d2);

    bool has_node(T data);
    bool has_edge(T d1, T d2);

    int get_degree(T data);
    int get_order();
    int get_size();

    void clear();
    void clear_node(T data);

    bool is_empty();

    void print();

private:
    Node<T>* find_node(T data);
};

//////////////////// IMPLEMENTATIONS ////////////////////

template <typename T>
Node<T>::Node(T d, Node<T> *n)
{
    data = d;
    degree = 0;
    first = last = nullptr;
    next = n;
}

template <typename T>
Edge<T>::Edge(Node<T> *adj, Edge<T> *n)
{
    adjacent = adj;
    next = n;
}

template <typename T>
Graph<T>::Graph()
{
    num_nodes = 0;
    num_edges = 0;
    first = last = nullptr;
}

template <typename T>
Graph<T>::~Graph()
{
    clear();
}

// ===== add_node =====
template <typename T>
void Graph<T>::add_node(T data)
{
    if (has_node(data)) return;

    Node<T> *new_node = new Node<T>(data);

    if (!first)
        first = last = new_node;
    else
    {
        last->next = new_node;
        last = new_node;
    }

    num_nodes++;
}

// ===== find_node =====
template <typename T>
Node<T>* Graph<T>::find_node(T data)
{
    Node<T> *temp = first;
    while (temp)
    {
        if (temp->data == data)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

// ===== has_node =====
template <typename T>
bool Graph<T>::has_node(T data)
{
    return find_node(data) != nullptr;
}

// ===== add_edge =====
template <typename T>
void Graph<T>::add_edge(T d1, T d2)
{
    Node<T> *a = find_node(d1);
    Node<T> *b = find_node(d2);

    if (!a || !b) return;
    if (has_edge(d1, d2)) return;

    Edge<T> *new_edge = new Edge<T>(b);

    if (!a->first)
        a->first = a->last = new_edge;
    else
    {
        a->last->next = new_edge;
        a->last = new_edge;
    }

    a->degree++;
    num_edges++;
}

// ===== has_edge =====
template <typename T>
bool Graph<T>::has_edge(T d1, T d2)
{
    Node<T> *a = find_node(d1);
    Node<T> *b = find_node(d2);

    if (!a || !b) return false;

    Edge<T> *e = a->first;
    while (e)
    {
        if (e->adjacent == b)
            return true;
        e = e->next;
    }
    return false;
}

// ===== remove_edge =====
template <typename T>
void Graph<T>::remove_edge(T d1, T d2)
{
    Node<T> *a = find_node(d1);
    Node<T> *b = find_node(d2);

    if (!a || !b) return;

    Edge<T> *curr = a->first, *prev = nullptr;

    while (curr)
    {
        if (curr->adjacent == b)
        {
            if (prev)
                prev->next = curr->next;
            else
                a->first = curr->next;

            if (curr == a->last)
                a->last = prev;

            delete curr;
            a->degree--;
            num_edges--;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

// ===== remove_node =====
template <typename T>
void Graph<T>::remove_node(T data)
{
    Node<T> *target = find_node(data);
    if (!target) return;

    // remove edges pointing to this node
    Node<T> *temp = first;
    while (temp)
    {
        remove_edge(temp->data, data);
        temp = temp->next;
    }

    // remove its own edges
    clear_node(data);

    // remove node from list
    Node<T> *curr = first, *prev = nullptr;
    while (curr)
    {
        if (curr == target)
        {
            if (prev)
                prev->next = curr->next;
            else
                first = curr->next;

            if (curr == last)
                last = prev;

            delete curr;
            num_nodes--;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

// ===== clear_node =====
template <typename T>
void Graph<T>::clear_node(T data)
{
    Node<T> *n = find_node(data);
    if (!n) return;

    Edge<T> *e = n->first;
    while (e)
    {
        Edge<T> *aux = e;
        e = e->next;
        delete aux;
        num_edges--;
    }

    n->first = n->last = nullptr;
    n->degree = 0;
}

// ===== get_degree =====
template <typename T>
int Graph<T>::get_degree(T data)
{
    Node<T> *n = find_node(data);
    return n ? n->degree : -1;
}

// ===== print =====
template <typename T>
void Graph<T>::print()
{
    Node<T> *temp = first;

    while (temp)
    {
        cout << temp->data << " -> ";
        Edge<T> *e = temp->first;

        while (e)
        {
            cout << e->adjacent->data << " ";
            e = e->next;
        }

        cout << endl;
        temp = temp->next;
    }
}

// ===== clear =====
template <typename T>
void Graph<T>::clear()
{
    while (first)
        remove_node(first->data);
}

// ===== getters =====
template <typename T>
int Graph<T>::get_order()
{
    return num_nodes;
}

template <typename T>
int Graph<T>::get_size()
{
    return num_edges;
}

template <typename T>
bool Graph<T>::is_empty()
{
    return first == nullptr;
}

#endif