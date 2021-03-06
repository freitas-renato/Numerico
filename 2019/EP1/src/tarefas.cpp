#include "tarefas.h"

using namespace std;

void primeira_tarefa() {
    int m, n, p;
    char choice;

    cout << "Primeiro teste, escolha uma alternativa [a,b,c,d]: ";
    cin >> choice;

    cout << "Digite n: ";
    cin >> n;
    cout << "Digite m: ";
    cin >> m;
    
    matrix_t W;
    matrix_t x(m, vector<double>(1, 0));
    matrix_t b(n, vector<double>(1, 0));
    
    if (choice == 'c' || choice == 'd') {
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
            for (double i = 0; i < (int)W.size(); i++) {
                for (double j = 0; j < (int)W[0].size(); j++) {
                    if (fabs(i - j) > 4) {
                        W[i][j] = 0;
                    } else {
                        W[i][j] = (double)(1/(i + j + 1));
                    }
                }
            }

            for (int i = 0; i < (int)b.size(); i++) {
                b[i][0] = i + 1;
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

            for (int i = 0; i < (int)A.size(); i++) {
                A[i][0] = 1;
                A[i][1] = i + 1;
                A[i][2] = 2 * (i + 1) - 1;
            }
            
            break;
        }

        case 'd': {
            for (double i = 0; i < (int)W.size(); i++) {
                for (double j = 0; j < (int)W[0].size(); j++) {
                    if (fabs(i - j) > 4) {
                        W[i][j] = 0;
                    } else if (fabs(i - j) <= 4) {
                        W[i][j] = (1/(i + j + 1));
                    }
                }
            }
            for (int i = 0; i < (int)A.size(); i++) {
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
        // Wx = b
        syst = new System(W, b);
    } else {
        // WH = A
        syst = new System(W, A);
    }

    matrix_t H;
    // Solucao do sistema 
    H = syst->solve();

    cout << endl << endl << endl << "Solucao: " << endl;
    print_matrix(H);
}

void segunda_tarefa() {
    int m, n, p;

    cout << "Digite n: ";
    cin >> n;
    cout << "Digite m: ";
    cin >> m;
    cout << "Digite p: ";
    cin >> p;

    matrix_t W(n, vector<double>(p, 0));
    matrix_t A(n, vector<double>(m, 0));
    matrix_t H(p, vector<double>(m, 0));

    // Adiciona valores à A
    cout << "* Matriz A *" << endl;
    for (int i = 0; i < (int)A.size(); i++) {
        for (int j = 0; j < (int)A[0].size(); j++) {
            cout << "Digitar linha " << i+1 << " coluna " << j+1 << ": ";
            cin >> A[i][j]; 
        }
    }
    // Decomposicao da matriz A em WH
    matrix_decompose(A, W, H);

    cout << "\n\nMatriz A original: " << endl;
    print_matrix(A);

    cout << "\n\nMatriz W: " << endl;
    print_matrix(W);

    cout << "\n\nMatriz H: " << endl;
    print_matrix(H);
}