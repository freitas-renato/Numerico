#include "rede.h"

static int total_barras = 0;

// static vetor_t* delta_theta = (vetor_t*)NULL;
// static vetor_t* delta_v = (vetor_t*)NULL;

static vetor_t* Vnom = (vetor_t*)NULL;
static vetor_t* Pesp = (vetor_t*)NULL;
// static vetor_t* Qesp = (vetor_t*)NULL;
static vetor_t* angulos = (vetor_t*)NULL;
static vetor_t* Vesp = (vetor_t*)NULL;

static vetor_t* organiza = (vetor_t*)NULL;

// static vetor_t* incognita = (vetor_t*)NULL;

static matrix_t* G = (matrix_t*)NULL;
static matrix_t* B = (matrix_t*)NULL;

// Quantidade de barras de cada tipo: PQ, PV, SWING
static int qnt_barras[3] = {0};

vetor_t* read_rede(int n) {
    char* dados = "";
    char* dados_y = "";

    switch(n) {
        case 1:
            dados = "./Redes_V2_20180516/1_Stevenson/1_Stevenson_DadosBarras.txt";
            dados_y = "./Redes_V2_20180516/1_Stevenson/1_Stevenson_Ynodal.txt";
        break;

        case 2:
            dados = "./Redes_V2_20180516/2_Reticulada/2_Reticulada_DadosBarras.txt";
            dados_y = "./Redes_V2_20180516/2_Reticulada/2_Reticulada_Ynodal.txt";
        break;

        case 3:
            dados = "./Redes_V2_20180516/3_Distribuicao_Primaria/3_Distribuicao_Primaria_DadosBarras.txt";
            dados_y = "./Redes_V2_20180516/3_Distribuicao_Primaria/3_Distribuicao_Primaria_Ynodal.txt";
        break;

        case 4:
            dados = "./Redes_V2_20180516/4_Distribuicao_Pri_Sec/4_Distribuicao_Primaria_Secundaria_DadosBarras.txt";
            dados_y = "./Redes_V2_20180516/4_Distribuicao_Pri_Sec/4_Distribuicao_Primaria_Secundaria_Ynodal.txt";
        break;

        default:
            printf("Erro! Opção inválida\n");
            exit(-1);
    }

    // printf("%s\n", dados);
    // printf("%s\n", dados_y);

    FILE* file = fopen(dados, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(-1);
    }

    // Numero total de barras
    if(fscanf(file, "%d", &total_barras) < 1) {
        printf("Falha ao ler o arquivo\n");
        exit(-1);
    }

    
    int posicao_inicial = ftell(file); 

    int tipo, num;
    double tensao, campo4, campo5;

    // Conta quantas barras de cada tipo tem
    for (int i = 0; i < total_barras; i++) {
        if(fscanf(file, "%d %d %lf %lf %lf", &num, &tipo, &tensao, &campo4, &campo5) != 5) {
            printf("Falha ao ler dados das barras\n");
            exit(-1);
        }
        qnt_barras[tipo]++;     
    }

    printf("Barras: %d %d %d\n", qnt_barras[0], qnt_barras[1], qnt_barras[2]);

    // Inicializa vetores com o tamanho certo, dado o numero de barras
    vetor_t* incognita = new_vetor(2*qnt_barras[0] + qnt_barras[1]);
    
    Vnom = new_vetor(total_barras);   
    Vesp = new_vetor(total_barras); 
    Pesp = new_vetor(total_barras);
    // Qesp = new_vetor(total_barras);
    angulos = new_vetor(total_barras);

    organiza = new_vetor(total_barras);

    printf("Inicializou todos os vetores\n");

    // Volta para a posicao de leitura dos dados no arquivo
    fseek(file, posicao_inicial, SEEK_SET);

    // Posicoes nos vetores
    int p_pq = 0;
    int p_pv = qnt_barras[0];
    int p_sw = qnt_barras[0] + qnt_barras[1];
    int p_inc = qnt_barras[0] + qnt_barras[1];


    for (int i = 0; i < total_barras; i++) {
        if(fscanf(file, "%d %d %lf %lf %lf", &num, &tipo, &tensao, &campo4, &campo5) != 5) {
            printf("Falha ao ler dados das barras\n");
            exit(-1);
        }

        switch(tipo) {
            case 0:
                organiza->data[i] = p_pq;
                Vnom->data[p_pq] = tensao;
                Vesp->data[p_pq++] = tensao;
                incognita->data[p_inc++] = tensao;
                // p_pq++;
                break;

            case 1:
                organiza->data[i] = p_pv;
                Vnom->data[p_pv] = tensao;
                Vesp->data[p_pv] = campo5;
                Pesp->data[p_pv++] = campo4;
                // p_pv++;
                break;

            case 2:
                organiza->data[i] = p_sw;
                Vnom->data[p_sw] = tensao;
                Vesp->data[p_sw] = campo4;
                angulos->data[p_sw++] = campo5*M_PI/180;
                // p_sw++;
                break;

        }
    }

    fclose(file);

    // Arquivo de Y_nodais
    file = fopen(dados_y, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de Y\n");
        exit(-1);
    }
    int total_y = 0;
    if(fscanf(file, "%d", &total_y) < 1){
        printf("Erro ao ler o arquivo de Y\n");
        exit(-1);
    }

    G = new_matrix(total_barras, total_barras);
    B = new_matrix(total_barras, total_barras);

    int y_j, y_k = 0;
    double G_arq, B_arq = 0;
    for (int i = 0; i < total_y; i++) {
        if (fscanf(file, "%d %d %lf %lf", &y_j, &y_k, &G_arq, &B_arq) != 4) {
            printf("Erro ao ler o arquivo de Y\n");
            exit(-1);
        }

        G->data[(int)organiza->data[y_j]][(int)organiza->data[y_k]] = G_arq;
        B->data[(int)organiza->data[y_j]][(int)organiza->data[y_k]] = B_arq;
    }

    fclose(file);

    return incognita;
}

