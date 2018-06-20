#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#include "vetor.h"
#include "matrix.h"

vetor_t* read_rede(int n);
vetor_t* constroiFRede(vetor_t* x);
matrix_t* constroiJRede(vetor_t* x);
vetor_t* newton_rede(int n);
