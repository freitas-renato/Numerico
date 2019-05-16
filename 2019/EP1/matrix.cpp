#include "matrix.h"

void print_matrix(matrix_t M) {
    for (int i = 0; i < M.size(); i++) {
        for (int j = 0; j < M[0].size(); j++) {
            cout << setw(10) << right << fixed << setprecision(3) << M[i][j];
        }
        cout << endl;
    }
}

matrix_t matrix_multiply(matrix_t A, matrix_t B) {
    // Matrix produto com (a.linhas) x (b.colunas)
    matrix_t mult((int)A.size(), vector<double>((int)B[0].size(), 0));

    for (int i = 0; i < (int)A.size(); i++) {
        for (int j = 0; j < (int)B[0].size(); j++) {
            for (int t = 0; t < (int)A[0].size(); t++) {
                mult[i][j] += A[i][t] * B[t][j];
            }
        }
    }

    return mult;
}