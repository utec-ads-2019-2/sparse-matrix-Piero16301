#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include "node.h"

using namespace std;

template <typename T>
class Matrix {
private:
    Node <T> *root = nullptr;
    unsigned int filas = 0, columnas = 0;

public:
    Matrix(unsigned int filas, unsigned int columnas) {
        this->root = new Node<T>();
        Node <T> *actual = this->root;
        for (int i = 0; i < columnas; ++i) {
            Node <T> *temporal = new Node<T>(i);
            actual->siguiente = temporal;
            actual = actual->siguiente;
        }
        actual->siguiente = nullptr;
        actual = this->root;
        for (int i = 0; i < filas; ++i) {
            Node <T> *temporal = new Node<T>(i);
            actual->abajo = temporal;
            actual = actual->abajo;
        }
        actual->abajo = nullptr;
        this->filas = filas;
        this->columnas = columnas;
    };

    void establecerCelda(unsigned int fila, unsigned int columna, T valor) {
        // Se asigna un valor a una celda específica
        Node <T> *actual = this->root;
        int minimo = (fila >= columna) ? columna : fila;
        while (actual->indice != minimo) {
            actual = (minimo == fila) ? actual->abajo : actual->siguiente;
        };
        Node <T> *previo = nullptr;
        while (actual && actual->fila <= fila && actual->columna <= columna) {
            if (actual->fila == fila && actual->columna == columna) {
                actual->valor = valor;
                return;
            }
            previo = actual;
            actual = (minimo == fila) ? actual->siguiente : actual->abajo;
        }
        if (!actual && previo) {
            if (minimo == fila) {
                Node <T> *temporal = new Node<T>(fila, columna, valor);
                previo->siguiente = temporal;
            } else {
                Node <T> *temporal = new Node<T>(fila, columna, valor);
                previo->abajo = temporal;
            }
        }
        else if (previo && previo->siguiente && minimo == fila) {
            Node <T> *temporal = new Node<T>(fila, columna, valor);
            previo->siguiente = temporal->siguiente;
            previo->siguiente = temporal;
        }
        else if (previo && previo->siguiente && minimo == columna) {
            Node <T> *temporal = new Node<T>(fila, columna, valor);
            previo->abajo = temporal->abajo;
            previo->abajo = temporal;
        }
    };

    T operator()(unsigned int fila, unsigned int columna) const {
        // Se retorna el valor contenido en la celda que se solicita
    };

    Matrix <T> operator*(T escalar) const {
        // Multiplicacion de matriz por un escalar (producto punto)
    };

    Matrix <T> operator*(Matrix <T> other) const {
        // Multiplicacion de matriz por matriz (producto cruz)
    };

    Matrix <T> operator+(Matrix<T> other) const {
        // Suma de matrices
    };

    Matrix <T> operator-(Matrix<T> other) const {
        // Resta de matrices
    };

    Matrix <T> transpose() const {
        // Retorna la matriz transpuesta
    };

    void imprimir() const {
        // Imprime la matriz
        Node <T> *actual = this->root;
        Node <T> *cota = this->root;
        while (actual) {
            while (actual) {
                cout << actual->indice << ' ';
                actual = actual->siguiente;
            }
            actual = cota->abajo;
            cota = actual;
            cout << endl;
        }
    };

    ~Matrix() {
        this->root->killSelf();
    };
};

#endif //SPARSE_MATRIX_MATRIX_H