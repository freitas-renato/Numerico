#include <iostream>

#include "matrix.h"
#include "system.h"

// using namespace std;

int main(void) {
    int m, n, p;
    char choice;

    cout << "Primeiro teste, escolha uma alternativa [a,b,c,d]: ";
    cin >> choice;

    cout << "Digite n: ";
    cin >> n;
    cout << "Digite m: ";
    cin >> m;
    // matrix_t W(n, vector<double>(m, 0));
    matrix_t W;
    matrix_t x(m, vector<double>(1, 0));
    matrix_t b(n, vector<double>(1, 0));
    
    if (choice != 'a' && choice != 'b') {
        cout << "Digite p: ";
        cin >> p;

        matrix_t aux(n, vector<double>(p, 0));
        W = aux;
    } else {
        matrix_t aux(n, vector<double>(m, 0));
        W = aux;
    }

    matrix_t A(n, vector<double>(m, 0));

    switch(choice) {
        case 'a': {
            // Monta W e b seguindo o enunciado
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (abs(i - j) == 1) {
                        W[i][j] = 1;
                    } else if (abs(i - j ) > 1) {
                        W[i][j] = 0;
                    } else { 
                        W[i][j] = 2;
                    }
                }
                b[i][0] = 1;
            }
            cout << "Matriz W:" << endl;
            print_matrix(W);
            cout << endl << "Vetor b:" << endl;
            print_matrix(b);
            
            break;
        }

        case 'b': {
            // Monta W e b seguindo o enunciado
            for (double i = 1; i <= n; i++) {
                for (double j = 1; j <= m; j++) {
                    if (abs(i - j) > 4) {
                        W[i-1][j-1] = 0;
                    }
                    else { /* if (abs(i - j) <= 4) */
                        W[i-1][j-1] = (double)(1/(i + j - 1));
                    }
                }
                b[i-1][0] = i;
            }

            cout << "Matriz W:" << endl;
            print_matrix(W);
            cout << endl << "Vetor b:" << endl;
            print_matrix(b);

            break;
        }

        case 'c': {
            for (int i = 0; i < (int)W.size(); i++) {
                for (int j = 0; j < (int)W[0].size(); j++) {
                    if (i == j) {
                        W[i][i] = 2;
                    } else if (abs(i - j) == 1) {
                        W[i][j] = 1;
                    } else if (abs(i - j) > 1) {
                        W[i][j] = 0;
                    }
                }
            }

            for (int i = 0; i < A.size(); i++) {
                A[i][0] = 1;
                A[i][1] = i + 1;
                A[i][2] = 2 * (i + 1) - 1;
            }
            
            break;
        }

        case 'd': {
            for (double i = 1; i < (double)W.size(); i++) {
                for (double j = 1; j <= (int)W[0].size(); j++) {
                    if (abs(i - j) > 4) {
                        W[i-1][j-1] = 0;
                    } else { /* if (abs(i - j) <= 4) */
                        W[i-1][j-1] = (double)(1/(i + j - 1));
                    }
                }
            }

            for (int i = 0; i < A.size(); i++) {
                A[i][0] = 1;
                A[i][1] = i + 1;
                A[i][2] = 2 * (i + 1) - 1;
            }

            break;
        }

        default: {
            cout << "Opcao invalida" << endl;
            exit(-1);

            break;
        }
    }
    
    System* syst;
    if (choice == 'a' || choice == 'b') {
        syst = new System(W, b);
    } else {
        syst = new System(W, A);
    }

    matrix_t H;

    H = syst->solve();

    cout << endl << endl << endl << "Solucao: " << endl;
    print_matrix(H);

    return 0;
}