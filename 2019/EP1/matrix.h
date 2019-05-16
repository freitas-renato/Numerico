#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;

typedef vector<vector<double>> matrix_t;

void print_matrix(matrix_t M);
matrix_t matrix_multiply(matrix_t A, matrix_t B);

#endif  // _MATRIX_H_