#include<cstdio>
#include<omp.h>
#include<unistd.h>
#include<cstdlib>
#include<iostream>

using namespace std;

#define n int(1e9)
#define c 1e-7

inline float rng(float a=1.0)
{
	srand(getpid());
	float r = rand()/float(RAND_MAX);
	return r*a;
}

int main()
{
	int *a = (int *) malloc(n*sizeof(int));
    size_t sum = 0;

    omp_set_num_threads(4);

    double t1 = omp_get_wtime();

    #pragma omp parallel for
	   for(size_t i=0;i<n;i++)
	   {
		  //srand(getpid());
		  //a[i] = c*(rand()/float(RAND_MAX));
		  a[i]=1;
	   }

/*
//------------------------------ single
    for(int i=0;i<n;i++)
        {
            sum += a[i];
        } 
//------------------------------ single
*/
  
//------------------------------ parallel
    #pragma omp parralel for reduction(+: sum)
    {    
        for(size_t i=0;i<n;i++)
            sum += a[i];      
    }
//------------------------------ parallel


	double t2 = omp_get_wtime();

	free(a);

	cout<<"Sum= "<<sum<<endl;
	cout<<"Time taken= "<<(t2-t1)<<endl;

	return 0;
}