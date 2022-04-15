#include <iostream>
#include <omp.h>

int main()
{
    setlocale(LC_ALL, "utf-8");
    omp_set_num_threads(8);

#pragma omp parallel
    {
        int threadIndex = omp_get_thread_num();
        int threadsAmount = omp_get_num_threads();
        printf("Идентификатор: %i, количество потоков всего: %i\n", threadIndex, threadsAmount);
        printf("Hello World!\n");
    }

    return 0;
}

// Ответы на вопросы:

/* Нет. Конструкции синхронизации и библиотечные подпрограммы позволяют согласовывать выполнение
нитей и доступ к данным в параллельных областях. Отметьте, что нет гарантий синхронного
доступа к файлам при выполнении ввода/вывода из разных нитей, поэтому синхронизация в этом
случае возлагается на программиста. */
