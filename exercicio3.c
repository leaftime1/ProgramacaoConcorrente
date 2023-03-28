#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

#define MAX 500000000
float *gerar_vetor(int n);

int main(){
    int i;
    double soma;
    double medi;
    time_t t;
    srand(time(NULL));
    double inicio = omp_get_wtime();
    float *vetor = (float*)malloc(MAX*sizeof(float));
    vetor = gerar_vetor(MAX);

    #pragma omp parallel num_threads(4)
    {
        #pragma omp for
        for(i = 0; i<MAX; i++){
            soma += vetor[i];
        }
    }
    medi = soma/MAX;
    double fim = omp_get_wtime();
    double t_serial = fim - inicio;
    printf("Media: %f \n", medi);
    printf("Execucao serial: %f \n", t_serial);
    
    return 0;   
}

float *gerar_vetor(int n){
    float *vetor;
    int i;
    vetor = (float *)malloc(sizeof(float) * n);
    for(i=0;i<n;i++){
        float num = (rand()%100000);
        vetor[i] = num;
    }
    return vetor;
}