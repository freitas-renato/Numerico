#include "testes_iniciais.h"
#include "fft.h"

void teste1() {
    vetor_t* func = new_vetor(4);
    vetor_t* c = new_vetor(func->tam);

    func->data[0] = 5;
    func->data[1] = -1;
    func->data[2] = 3;
    func->data[3] = 1;
    
    printf("\nTransformada direta Lenta: \n");
    fft(c, func, c->tam, 1);
    print_vetor(c);


    printf("Transformada direta Rápida: \n");
    fftrec(c, func, c->tam / 2, 1);
    print_vetor(c);

}


void teste2() {
    vetor_t* c = new_vetor(4);
    vetor_t* func = new_vetor(c->tam);

    c->data[0] = 2;
    c->data[1] = (0.5 + 0.5*I);
    c->data[2] = 2;
    c->data[3] = (0.5 - 0.5*I);

    printf("\nTransformada Inversa Lenta: \n");
    fft(c, func, c->tam, 0);
    print_vetor(func);

    printf("Transformada inversa Rápida: \n");
   
    fftrec(func, c, func->tam/2 , 0);
    print_vetor(func);
}
