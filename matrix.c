#include "matrix.h"

matrix_t* new_matrix(int a, int b) {
    matrix_t* new_mat;

    if (a <= 0 || b <= 0) {
        printf("Linhas e colunas devem ser positivos\n");
        exit (-1);
    }

    if ((new_mat = (matrix_t*)calloc((size_t)1, sizeof(matrix_t))) == (matrix_t*)NULL) {
        printf("Erro ao alocar memoria para nova matriz\n");
        exit (-1);
    }

    new_mat->lin = a;
    new_mat->col = b;

    if ((new_mat->data = (double**)calloc(new_mat->lin, sizeof(double *))) == (double**)NULL) {
        free(new_mat);
        printf("Erro ao alocar memoria para nova matriz\n");
        exit (-1);
    }

    for (int i = 0; i < new_mat->lin; i++) {
        if ((new_mat->data[i] = (double*)calloc(new_mat->col, sizeof(double))) == (double*)NULL) {
            printf("Erro ao alocar memoria para nova matriz\n");
            exit (-1);
        }
    }

    return new_mat;
}


void copy_matrix(matrix_t* A, matrix_t* B) {
    if ((A->lin != B->lin) || (A->col != B->col)) {
        printf("Matrizes precisam ter as mesmas dimensões\n");
        exit(-1);
    }

    for (int i = 0; i < A->lin; i++) {
        for (int j = 0; j < A->col; j++) {
            B->data[i][j] = A->data[i][j];
        }
    }
}

void print_matrix(matrix_t* mat) {
    for (int i = 0; i < mat->lin; i++) {
        for (int j = 0; j < mat->col; j++) {
            printf ("%.1lf ", mat->data[i][j]);
        }
        printf("\n");
    }
}

void change_two_lines(matrix_t* mat, int l1, int l2) {
    double aux = 0;
    
    for (int j = 0; j < mat->col; j++) {
        aux = mat->data[l1][j];
        mat->data[l1][j] = mat->data[l2][j];
        mat->data[l2][j] = aux;
    }
}

matrix_t* multiply(matrix_t* A, matrix_t* B) {
    matrix_t* result = new_matrix(A->col, B->lin);
    int sum = 0;

    for (int c = 0; c < A->lin; c++) {
        for (int d = 0; d < B->col; d++) {
            for (int k = 0; k < B->lin; k++) {
                sum += A->data[c][k] * B->data[k][d];
            }
 
            result->data[c][d] = sum;
            sum = 0;
        }
    }

    return result;
}

matrix_t* lu_decomposition(matrix_t* mat) {
    int n = mat->lin;
    int l = 0;
    double aux = 0;
    // printf("%d\n", mat->lin);

    matrix_t* lu = new_matrix(mat->lin, mat->col);
    copy_matrix(mat, lu);

    double* p = (double*)calloc((size_t)n, sizeof(double));

    if (lu->lin != lu->col) {
        printf("Matriz precisa ser quadrada\n");
        exit(-1);
    }

    for (int k = 0; k < n; k++) {
        l = 0;
        aux = 0;
        for (int i = k; i < n; i++) {
            for (int j = 0; j < k; j++) {
                lu->data[i][k] -= lu->data[i][j] * lu->data[j][k];
            }
        }
        for (int i = k; i < n; i++) {
            if (mod(lu->data[i][k]) > aux) {
                aux = lu->data[i][k];
                l = i;
            }
        }
        p[k] = l;
        if (k != p[k]) {
            change_two_lines(lu, k, p[k]);
        }

        for (int j = k + 1; j < n; j++) {
            for (int i = 0; i < k; i++) {
                lu->data[k][j] -= lu->data[k][i] * lu->data[i][j];
                lu->data[j][k] /= lu->data[k][k];
            }
        }        
    }

    for (int i = 0; i < n; i++) {
        printf("%.1lf ", p[i]);
    }
    printf("\n \n");

    return lu;
}