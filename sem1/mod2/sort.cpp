#include <iostream>
#include <sys/time.h>
#include <cstring>

using std::cout;
using std::cin;
using std::endl;
using std::swap;

void swap(int* a, int i, int j);
void dualPivotQuicksort(int* a, int left,int right);
void quickSort(int* a, int left, int right);

long measureTime(int* a, int n, void (*sort)(int* a, int left,int right));


/******************************************************************************/
int main() {

    int maxSize = 5e7;
    int size = 0;
    int* arr = new int[maxSize];

    while (scanf("%d", &arr[size]) != EOF) {
        ++size;
    }


    dualPivotQuicksort(arr, -1, size-1);

    
    int it = -1;
    while ((it + 10) < size) {
        it = (it + 10);
        printf("%d ", arr[it]);
    }
    delete arr;

    return 0;
}

/******************************************************************************/

void swap(int* a, int i, int j)
{
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}



void dualPivotQuicksort(int* a, int left,int right)
{
    int div = 3;
    int len = right - left;
    if (len < 27) { // insertion sort for tiny array
        for (int i = left + 1; i <= right; i++) {
            for (int j = i; j > left && a[j] < a[j - 1]; j--) {
                swap(a, j, j - 1);
            }
        }
        return;
    }
    int third = len / div;
// "medians"
    int m1 = left + third;
    int m2 = right - third;
    if (m1 <= left) {
        m1 = left + 1;
    }
    if (m2 >= right) {
        m2 = right - 1;
    }
    if (a[m1] < a[m2]) {
        swap(a, m1, left);
        swap(a, m2, right);
    }
    else {
        swap(a, m1, right);
        swap(a, m2, left);
    }
// pivots
    int pivot1 = a[left];
    int pivot2 = a[right];
// pointers
    int less = left + 1;
    int great = right - 1;
// sorting
    for (int k = less; k <= great; k++) {
        if (a[k] < pivot1) {
            swap(a, k, less++);
        }
        else if (a[k] > pivot2) {
            while (k < great && a[great] > pivot2) {
                great--;
            }
            swap(a, k, great--);
            if (a[k] < pivot1) {
                swap(a, k, less++);
            }
        }
    }
// swaps
    int dist = great - less;
    if (dist < 13) {
        div++;
    }
    swap(a, less - 1, left);
    swap(a, great + 1, right);
// subarrays
    dualPivotQuicksort(a, left, less - 2);
    dualPivotQuicksort(a, great + 2, right);
// equal elements
    if (dist > len - 13 && pivot1 != pivot2) {
        for (int k = less; k <= great; k++) {
            if (a[k] == pivot1) {
                swap(a, k, less++);
            }
            else if (a[k] == pivot2) {
                swap(a, k, great--);
                if (a[k] == pivot1) {
                    swap(a, k, less++);
                }
            }
        }
    }
// subarray
    if (pivot1 < pivot2) {
        dualPivotQuicksort(a, less, great);
    }
}



long measureTime(int* a, int n, void (*sort)(int* a, int left,int right))
{
    struct timeval t1, t2;

    gettimeofday(&t1, NULL);
    long mt;

    sort(a, 0, n);

    gettimeofday(&t2, NULL);
    mt = (long)(t2.tv_sec - t1.tv_sec) * 1000000 +
         (t2.tv_usec - t1.tv_usec)  ;
    return mt;
}



void quickSort(int* a, int left, int right)
{
    int x = a[left + (right - left) / 2];
    int i = left;
    int j = right;
    while(i <= j)
    {
        while(a[i] < x) i++;
        while(a[j] > x) j--;
        if(i <= j)
        {
            swap(a, i, j);
            i++;
            j--;
        }
    }
    if (i < right)
        quickSort(a, i, right);

    if (left < j)
        quickSort(a, left, j);
}

