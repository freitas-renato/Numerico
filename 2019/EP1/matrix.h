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
// void rot_givens(int columns, int i, int j, int k);
// void calc_c_s(int i, int j, int k);


#endif  // _MATRIX_H_