vetor_t* constroiFRede(vetor_t* x) {
    vetor_t* F = new_vetor(2*qnt_barras[0] + qnt_barras[1]);
    double soma = 0;

    // atualiza os valores de angulo e V a partir do x
    for (int i = 0; i < qnt_barras[0] + qnt_barras[1]; i++) {
        angulos->data[i] = x->data[i];
        
        if (i < qnt_barras[0])
            Vesp->data[i] = x->data[qnt_barras[0] +  qnt_barras[1] + i]; 
    }

    printf("atualizou o x\n");

    // Fp
    for (int j = 0; j < qnt_barras[0] + qnt_barras[1]; j++) {
        soma = 0;
        for (int k = 0; k < G->lin; k++) {
            if (j == k)
                continue;
            
            soma += Vesp->data[k] * (
                    G->data[j][k] * cos(angulos->data[k] - angulos->data[j]) - 
                    B->data[j][k] * sin(angulos->data[k] - angulos->data[j])
            );
        }
        
        F->data[j] = pow(Vesp->data[j], 2) * G->data[j][j] + Vesp->data[j] * soma - Pesp->data[j];
    }

    // Fq
    for (int j = 0; j < qnt_barras[0]; j++) {
        soma = 0;
        for (int k = 0; k < G->lin; k++) {
            if (j == k)
                continue;
            
            soma += Vesp->data[k] * (
                    G->data[j][k] * sin(angulos->data[k] - angulos->data[j]) +
                    B->data[j][k] * cos(angulos->data[k] - angulos->data[j])
                    
            );
        }

        F->data[j + qnt_barras[0] + qnt_barras[1]] = -pow(Vesp->data[j], 2) * B->data[j][j] - Vesp->data[j] * soma;
    }

    return F;
}

