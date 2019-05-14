#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "rot_givens.h"

using namespace std;

typedef vector<vector<double>> matrix_t;

int main(){
    int m, n;
    double soma;
    char choice;


    cout << "Primeiro teste, escolha uma alternativa [a,b,c,d]: ";
    cin >> choice;

    cout << "Digite n: ";
    cin >> n;
    cout << "Digite m: ";
    cin >> m;
    
    vector<vector<double>> w(n, vector<double>(m, 0));
    vector<double> b(n, 1);
    vector<double> x(n, 0);

    switch (choice) {
        case ('a'):
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (abs(i - j) == 1) {
                        w[i][j] = 1;
                    } else if (abs(i - j ) > 1) {
                        w[i][j] = 0;
                    } else { 
                        w[i][j] = 2;
                    }
                }
            }
        break;
        
        case ('b'):
            for (double i = 1; i <= n; i++) {
                for (double j = 1; j <= m; j++) {
                    if (abs(i - j) > 4) {
                        w[i-1][j-1] = 0;
                    }
                    else { /* if (abs(i - j) <= 4) */
                        w[i-1][j-1] = (double)1/(i + j - 1);
                    }
                }
                b[i] = i;
            }
        break;

        default:
            cout << "Opcao invalida :(" << endl;
            break;
    }

    // Imprime matriz W criada
    cout << "W:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "\n";
        for (int j = 0; j < m; j++) {
            cout << w[i][j] << " ";
        }
    }
    cout << "\nb: ";
    for (int i = 0; i < (int)b.size(); i++) {
        cout << b[i] << " ";
    }
    cout << "\nok" << endl;
       
    Rotacao *givens = new Rotacao(w, b, m, n);

    for (int k = 0; k < m; k++){
        for (int j = n - 1 ; j >= k + 1; j--) {
            int i = j - 1;
            if (w[j][k] != 0) {
                givens->fatoracao(i, j, k);
                givens->calculo_Q(i, j, m);
           }
        }
    }

    w = givens->getW();
    b = givens->getB();
    
    cout << "\nMatriz R triangular: ";
    cout << fixed;
    for (int i = 0; i < n; i++) {
        cout << "\n";
        for (int j = 0; j < m; j++) {
            cout << setw(3) << setprecision(1) << w[i][j];
        }
    }

    cout << "\n\nVetor ~b: ";
    for (int i = 0; i < b.size(); i++) {
        cout << b[i] << " ";
    }

    cout << endl << endl << "Solucao x: ";
    for (int k = m - 1; k >= 0; k--){
        soma = 0;
        for (int j = k; j < m; j++){
            soma += w[k][j] * x[j];
        }
        x[k] = (b[k] - soma)/w[k][k];
        cout << " " << x[k];
    }

    cout << endl;

    return 0;
}



