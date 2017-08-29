//============================================================================
// Name        : main.cpp
// Author      : lamus48
// Version     : 1.0
// Copyright   :
// Description : Task #3_2
//============================================================================


#include <iostream>
#include <cstring>

using std::cout;
using std::cin;
using std::endl;
using std::swap;


int64_t merge(int* arr, int left, int right, int* buf);
int64_t mergeSort(int* arr, int size);


/******************************************************************************/
int main()
{
    int maxSize = 20,
        size = 0;
    int* arr = new int[maxSize];

    while (scanf("%d", &arr[size]) != EOF) {
        ++size;
        if (size > maxSize) {
            maxSize *= 2;
            int* buf = new int[maxSize];
            memcpy(buf, arr, size * sizeof(int));
            swap(arr, buf);
            delete[] buf;
        }
    }

    int64_t invNum = mergeSort(arr, size);

    cout << invNum;

    delete[] arr;
    return 0;
}

/******************************************************************************/
int64_t merge(int* arr, int left, int right, int* buf)
{
    if (right - left == 0) {
        return 0;
    }

    int mid = (right - left) / 2 + left,
        i = left,
        j = mid + 1;

    int64_t in0 = 0,
            inL = merge(arr, left, mid, buf),
            inR = merge(arr, mid + 1, right, buf);

    for (int k = left; k <= right; ++k) {
        if      (i > mid)          buf[k] = arr[j++];
        else if (j > right)        buf[k] = arr[i++];
        else if (arr[i] <= arr[j]) buf[k] = arr[i++];
        else {                     buf[k] = arr[j++]; in0 += (mid - i + 1); }
    }

    for (int k = left; k <= right; ++k)  arr[k] = buf[k];
    
    return inL + inR + in0;
}



int64_t mergeSort(int* arr, int size)
{
    int *buf = new int[size + 1];
    int64_t invNum = merge(arr, 0, size - 1, buf);
    delete[] buf;
    return invNum;
}

