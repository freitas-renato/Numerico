#ifndef _TRAIN_H_
#define _TRAIN_H_

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <vector>

#include "matrix.h"
#include "system.h"

using namespace std;

/**
* @class   Treinamento para a classificação de dígitos 
* @param   m     colunas da matriz A
* @param   p     colunas da matriz Wd
* @param   ntest número de digitos a serem classificados
*/
class Train {
public:
    Train(int m, int p, int ntest);
    ~Train();

    /**
    * @brief   Cria a matriz A para todos os digitos
    */
    void get_A();
    
    /**
    * @brief   Calcula a matriz Wd para todos os digitos
    *          fazendo a decomposição da matriz A
    */
    void calc_Wd();

    /**
    * @brief   Classifica os imagens do arquivo test_images.txt
    *          Resultado armazenado no arquvio test_result.txt
    */
    void classify();

    /**
    * @brief   Analisa a porcentagem de acerto com base no 
    *          gabarito test_index.txt
    */
    void analise();

private:
    matrix3d_t A;
    matrix3d_t Wd;
    vector<double> digi;
    vector<double> erro;
    vector<double> compare;
    int n, m, p, d;
    int ntest;  
};

#endif  // _TRAIN_H_