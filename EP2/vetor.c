#include "vetor.h"

vetor_t* new_vetor(int a) {
    vetor_t* new_vet;

    if (a <= 0) {
        printf("Vetor tem que ter tamanho positivo\n");
        exit(-1);
    }

    if ((new_vet = (vetor_t*)calloc((size_t)1, sizeof(vetor_t))) == (vetor_t*)NULL) {
        printf("Erro na alocacao do vetor\n");
        exit(-1);
    }

    new_vet->tam = a;


    if ((new_vet->data = (double complex*)calloc(new_vet->tam, sizeof(double complex))) == (double complex*)NULL) {
        free(new_vet);
        printf("Erro ao alocar vetor\n");
        exit(-1);
    }

    return new_vet;
}

// void print_vetor(vetor_t* vetor) {
//     for (int i = 0; i < vetor->tam; i++) {
//         printf("%10.5e ", vetor->data[i]);
//     }
//     printf("\n\n");
// }

void print_vetor(vetor_t* vetor) {
    printf("vetor: \n");
    for (int i = 0; i < vetor->tam; i++) {
        printf("%8.2f %8.2fi\n", creal(vetor->data[i]), cimag(vetor->data[i]));
    }
    printf ("\n\n");
}

vetor_t* mult_vetor_vetor(vetor_t* A, vetor_t* B) {
    vetor_t* result = new_vetor(A->tam);
    
    if (A->tam != B->tam) {
        printf("Vetores precisam ter o mesmo tamanho\n");
        exit(-1);
    }

    for (int i = 0; i < A->tam; i++) {
        result->data[i] = A->data[i] * B->data[i];
    }

    return result;
}

void mult_vetor_numero(vetor_t* A, double num) {
    for (int i = 0; i < A->tam; i++) {
        A->data[i] *= num;
    }
}

vetor_t* soma_vetores(vetor_t* A, vetor_t* B) {
    if (A->tam != B->tam) {
        printf("Vetores precisam ter o mesmo tamanho\n");
        exit(-1);
    }
    
    vetor_t* result = new_vetor(A->tam);

    for (int i = 0; i < result->tam; i++) {
        result->data[i] = A->data[i] + B->data[i]; 
    }

    return result;
}

double mod_vetor(vetor_t* A) {
    double sum = 0;

    for (int i = 0; i < A->tam; i++) {
        sum += A->data[i] * A->data[i];
    }

    return sqrt(sum);
}

void free_vetor(vetor_t* vet) {
    vet->tam = 0;
    free(vet->data);
    free(vet);
    vet = (vetor_t*)NULL;
}

vetor_t* read_file(char* nome) {
    vetor_t* vetor;
    double total_dados = 0;
    double numero;
    double real, imag;
    
    FILE* arquivo = fopen(nome, "r");
    int file_position = 0;

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo \n");
        exit(-1);
    }

    /*
      Ignora as duas primeiras linhas do arquivo:
        Sample rate e channels
    */
    char ignore[100];
    for (int i = 0; i < 2; i++) {
        fgets(ignore, 100, arquivo);
    }

    file_position = ftell(arquivo);
    while (fscanf(arquivo, "%lf", &numero) > 0) {
        total_dados++;
    }

    vetor = new_vetor(total_dados/2);

    fseek(arquivo, file_position, SEEK_SET);
    for (int i = 0; i < vetor->tam; i++) {
        fscanf(arquivo, "%lf %lf", &real, &imag);
        vetor->data[i] = real + imag*I;
    }

    printf("Total de dados no arquivo: %.1lf\n", total_dados/2 + 2);
    fclose(arquivo);

    return vetor;
}

void write_to_file(char* nome, vetor_t* vetor) {
    FILE* arquivo = fopen(nome, "w");

    for (int i = 0; i < vetor->tam; i++) {
        fprintf(arquivo, "%10.8e \t\t %10.8e\n", creal(vetor->data[i]), cimag(vetor->data[i]));
    }

    fclose(arquivo);
}
