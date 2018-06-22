#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#include "vetor.h"

void fft(vetor_t* c, vetor_t* f, int dois_n, int dir);
void fftrec(vetor_t* c, vetor_t* f, int n, int dir);