#include<chrono>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<omp.h>

#define PI 4.0*atan(1.0)

using namespace std;

double h=1e-9;

double single()
{
	size_t n = int(1/h);
	double sum=0;
	double x=0;

	for(size_t i=0; i<n;i++)
	{	
		sum+= h*(4.0/(1+x*x));
		x+=h;
	}

	return sum;
}

double par()
{
	size_t n = int(1/h);
	double pi=0;
	int nt=4;
	double x0=0;
	double sum[nt];

	for(int i=0;i<nt;i++)
	{
		sum[nt]=0.0;
	}

	omp_set_num_threads(nt);
	#pragma omp parallel shared(sum,h)
	{
	 	int id=omp_get_thread_num();
	 	int n_thr;
	 	double x=x0;
	 	char ch;
	 	if(id==0)
	 	{
	 		n_thr=nt;
	 	}
	#pragma omp for
		for(size_t i=0;i<n;i++)
		{
			sum[id]+=h*4.0/(1+x*x);
			x=x0+i*h;
			//printf("i= %d\t\tid=%d\tn_thr=%d\t", i,id,n_thr);
			//printf("x=%f\tsum[%d]=%f\t", x, id, sum[id]);
			//printf("h=%e\n", h);

			//cin>>ch;
		}
	}
	for(int i=0;i<nt;i++)
	{
		pi+=sum[i];
		//printf("sum[%d]=%f\n", i,sum[i]);
	}
	//printf("PI=%lf\n", pi);
	return pi;

}

int main()
{
	system("clear");

	auto t1=std::chrono::high_resolution_clock::now();
	auto t2=std::chrono::high_resolution_clock::now();
	std::chrono::milliseconds d;
	float t_s=0,t_p=0;
	double pi_s=0, pi_p=0;

	t1=std::chrono::high_resolution_clock::now();
	pi_s=single();
	t2=std::chrono::high_resolution_clock::now();
	d=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
	t_s=d.count();


	t1=std::chrono::high_resolution_clock::now();
	pi_p=par();
	t2=std::chrono::high_resolution_clock::now();
	d=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
	t_p=d.count();

	printf("\t\tsingle\t\tparallel\tactual\n");
	printf("\t\t------\t\t--------\t------\n");
	printf("value:\t\t%lf\t%lf\t%lf\n", pi_s, pi_p, PI);
	printf("time:\t\t%.3e\t%.3e\t-------\n",  t_s,t_p);
	
}