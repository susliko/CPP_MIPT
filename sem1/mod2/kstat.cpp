//============================================================================
// Name        : main.cpp
// Author      : lamus48
// Version     : 1.0
// Copyright   :
// Description : Task #3_2
//============================================================================

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::swap;


int findMed(int* a, int l, int r);
int partition(int* a, int l, int r);
int findKStat(int* a, int n, int k);


/******************************************************************************/
int main() {
    int n = 0,
        k = 0;
    cin >> n >> k;
    int* m = new int[n];
    for (int j = 0; j < n; ++j) {
        cin >> m[j];
    }

    cout << m[findKStat(m, n, k)];
    return 0;
}


/******************************************************************************/
int findMed(int* a, int l, int r)
{
    int mid = (l + r) / 2;

    if (a[l] > a[r]) {
        if (a[r] > a[mid]) {
            return r;
        } else {
            return mid;
        }
    } else if (a[l] > a[mid]) {
        return l;
    } else {
        return mid;
    }
}



int partition(int* a, int l, int r)
{
    int med = findMed(a, l, r);
    swap(a[l], a[med]);
    int i = r,
            j = r;
    while (j > l) {
        if (a[j] < a[l]) {
            j--;
        } else {
            swap(a[j], a[i]);
            --j;
            --i;
        }
    }

    if (i - j >= 1) {
        swap(a[l], a[i]);
        return i;
    } else {
        return l;
    }
}



int findKStat(int* a, int n, int k)
{
    int l = 0,
        r = n - 1,
        pivot = partition(a, l, r);

    while (k != pivot) {
        if (pivot < k) {
            l = pivot + 1;
        } else {
            r = pivot;
        }
        pivot = partition(a, l, r);
    }
    return pivot;
}

