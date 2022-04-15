#include <iostream>
#include <omp.h>

int main()
{
    setlocale(LC_ALL, "utf-8");

    omp_set_num_threads(3);
#pragma omp parallel if (omp_get_max_threads() > 1)
    {
        printf("Номер нити: %d, кол-во нитей: %d\n", omp_get_thread_num(), omp_get_num_threads());
    }

    omp_set_num_threads(1);
#pragma omp parallel if (omp_get_max_threads() > 1)
    {
        printf("Номер нити: %d, кол-во нитей: %d\n", omp_get_thread_num(), omp_get_num_threads());
    }

    return 0;
}
