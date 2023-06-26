#include <iostream>
#include <cmath>
#include <fstream>
#include <time.h>
#include "Definitions.h"


using namespace std;
int main(int argc, char* argv[])
{
if(argc < 4)
	{ cout << "Wrong number of arguments"; return -1;
}
    clock_t time;
    int result;
  char* Filename;
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);
	int k = atoi(argv[3]);
	if(m > n || m < 0 || n <= 0)
		{cout << "Incorrect arguments" << endl; return -1;}
	if(k == 0)
		Filename = argv[4];
	



    double* massive = new double[n*n];
    double* inverse = new double[n*n];
    int* Column = new int[n];
    double* Row = new double[n];
	

    if(k == 0)
    {
    int a = MatrixInputFile(n*n, massive, Filename);
        if(a == -1)
            {cout << "Incorrect arguments" << endl;
		return -1;}
    for(int i = 0; i <= n*n-1; i++)
            {

                if(i/n == i%n)
                    inverse[i] = 1;
                else inverse[i] = 0;
            }
    }


    if(k > 0 && k <5)
        for(int i = 0; i <= n*n-1; i++)
            {
                massive[i] = FunctionInput(k, n, i/n, i%n);
                if(i/n == i%n)
                    inverse[i] = 1;
                else inverse[i] = 0;
            }
	if(k < 0 || k > 4)
	{ cout << "Wrong argument" << endl; return -1;}

	cout << "The matrix is of the form: " << endl;
	MatrixOutput(m, m, n, massive);
	cout << endl;
	




       time = clock();
 //START
    result = GaussMethod(massive, inverse, Column, Row, n);
//END
	if(result == -1)
		cout << "Singular";

    time = clock() - time;
    double time_taken = (double)time/1000000.0;
    if(result == -1)
        return 0;
    if(result == 0)
    {
        cout << "Inverse matrix is of the form: " << endl;

    MatrixOutput(m, m, n, inverse);
    }
    cout<<"\n Time taken: " << time_taken << endl;
    cout << "\nError norm: ";
    if(k != 0)
        for(int i = 0; i <= n*n-1; i++)
                massive[i] = FunctionInput(k, n, i/n, i%n);

    if(k == 0)
    {
        MatrixInputFile(n*n, massive, Filename);
        }
    ErrorNorm(inverse, massive, n);
	delete[] massive;
	delete[] inverse;
	delete[] Column;
        delete[] Row;
    return 0;


}

