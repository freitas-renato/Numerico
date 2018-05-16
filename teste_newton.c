#include "matrix.h"
#include "vetor.h"
#include "teste_newton.h"


matrix_t* constroiJ1(vetor_t* x) {
    matrix_t* J = new_matrix(x->tam, x->tam);

    J->data[0][0] = 2;
    J->data[0][1] = 0;
    J->data[1][0] = 0;
    J->data[1][1] = 3;

    return J;
}

vetor_t* constroiF1(vetor_t* x) {
    vetor_t* F = new_vetor(x->tam);

    F->data[0] = 2*(x->data[0] - 2);
    F->data[1] = 3*(x->data[1] - 3);

    return F;
}

matrix_t* constroiJ2(vetor_t* x) {
    matrix_t* J = new_matrix(x->tam, x->tam);

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

vetor_t* constroiF2(vetor_t* x) {
    vetor_t* F = new_vetor(x->tam);

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

matrix_t* constroiJ3(vetor_t* x) {
    matrix_t* J = new_matrix(x->tam, x->tam);

    // Sistema n-1 x n-1
    int n = x->tam + 1;

    J->data[0][0] = 2 - exp(x->data[0])/(n*n);
    J->data[0][1] = -1;

    for (int i = 1; i < n - 2; i++) {
        J->data[i][i-1] = -1;
        J->data[i][i] = 2 - exp(x->data[i])/(n*n);
        J->data[i][i+1] = -1;
    }

    J->data[n-2][n-3] = -1;
    J->data[n-2][n-2] = 2 - exp(x->data[n-2])/(n*n);

    return J; 
}

vetor_t* constroiF3(vetor_t *x) {
    // Sistema n-1 x n-1
    int n = x->tam + 1;

    vetor_t* F = new_vetor(b->tam);

    F->data[0] = 2*x->data[0] - x->data[1] - (exp(x->data[0])/(n*n));

    for (int i = 1; i < n - 2; i++) {
        F->data[i] = -x->data[i-1] + 2*x->data[i] - x->data[i+1] - (exp(x->data[i])/(n*n));
    }

    F->data[n-2] = -x->data[n-3] + 2*x->data[n-2] - (exp(x->data[n-2])/(n*n));

    return F;
}
