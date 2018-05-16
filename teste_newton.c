#include "matrix.h"
#include "vetor.h"
#include "teste_newton.h"


matrix_t* constroiJ1(matrix_t* A, vetor_t* x) {
    matrix_t* J = new_matrix(A->lin, A->col);

    J->data[0][0] = 2;
    J->data[0][1] = 0;
    J->data[1][0] = 0;
    J->data[1][1] = 3;

    return J;
}

vetor_t* constroiF1(vetor_t* b, vetor_t* x) {
    vetor_t* F = new_vetor(b->tam);

    F->data[0] = 2*(x->data[0] - 2);
    F->data[1] = 3*(x->data[1] - 3);

    return F;
}

matrix_t* constroiJ2(matrix_t* A, vetor_t* x) {
    matrix_t* J = new_matrix(A->lin, A->col);

    double x1 = x->data[0];
    double x2 = x->data[1];
    double x3 = x->data[2];
    double x4 = x->data[3];

    J->data[0][0] = 4 - x4;
    J->data[0][1] = -1;
    J->data[0][2] = 1;
    J->data[0][3] = -x1;
    
    J->data[1][0] = -1;
    J->data[1][1] = 3 - x4;
    J->data[1][2] = -2;
    J->data[1][3] = -x2;

    J->data[2][0] = 1;
    J->data[2][1] = -2;
    J->data[2][2] = 3 - x4;
    J->data[2][3] = -x3;

    J->data[3][0] = 2*x1;
    J->data[3][1] = 2*x2;
    J->data[3][2] = 2*x3;
    J->data[3][3] = 0;

    return J;
}

vetor_t* constroiF2(vetor_t* b, vetor_t* x) {
    vetor_t* F = new_vetor(b->tam);

    double x1 = x->data[0];
    double x2 = x->data[1];
    double x3 = x->data[2];
    double x4 = x->data[3];

    F->data[0] = 4*x1 - x2 + x3 - x1*x4;
    F->data[1] = -x1 + 3*x2 - 2*x3 - x2*x4;
    F->data[2] = x1 - 2*x2 + 3*x3 - x3*x4;
    F->data[3] = x1*x1 + x2*x2 + x3*x3 - 1;

    return F;
}
