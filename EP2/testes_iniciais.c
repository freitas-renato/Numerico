#include "testes_iniciais.h"
#include "fft.h"

void teste1() {
    vetor_t* func = new_vetor(4);
    vetor_t* c = new_vetor(func->tam);

    func->data[0] = 5;
    func->data[1] = -1;
    func->data[2] = 3;
    func->data[3] = 1;


    printf("Transformada direta: \n");
    // fft(c, func, c->tam, 0);
    fftrec(c, func, c->tam / 2, 0);
    // print_vetor(c);

    printf("\nTransformada inversa nos valores anteriores: \n");
    fft(c, func, c->tam, 1);
}
