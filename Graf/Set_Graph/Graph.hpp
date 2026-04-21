#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <limits>

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
    int weight; // 🔥 añadido
    Edge<T> *next;

    Edge(Node<T> *adj, int w, Edge<T> *n = nullptr);
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
    void add_edge(T d1, T d2, int w); // 🔥 con peso

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

    Graph<T> prim(T start);

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
Edge<T>::Edge(Node<T> *adj, int w, Edge<T> *n)
{
    adjacent = adj;
    weight = w;
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

// ===== add_edge (NO DIRIGIDO) =====
template <typename T>
void Graph<T>::add_edge(T d1, T d2, int w)
{
    Node<T> *a = find_node(d1);
    Node<T> *b = find_node(d2);

    if (!a || !b) return;
    if (has_edge(d1, d2)) return;

    Edge<T> *e1 = new Edge<T>(b, w);
    Edge<T> *e2 = new Edge<T>(a, w);

    // a -> b
    if (!a->first)
        a->first = a->last = e1;
    else
    {
        a->last->next = e1;
        a->last = e1;
    }

    // b -> a
    if (!b->first)
        b->first = b->last = e2;
    else
    {
        b->last->next = e2;
        b->last = e2;
    }

    a->degree++;
    b->degree++;
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
            break;
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

    Node<T> *temp = first;
    while (temp)
    {
        remove_edge(temp->data, data);
        temp = temp->next;
    }

    clear_node(data);

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
            cout << "(" << e->adjacent->data
                 << ", w=" << e->weight << ") ";
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

// ===== PRIM =====
template <typename T>
Graph<T> Graph<T>::prim(T start)
{
    const int INF = numeric_limits<int>::max();

    Graph<T> mst;

    vector<T> nodes;
    vector<bool> visited;
    vector<int> min_weight;
    vector<T> parent;

    Node<T>* temp = first;

    while (temp)
    {
        nodes.push_back(temp->data);
        visited.push_back(false);
        min_weight.push_back(INF);
        parent.push_back(temp->data);

        mst.add_node(temp->data);

        temp = temp->next;
    }

    int n = nodes.size();

    int start_index = -1;
    for (int i = 0; i < n; i++)
        if (nodes[i] == start)
            start_index = i;

    if (start_index == -1)
        return mst;

    min_weight[start_index] = 0;

    for (int i = 0; i < n; i++)
    {
        int u = -1;

        for (int j = 0; j < n; j++)
        {
            if (!visited[j] && (u == -1 || min_weight[j] < min_weight[u]))
                u = j;
        }

        visited[u] = true;

        Node<T>* node_u = find_node(nodes[u]);
        Edge<T>* e = node_u->first;

        while (e)
        {
            int v = -1;

            for (int k = 0; k < n; k++)
            {
                if (nodes[k] == e->adjacent->data)
                {
                    v = k;
                    break;
                }
            }

            if (v != -1 && !visited[v] && e->weight < min_weight[v])
            {
                min_weight[v] = e->weight;
                parent[v] = nodes[u];
            }

            e = e->next;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (nodes[i] != start)
        {
            mst.add_edge(parent[i], nodes[i], min_weight[i]);
        }
    }

    return mst;
}

#endif