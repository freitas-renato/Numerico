#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>
#include <stdlib.h>

#define max(a,b) ((a) > (b) ? (a) : (b))
#define mod(a)   ((a) > 0 ? (a) : (-a))

typedef struct {
    double** data;
    int lin, col;
} matrix_t;

matrix_t* new_matrix(int a, int b);
void copy_matrix(matrix_t* A, matrix_t* B);
void print_matrix(matrix_t* mat);
void change_two_lines(matrix_t* mat, int l1, int l2);
matrix_t* lu_decomposition(matrix_t* mat);
matrix_t* multiply(matrix_t* A, matrix_t* B);




#endif