//============================================================================
// Name        : main.cpp
// Author      : lamus48
// Version     : 1.0
// Copyright   :
// Description : Task #1_4
//============================================================================

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

/******************************************************************************/
void findResult(int& A, int& B, int& minDivisor, int N);

/******************************************************************************/
int main() {
    int N = 0,
        A = 0,
        B = 0,
        minDivisor = 1;
    cin >> N;

    findResult(A, B, minDivisor, N);

    cout << A << " " << B;

    return 0;
}

/******************************************************************************/
void findResult(int& A, int& B, int& minDivisor, int N) {
    for (int i = 2; i <= N/2; i++) {
        if (N % i == 0) {
            minDivisor = i;
            break;
        }
    }
    A = (minDivisor == 1) ? (1) : (N / minDivisor);
    B = N - A;
}

