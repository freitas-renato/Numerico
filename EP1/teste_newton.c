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

    vetor_t* F = new_vetor(x->tam);

    F->data[0] = 2*x->data[0] - x->data[1] - (exp(x->data[0])/(n*n));

    for (int i = 1; i < n - 2; i++) {
        F->data[i] = -x->data[i-1] + 2*x->data[i] - x->data[i+1] - (exp(x->data[i])/(n*n));
    }

    F->data[n-2] = -x->data[n-3] + 2*x->data[n-2] - (exp(x->data[n-2])/(n*n));

    return F;
}

vetor_t* newton_teste(int n) {
    vetor_t* x = (vetor_t*)NULL;

    matrix_t* J = (matrix_t*)NULL;
    vetor_t* c = (vetor_t*)NULL;
    vetor_t* F = (vetor_t*)NULL;

    matrix_t* lu = (matrix_t*)NULL;
    vetor_t* p = (vetor_t*)NULL;

    int iteracoes = 0;
    switch(n) {
        case 1:
            x = new_vetor(2);
            c = new_vetor(2);
            p = new_vetor(2);
            for(;;) {
                J = constroiJ1(x);
                print_matrix(J);
                // Mudar entre f1 f2 f3 para os testes
                F = constroiF1(x);
                print_vetor(F);
                
                // F => -F
                mult_vetor_numero(F, -1);

                // LU a partir de J
                lu = lu_decomposition(J, p);
                // Resolve em c usando a matrix LU: J*c = -F
                c = solve(lu, c, F, p);

                // x = x + c
                x = soma_vetores(x, c);
                printf("X: ");
                print_vetor(x);
                
                iteracoes++;
                // Erro em 1e-2
                if (mod_vetor(c) < 1e-2) {
                    free_vetor(c);
                    free_vetor(p);
                    free_matrix(lu);
                    free_matrix(J);
                    free_vetor(F);
                    printf("Iteracoes: %d\n", iteracoes);
                    return x;
                }
            }
        break;

        case 2:
            x = new_vetor(4);
            c = new_vetor(4);
            p = new_vetor(4);
            for (int i = 0; i < x->tam; i++) {
                x->data[i] = 1;
            }
            for(;;) {
                J = constroiJ2(x);
                print_matrix(J);
                // Mudar entre f1 f2 f3 para os testes
                F = constroiF2(x);
                print_vetor(F);
                
                // F => -F
                mult_vetor_numero(F, -1);

                // LU a partir de J
                lu = lu_decomposition(J, p);
                // Resolve em c usando a matrix LU: J*c = -F
                c = solve(lu, c, F, p);

                // x = x + c
                x = soma_vetores(x, c);
                printf("X: ");
                print_vetor(x);
                
                iteracoes++;
                // Erro em 1e-2
                if (mod_vetor(c) < 1e-2) {
                    free_vetor(c);
                    free_vetor(p);
                    free_matrix(lu);
                    free_matrix(J);
                    free_vetor(F);
                    printf("Iteracoes: %d\n", iteracoes);
                    
                    return x;
                }
            }
        break;

        case 3:
            printf("Escolha a dimensao do sistema: ");
            int dimensao;
            scanf("%d", &dimensao);
            x = new_vetor(dimensao);
            c = new_vetor(dimensao);
            p = new_vetor(dimensao);
            for(;;) {
                J = constroiJ3(x);
                print_matrix(J);
                // Mudar entre f1 f2 f3 para os testes
                F = constroiF3(x);
                print_vetor(F);
                
                // F => -F
                mult_vetor_numero(F, -1);

                // LU a partir de J
                lu = lu_decomposition(J, p);
                // Resolve em c usando a matrix LU: J*c = -F
                c = solve(lu, c, F, p);

                // x = x + c
                x = soma_vetores(x, c);
                printf("X: ");
                print_vetor(x);
                
                iteracoes++;
                // Erro em 1e-2
                if (mod_vetor(c) < 1e-2) {
                    free_vetor(c);
                    free_vetor(p);
                    free_matrix(lu);
                    free_matrix(J);
                    free_vetor(F);
                    printf("Iteracoes: %d\n", iteracoes);
                    
                    return x;
                }
            }
        break;

        default:
            printf("Valor invalido para os testes\n");
        break;
    }

    return (vetor_t*)NULL;
}
