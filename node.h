#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

template <typename T>
class Matrix;

template <typename T>
class Node {
protected:
    Node<T> *siguiente = nullptr, *abajo = nullptr;
    int fila = -1, columna = -1, indice = -1;
    T valor = 0;

public:
    Node() : siguiente{nullptr}, abajo{nullptr} {}
    Node(int indice) : siguiente{nullptr}, abajo{nullptr}, indice{indice} {}
    Node(int fila, int columna, T valor) : siguiente{nullptr}, abajo{nullptr}, fila{fila}, columna{columna}, valor{valor} {};

    void killSelf() {
        if (this->abajo) {
            this->abajo->killSelf();
        }
        if (this->siguiente) {
            this->siguiente->killSelf();
        }
        delete this;
    }

    friend class Matrix<T>;
};

#endif //SPARSE_MATRIX_NODE_H
