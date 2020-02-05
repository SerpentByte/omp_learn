#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main()
{
	system("clear");
	double a[10];
	omp_set_num_threads(3);
	#pragma omp parallel
	{
		int id=omp_get_thread_num();
		printf("Hello from %d. \n", id);
	}
	return 0;

}

