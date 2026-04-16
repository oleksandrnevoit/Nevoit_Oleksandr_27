#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <map>
using namespace std;
int** CreateMatrix(int n)
{
    int** a = new int* [n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new int[n];
    }
    return a;
}
void DeleteMatrix(int** a, int n)
{
    for (int i = 0; i < n; i++)
    {
        delete[] a[i];
    }
    delete[] a;
}
void FillMatrix(int** a, int n, int minValue, int maxValue)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j] = minValue + rand() % (maxValue - minValue + 1);
        }
    }
}
void PrintMatrix(int** a, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << setw(5) << a[i][j];
        }
        cout << endl;
    }
}
int FindMostFrequentValue(int** a, int n)
{
    map<int, int> counts;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            counts[a[i][j]]++;
        }
    }
    int mostFrequentValue = a[0][0];
    int maxCount = counts[a[0][0]];
    for (auto item : counts)
    {
        if (item.second > maxCount)
        {
            maxCount = item.second;
            mostFrequentValue = item.first;
        }
    }
    return mostFrequentValue;
}
bool IsSector2(int i, int j, int n)
{
    return (j < i && i + j < n - 1);
}
bool IsSector10(int i, int j, int n)
{
    return (j > (n - 1) / 2);
}

int CountLessThanKInSector2(int** a, int n, int k)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (IsSector2(i, j, n) && a[i][j] < k)
            {
                count++;
            }
        }
    }
    return count;
}
int ReplaceSector10(int** a, int n, int newValue)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (IsSector10(i, j, n))
            {
                a[i][j] = newValue;
                count++;
            }
        }
    }
    return count;
}
int main()
{
    srand(time(0));
    int n;
    int k;
    int variant = 27;
    cout << "Enter n: ";
    cin >> n;
    if (n < 3)
    {
        cout << "Matrix size must be at least 3." << endl;
        return 0;
    }
    cout << "Enter k: ";
    cin >> k;
    int minValue = -10 - variant;
    int maxValue = 10 + variant;
    int** matrix = CreateMatrix(n);
    FillMatrix(matrix, n, minValue, maxValue);
    cout << "\nOriginal matrix:\n";
    PrintMatrix(matrix, n);
    int countSector2 = CountLessThanKInSector2(matrix, n, k);
    int mostFrequentValue = FindMostFrequentValue(matrix, n);
    int countSector10 = ReplaceSector10(matrix, n, mostFrequentValue);
    cout << "\nCount of elements in sector 2 less than k: " << countSector2 << endl;
    cout << "Most frequent value in matrix: " << mostFrequentValue << endl;
    cout << "Count of elements in sector 10: " << countSector10 << endl;
    cout << "\nModified matrix:\n";
    PrintMatrix(matrix, n);
    DeleteMatrix(matrix, n);
    return 0;
}