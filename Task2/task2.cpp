#include <iostream>
#include <cmath>
using namespace std;
long long Factorial(int n)
{
    long long result = 1;

    for (int i = 1; i <= n; i++)
    {
        result *= i;
    }
    return result;
}
double ProductArray(const double arr[], int size)
{
    double product = 1.0;
    for (int i = 0; i < size; i++)
    {
        product *= arr[i];
    }
    return product;
}
double ProductCubeRoots(const double arr[], int size)
{
    double product = 1.0;
    for (int i = 0; i < size; i++)
    {
        product *= cbrt(arr[i]);
    }
    return product;
}
double CalculateZ(int n, const double x[], int size)
{
    double firstPart = (Factorial(5 * n - 4) + 8.0) / Factorial(2 * n + 1);
    double secondPart = (Factorial(n) + ProductArray(x, size)) / ProductCubeRoots(x, size);

    return firstPart + secondPart;
}
int main()
{
    int n = 3;
    const int size = 7;
    double x[size] = { 5, 6, 7, 3, 9, 8, 4 };
    double z = CalculateZ(n, x, size);
    cout << "n = " << n << endl;
    cout << "X = { ";

    for (int i = 0; i < size; i++)
    {
        cout << x[i];

        if (i < size - 1)
        {
            cout << ", ";
        }
    }
    cout << " }" << endl;
    cout << "Z = " << z << endl;
    return 0;
}