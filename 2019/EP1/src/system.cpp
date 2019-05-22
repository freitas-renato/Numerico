#include "system.h"

System::System(matrix_t W, matrix_t A) : W(W), A(A) {
    this->c = 0;
    this->s = 0;
}

System::~System() {
    // Class destructor
}

void System::rot_givens(int i, int j, int k) {
    double aux = 0;
    double tau = 0;

    // Calculo de C e S
    if (abs(this->W[i][k]) > abs(this->W[j][k])) {
        tau = -this->W[j][k]/this->W[i][k]; 
        c = 1/sqrt(1 + pow(tau, 2.0));
        s = c * tau;
    } else {
        tau = -this->W[i][k]/this->W[j][k];
        s = 1/sqrt(1 + pow(tau, 2.0));
        c = s * tau;
    }

    // Rotação de Givens em W
    for (int r = 0; r < (int)W[i].size(); r++) {
        aux = (c * this->W[i][r]) - (s * this->W[j][r]);
        this->W[j][r] = (s * this->W[i][r]) + (c * this->W[j][r]);
        this->W[i][r] = aux;
    }

    // Rotação de Givens em A
    for (int r = 0; r < (int)A[i].size(); r++) {
        aux = (c * this->A[i][r]) - (s * this->A[j][r]);
        this->A[j][r] = (s * this->A[i][r]) + (c * this->A[j][r]);
        this->A[i][r] = aux;
    }
}

matrix_t System::solve() {
    matrix_t H((int)W[0].size(), vector<double>(A[0].size(), 0));
    double soma = 0;

    for (int k = 0; k < (int)W[0].size(); k++) {
        for (int j = (int)W.size() - 1; j >= k + 1; j--) {
            int i = j - 1;
            if (W[j][k] != 0) {
                rot_givens(i, j, k);
            }
        }
    }

    for (int k = (int)W[0].size() - 1; k >= 0; k--) {
        for (int j = 0; j < (int)A[0].size(); j++) {
            soma = 0;
            for (int i = k; i < (int)W[0].size(); i++) {
                soma += W[k][i] * H[i][j];
            }
            // Verificação para não ocorrer divisão por 0
            H[k][j] = (W[k][k] != 0) ? ((A[k][j] - soma) / W[k][k]) : (A[k][j] - soma);
        }
    }

    return H;
}
