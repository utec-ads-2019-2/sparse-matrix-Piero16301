#include <iostream>

#include "tester/tester.h"

int main() {
    //Tester::execute();

    Matrix <int> matrix(4, 6);
    matrix.establecerCelda(0, 0, 9);
    matrix.establecerCelda(0, 1, 8);
    matrix.establecerCelda(0, 2, 7);
    matrix.establecerCelda(0, 3, 6);
    matrix.imprimir();

    return EXIT_SUCCESS;
}