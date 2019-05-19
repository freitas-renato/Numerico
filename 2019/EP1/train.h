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

class Train {
public:
    Train(int m, int p, int ntest);
    ~Train();

    void get_A();
    void calc_Wd();
    void calc_H();
    void machine();
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