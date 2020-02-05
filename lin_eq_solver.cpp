#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<omp.h>

//****************
// parameters
//****************
int n = 3;
double r = 1e-5, h = 1e-8;
size_t ctr = 1;
//****************

//****************
// initialization
double **A = (double **)malloc(n*sizeof(double));
for(int i=0;i<n;i++)
{
    A[i] = (double *)malloc(n*sizeof(double));
}

int main()
{
    return 0;
}

