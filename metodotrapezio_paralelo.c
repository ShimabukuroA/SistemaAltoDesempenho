#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>
#include "mede_time.h"
#define NTHREADS 4


double f(double x);
double f(double x)
{
  return 1.0 / exp(x);
} 


double g(double x){

}

double h(double x){

}

int main(){
    int n; //numero de particoes
    int i;
    double a, b; //intervalo de integracao
    double x; //valor de x onde a funcao e calculada
    double delta; //tamanho de cada particao
    double sum  = 0; //soma da integral
    printf("Digite o número de particoes\n");
    fflush(stdout);
    scanf("%d", &n);
    printf("Digite o limite inferior\n");
    fflush(stdout);
    scanf("%lf", &a);
    printf("Digite o limite superior\n");
    fflush(stdout);
    scanf("%lf", &b);
    delta = (b-a)/(n-1);
    x=a;

    TIMER_CLEAR;  
    TIMER_START;

    #pragma omp parallel for num_threads(NTHREADS) shared(a, delta, n) private(i, x) reduction(+: sum)
    for(int i = 0 ; i < n-1; i++){
      x = a + i*delta;
      sum += f(x) + f(x + delta);
    }
    sum = sum * delta/2;
    TIMER_STOP;
    printf ("\nTEMPO EXECUCAO: %12.7f\n",TIMER_ELAPSED );
    printf("O resultado da integral e: %lf\n", sum);

    return 0;
}

   
