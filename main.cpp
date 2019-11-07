#include <iostream>

#include "tester/tester.h"

int main() {
    //Tester::execute();

    Matrix <int> matrix(4, 6);
    matrix.establecerCelda(0, 0, 2);
    matrix.establecerCelda(2, 1, 5);
    matrix.imprimir();

    return EXIT_SUCCESS;
}