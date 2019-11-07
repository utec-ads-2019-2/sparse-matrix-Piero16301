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

protected:
    void buscarIndiceFila(unsigned int indice, Node<T>* &actual) {
        while (actual->indice != indice) {
            actual = actual->abajo;
        }
    }

    void buscarIndiceColumna(unsigned int indice, Node<T>* &actual) {
        while (actual->indice != indice) {
            actual = actual->siguiente;
        }
    }

    void clear(Node <T>* &actual) {
        if (actual->abajo) {
            clear(actual->abajo);
        }
        if (actual->siguiente) {
            clear(actual->siguiente);
        }
        actual = nullptr;
        delete actual;
    }

public:
    Matrix(unsigned int filas, unsigned int columnas) : filas{filas}, columnas{columnas} {
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
    };

    void establecerCelda(unsigned int fila, unsigned int columna, T valor) {
        // Se asigna un valor a una celda específica
        if (!(fila >= 0 && fila < this->filas && columna >= 0 && columna < this->columnas)) {
            throw invalid_argument("La posicion de filas o columnas introducidas es invalida");
        }
        Node <T> *actual = this->root;
        string recorrido = (fila > columna) ? "columna" : "fila";
        if (recorrido == "fila") {
            buscarIndiceFila(fila, actual);
            if (!actual->siguiente) {
                Node <T> *temporal = new Node<T>(fila, columna, valor);
                actual->siguiente = temporal;
                Node <T> *numeroColumna = this->root;
                buscarIndiceColumna(columna, numeroColumna);
                while (numeroColumna && numeroColumna->fila <= fila) {
                    numeroColumna = numeroColumna->abajo;
                }
                if (numeroColumna->abajo) {
                    Node <T> *siguienteNodo = numeroColumna->abajo;
                    temporal->abajo = siguienteNodo;
                    numeroColumna->abajo = temporal;
                } else {
                    numeroColumna->abajo = temporal;
                }
            } else {
                while (actual && actual->columna <= columna) {
                    if (actual->columna == columna) {
                        actual->valor = valor;
                        return;
                    }
                    actual = actual->siguiente;
                }
                Node <T> *temporal = new Node<T>(fila, columna, valor);
                if (actual->siguiente) {
                    temporal->siguiente = actual->siguiente;
                    actual->siguiente = temporal;
                } else {
                    actual->siguiente = temporal;
                }
                Node <T> *numeroColumna = this->root;
                buscarIndiceColumna(columna, numeroColumna);
                while (numeroColumna && numeroColumna->fila <= fila) {
                    numeroColumna = numeroColumna->abajo;
                }
                if (numeroColumna->abajo) {
                    Node <T> *siguienteNodo = numeroColumna->abajo;
                    temporal->abajo = siguienteNodo;
                    numeroColumna->abajo = temporal;
                } else {
                    numeroColumna->abajo = temporal;
                }
            }
        } else {
            buscarIndiceColumna(columna, actual);

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
        Node <T> *actual = nullptr;
        Node <T> *pivote = this->root;
        for (int i = 0; i <= this->filas; ++i) {
            actual = pivote;
            for (int j = 0; j <= this->columnas; ++j) {
                if (actual) {
                    if (actual->indice == -1) {
                        if (actual->fila == i-1 && actual->columna == j-1) {
                            cout << actual->valor << ' ';
                        } else {
                            cout << '0' << ' ';
                            continue;
                        }
                    } else {
                        cout << actual->indice << ' ';
                    }
                    actual = actual->siguiente;
                } else {
                    cout << '0' << ' ';
                }
            }
            pivote = pivote->abajo;
            cout << endl;
        }
        /*Node <T> *actual = this->root;
        Node <T> *cota = this->root;
        while (actual) {
            while (actual) {
                cout << actual->valor << ' ';
                actual = actual->siguiente;
            }
            actual = cota->abajo;
            cota = actual;
            cout << endl;
        }*/
    };

    ~Matrix() {
        clear(this->root);
    };
};

#endif //SPARSE_MATRIX_MATRIX_H