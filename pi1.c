#include <stdio.h>
#include <omp.h>

int main() {

    const int n = 2000000000;

    double area = 0.0;
    double x;
    int i;
    double temp = 0.0;
    double elt = omp_get_wtime();
   
    #pragma omp parallel for reduction(+:area)
    for (i = 0; i < n; i++) {
        x = (i + 0.5) / n; /* one add, one divide */
        area += 4.0 / (1.0 + x * x); /* two adds, one multiply, one divide */ 
        temp = 4.0 / (1.0 + x * x); /*one add, one multiply, one divide*/
        #pragma omp critical
        {
            area += temp; /* one add */
        }
    }
    double pi_est = area / n;
    elt = omp_get_wtime() - elt;

    printf("Estimate of pi: %.10lf\n", pi_est);
    printf("Time taken: %.3lf seconds\n", elt);
    printf("Performance rate: %.3lf GFLOPS\n", (6.0 * n * 1e-9)/elt);

    return 0;
}
