#include "matrix.h"
#include "system.h"

void print_matrix(matrix_t M) {
    for (int i = 0; i < (int)M.size(); i++) {
        for (int j = 0; j < (int)M[0].size(); j++) {
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

matrix_t matrix_subtract(matrix_t A, matrix_t B) {
    matrix_t sub((int)A.size(), vector<double>((int)A[0].size(), 0));

    if (A.size() != B.size() || A[0].size() != B[0].size()) {
        cout << "Erro ao subtrair matrizes:" << endl;
        cout << "   As matrizes devem ter a mesma dimensao." << endl;

        exit(-1);
    }

    for (int i = 0; i < (int)A.size(); i++) {
        for (int j = 0; j < (int)A[0].size(); j++) {
            sub[i][j] = A[i][j] - B[i][j];
        }
    }

    return sub;
}

void matrix_decompose(matrix_t &A, matrix_t &W, matrix_t &H) {
    matrix_t Copia;
    matrix_t prod;

    // Transpostas
    matrix_t At(A[0].size(), vector<double>(A.size(), 0));
    matrix_t Wt(W[0].size(), vector<double>(W.size(), 0));
    matrix_t Ht(H[0].size(), vector<double>(H.size(), 0));

    double norma;
    double erro = 0;
    double last_erro = 0;
    
    srand(time(NULL));
    // Inicializa W randomicamente
    for (int i = 0; i < (int)W.size(); i++) {
        for (int j = 0; j < (int)W[0].size(); j++) {
            W[i][j] = (rand() % 1000) + 1;
        }
    }

    // cout << "Matriz W: " << endl << endl;
    // print_matrix(W);

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
                W[i][j] = (soma[j] != 0.0) ? (W[i][j] / sqrt(soma[j])) : (W[i][j]);
            }
        }

        A = Copia;
        System sys(W, A);
        H = sys.solve();
        // print_matrix(H);
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
        cout << "Iteracao: "<< itmax << ", erro: "<< norma << endl;

        if (norma < 1e-5) {
            cout << "\nFim, erro < 1e-5" << endl;
            break;
        }
    }

    A = Copia;
}