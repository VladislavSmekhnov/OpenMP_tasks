#include <iostream>
#include <omp.h>
#include <ctime>

void fill_array(int *arr, size_t amount)
{
	for (int i = 0; i < amount; i++)
		arr[i] = (rand() % 100) + 1;
}

void show_array(int* arr, size_t amount)
{
	for (int i = 0; i < amount; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int main()
{
	setlocale(LC_ALL, "utf-8");
	std::srand(std::time(NULL));
	int n = 10;
	int max = INT_MIN;
	int min = INT_MAX;
	int* a = new int[n];
	int* b = new int[n];

	fill_array(a, n);
	fill_array(b, n);
	
	printf("Массив \'a\':\n");
	show_array(a, n);
	printf("Массив \'b\':\n");
	show_array(b, n);

	omp_set_num_threads(2);
#pragma omp parallel
	{
		int threadNum;
		threadNum = omp_get_thread_num();
		#pragma omp master
		{
			printf("\nНомер нити: %d\nИщем минимум", threadNum);
			for (int i = 0; i < n; i++)
				if (a[i] < min) min = a[i];
		}
		#pragma omp barrier
		#pragma omp single
		{
			printf("\nНомер нити: %d\n\n", threadNum);
			for (int i = 0; i < n; i++)
				if (b[i] > max) max = b[i];
		}
	}
	printf("min in \'a\' array = %d\nmax in \'b\' array = %d", min, max);

	delete[] a;
	delete[] b;
	return 0;
}
