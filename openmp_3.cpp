#include <iostream>
#include <omp.h>

int main()
{
    setlocale(LC_ALL, "utf-8");
    
    int a, b;
    
    a = 1;
    b = 3;

    printf("Значения до входа в 1-ую параллельную область: a = %d, b = %d\n", a, b);

#pragma omp parallel private(a) firstprivate(b) num_threads(2)
    {
        a = 2;
        
        a += omp_get_thread_num();
        b += omp_get_thread_num();
        printf("В 1-ой параллельной области: a = %d, b = %d\n", a, b);
    }
    printf("После выхода из 1-ой параллельной области: a = %d, b = %d\n\n", a, b);

    printf("Значения до входа во 2-ую параллельную область: a = %d, b = %d\n", a, b);
#pragma omp parallel shared(a) private(b) num_threads(4)
    {
        b = 1;

        a -= omp_get_thread_num();
        b -= omp_get_thread_num();
        printf("Во 2-ой параллельной области: a = %d, b = %d\n", a, b);
    }
    printf("После выхода из 2-ой параллельной области: a = %d, b = %d\n", a, b);

    return 0;
}
