#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include "node.h"

using namespace std;

template <typename T>
class Matrix {
private:
    Node <T> *root = nullptr;
    vector <Node <T>*> indicesFilas;
    vector <Node <T>*> indicesColumnas;
    unsigned int filas = 0;
    unsigned int columnas = 0;

protected:
    void borrarNodo(Node <T> *columna, Node <T> *fila) {
        Node <T> *temporal = columna->abajo;
        columna->abajo = columna->abajo->abajo;
        fila->siguiente = fila->siguiente->siguiente;
        delete temporal;
    }

    Node <T>* encontrarFila(Node <T> *valor) {
        Node <T> *temporal = indicesFilas[valor->fila];
        while (temporal->siguiente->columna < valor->columna && temporal->siguiente != indicesColumnas[valor->fila]) {
            temporal = temporal->siguiente;
        }
        return temporal;
    }

    void clear() {
        for (auto it = indicesColumnas.begin() + 1; it != indicesColumnas.end(); it++) {
            Node <T> *temporal = *it;
            while (temporal->abajo != *it) {
                if (temporal->abajo->valor == 0 && temporal->abajo->fila != 0) {
                    borrarNodo(temporal, encontrarFila(temporal->abajo));
                }
                temporal = temporal->abajo;
            }
        }
    }

    void inicializarCeldas() {
        // Inicializar filas
        int sizeInicial = 1;
        int ampliar = filas - 1;
        int maximo = sizeInicial - 1;
        while (ampliar--) {
            Node <T> *temporal = new Node<T>(sizeInicial, 0, 0);
            indicesFilas[sizeInicial] = temporal;
            sizeInicial++;
            indicesFilas[maximo]->abajo = indicesFilas[maximo + 1];
            maximo++;
        }
        indicesFilas[sizeInicial - 1]->abajo = indicesFilas[0];

        // Inicializar columnas
        sizeInicial = 1;
        ampliar = columnas - 1;
        maximo = sizeInicial - 1;
        while (ampliar--) {
            Node <T> *temporal = new Node<T>(0, sizeInicial, 0);
            indicesColumnas[sizeInicial] = temporal;
            sizeInicial++;
            indicesColumnas[maximo]->siguiente = indicesColumnas[maximo + 1];
            maximo++;
        }
        indicesColumnas[sizeInicial - 1]->siguiente = indicesColumnas[0];
    }

public:
    Matrix(unsigned int filas, unsigned int columnas) : filas{filas}, columnas{columnas}, indicesFilas(filas), indicesColumnas(columnas) {
        if (this->columnas < 1 || this->filas < 1) {
            throw invalid_argument("Numero de filas y columnas debe ser mayor a 0");
        }
        root = new Node<T>(0, 0, 0);
        root->siguiente = root;
        root->abajo = root;
        indicesFilas[0] = root;
        indicesColumnas[0] = root;
        inicializarCeldas();
    };

    Matrix(const Matrix &other) : indicesFilas(other.filas), indicesColumnas(other.columnas) {
        filas = other.filas;
        columnas = other.columnas;
        root = new Node<T>(0, 0, 0);
        root->siguiente = root;
        root->abajo = root;
        indicesFilas[0] = root;
        indicesColumnas[0] = root;
        inicializarCeldas();
        for (int i = 0; i < other.filas; ++i) {
            for (int j = 0; j < other.columnas; ++j) {
                this->establecerCelda(i, j, other.operator()(i, j));
            }
        }
    }

    Matrix <T> &operator=(const Matrix <T> &other) {
        for (int i = 0; i < other.filas; ++i) {
            for (int j = 0; j < other.columnas; ++j) {
                this->establecerCelda(i, j, other.operator()(i, j));
            }
        }
        return (*this);
    }

    // No estás borrando cuando valor es 0
    void establecerCelda(int fila, int columna, T valor) {
        // Se asigna un valor a una celda específica
        if (!(fila >= 0 && fila < this->filas && columna >= 0 && columna < this->columnas)) {
            throw invalid_argument("La posicion de filas o columnas introducidas es invalida");
        }
        Node <T> *nodoFila = indicesFilas[fila];
        Node <T> *nodoColumna = indicesColumnas[columna];
        while (nodoFila->siguiente->columna <= columna && nodoFila->siguiente != indicesFilas[fila]) {
            nodoFila = nodoFila->siguiente;
        }
        while (nodoColumna->abajo->fila <= fila && nodoColumna->abajo != indicesColumnas[columna]) {
            nodoColumna = nodoColumna->abajo;
        }
        if (nodoColumna == nodoFila) {
            nodoColumna->valor = valor;
            return;
        }
        Node <T> *temporal = new Node<T>(fila, columna, valor);
        temporal->siguiente = nodoFila->siguiente;
        nodoFila->siguiente = temporal;
        temporal->abajo = nodoColumna->abajo;
        nodoColumna->abajo = temporal;
    };

