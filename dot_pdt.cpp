#include<iostream>
#include<cstdio>
#include<omp.h>
#include<unistd.h>
#include<cstdlib>

using namespace std;

#define n int(1e9)
#define c float(1e-3)

int main()
{
	//system("clear");

	float *a=(float* )malloc(n*sizeof(float));
	float *b=(float* )malloc(n*sizeof(float));
	double dot=0;
	
		
	float t1 = omp_get_wtime();

	omp_set_num_threads(4);
	#pragma omp parallel for schedule(dynamic,10000)
		for(size_t i=0;i<n;i++)
		{
			a[i]=1e-3;b[i]=1e-3;
		}

	#pragma omp parallel for reduction(+: dot) schedule(dynamic,10000)
		for(size_t i=0;i<n;i++)
			dot += a[i]*b[i];

	float t2 = omp_get_wtime();

	free(a); free(b);

	cout<<"Dot product= "<<dot<<endl;
	cout<<"Time taken= "<<(t2-t1)<<endl;

	return 0;
}