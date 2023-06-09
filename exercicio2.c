#include <stdio.h>
#include <omp.h>


int main(){
    static long num_steps = 100000000;
    double step;
    int i; double x, pi, sum = 0.0;
    int t = omp_get_num_threads();
    double inicio = omp_get_wtime();
    step = 1.0/(double) num_steps;
    for(i=0; i<num_steps;i++){
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x*x);
    }

    pi = step * sum;
    double fim = omp_get_wtime();
    printf("pi: %.5f \n", pi);
    printf("Seq: %f\n", fim-inicio);

    inicio = omp_get_wtime();
    sum = 0;

    #pragma omp parallel private(x) num_threads(3)
    {
        #pragma omp for reduction (+ : sum)
        for(i = 0;i<num_steps;i++){
            x = (i + 0.5) * step;
            sum = sum + 4.0/(1.0 + x*x);           
        }
    }
    pi = step*sum;
    fim = omp_get_wtime();
    printf("pi: %.5f \n", pi);
    printf("Seq: %f\n", fim-inicio);

    return 0;
}