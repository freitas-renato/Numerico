#include "matrix.h"

void print_matrix(matrix_t M) {
    for (int i = 0; i < M.size(); i++) {
        for (int j = 0; j < M[0].size(); j++) {
            cout << setw(10) << right << setprecision(3) << M[i][j];
        }
        cout << endl;
    }
}