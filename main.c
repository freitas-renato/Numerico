#include <stdio.h>

#include "matrix.h"
#include "vetor.h"
#include "teste_newton.h"

// Dimensao do sistema
#define N 179

int main() {

    matrix_t* A = new_matrix(N,N);    
    vetor_t* x = new_vetor(N);
    vetor_t* b = new_vetor(N);

    matrix_t* J = new_matrix(N,N);
    vetor_t* c = new_vetor(N);
    vetor_t* F = new_vetor(N);

    matrix_t* lu = new_matrix(N, N);
    vetor_t* p = new_vetor(N);

    // x0
    // for (int i = 0; i < N; i++) {
    //     x->data[i] = 1;
    // }

    int n = 0;
    for(;;) {
        // Mudar entre j1 j2 j3 para os testes
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
        solve(lu, c, F, p);

        // x = x + c
        x = soma_vetores(x, c);
        printf("X: ");
        print_vetor(x);
        
        n++;
        // Erro em 1e-2
        if (mod_vetor(c) < 1e-2) {
            break;
        }
    }

    printf("Solucao: ");
    print_vetor(x);
    printf("\n");

    printf("Numero de iteracoes: %d\n", n);
        
    return 0;
}