#include <iostream>

#include "matrix.h"
#include "system.h"
#include "tarefas.h"
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

        case 2: {
            segunda_tarefa();
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

