#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <future>
using namespace std;
using namespace chrono;
void fillArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 10000;
    }
}
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void copyArray(int source[], int target[], int n)
{
    for (int i = 0; i < n; i++)
    {
        target[i] = source[i];
    }
}
void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}
void shellSort(int arr[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j = i;

            while (j >= gap && arr[j - gap] > temp)
            {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}
int binarySearch(int arr[], int n, int key)
{
    int left = 0;
    int right = n - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (arr[mid] == key)
        {
            return mid;
        }
        else if (arr[mid] < key)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return -1;
}
long long measureBubble(int arr[], int n)
{
    auto start = high_resolution_clock::now();
    bubbleSort(arr, n);
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}
long long measureSelection(int arr[], int n)
{
    auto start = high_resolution_clock::now();
    selectionSort(arr, n);
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}
long long measureShell(int arr[], int n)
{
    auto start = high_resolution_clock::now();
    shellSort(arr, n);
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}
int main()
{
    srand(time(0));
    int sizes[] = { 10, 50, 800, 5000, 40000, 120000 };
    int repeatCount = 5;
    cout << "===== SORTING RESULTS =====" << endl;
    for (int s = 0; s < 6; s++)
    {
        int n = sizes[s];
        long long bubbleTotal = 0;
        long long selectionTotal = 0;
        long long shellTotal = 0;
        cout << "\nArray size: " << n << endl;
        for (int repeat = 1; repeat <= repeatCount; repeat++)
        {
            int* arr = new int[n];
            fillArray(arr, n);
            if (repeat == 1 && n <= 50)
            {
                cout << "Original array: ";
                printArray(arr, n);
            }
            int* copy1 = new int[n];
            int* copy2 = new int[n];
            int* copy3 = new int[n];
            copyArray(arr, copy1, n);
            copyArray(arr, copy2, n);
            copyArray(arr, copy3, n);
            bubbleTotal += measureBubble(copy1, n);
            selectionTotal += measureSelection(copy2, n);
            shellTotal += measureShell(copy3, n);
            delete[] copy1;
            delete[] copy2;
            delete[] copy3;
            delete[] arr;
        }
        cout << "Bubble sort average time: " << bubbleTotal / repeatCount << " ms" << endl;
        cout << "Selection sort average time: " << selectionTotal / repeatCount << " ms" << endl;
        cout << "Shell sort average time: " << shellTotal / repeatCount << " ms" << endl;
    }
    cout << "\n===== BINARY SEARCH =====" << endl;
    int searchSize = 20;
    int* searchArray = new int[searchSize];
    fillArray(searchArray, searchSize);
    cout << "Array before sorting: ";
    printArray(searchArray, searchSize);
    shellSort(searchArray, searchSize);
    cout << "Sorted array: ";
    printArray(searchArray, searchSize);
    int key;
    cout << "Enter number for search: ";
    cin >> key;
    int index = binarySearch(searchArray, searchSize, key);
    if (index != -1)
    {
        cout << "Element found at index: " << index << endl;
    }
    else
    {
        cout << "Element not found." << endl;
    }
    delete[] searchArray;
    cout << "\n===== SYNCHRONOUS AND ASYNCHRONOUS COMPARISON =====" << endl;
    for (int s = 0; s < 6; s++)
    {
        int n = sizes[s];
        int* baseArray = new int[n];
        fillArray(baseArray, n);
        int* sync1 = new int[n];
        int* sync2 = new int[n];
        int* sync3 = new int[n];
        copyArray(baseArray, sync1, n);
        copyArray(baseArray, sync2, n);
        copyArray(baseArray, sync3, n);
        auto startSync = high_resolution_clock::now();
        bubbleSort(sync1, n);
        selectionSort(sync2, n);
        shellSort(sync3, n);
        auto endSync = high_resolution_clock::now();
        long long syncTime = duration_cast<milliseconds>(endSync - startSync).count();
        delete[] sync1;
        delete[] sync2;
        delete[] sync3;
        int* async1 = new int[n];
        int* async2 = new int[n];
        int* async3 = new int[n];
        copyArray(baseArray, async1, n);
        copyArray(baseArray, async2, n);
        copyArray(baseArray, async3, n);
        auto startAsync = high_resolution_clock::now();
        auto f1 = async(launch::async, bubbleSort, async1, n);
        auto f2 = async(launch::async, selectionSort, async2, n);
        auto f3 = async(launch::async, shellSort, async3, n);
        f1.get();
        f2.get();
        f3.get();
        auto endAsync = high_resolution_clock::now();
        long long asyncTime = duration_cast<milliseconds>(endAsync - startAsync).count();
        cout << "\nArray size: " << n << endl;
        cout << "Synchronous time: " << syncTime << " ms" << endl;
        cout << "Asynchronous time: " << asyncTime << " ms" << endl;
        delete[] async1;
        delete[] async2;
        delete[] async3;
        delete[] baseArray;
    }

    return 0;
}