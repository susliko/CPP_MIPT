#include <iostream>
#include <cstring>


using std::cout;
using std::cin;
using std::endl;


// return the number of possible combinations
// for "i" cubes with "j" cubes in the first layer
long getVars(long ** m, int i, int j);



// prints the array
void print(long ** m, int n);



// returns total num of combinations for pyramids of "n" cubes
long getResult(int n);



/******************************************************************************/
int main() {
    int n ;
    cin >> n;

    cout << getResult(n);

    return 0;
}



/******************************************************************************/
long getVars(long ** m, int i, int j)
{
    long res = 0;
    int left = i - j;
    int min  = (left > j) ? j : left ;

    for (int k = 1; k <= min; ++k) {
        if (m[left][k] == 0) m[left][k] = getVars(m, left, k);
        res += m[left][k];
    }

    if (m[i][j] == 0) m[i][j] = res;

    return res;
}



void print(long ** m, int n)
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}



long getResult(int n)
{
    n = n + 1;
// array initialization
    long ** m = new long * [n];
    for (int i = 0; i < n; ++i) {
        m[i] = new long[n];
    }


// creating the base of dynamics
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if ((j == 1) || (i == j)) m[i][j] = 1;
            else m[i][j] = 0;
        }
    }


// calculating only needed values by the lazy dynamics
    for (int l = 1; l < n; ++l) {
        getVars(m, n - 1, l);
    }


// calculating the result
    long res = 0;
    for (int i1 = 0; i1 < n; ++i1) {
        res += m[n - 1][i1];
    }


// releasing memory
    for (int i = 0; i < n; ++i) {
        delete[] m[i];
    }
    delete[] m;


    return res;
}
