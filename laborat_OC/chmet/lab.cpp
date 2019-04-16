#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    int n;
    cout << "enter n" << endl;
    cin >> n;
    double **a = new double* [n];
    for (int i = 0; i < n; i++)
        a[i] = new double [n];

    double *b = new double[n];

    double *x = new double [n];
    double *y = new double [n];

    cout << "enter matrix a" << endl;
    for (int i=0; i < n; i++ )
        for (int j=0; j < n; j++)
            cin >> a[i][j];

    cout << "enter matrix B" << endl;
    for (int i = 0; i < n; i++)
        cin >> b[i];

    for (int i = 0; i < n; i++)
    {
        int cur;
        cur = a[i][i];
        for (int j = 0; j < n; j++)
        {
            a[i][j] = -a[i][j]/cur;
        }
        b[i] = b[i]/cur;
        x[i] = b[i];
        a[i][i] = 0;
    }

    int iter;
    cout << "enter number of iter" << endl;
    cin >> iter;

    for (int k = 0; k < iter; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                y[i] = b[i] + x[j]*a[i][j];
            }
        }
    }

    for (int i = 0; i < n; i++)
        printf ("%f\n",y[i]);


    /*for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }*/

    for (int i = 0; i < n; i++)
        delete [] a[i];
    delete [] b;
    delete [] y;
}

