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

vector_t* new_vector(int a) {
    vector_t* new_vec;

    if (a <= 0) {
        printf("Vetor precisa ter tamanho positivo\n");
        exit(-1);
    }

    new_vec = (vector_t*)calloc((size_t)1, sizeof(vector_t));

    new_vec->tamanho = a;

    new_vec->data = (double*)calloc(new_vec->tamanho, sizeof(double));

    return new_vec;
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
            printf ("%.3e ", mat->data[i][j]);
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
    for (int i = 0; i < A->lin; i++) {
        for (int j = 0; j < B->col; j++) {
            result->data[i][j] = 0;
            for (int k = 0; k < B->lin; k++)
                result->data[i][j] += A->data[i][k] * B->data[k][j];
        }
    }

    return result;
}

matrix_t* lu_decomposition(matrix_t* mat, double* p) {
    int n = mat->lin;
    int l = 0;
    double max, max_ant = 0;
    double soma = 0;
    // printf("%d\n", mat->lin);

    matrix_t* lu = new_matrix(mat->lin, mat->col);
    copy_matrix(mat, lu);


    if (lu->lin != lu->col) {
        printf("Matriz precisa ser quadrada\n");
        exit(-1);
    }

    for (int k = 0; k < n; k++) {
        l = 0;
        for (int i = k; i < n; i++) {
            soma = 0;

            for (int j = 0; j < k; j++) {
                lu->data[i][k] -= lu->data[i][j] * lu->data[j][k];
            }
        }

        // L
        max = 0, max_ant = -1;
        for (int i = k; i < n; i++) {
            if (mod(lu->data[i][k]) > max) {
                max = lu->data[i][k];
                l = i;
            }
        }
        p[k] = l;
        if (k != (int)p[k]) {
            change_two_lines(lu, k, (int)p[k]);
        }

        for (int j = k + 1; j < n; j++) {
            soma = 0;
            for (int i = 0; i < k; i++) {
                lu->data[k][j] -= lu->data[k][i] * lu->data[i][j];
            }
            lu->data[j][k] /= lu->data[k][k];
        }        
    }

    // Imprime vetor p
    for (int i = 0; i < n; i++) {
        printf("%.1lf ", p[i]);
    }
    printf("\n \n");

    return lu;
}

void solve(matrix_t* A, double* x, double* b, double* p) {
    int n = A->col;
    // Permuta b
    double aux;
    for (int i = n - 1; i >= 0; i--) {
        if (i != (int)p[i]) {
            aux = b[i];
            b[i] = b[(int)p[i]];
            b[(int)p[i]] = aux;
        }
    }

    for (int i = 0; i < n; i++) {
        x[i] = b[i];
        // printf("%lf ", x[i]);
        for (int k = 0; k < i; k++) {
            x[i] -= A->data[i][k] * x[k];
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int k = i + 1; k < n; k++) {
            x[i] -= A->data[i][k] * x[k]; 
        }
        
        x[i] /= A->data[i][i];
    }

    
}