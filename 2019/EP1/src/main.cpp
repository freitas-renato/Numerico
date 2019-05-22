/**
 * Escola Politécnica da USP
 * MAP3121 - Metodos Numericos e Aplicacoes
 *
 * Exercicio Programa 1
 *
 * Lucas Sorensen Paes          9836919     <lucas.paes@usp.br>
 * Renato de Oliveira Freitas   9837708     <renato.freitas@usp.br>
 * 
 * 
 * 05/2019
 */

#include <iostream>
#include <fstream>
#include <istream>
#include <string>

#include "matrix.h"
#include "system.h"
#include "tarefas.h"
#include "train.h"

using namespace std;

int main(void) {  
    int tarefa;
    int p, m, ntest;
    
    cout << R"(Escolha a tarefa a ser executada:
        1 - Rotacao de Givens
        2 - Fatoracao de Matriz Nao Negativa
        3 - Tarefa Principal - Machine Learning)" << endl;
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
            treino.classify();
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

