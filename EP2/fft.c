#include <math.h>
#include <complex.h>
#include "fft.h"

void fft(vetor_t* c, vetor_t* f, int dois_n, int dir) {
    int j, k = 0;
    double complex aux = 0;
    
    switch(dir){
        case 0:
            // DIRETA
            for(k = 0; k <= dois_n - 1; k++){
                c->data[k] = 0;

                for(j = 0; j <= dois_n - 1; j++){
                    aux = f->data[j] * cpow(M_E, (I*(-k)*(j*M_PI*2/dois_n)));
                    c->data[k] = c->data[k] + aux; 
                }

                c->data[k] = c->data[k]/(dois_n); 
                printf("%.2f %.2fi \n", creal(c->data[k]), cimag(c->data[k]));
            }
        break;

        case 1:
            // INVERSA
            for(j = 0; j <= dois_n - 1; j++){
                f->data[j] = 0;
                
                for(k = 0; k <= dois_n - 1; k++){
                    aux = c->data[k] * cpow((M_E), (I*k*(j*M_PI*2/dois_n)));
                    f->data[j] = f->data[j] + aux; 
                } 
                
                printf("%.2f %.2fi \n", creal(f->data[j]), cimag(f->data[j]));

            }
        break;

        default:
            printf("Direção da FFT invalida.\n");
            exit(-1);
        break;
    }
 
}

void fftrec(vetor_t* c, vetor_t* f, int n, int dir) {
    // int p = n / 2;
    vetor_t* even = new_vetor(n);
    vetor_t* odd = new_vetor(n);
    vetor_t* fe = new_vetor(n);
    vetor_t* fo = new_vetor(n);

    double complex eij;

    if (n == 1) {
        c->data[0] = f->data[0] + f->data[1];
        c->data[1] = f->data[0] + f->data[1];
    } else {
        for (int j = 0; j < n; j++) {
            fe->data[j]  = f->data[2*j];
            fo ->data[j] = f->data[2*j + 1];
        }

        fftrec(even, fe, n/2, dir);
        fftrec(odd, fo, n/2, dir);

        for (int j = 0; j < n; j++) {
            if (dir) 
                eij = cpow(M_E, -I * j * M_PI/n);
            else 
                eij = cpow(M_E, I * j * M_PI/n);
            
            c->data[j] = even->data[j] + eij * odd->data[j];
            c->data[j+n] = even->data[j] - eij * odd->data[j];

            c->data[j] /= 2*n;
            c->data[j+n] /= 2*n;
        }
    }
}

  


// INVERSA
// int j;
// int k;
// double complex c[] =  {2,0.5+0.5*I,2,0.5-0.5*I};
// int dois_n = sizeof (c)/sizeof(c[0]);
// printf("%d\n", dois_n);
// double complex fun[dois_n];
// double complex aux2;

//     for(j=0; j<=dois_n-1; j++){
//         fun[k] = 0;
//         for(k=0; k<=dois_n-1; k++){
//             aux2 = c[k]*cpow((M_E),(I*k*(j*M_PI*2/dois_n)));
//             fun[j] = fun[j] + aux2; 
//         } 
//     printf("%.2f %.2fi \n", creal(fun[j]), cimag(fun[j]));
//     }
// }
// }












