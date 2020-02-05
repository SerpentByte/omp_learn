#include<cstdio>
#include<omp.h>
#include<unistd.h>
#include<cstdlib>
#include<iostream>

using namespace std;

#define n int(4e4)

int main()
{
    system("clear");

	float *a = (float *)malloc(n*n*sizeof(float));
    float *b = (float *)malloc(n*sizeof(float));
    float *c = (float *)malloc(n*sizeof(float));

    omp_set_num_threads(4);
	
    for(size_t i=0;i<n;i++)
    {
        for(size_t j=i*n;j<(i+1)*n;j++)
        {
            if(i==(j-i*n))
            {
                a[j] = 1;
            }
            else
            {
                a[j] = 0;
            }
        }
        b[i] = i;
        c[i] = 0;
    }


    double t1 = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic,int(1e3))
    for(size_t i=0;i<n;i++)
    {
        #pragma omp reduction (+: c[i]) schedule(dynamic,int(1e3))
        for(size_t j=i*n;j<(i+1)*n;j++)
        {
            c[i] += a[j]*b[j-i*n];
        }

    }

    double t2 = omp_get_wtime();

    cout<<"Time= "<<(t2-t1)<<endl;

    /*for(int i=0;i<n;i++)
    {
        cout<<c[i]<<' ';
    }

    cout<<endl;*/

    free(a); free(b); free(c);
	return 0;
}