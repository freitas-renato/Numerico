#include <stdio.h>
#include <string.h>

#include "fft.h"
#include "testes_iniciais.h"
#include "vetor.h"

int main(void) {
    char* dados[256];
    char* arquivo[256];
    int opcao;
    vetor_t* vet_f;
    vetor_t* vet_c;

    printf("Arquivos devem estar na pasta 'dados_sons'\n");
    printf("Digite o nome do arquivo .dat a ser analisado: ");
    scanf("%s", dados);
    
    strcpy(arquivo, "./dados_sons/");
    strcat(arquivo, dados);

    // printf("\n%s", arquivo);
    // printf("\n%s\n", dados);


    printf("Transformada a ser realizada: \n  0) Fourier Lenta \n  1) FFT recursiva \n  2) FFTPACK4\n");
    scanf("%d", &opcao);

    vet_f = read_file(arquivo);
    vet_c = new_vetor(vet_f->tam);

    vetor_t* vet_blabla = new_vetor(vet_c->tam);

    switch (opcao) {
        case 0:
            printf("Arquivo %s aberto, fazer a transformada lenta\n", arquivo);
            
            printf("Tempo de execucao: %lf segundos\n", fft(vet_c, vet_f, vet_c->tam, 1));
            write_to_file("./out/saida_coef.txt", vet_c);
            
            printf("Tempo de execucao: %lf segundos\n", fft(vet_c, vet_f, vet_c->tam, 0));
            write_to_file("./out/saida_func.txt", vet_f);

            printf("Arquivos de saida gerados.\n");
        break;
        
        case 1:
            printf("Arquivo %s aberto, fazer FFT recursiva\n", arquivo);
            
            printf("Tempo de execucao: %lf segundos\n", fftrec(vet_c, vet_f, vet_c->tam/2, 1));
            write_to_file("./out/saida_coef.txt", vet_c);
            
            printf("Tempo de execucao: %lf segundos\n", fftrec(vet_blabla, vet_c, vet_c->tam/2, 0));
            write_to_file("./out/saida_func.txt", vet_blabla);

            printf("Arquivos de saida gerados.\n");
        break;
        
        case 2:
            printf("abrir arquivo %s e fazer a FFTPACK4\n", arquivo);
        break;

        case 3:
            teste2();
        break;

        default:
            printf("opcao invalida \n");
        break;
    }

    // teste2();
    return 0;
}
