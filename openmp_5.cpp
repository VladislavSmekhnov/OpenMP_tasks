#include <iostream>
#include <omp.h>

#define ROWS 6
#define COLUMNS 8

int d[ROWS][COLUMNS];

void fill_array()
{ // Заполняем массив случайными числами
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
            d[i][j] = (rand() % 100) + 1;
    }
}

void show_array()
{ // Печать массива
    printf("Исходный массив:\n");
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
            printf("%d\t", d[i][j]);

        printf("\n");
    }
    printf("\n");
}

int main()
{
    setlocale(LC_ALL, "utf-8");
    srand(std::time(NULL));
    float arithmMean;
    int amount = ROWS * COLUMNS; // кол-во элементов в массиве
    int min;
    int max;
    int count_div_3;

    arithmMean = 0;
    min = INT_MAX;
    max = INT_MIN;
    count_div_3 = 0;

    fill_array();
    //show_array();

    omp_set_num_threads(5);
    #pragma omp parallel sections shared(arithmMean)
    {
        #pragma omp section
        { // Среднее арифметическое значение элементов двумерного массива
            for (int i = 0; i < ROWS; i++)
            {
                for (int j = 0; j < COLUMNS; j++)
                    arithmMean += d[i][j];
            }
            arithmMean /= amount;
            printf("Среднее арифметическое: %.2f, номер исполняющей нити: %d\n", arithmMean, omp_get_thread_num());
        }
        #pragma omp section
        { // max, min значений элементов двумерного массива
            for (int i = 0; i < ROWS; i++)
            {
                for (int j = 0; j < COLUMNS; j++)
                {
                    if (d[i][j] > max) max = d[i][j];
                    if (d[i][j] < min) min = d[i][j];
                }
            }
            printf("max = %d, min = %d, номер исполняющей нити: %d\n", max, min, omp_get_thread_num());
        }
        #pragma omp section
        { // Вычисление кол-ва элементов массива, числовые значения которых кратны 3
            for (int i = 0; i < ROWS; i++)
            {
                for (int j = 0; j < COLUMNS; j++)
                    if (d[i][j] % 3 == 0) count_div_3++;
            }
            printf("Кол-во элементов, кратных 3: %d, номер исполняющей нити: %d\n", count_div_3, omp_get_thread_num());
        }
    }

    return 0;
}
