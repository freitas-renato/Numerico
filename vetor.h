#ifndef _VETOR_H_
#define _VETOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double* data;
    int tam;
} vetor_t;

vetor_t* new_vetor(int a);
void print_vetor(vetor_t* vetor);
void mult_vetor_numero(vetor_t* A, double num);
vetor_t* mult_vetor_vetor(vetor_t* A, vetor_t* B);
vetor_t* soma_vetores(vetor_t* A, vetor_t* B);

double mod_vetor(vetor_t* A);

void free_vetor(vetor_t* vet);

#endif