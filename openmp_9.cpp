#include <iostream>
#include <omp.h>
#include <ctime>

#define ROWS 6
#define COLUMNS 8

void show_arr(int(&arr)[ROWS][COLUMNS]);
void fill_arr(int(&arr)[ROWS][COLUMNS]);

int main()
{
    setlocale(LC_ALL, "utf-8");
    srand(std::time(NULL));

    int d[ROWS][COLUMNS];
    int max, min;
    
    max = INT_MIN;
    min = INT_MAX;
    fill_arr(d);
    //show_arr(d);
    #pragma omp parallel for num_threads(2) schedule(dynamic, 1)
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            if (d[i][j] > max)
            {
            #pragma omp critical
                max = d[i][j];
            }
            if (d[i][j] < min)
            {
            #pragma omp critical
                min = d[i][j];
            }
        }
    }

    printf("max = %d, min = %d\n", max, min);

    return 0;
}

void show_arr(int(&arr)[ROWS][COLUMNS])
{
    printf("Массив:\n");
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
            std::cout << arr[i][j] << " ";

        printf("\n");
    }
    printf("\n");
}

void fill_arr(int(&arr)[ROWS][COLUMNS])
{ // Генерируем числа в диапазоне [12;100]
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
            arr[i][j] = rand() % 89 + 12;
    }
}
