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
            printf ("%.3lf \t", mat->data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
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

matrix_t* lu_decomposition(matrix_t* mat, vetor_t* p) {
    int n = mat->lin;
    int l = 0;
    double max = 0;
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
            for (int j = 0; j < k; j++) {
                lu->data[i][k] -= lu->data[i][j] * lu->data[j][k];
            }
        }

        // L
        max = 0;
        for (int i = k; i < n; i++) {
            if (mod(lu->data[i][k]) > max) {
                max = lu->data[i][k];
                l = i;
            }
        }
        p->data[k] = l;
        if (k != (int)p->data[k]) {
            change_two_lines(lu, k, (int)p->data[k]);
        }

        for (int j = k + 1; j < n; j++) {
            for (int i = 0; i < k; i++) {
                lu->data[k][j] -= lu->data[k][i] * lu->data[i][j];
            }
            lu->data[j][k] /= lu->data[k][k];
        }        
    }

    // Imprime vetor p
    printf("p: ");
    for (int i = 0; i < n; i++) {
        printf("%.1lf ", p->data[i]);
    }
    printf("\n \n");

    return lu;
}

void solve(matrix_t* A, vetor_t* x, vetor_t* b, vetor_t* p) {
    int n = A->col;
    // Permuta b
    double aux;
    for (int i = n - 1; i >= 0; i--) {
        if (i != (int)p->data[i]) {
            aux = b->data[i];
            b->data[i] = b->data[(int)p->data[i]];
            b->data[(int)p->data[i]] = aux;
        }
    }

    for (int i = 0; i < n; i++) {
        x->data[i] = b->data[i];
        // printf("%lf ", x[i]);
        for (int k = 0; k < i; k++) {
            x->data[i] -= A->data[i][k] * x->data[k];
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int k = i + 1; k < n; k++) {
            x->data[i] -= A->data[i][k] * x->data[k]; 
        }
        
        x->data[i] /= A->data[i][i];
    }

    
}

void free_matrix(matrix_t* mat) {
    for (int i = 0; i < mat->lin; i++) {
        free(mat->data[i]);
    }

    mat->lin = 0;
    mat->col = 0;
    free(mat->data);
    free(mat);
    mat = (matrix_t*)NULL;
}

matrix_t* read_file(char* nome) {
    matrix_t* new_mat;
    int num = 0;
    FILE* file = fopen(nome, "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(-1);
    }

    if(fscanf(file, "%d ", &num) < 1) {
        printf("Falha ao ler o arquivo\n");
        exit(-1);
    }

    new_mat = new_matrix(num, 5);

    for (int i = 0; i < num; i++) {
        for (int j = 0; j < 5; j++) {
            fscanf(file, "%lf ", &new_mat->data[i][j]);
        }
    }

    return new_mat;
}