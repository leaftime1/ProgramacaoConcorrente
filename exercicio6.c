#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define TAMANHO 100

double *gerar_vetor(int n);
int *gerar_vetor_inteiro(int n);
void mostrar_vetor_inteiro(int *v,int tamanho);
void mostrar_vetor(double *v,int tamanho);

int main() {
    /*
    INICIO
    */
    int contador = 0;
    int x = 77;
    time_t t;
    srand(time(NULL));
    double inicioSeq = omp_get_wtime();
    int *vetor = NULL;
    vetor = gerar_vetor_inteiro(TAMANHO);
    for(int i=0;i<TAMANHO;i++){
        if(vetor[i]==x){
            contador++;
        }
    }
    printf("Numero de vezes em que 77 aparece: %d \n", contador);
    double fimSeq = omp_get_wtime();
    printf("Tempo sequencial: %f \n", fimSeq -inicioSeq);

    /*Paralelo
    */
    contador = 0;
    double inicioP = omp_get_wtime();

    #pragma omp parallel num_threads(3)
    {
        int cont = 0;
        #pragma omp for
            for(int i=0;i<TAMANHO;i++){
                if(vetor[i]==x){
                    cont += 1;
                }
            }
        #pragma omp critical
            contador += cont;
    }
    double fimP = omp_get_wtime();
    printf("Numero de vezes em que 77 aparece: %d \n", contador);
    printf("Tempo paralelo: %f \n", fimP - inicioP);

    float speedup = ((fimP - inicioP) - (fimSeq - inicioSeq));
    printf("Speedup: %f \n", speedup);
    printf("Eficiencia: %f \n", speedup/3);
    /*
    FIM
    */
    return 0;
}

double *gerar_vetor(int n) {
    double *vetor;
    int i;
    vetor = (double *)malloc(sizeof(double) * n);
    for (i=0;i<n;i++) {
        double num = (rand() / (float)RAND_MAX);
        vetor[i] = num;
    }
    return vetor;
}

int *gerar_vetor_inteiro(int n) {
    int *vetor;
    int i;
    vetor = (int *)malloc(sizeof(int) * n);
    for (i=0;i<n;i++) {
        int num = (rand() % MAX);
        vetor[i] = num;
    }
    return vetor;
}

void mostrar_vetor(double *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%.5f]",v[i]);
    }
    printf("\n");
}

void mostrar_vetor_inteiro(int *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%d]",v[i]);
    }
    printf("\n");
}