#include <stdio.h>

#include "matrix.h"


int main() {

    matrix_t* matrix = new_matrix(3,3);
    matrix_t* lu = new_matrix(3,3); 
    matrix_t* l = new_matrix(3,3);
    matrix_t* u = new_matrix(3,3);
    matrix_t* A = new_matrix(3,3);
    // for (int i = 0; i < matrix->lin; i++) {
    //     for (int j = 0; j < matrix->col; j++) {
    //         matrix->data[i][j] = 1;
    //     }
    // }

    matrix->data[0][0] = 1;
    matrix->data[0][1] = 2;
    matrix->data[0][2] = 3;
    matrix->data[1][0] = 4;
    matrix->data[1][1] = 5;
    matrix->data[1][2] = 6;
    matrix->data[2][0] = 7;
    matrix->data[2][1] = 8;
    matrix->data[2][2] = 9;

    // change_two_lines(matrix, 0, 2);
    print_matrix(matrix);
    
    lu = lu_decomposition(matrix);

    // matriz u
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i <= j; i++) {
            u->data[i][j] = lu->data[i][j];
        }
    }

    //matriz l
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                l->data[i][j] = 1;
            } else if(i > j) {
                l->data[i][j] = lu->data[i][j];
            } else {
                l->data[i][j] = 0;
            }
        }
    }

    A = multiply(l, u);



    print_matrix(matrix);
    printf("\n");
    print_matrix(lu);
    printf("\n");
    print_matrix(l);
    printf("\n");
    print_matrix(u);
    printf("\n");
    print_matrix(A);
        
    

    return 0;
}