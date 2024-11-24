#include <bits/stdc++.h>
using namespace std;

void foo(int a, int b, double d)
{
    int result = a + b;
    cout << result;
}

int call2(int a, int b)
{
    return (a - b);
}
int call1(int a, int b)
{

    int sum = a + b;
    return call2(a, b) + sum;
}

int main()
{
    int x, y = 2, z = 3;

    foo(x, y, 5.00);

    int val = call1(y, z);

    int mat[10][10];
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            mat[i][j] = 0;
        }
    }

    for (int i = 0; i < 10; i++)
    {
        mat[i][i] = 1;
    }

    return 0;
}