    T operator()(unsigned int fila, unsigned int columna) const {
        // Se retorna el valor contenido en la celda que se solicita
        if (!(fila >= 0 && fila < this->filas && columna >= 0 && columna < this->columnas)) {
            throw invalid_argument("La posicion de filas o columnas introducidas es invalida");
        }
        Node <T> *nodoFila = indicesFilas[fila];
        Node <T> *nodoColumna = indicesColumnas[columna];
        while (nodoFila->siguiente->columna <= columna && nodoFila->siguiente != indicesFilas[fila]) {
            nodoFila = nodoFila->siguiente;
        }
        while (nodoColumna->abajo->fila <= fila && nodoColumna->abajo != indicesColumnas[columna]) {
            nodoColumna = nodoColumna->abajo;
        }
        if (nodoColumna == nodoFila) {
            return nodoColumna->valor;
        }
        Node <T> *temporal = new Node<T>(fila, columna, 0);
        temporal->siguiente = nodoFila->siguiente;
        nodoFila->siguiente = temporal;
        temporal->abajo = nodoColumna->abajo;
        nodoColumna->abajo = temporal;
        return temporal->valor;
    };

    // Trabajar con la sobrecarga para obtener los valores va a disminuir el performance de las operaciones

    Matrix <T> operator*(T escalar) const {
        // Multiplicacion de matriz por un escalar (producto punto)
        Matrix <T> resultado(this->filas, this->columnas);
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                resultado.establecerCelda(i, j, this->operator()(i, j) * escalar);
            }
        }
        resultado.clear();
        return resultado;
    };

    Matrix <T> operator*(Matrix <T> other) const {
        // Multiplicacion de matriz por matriz (producto cruz)
        if (!this->columnas == other.filas) {
            throw invalid_argument("El numero de filas de la segunda matriz debe ser igual al numero de columnas de la primera matriz");
        }
        Matrix <T> resultado(this->filas, other.columnas);
        for (int k = 0; k < other.columnas; ++k) {
            for (int i = 0; i < this->filas; ++i) {
                T suma = 0;
                for (int j = 0; j < this->columnas; ++j) {
                    suma += (this->operator()(i, j) * other.operator()(j, k));
                }
                resultado.establecerCelda(i, k, suma);
            }
        }
        resultado.clear();
        return resultado;
    };

    Matrix <T> operator+(Matrix<T> other) const {
        // Suma de matrices
        if (!(this->filas == other.filas && this->columnas == other.columnas)) {
            throw invalid_argument("El numero de filas y columnas de ambas matrices deben ser el mismo");
        }
        Matrix <T> resultado(this->filas, this->columnas);
        for (int i = 0; i < this->filas; ++i) {
            for (int j = 0; j < this->columnas; ++j) {
                resultado.establecerCelda(i, j, this->operator()(i, j) + other.operator()(i, j));
            }
        }
        resultado.clear();
        return resultado;
    };

    Matrix <T> operator-(Matrix<T> other) const {
        // Resta de matrices
        if (!(this->filas == other.filas && this->columnas == other.columnas)) {
            throw invalid_argument("El numero de filas y columnas de ambas matrices deben ser el mismo");
        }
        Matrix <T> resultado(this->filas, this->columnas);
        for (int i = 0; i < this->filas; ++i) {
            for (int j = 0; j < this->columnas; ++j) {
                resultado.establecerCelda(i, j, this->operator()(i, j) - other.operator()(i, j));
            }
        }
        resultado.clear();
        return resultado;
    };

    Matrix <T> transpose() const {
        // Retorna la matriz transpuesta
        Matrix <T> resultado(this->columnas, this->filas);
        for (int i = 0; i < this->columnas; ++i) {
            for (int j = 0; j < this->filas; ++j) {
                resultado.establecerCelda(i, j, this->operator()(j, i));
            }
        }
        resultado.clear();
        return resultado;
    };

    void imprimir() {
        // Imprime la matriz
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                cout << this->operator()(i, j) << ' ';
            }
            cout << endl;
        }
        cout << endl;
        clear();
    };

    ~Matrix() {
        // Se eliminan todos los nodos
        for (Node <T> *&iterador : indicesColumnas) {
            Node <T> *temporal = iterador->abajo;
            delete iterador;
            while (temporal != iterador) {
                Node <T> *temporal2 = temporal;
                temporal = temporal->abajo;
                delete temporal2;
            }
            iterador = nullptr;
        }
    };
};

#endif //SPARSE_MATRIX_MATRIX_H