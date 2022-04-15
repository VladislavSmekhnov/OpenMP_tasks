#include <iostream>
#include <omp.h>
#include <ctime>

void show_array(int* arr);

int main()
{
    setlocale(LC_ALL, "utf-8");
    srand(std::time(NULL));

    int a[30];
    int counter = 0;
    // Заполнили массив числами из диапазона [1;100]
    for (int i = 0; i < 30; i++)
        a[i] = rand() % 100 + 1;

    show_array(a);
    #pragma omp parallel for shared(counter) num_threads(2) schedule(dynamic, 1)
    for (int i = 0; i < 30; i++)
    {
        if (a[i] % 9 == 0)
        {
            #pragma omp atomic
            counter++;
        }
    }
    printf("Количество чисел, кратных 9-ти: %d\n", counter);

    return 0;
}

void show_array(int* arr)
{
    unsigned int size = 30; // 30 - для конкретного случая

    for (int i = 0; i < size; i++)
        std::cout << arr[i] << " ";

    printf("\n");
}
