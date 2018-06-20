#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <complex.h>

void main(void){
// int j;
// int k;
// double complex fun [] =  {5,-1,3,1};
// int dois_n = sizeof (fun)/sizeof(fun[0]);
// printf("%d\n", dois_n);
// double complex c[dois_n];
// double complex aux1;

// //DIRETA
//     for(k=0; k<=dois_n-1; k++){
//         c[k] = 0;
//         for(j=0; j<=dois_n-1; j++){
//             aux1 = fun[j]*cpow((M_E),(I*(-k)*(j*M_PI*2/dois_n)));
//             c[k] = c[k] + aux1; 
//         }
//     c[k] = c[k]/(dois_n); 
//     printf("%.2f %.2fi \n", creal(c[k]), cimag(c[k]));
//     }
  
// }

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


double complex c[] =  {2,0.5+0.5*I,2,0.5-0.5*I};
int n = sizeof (c)/sizeof(c[0]);
double complex f[n];
bool dir = true ; 

fftrec (c, f, n, dir);

printf("%.2f %.2fi \n %.2f %.2fi \n  %.2f %.2fi \n  %.2f %.2fi \n ", creal(f[0]),cimag(f[0]),creal(f[1]),cimag(f[1]),creal(f[2]),cimag(f[02),creal(f[3]),cimag(f[3]));

int fftrec (double complex c, double complex f ,int n ,bool dir){

    int j;
    int p = n/2;
    double complex even[p];
    double complex odd[p];
    double complex eij;
    double complex fe[p];
    double complex fo[p];

    if (n == 1) {
        c[0] = f[0] + f[1];
        c[1] = f[0] - f[1];
    }

    else
    {
        for (j==0; j<=n-1; j++){
            fe[j] = f[2j]; 
            fo[j] = f[2j+1];
        }
        fftrec(even,fe,p,dir)
        fftrec(odd,fo,p,dir)

        for (j==0; j<=n-1; j++){
            if(dir == true)
                eij = pow((M_E),(-I*j*M_PI/n)
            else
                eij = pow((M_E),(I*j*M_PI/n)
            c[j] = even[j] + eij*odd[j]
            c[j+n] = even[j] - eij*odd[j]
            if (dir == true){
                c[j] = c[j]/n;
                c[j+n] = c[j+n]/n;
            }
        }
    }

}

