#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <vector>

#include "matrix.h"

using namespace std;

/**
* @class   Resolve sistemas do tipo WH = A 
* @param   W    matriz n x p 
* @param   A    matriz n x m
*/
class System {
public:
    System(matrix_t W, matrix_t A);
    ~System();

    /**
    * @brief   Rotação de Givens nas matrizes W e A 
    * @param   i    linha i para rotacionar
    * @param   j    linha j para rotacionar
    * @param   k    coluna para os elementos i,k e j,k
    */
    void rot_givens(int i, int j, int k);

    /**
    * @brief   Soluciona o sistema 
    * @retval  Matriz H (p x m) com a solução do sistema WH = A
    */
    matrix_t solve();

private:
    matrix_t W;
    matrix_t A;

    double c, s;
};

#endif  // _SYSTEM_H_
