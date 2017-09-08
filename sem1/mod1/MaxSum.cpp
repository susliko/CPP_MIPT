#include <iostream>

using std::cin;
using std::cout;
using std::endl;

/******************************************************************************/
void findMaxSum (int* A, int* B, int n, int* maxA, int* maxB);

int main() {

    int n = 0,
        maxA = 0,
        maxB = 0;

    cin >> n;
    int *A = new int[n];
    int *B = new int[n];

    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> B[i];
    }

    findMaxSum(A, B, n, &maxA, &maxB);

    cout << maxA << " " << maxB;

    delete[] A;
    delete[] B;
    return 0;
}

/******************************************************************************/
void findMaxSum (int* A, int* B, int n, int* maxA, int* maxB) {
    int aM = 0;
    for (int b = 1; b < n; ++b) {
        if (B[b] > B[*maxB]) {
            *maxB = b;
        }

        if (A[b] > A[aM]) {
            aM = b;
        }

        if ((B[b] + A[aM]) > B[*maxB] + A[*maxA]) {
            *maxA = aM;
            *maxB = b;
        }
    }
}
