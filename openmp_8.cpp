#include <iostream>
#include <vector>
#include <omp.h>
#include <ctime>

void check_vectors(std::vector<int> v1, std::vector<int> v2);
void show_array(int** arr, size_t n, size_t m);
void show_vector(std::vector<int> v)
{
    for (int i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
    printf("\n");
}
double count_wtime(double start, double end)
{
    return end - start;
}

int main()
{
    setlocale(LC_ALL, "utf-8");
    srand(std::time(NULL));

    int rows, columns;
    double startTime, startTime2, endTime, endTime2;
    double wtime1, wtime2;

    printf("Введите количество строк: ");
    std::cin >> rows;
    printf("Введите количество столбцов: ");
    std::cin >> columns;
    printf("\n");

    std::vector<int> v(columns, 0);
    std::vector<int> vRes(columns, 0);
    std::vector<int> vRes_2(columns, 0);
    
    // Создаём матирцу
    int **matrix = new int* [rows];
    for (int i = 0; i < rows; i++)
        matrix[i] = new int[columns];

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
            matrix[i][j] = rand() % 10 + 1;
    }
    
    //printf("Изначальная матрица:\n");
    //show_array(matrix, rows, columns);
    
    // Создаём главный вектор
    for (int i = 0; i < v.size(); i++)
        v[i] = rand() % 10 + 1;
    
    //printf("initial vector:\n");
    //show_vector(v);

    // Умножаем матрицу на вектор (последовательно)
    startTime = omp_get_wtime();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
            vRes[i] += matrix[i][j] * v[j];
    }
    endTime = omp_get_wtime();

    // Умножаем матрицу на вектор (параллельно)
    startTime2 = omp_get_wtime();
    #pragma omp parallel for shared(rows, columns) num_threads(2) schedule (dynamic, 1)
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
            vRes_2[i] += matrix[i][j] * v[j];
    }
    endTime2 = omp_get_wtime();

    // Вывод результатов
    printf("Результирующий вектор последовательных вычислений:\n");
    show_vector(vRes);
    printf("Результирующий вектор параллельных вычислений:\n");
    show_vector(vRes);
    check_vectors(vRes, vRes_2);
    printf("\n");

    // Сравниваем работу времени последовательной и параллельной частей
    wtime1 = count_wtime(startTime, endTime);
    wtime2 = count_wtime(startTime2, endTime2);
    printf("Последовательное время работы: %f\n", wtime1);
    printf("Параллельное время работы: %f\n", wtime2);
    
    if (wtime1 > wtime2) printf("Параллельные вычисления быстрее!\n");
    else if (wtime1 < wtime2) printf("Последовательные вычисления быстрее!\n");
    else printf("Одинаковое время обоих способов вычисления!\n");

    // Удаляем матрицу
    for (int i = 0; i < rows; i++)
        delete[] matrix[i];

    return 0;
}

void check_vectors(std::vector<int> v1, std::vector<int> v2)
{
    for (int i = 0; i < v1.size(); i++)
    {
        if (v1[i] != v2[i])
        {
            printf("Результаты вычислений разные!\n");
            return;
        }
    }
    printf("Результаты вычислений одинаковые.\n");
}

void show_array(int** arr, size_t n, size_t m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            std::cout << arr[i][j] << "\t";
        printf("\n");
    }
    printf("\n");
}

