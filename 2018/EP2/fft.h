#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#include "vetor.h"

// Funcoes retornam o tempo de execucao
double fft(vetor_t* c, vetor_t* f, int dois_n, int dir);
double fftrec(vetor_t* c, vetor_t* f, int n, int dir);
