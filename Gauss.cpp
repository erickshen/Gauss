#include <iostream>
#include <cmath>
#include <fstream>
#include "Definitions.h"
using namespace std;
int Rationing(double* x, double* inverse, int n);
void PermuteColumn(double* x, int index, int step, double*Row, int n);
int FindMax(double* x, int step, int n);
void PermuteRow(double* x, int index, int step, double*Row, int n);
void Substitute(double* x, double* inverse, int step, int n);
int Back(double* x, double* inverse, int n);
int Rationing(double* x, double* inverse, int n);
double mach_eps(void);
static double eps;
int GaussMethod(double* massive, double* inverse, int* Column, double*Row, int n)
{

	double Norm = MatrixNorm(massive, n);
       for(int i =0; i<= n*n-1; i++)
            massive[i] = massive[i]/Norm;
	 eps = 10*mach_eps();

        for(int step = 0; step <= n-1; step++)
    {
       int ind_max = FindMax(massive, step, n); 
       if(sqrt(massive[ind_max]*massive[ind_max])< eps)
           {return -1; }
       Column[step] = ind_max;
                PermuteRow(massive, ind_max/n, step, Row, n);
                PermuteColumn(massive, ind_max%n, step, Row, n);
                PermuteRow(inverse, ind_max/n, step, Row, n);
     		Substitute(massive, inverse, step, n);




    }
    int a = Back(massive, inverse, n);
        if(a == -1)
            {return -1;}
    a = Rationing(massive, inverse, n);
        if(a == -1)
           {return -1;}
    for(int i = n-1; i >= 0; i--)
        PermuteRow(inverse, Column[i]%n, i, Row, n);

	        for(int i =0; i<= n*n-1; i++)
        inverse[i] = inverse[i]/Norm;

    return 0;

}
int FindMax(double* x, int step, int n)
{
    double k = 0;
    int index = 0;
    for(int i = n*step+step; i <= (n)*(n)-1; i = ((i+1)/n)*n + std::max(step, (i+1)%n))
      {  if(x[i]*x[i] > k*k)
        {
            k = x[i];
            index = i;
		
		
        }
      }
    return index;
}

void PermuteRow(double* x, int index, int step, double*Row, int n)
{
       for(int i = 0; i<= n-1; i++)
       {
           Row[i] = x[n*(index) + i];
           x[n*(index) + i] = x[n*step + i];
           x[n*step + i] = Row[i];
       }
}

 void PermuteColumn(double* x, int index, int step, double*Row, int n)
 {

     for(int j = 0; j <= n-1; j++)
            {
            Row[j] = x[index + n*j];
            x[index + n*j] = x[step + n*j];
            x[step  + n*j] = Row[j];

            }
}

void Substitute(double* x, double* inverse, int step, int n)
{

        for(int i = step+1; i <= n-1; i++)
        {
            double a = x[i*n + step];
            for(int j = 0; j <= n-1; j++)
                {
                    x[i*n  + j] = x[i*n + j] - x[step*n + j]*a/x[step*n+step];
                    inverse[i*n + j] = inverse[i*n + j] - inverse[step*n + j]*a/x[step*n+step];
                }
        }
}

int Back(double* x, double* inverse, int n)
{

    for(int i = n-1; i >= 0; i--)
        for(int j = i-1; j >= 0; j--)
            {
            if(sqrt(x[i*n+i]*x[i*n+i])  > eps)
                for(int k = 0; k <= n-1; k++)
                    inverse[j*n + k] = inverse[j*n+k] - inverse[i*n+k]*x[j*n+i]/x[i*n+i];
            else  return -1;
            }

    return 0;
}

int Rationing(double* x, double* inverse, int n)
{
    for(int i =0; i<=n-1; i++)
    {
        if(sqrt(x[i*n+i]*x[i*n+i]) > eps)
            for(int j = 0; j<=n-1; j++)
                inverse[i*n+j] = inverse[i*n+j]/x[i*n+i];
        else
            return -1;
    }
        return 0;
}
double mach_eps(void)
{ double eps = 1.0;
 while(1.0 + eps/2.0 > 1.0)
{ eps /= 2.0;}
return eps;
}
