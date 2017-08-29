//============================================================================
// Name        : main.cpp
// Author      : lamus48
// Version     : 1.0
// Copyright   :
// Description : Task #5_2
//============================================================================

#include <iostream>
#define uchar unsigned char
#define ulong unsigned long long
#define MAX 256 // Number of various values

using std::cout;
using std::cin;
using std::endl;

template <class T>
void countingSort(T *arr, int size, int curByte);

template <class T>
void LSDSort( T* arr, int size );

/******************************************************************************/
int main()
{

// Initialization
    int n;
    cin >> n;
    ulong *arr = new ulong[n];
    for (int i = 0; i < n; ++i) cin >> arr[i];

// Sorting data
    LSDSort(arr, n);

// Printing result
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete [] arr;
    return 0;
}

/******************************************************************************/
template <class T>
void countingSort(T *arr, int size, int curByte)
{
    // Array "bytesFreq" is used to store the number 
    // of occurrences for each possible value
    int *bytesFreq = new int[MAX];
    for (int i = 0; i < MAX; ++i) bytesFreq[i] = 0;
    
    
    // Filling "bytesFreq"
    T* ptr;
    for (int i = 0; i < size; ++i) {
        ptr = arr + i;
        uchar* charPtr = (uchar*)ptr;
        ++bytesFreq[charPtr[curByte]];
    }
    int sum = 0;
    for (int i = 0; i < MAX; ++i) {
        int tmp = bytesFreq[i];
        bytesFreq[i] = sum;
        sum += tmp;
    }

    
    // Array "res" is used to store sorted values
    T *res = new T[size];
    for (int i = 0; i < size; ++i) {
        ptr = arr + i;
        uchar* charPtr = (uchar*)ptr;
        res[bytesFreq[charPtr[curByte]]++] = arr[i];
    }

    for (int i = 0; i < size; ++i) arr[i] = res[i];

    delete[] res;
    delete[] bytesFreq;
}


template <class T>
void LSDSort( T* arr, int size )
{
    for(int curByte = 0; curByte < sizeof(T); ++curByte) {
        countingSort(arr, size, curByte);
    }
}

