#include "train.h"

#include <fstream>

using namespace std;

Train::Train(int m, int p, int ntest) : A(10, matrix_t(784, vector<double>(m, 0))),
                                        Wd(10, matrix_t(784, vector<double>(p, 0))),
                                        digi(ntest, 0),
                                        erro(ntest),
                                        compare(10000) {
    this->m = m;
    this->p = p;
    this->ntest = ntest;

}

Train::~Train() {
    // Class destructor
}

void Train::get_A() {
    double tmp;
    int total = 0, linha = 0, coluna = 0;
    string batata;
    ifstream file;

    for (int i = 0; i < 10; i++) {
        file.open(("./dados_mnist/train_dig" + to_string(i) + ".txt"), ios::in);
    
        if (!file) {
            cout << "Erro ao abrir o arquivo" << endl;
            exit(-1);
        }

        total = 0;
        linha = 0;

        if (file.is_open()) {
            while (file >> tmp) {
                total++;
            }
            cout << "Total: " << total << endl;

            file.clear();
            file.seekg(0, ios::beg);    
                
            while (getline(file, batata)) {
                linha++;
            }
            cout << "Linhas: " << linha << endl;

            coluna = total/linha;
            file.clear();
            file.seekg(0, ios::beg);

            cout << "Colunas: "<< coluna << endl;
            for (int j = 0; j < linha; j++) {
                for (int k = 0; k < coluna; k++) {
                    file >> tmp;
                    if (k < this->m) {
                        A[i][j][k] = tmp;       
                    }
                }
            }
        } 
        else { 
            cout << "Erro ao abrir o arquivo" << endl;
        }        
        file.close();

        cout << "Arquivo " << i << " done." << endl << endl;
    }

}

void Train::calc_Wd() {
    for (int i = 0; i < 10; i++) {
        matrix_t H(this->p, vector<double>(this->m, 0));
        matrix_decompose(A[i], Wd[i], H);
        cout << "Matriz " << i << "ok." << endl;
    }
}

void Train::machine() {
    matrix_t Luquinhas(784, vector<double>(ntest, 0));
    matrix_t Renatinho(784, vector<double>(ntest, 0));
    matrix3d_t H(10, matrix_t(this->p, vector<double>(ntest, 0)));
    matrix3d_t E(10, matrix_t(784, vector<double>(ntest, 0)));

    string batata;
    int total, linha, coluna;
    double tmp;
    ifstream file;

    file.open(("./dados_mnist/test_images.txt"), ios::in);
    if (!file) {
        cout << "Erro ao abrir o arquivo" << endl;
        exit(-1);
    }
    
    total = 0;
    linha = 0;
    
    if (file.is_open()) {
        while (file >> tmp) {
            total++;
        }
        cout << "Total: " << total << endl;

        file.clear();
        file.seekg(0, ios::beg);    
            
        while (getline(file, batata)) {
            linha++;
        }
        cout << "Linhas: " << linha << endl;

        coluna = total/linha;
        file.clear();
        file.seekg(0, ios::beg);

        cout << "Colunas: "<< coluna << endl;
        for (int i = 0; i < linha; i++) {
            for (int j = 0; j < coluna; j++) {
                file >> tmp;
                if (j < ntest) {
                    Luquinhas[i][j] = tmp;       
                }
            }
        }
    } 
    else { 
        cout << "Erro ao abrir o arquivo" << endl;
    }        
    file.close();

    cout << "Arquivo done." << endl << endl;

    Renatinho = Luquinhas;

    matrix_t soma(10, vector<double>(ntest, 0)); // Vetor para soma das colunas
    
    for (int e = 0; e < 10; e++) {

        System Flavinha(Wd[e], Luquinhas);
        H[e] = Flavinha.solve();
        E[e] = matrix_subtract(Renatinho, matrix_multiply(Wd[e], H[e]));
        //🤦‍♀️🤬🤡🙊🙈👀💩
        
        for (int i = 0; i < 784; i++) {
            for (int j = 0; j < ntest; j++) {
                soma[e][j] += E[e][i][j] * E[e][i][j];
            }
        }
        for (int j = 0; j < ntest; j++) {
            soma[e][j] = sqrt(soma[e][j]);
        }
    }

    erro = soma[0];
    for (int i = 1; i < 10; i++) {
        for (int j = 0; j < ntest; j++) {
            if (soma[i][j] < erro[j]){
                erro[j] = soma[i][j];
                digi[j] = i;
            }
        }
    }

    ofstream mand;
    mand.open("./mandragora.txt");

    for (int i = 0; i < ntest; i++) {
        cout << digi[i] << endl;
        mand << digi[i] << endl;
    }

    mand.close();
}

void Train::analise() {
    int certo = 0;
    vector<double> acertos(10, 0);
    vector<double> total(10, 0);
    ifstream file;

    file.open(("./dados_mnist/test_index.txt"), ios::in);
    if (!file) {
        cout << "Erro ao abrir o arquivo test_index" << endl;
        exit(-1);
    }
    
    if (file.is_open()) {
        for (int i = 0; i < 10000; i++) {
            file >> compare[i];
        }
    } 
    else { 
        cout << "Erro ao abrir o arquivo" << endl;
    }        

    file.close();

    for (int i = 0; i < ntest; i++) {
        total[compare[i]]++;
        
        if (compare[i] == digi[i]) {
            certo++;
            acertos[digi[i]]++;    
        }
    }


    cout << "Percentual de acertos: " << certo/(double)ntest << endl;

    for (int j = 0; j < 10; j++){
        cout << "Percentual de acertos do dígito " << j << ": "<< acertos[j]/total[j] * 100 << "%"<< endl;
    }

}