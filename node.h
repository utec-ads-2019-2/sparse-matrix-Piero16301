#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

template <typename T>
class Matrix;

template <typename T>
class Node {
protected:
    Node<T> *siguiente = nullptr;
    Node<T> *abajo = nullptr;
    int fila = 0;
    int columna = 0;
    T valor = 0;

public:
    Node(int fila, int columna, T valor) : siguiente{this}, abajo{this}, fila{fila}, columna{columna}, valor{valor} {};
    ~Node() {};

    friend class Matrix<T>;
};

#endif //SPARSE_MATRIX_NODE_H
