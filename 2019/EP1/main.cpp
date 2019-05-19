#include <iostream>
#include <fstream>
#include <istream>
#include <string>

#include "matrix.h"
#include "system.h"
#include "tarefas.h"
#include "train.h"
// using namespace std;

int main(void) {  
    int tarefa;
    int p, m, ntest;
    
    cout << R"(Escolha a tarefa a ser executada:
         😢 😜- Rotacao de Givens(1)
         ✌ 😂- Fatoracao de Matriz Nao Negativa(2)
         😎  - Tarefa Principal - Machine Learning(3))" << endl;;
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

        case 3: {
            cout << "Escreva 'ndig_treino': ";
            cin >> m;
            cout << "Escreva 'ntest': ";
            cin >> ntest; 
            cout << "Escreva 'p': ";
            cin >> p;        
            Train treino(m, p, ntest);
            treino.get_A();
            treino.calc_Wd();
            treino.machine();
            treino.analise();
            cout << "Cabou 👌 🔝";
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

