#include <iostream>
#include <ctime>
#include <omp.h>

#define SIZE 10

int a[SIZE], b[SIZE];

void fill_arrays()
{
	for (int i = 0; i < SIZE; i++)
	{
		a[i] = (rand() % 10) + 1;
		b[i] = (rand() % 10) + 1;
	}
}

int main()
{
	setlocale(LC_ALL, "utf-8");
	srand(std::time(NULL));
    
	float arithmMean_a, arithmMean_b;
	
	arithmMean_a = arithmMean_b = 0;
	fill_arrays();

#pragma omp parallel for reduction(+: arithmMean_a) reduction(+: arithmMean_b)
	for (int i = 0; i < SIZE; i++)
	{
		arithmMean_a += a[i];
		arithmMean_b += b[i];
	}
	arithmMean_a /= SIZE;
	arithmMean_b /= SIZE;

	printf("Среднее арифметическое массива \'a\' = %.2f ", arithmMean_a);
	if (arithmMean_a > arithmMean_b)
		printf("> среднего арифметического массива \'b\' = %.2f\n", arithmMean_b);
	else if (arithmMean_a < arithmMean_b)
		printf("< среднего арифметического массива \'b\' = %.2f\n", arithmMean_b);
	else printf("равняется среднему арифметическому массива \'b\' = %.2f\n", arithmMean_b);

    return 0;
}
