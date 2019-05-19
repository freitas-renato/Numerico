#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;

typedef vector<vector<double>> matrix_t;
typedef vector<matrix_t> matrix3d_t;


void print_matrix(matrix_t M);
matrix_t matrix_multiply(matrix_t A, matrix_t B);
matrix_t matrix_subtract(matrix_t A, matrix_t B);
void matrix_decompose(matrix_t &A, matrix_t &W, matrix_t &H);


#endif  // _MATRIX_H_