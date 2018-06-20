#include "fft.h"

double complex fftrec(double complex c, double complex f, int n, int dir) {
    // //DIRETA
    for(k=0; k<=dois_n-1; k++){
        c[k] = 0;
        for(j=0; j<=dois_n-1; j++){
            aux1 = fun[j]*cpow((M_E),(I*(-k)*(j*M_PI*2/dois_n)));
            c[k] = c[k] + aux1; 
        }
    c[k] = c[k]/(dois_n); 
    printf("%.2f %.2fi \n", creal(c[k]), cimag(c[k]));
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
}












