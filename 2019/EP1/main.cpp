#include <iostream>

#include "matrix.h"
#include "system.h"
#include "primeira_tarefa.h"
// using namespace std;

int main(void) {
    int tarefa;

    cout << "Escolha a tarefa a ser executada [1, 2]: ";
    cin >> tarefa;

    switch(tarefa) {
        case 1: {
            primeira_tarefa();
            break;
        }
        
        default: {
            cout << "Opcao invalida" << endl;
            exit(-1);
            break;
        }        
    }

    return 0;
}

// Oq vc tava escrevendo, comentei só pra ver se compilava tudo

//   for (int i = 0; i < n; i++) {
//                 for (int j = 0; j < m; j++) {
//                     W[i][j] = 1;
//                     Copia[i][j] = A[i][j];
//                 }
//                 b[i][0] = 1;
//             }