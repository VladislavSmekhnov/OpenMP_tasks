#include <iostream>
#include <omp.h>
#include <ctime>

void show_array(int* arr, std::size_t size);

int main()
{
    setlocale(LC_ALL, "utf-8");
    srand(std::time(NULL));

    int size;
    int max_7 = INT_MIN; // максимальное числовое значение элемента массива, кратного 7-ми
    std::cout << "Укажите размер массива: ";
    std::cin >> size;
    int* a = new int[size];
    // Заполняем массив числами в диапазоне [1;150]
    for (int i = 0; i < size; i++)
        a[i] = rand() % 150 + 1;
    
    show_array(a, size);
    #pragma omp parallel for shared(max_7, size) num_threads(2) schedule(dynamic, 1)
    for (int i = 0; i < size; i++)
    {
        if (a[i] % 7 == 0)
        {
            #pragma omp critical
                if (a[i] > max_7) max_7 = a[i];
        }
    }
    printf("Максимальное числовое значение элемента массива, кратного 7-ми = %d\n", max_7);

    return 0;
}

void show_array(int *arr, std::size_t size)
{
    printf("\nМассив:\n");
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << " ";

    printf("\n\n");
}
