#include <iostream>
#include <vector>
#include <math.h>

//#ifndef Rotacao
//#define Rotacao
 
using namespace std;

class Rotacao {
public:
    Rotacao(vector<vector<double>> w, vector<double> b, int m, int n);
    ~Rotacao();

    void fatoracao(int i, int j, int k);
    void calculo_Q(int i, int j, int m);

    vector<vector<double>> getW(void);
    vector<double> getB(void);
    
    double getC(void);
    double getS(void);

private:
    double c, s, tal;
    vector<vector<double>> w;
    vector<double> b;
    int m, n;
};
//#endif