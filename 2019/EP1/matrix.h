#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;

/**
 * @type   2D vector 
 */
typedef vector<vector<double>> matrix_t;

/**
 * @type   3D vector 
 */
typedef vector<matrix_t> matrix3d_t;

/**
 * @brief   Imprime uma matriz 
 * @param   M       Matriz a ser impressa
 * @retval  None
 */
void print_matrix(matrix_t M);

/**
 * @brief   Multiplica duas matrizes
 * @param   A       Primeira Matriz
 * @param   B       Segunda Matriz
 * @retval  prod    Matriz resultante
 */
matrix_t matrix_multiply(matrix_t A, matrix_t B);

/**
 * @brief   Subtrai duas matrizes
 * @param   A       Primeira Matriz
 * @param   B       Segunda Matriz
 * @retval  result  Matriz resultante
 */
matrix_t matrix_subtract(matrix_t A, matrix_t B);

/**
 * @brief   Realiza a fatoração QR de uma matriz
 * @param   A       Matriz a ser decomposta (n x m)
 * @param   W       Matriz com tamanho n x p
 * @param   W       Matriz com tamanho p x m
 * @retval  none
 */
void matrix_decompose(matrix_t &A, matrix_t &W, matrix_t &H);


#endif  // _MATRIX_H_