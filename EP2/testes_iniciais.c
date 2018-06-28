#include "testes_iniciais.h"
#include "fft.h"

void teste1() {
    vetor_t* func = new_vetor(4);
    vetor_t* c = new_vetor(func->tam);
    double tempo = 0;

    func->data[0] = 5;
    func->data[1] = -1;
    func->data[2] = 3;
    func->data[3] = 1;
    
    printf("\nTransformada direta Lenta: \n");
    tempo = fft(c, func, c->tam, 1);
    print_vetor(c);


    printf("Transformada direta Rápida: \n");
    tempo = fftrec(c, func, c->tam / 2, 1);
    print_vetor(c);
    

}


void teste2() {
    vetor_t* c = new_vetor(4);
    vetor_t* func = new_vetor(c->tam);
    double tempo = 0;

    c->data[0] = 2;
    c->data[1] = (0.5 + 0.5*I);
    c->data[2] = 2;
    c->data[3] = (0.5 - 0.5*I);

    printf("\nTransformada Inversa Lenta: \n");
    tempo = fft(c, func, c->tam, 0);
    print_vetor(func);
    

    printf("Transformada inversa Rápida: \n");
    tempo = fftrec(func, c, func->tam/2 , 0);
    print_vetor(func);
}

void teste3() {
    vetor_t* func = new_vetor(8);
    vetor_t* c = new_vetor(func->tam);
    double tempo = 0;

    func->data[0] = 6;
    func->data[1] = 2;
    func->data[2] = 5;
    func->data[3] = 2;
    func->data[4] = 11;
    func->data[5] = 2;
    func->data[6] = 8;
    func->data[7] = 8;

    printf("FFT direta: \n");
    tempo = fftrec(c, func, c->tam/2, 1);
    printf("Tempo = %lf\n", tempo);
    print_vetor(c);

    printf("FFT inversa nos valores anteriores normalizados: \n");
    tempo = fftrec(func, c, func->tam/2, 0);
    print_vetor(func);

}
