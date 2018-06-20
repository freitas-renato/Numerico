#ifndef _TESTE_NEWTON_H_
#define _TESTE_NEWTON_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define e M_E

// Primeiro teste
matrix_t* constroiJ1(vetor_t* x);
vetor_t* constroiF1(vetor_t *x);

// Segundo teste
matrix_t* constroiJ2(vetor_t* x);
vetor_t* constroiF2(vetor_t *x);

// Terceiro teste
matrix_t* constroiJ3(vetor_t* x);
vetor_t* constroiF3(vetor_t *x);

vetor_t* newton_teste(int n);


#endif