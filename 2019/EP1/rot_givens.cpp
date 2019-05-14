#include "rot_givens.h"

Rotacao::Rotacao (vector<vector<double>> w, vector<double> b, int m, int n) : w(w), b(b), m(m), n(n) {
}

Rotacao::~Rotacao() {
}

void Rotacao::fatoracao(int i, int j, int k) {
    if (abs(this->w[i][k]) > abs(this->w[j][k])) {
        tal = -this->w[j][k]/this->w[i][k]; 
        c = 1/sqrt(1 + pow(tal, 2.0));
        s = c * tal;
    }
    else {
        tal = -this->w[i][k]/this->w[j][k];
        s = 1/sqrt(1 + pow(tal, 2.0));
        c = s * tal;
    }
}

void Rotacao::calculo_Q(int i, int j, int m){
    double aux = 0;
    for (int r = 0; r < m; r++){
        aux = (c * this->w[i][r]) - (s * this->w[j][r]);
        this->w[j][r] = (s * this->w[i][r]) + (c * this->w[j][r]);
        this->w[i][r] = aux;
    }
    aux = (c * this->b[i]) - (s * this->b[j]);
    this->b[j] = (s * this->b[i]) + (c * this->b[j]);
    this->b[i] = aux;
}


//double Rotacao::getC(void){
  //  return c;
//}

//double Rotacao::getS(void){
//    return s;
//}

vector<vector<double>> Rotacao::getW(void){
   return w;
}

vector<double> Rotacao::getB(void){
   return b;
}
