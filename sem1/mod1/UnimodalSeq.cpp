#include <iostream>

using std::cin;
using std::cout;
using std::endl;

/******************************************************************************/
/*Searches for maximum element in ordered array*/
int searchPivot(int* m, int b, int e);

int main() {
    int n;
    cin >> n;
    int *m = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> m[i];
    }
    cout << searchPivot(m, 0, n - 1);
    delete[] m;
    return 0;
}

/******************************************************************************/
int searchPivot(int* m, int b, int e) {
    if (b > e) {
        cout << "Wrong sequence!" << endl;
        return -1;
    }

    if (b == e) return b;

    int mid = (b + e) / 2;
    if ((m[mid] < m[mid + 1])) {
        return searchPivot(m, mid + 1, e);
    } else if (m[mid] < m[mid - 1]) {
        return searchPivot(m, b, mid-1);
    } else {
        return mid;
    }
}
