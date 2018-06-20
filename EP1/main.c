#include <stdio.h>

#include "matrix.h"
#include "vetor.h"
#include "rede.h"
#include "teste_newton.h"

// Dimensao do sistema
#define N 5

int main() {

    // matrix_t* A = new_matrix(N,N);    
    // vetor_t* x = read_rede(1);
    // vetor_t* b = new_vetor(N);

    // matrix_t* J = new_matrix(N,N);
    // vetor_t* c = new_vetor(N);
    // vetor_t* F = new_vetor(N);

    // matrix_t* lu = new_matrix(N, N);
    // vetor_t* p = new_vetor(N);

    // x0
    // for (int i = 0; i < N; i++) {
    //     x->data[i] = 1;
    // }

    vetor_t* solucao = (vetor_t*)NULL;

    int escolha, num_teste, num_rede;
    printf("Escolha 1 para testes inciais e 2 para redes: ");
    scanf("%d", &escolha);
    switch(escolha){
        case 1:
            printf("Escolha o numero do teste (1 a 3)");
            scanf("%d", &num_teste);
            solucao = newton_teste(num_teste);
        break;
        
        case 2:
            printf("Escolha o numero da rede (1 a 4): ");
            scanf("%d", &num_rede);
            solucao = newton_rede(num_rede);
            // solucao = read_rede(num_rede);
        break;

        default:
            printf("Valor invalido\n");
            exit(-1);
        break;
    }

    printf("Solucao: ");
    print_vetor(solucao);
    printf("\n");

    // printf("Numero de iteracoes: %d\n", n);

    // matrix_t* mat = read_file("./Redes/1_Stevenson/1_Stevenson_DadosBarras.txt");
    // print_matrix(mat);
        
    return 0;
}