matrix_t* constroiJRede(vetor_t* x) {
    matrix_t* J = new_matrix(2*qnt_barras[0] + qnt_barras[1], 2*qnt_barras[0] + qnt_barras[1]);
    double soma;

    for(int i = 0; i < qnt_barras[0] + qnt_barras[1]; i++) {
        angulos->data[i] = x->data[i];
        
        if (i < qnt_barras[0])
            Vesp->data[i] = x->data[qnt_barras[0] +  qnt_barras[1] + i]; 
    }
    printf("VEsp = ");
    print_vetor(Vesp);
    for (int j = 0; j < qnt_barras[0] + qnt_barras[1]; j++) {
        // dFp/dtheta
        for (int k = 0; k < qnt_barras[0] + qnt_barras[1]; k++) {
            if (j == k) {
                soma = 0;
                for (int i = 0; i < G->lin; i++) {
                    if (i == j) continue;

                    soma += Vesp->data[i] * (
                        G->data[j][i] * sin(angulos->data[i] - angulos->data[j]) + 
                        B->data[j][i] * cos(angulos->data[i] - angulos->data[j])
                    );
                }

                J->data[j][k] = Vesp->data[j] * soma;
            } else {
                J->data[j][k] = -Vesp->data[j] * Vesp->data[k] * (
                    G->data[j][k] * sin(angulos->data[k] - angulos->data[j]) - 
                    B->data[j][k] * cos(angulos->data[k] - angulos->data[j])
                );
            }

        }

        // dFp/dV
        for (int k = qnt_barras[0] + qnt_barras[1]; k < J->col; k++) {
            // k == j
            if (k - qnt_barras[0] - qnt_barras[1] == j) {
                soma = 0;
                for (int i = 0; i < G->lin; i++) {
                    if (i == j) continue;

                    soma += Vesp->data[i] * (
                        G->data[j][i] * cos(angulos->data[i] - angulos->data[j]) - 
                        B->data[j][i] * sin(angulos->data[i] - angulos->data[j])
                    );
                    
                }

                J->data[j][k] = (2 * Vesp->data[j] * G->data[j][j]) + soma;
                
            } else {
                J->data[j][k] = Vesp->data[j] * (
                    G->data[j][k - qnt_barras[0] - qnt_barras[1]] * cos(angulos->data[k - qnt_barras[0] - qnt_barras[1]] - angulos->data[j]) -
                    B->data[j][k - qnt_barras[0] - qnt_barras[1]] * sin(angulos->data[k - qnt_barras[0] - qnt_barras[1]] - angulos->data[j])
                );
                
            }
        }
    }

    for (int j = 0; j < qnt_barras[0]; j++) {
        // dFq/dthetha
        for (int k = 0; k < qnt_barras[0] + qnt_barras[1]; k++) {
            if (j == k) {
                soma = 0;
                for (int i = 0; i < G->lin; i++) {
                    if (i == j) continue;

                    soma += Vesp->data[i] * (
                        G->data[j][i] * cos(angulos->data[i] - angulos->data[j]) -
                        B->data[j][i] * sin(angulos->data[i] - angulos->data[j])
                    );
                }

                J->data[j + qnt_barras[0] + qnt_barras[1]][k] = Vesp->data[j] * soma;
            } else {
                J->data[j + qnt_barras[0] + qnt_barras[1]][k] = -Vesp->data[j] * Vesp->data[k] * (
                    G->data[j][k] * cos(angulos->data[k] - angulos->data[j]) - 
                    B->data[j][k] * sin(angulos->data[k] - angulos->data[j])
                );
            }
        }

        // dFq/dV
        for (int k = qnt_barras[0] + qnt_barras[1]; k < J->col; k++) {
            if (k - qnt_barras[0] - qnt_barras[1] == j) {
                soma = 0;
                for (int i = 0; i < G->lin; i++) {
                    if(i == j) continue;

                    soma += Vesp->data[i] * (
                        G->data[j][i] * sin(angulos->data[i] - angulos->data[j]) + 
                        B->data[j][i] * cos(angulos->data[i] - angulos->data[j])   
                    );
                }

                J->data[j + qnt_barras[0] + qnt_barras[1]][k] = -2 * Vesp->data[j] * B->data[j][j] - soma;

            } else {
                J->data[j + qnt_barras[0] + qnt_barras[1]][k] = -Vesp->data[j] * (
                    G->data[j][k - qnt_barras[0] - qnt_barras[1]] * sin(angulos->data[k - qnt_barras[0] - qnt_barras[1]] - angulos->data[j]) +
                    B->data[j][k - qnt_barras[0] - qnt_barras[1]] * cos(angulos->data[k - qnt_barras[0] - qnt_barras[1]] - angulos->data[j])
                );
            }
        }
    }

    return J;
}

vetor_t* newton_rede(int n) {
    vetor_t* x = (vetor_t*)NULL;

    matrix_t* J = (matrix_t*)NULL;
    vetor_t* c = (vetor_t*)NULL;
    vetor_t* F = (vetor_t*)NULL;

    matrix_t* lu = (matrix_t*)NULL;
    vetor_t* p = (vetor_t*)NULL;

    int iteracoes = 0;
    x = read_rede(n);
    p = new_vetor(x->tam);

    printf("X0: ");
    print_vetor(x);
    c = new_vetor(x->tam);
    for(int i = 0; i < 100; i++) {
        F = constroiFRede(x);
        printf("Vetor F: ");
        print_vetor(F);
        
        J = constroiJRede(x);
        printf("Construiu J\n");
        print_matrix(J);
        
        // F => -F
        mult_vetor_numero(F, -1);

        // LU a partir de J
        lu = lu_decomposition(J, p);
        // Resolve em c usando a matrix LU: J*c = -F
        c = solve(lu, c, F, p);
        printf("Vetor C: ");
        print_vetor(c);
        
        // x = x + c
        x = soma_vetores(x, c);
        printf("X: ");
        print_vetor(x);
        
        iteracoes++;
        printf("Iteracoes: %d\n", iteracoes);

        free_vetor(F);
        free_matrix(J);
        free_matrix(lu);
        // Erro em 1e-2
        if (mod_vetor(c) < 1e-3) {
            free_vetor(c);
            free_vetor(p);
            free_matrix(lu);
            free_matrix(J);
            free_vetor(F);
            printf("Iteracoes: %d\n", iteracoes);
            return x;
        }
        // free_vetor(c);
    }

    return x;
}
