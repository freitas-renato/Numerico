#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <vector>

#include "matrix.h"

using namespace std;

class System {
public:
    System(matrix_t W, matrix_t A);
    ~System();

    void rot_givens(int i, int j, int k);

    matrix_t solve();

private:
    matrix_t W;
    matrix_t A;

    double c, s;
};

#endif  // _SYSTEM_H_