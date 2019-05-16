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
    // matrix_t W(n, vector<double>(m, 0));
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
            for (double i = 0; i < W.size(); i++) {
                for (double j = 0; j < W[0].size(); j++) {
                    if (fabs(i - j) > 4) {
                        W[i][j] = 0;
                    } else {
                        W[i][j] = (double)(1/(i + j + 1));
                    }
                }
            }

            for (int i = 0; i < b.size(); i++) {
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

            for (int i = 0; i < A.size(); i++) {
                A[i][0] = 1;
                A[i][1] = i + 1;
                A[i][2] = 2 * (i + 1) - 1;
            }
            
            break;
        }

        case 'd': {
            for (double i = 0; i < W.size(); i++) {
                for (double j = 0; j < W[0].size(); j++) {
                    if (fabs(i - j) > 4) {
                        W[i][j] = 0;
                    } else if (fabs(i - j) <= 4) {
                        W[i][j] = (1/(i + j + 1));
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
}

void segunda_tarefa() {
    int m, n, p;
    double norma;
    double erro = 0;
    double last_erro = 0;

    cout << "Digite n: ";
    cin >> n;
    cout << "Digite m: ";
    cin >> m;
    cout << "Digite p: ";
    cin >> p;

    matrix_t W(n, vector<double>(p, 0));
    matrix_t Wt(p, vector<double>(n, 0));

    matrix_t A(n, vector<double>(m, 0));
    matrix_t At(m, vector<double>(n, 0));
    matrix_t Copia;

    // matrix_t H(p, vector<double>(m, 0));
    matrix_t H;
    matrix_t Ht(m, vector<double>(p, 0));

    matrix_t prod;

    // Adiciona valores à A
    cout << "* Matriz A *" << endl;
    for (int i = 0; i < (int)A.size(); i++) {
        for (int j = 0; j < (int)A[0].size(); j++) {
            cout << "Digitar linha " << i << " coluna " << j << ": ";
            cin >> A[i][j]; 
        }
    }

    // Inicializa W randomicamente
    for (int i = 0; i < (int)W.size(); i++) {
        for (int j = 0; j < (int)W[0].size(); j++) {
            W[i][j] = 1;
        }
    }
    cout << "Matriz W: " << endl << endl;
    print_matrix(W);

    // Salva matriz A
    Copia = A;

    for (int itmax = 0; itmax < 100; itmax++) {
        last_erro = erro;
        erro = 0;

        vector<double> soma((int)W[0].size(), 0); // Vetor para soma das colunas
        // Soma as colunas (w * w)
        for (int i = 0; i < (int)W.size(); i++) {
            for (int j = 0; j < (int)W[0].size(); j++) {
                soma[j] += W[i][j] * W[i][j];
            }
        }

        // Normaliza W
        for (int i = 0; i < (int)W.size(); i++) {
            for (int j = 0; j < (int)W[0].size(); j++) {
                W[i][j] = (soma[j] != 0) ? (W[i][j] / sqrt(soma[j])) : (W[i][j]);
            }
        }

        A = Copia;
        System sys(W, A);
        H = sys.solve();

        // Coloca h = max{0, h}
        for (int i = 0; i < (int)H.size(); i++) {
            for (int j = 0; j < (int)H[0].size(); j++) {
                H[i][j] = (H[i][j] < 0) ? 0 : H[i][j];
            }
        }

        // Transposta de A original em At
        for (int i = 0; i < (int)Copia.size(); i++) {
            for (int j = 0; j < (int)Copia[0].size(); j++) {
                At[j][i] = Copia[i][j];
            }
        }

        // Transposta de H em Ht
        for (int i = 0; i < (int)H.size(); i++) {
            for (int j = 0; j < (int)H[0].size(); j++) {
                Ht[j][i] = H[i][j];
            }
        }

        System sys2(Ht, At);
        Wt = sys2.solve();

        // Transposta de Wt em W
        for (int i = 0; i < (int)Wt.size(); i++) {
            for (int j = 0; j < (int)Wt[0].size(); j++) {
                W[j][i] = Wt[i][j];
            }
        }

        // Redefine W: w = max{0, w}
        for (int i = 0; i < (int)W.size(); i++) {
            for (int j = 0; j < (int)W[0].size(); j++) {
                W[i][j] = (W[i][j] < 0) ? 0 : W[i][j];
            }
        }

        prod = matrix_multiply(W, H);

        for (int i = 0; i < (int)Copia.size(); i++) {
            for (int j = 0; j < (int)Copia[0].size(); j++) {
                erro += pow(Copia[i][j] - prod[i][j], 2);
            }
        }

        norma = fabs(erro - last_erro);
        cout << "Iteração: "<< itmax << ", erro: "<< norma << endl;

        if (norma < 1e-5) {
            cout << "\nFim, erro < 1e-5" << endl;
            break;
        }

    }

    cout << "\n\nMatriz A original: " << endl;
    print_matrix(Copia);

    cout << "\n\nMatriz W: " << endl;
    print_matrix(W);

    cout << "\n\nMatriz H: " << endl;
    print_matrix(H);
}