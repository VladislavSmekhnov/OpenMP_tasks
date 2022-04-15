#include <iostream>
#include <omp.h>
#include <ctime>

#define SIZE 12

int a[SIZE], b[SIZE], c[SIZE];

void show_array(int arr[])
{
    for (int i = 0; i < SIZE; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    setlocale(LC_ALL, "utf-8");
    srand(std::time(NULL));

    #pragma omp parallel for num_threads(3) schedule (static, 2)
    for (int i = 0; i < SIZE; i++)
    {
        a[i] = rand() % 10 + 1;
        b[i] = rand() % 10 + 1;

        printf("number of threads: %d, thread number: %d, номер итерации: %d\n", omp_get_num_threads(), omp_get_thread_num(), i);
    }

    printf("\n");
    printf("Результат, массив \'a\':\n");
    show_array(a);
    printf("Результат, массив \'b\':\n");
    show_array(b);
    printf("\n");

#pragma omp parallel for num_threads(4) schedule (dynamic, 3)
    for (int i = 0; i < SIZE; i++)
    {
        c[i] = a[i] + b[i];

        printf("number of threads: %d, thread number: %d, номер итерации: %d\n", omp_get_num_threads(), omp_get_thread_num(), i);
    }

    printf("\n");
    printf("Результат, массив \'c\':\n");
    show_array(c);

    return 0;
}
