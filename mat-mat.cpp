#include<cstdio>
#include<omp.h>
#include<unistd.h>
#include<cstdlib>
#include<iostream>

using namespace std;

#define n int(1e3)

int main()
{
    system("clear");

    float *a = (float *)malloc(n*n*sizeof(float));
    float *b = (float *)malloc(n*n*sizeof(float));
    float *c = (float *)malloc(n*n*sizeof(float));

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
            b[j] = 5;
            c[j] = 0;
        }
    }


    double t1 = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic,int(100))
        for(size_t i=0;i<n;i++)
        {
            for(size_t j=0;j<n;j++)
            {
                #pragma reduction (+: c[i+(j*n)]) schedule(dynamic,int(100))
                for(size_t k=0;k<n;k++)
                {
                    c[i+(j*n)] += a[i+(k*n)]*b[k+(i*n)];
                }
            }
        }

    double t2 = omp_get_wtime();

    free(a); free(b); free(c);

    cout<<"Time= "<<(t2-t1)<<endl;

    return 0;
}