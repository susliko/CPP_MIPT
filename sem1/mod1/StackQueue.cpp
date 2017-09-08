#include <iostream>

using std::cin;
using std::cout;
using std::endl;

/******************************************************************************/
class MyStack {
public:
    explicit MyStack(int maxSize = 4)
            : maxSize(maxSize)
            , data(new int[maxSize])
    {};

    ~MyStack() {
        delete[] data;
    }

    void push(int v) {
        if (isFull()) incSize();
        data[nextFree++] = v;
    }

    int pop() {
        if (!isEmpty()) return data[(nextFree--) - 1];
        else {
            return  -1;
        }
    }

    bool isFull () {
        return (nextFree == maxSize) ? true : false;
    }

    bool isEmpty () {
        return  (nextFree == 0) ? true : false;
    }

    void print() {
        for (int i = 0; i < nextFree; ++i) {
            cout << data[i] << " ";
        }
    }
private:
    int maxSize = 0,
        nextFree = 0;
    int *data;

    void incSize() {
        maxSize *=2;
        int *tmp = new int[maxSize];
        for (int i = 0; i < nextFree; ++i) {
            tmp[i] = data[i];
        }
        delete[] data;
        data = tmp;
    }
};

/******************************************************************************/
/*  Realised by two Stacks :
 *     (tail) -> (leftStack:rightStack) -> (head)    */
class MyQueue {
public:

    void push(int v) {
        left.push(v);
    }

    int pop() {
        if (!right.isEmpty()) {
            return right.pop();
        } else {
            while (!left.isEmpty()) {
                right.push(left.pop());
            }
            return right.pop();
        }
    }

private:
    MyStack left, right;
};

/******************************************************************************/
int main() {

    /* Initialisation */
    int n = 0;
    cin >> n;
    int *m[2];
    m[0] = new int[n];
    m[1] = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> m[0][i] >> m[1][i];
    }
    MyQueue q;
    bool yes = true;

    /* Calculating answer */
    for (int i = 0; i < n; ++i) {
        switch (m[0][i]) {
            /*a = 2 - pop front
             *a = 3 - push back*/
            case 2 :
                if (q.pop() != m[1][i]) yes = false;
                break;
            case 3 :
                q.push(m[1][i]);
                break;
        }
    }

    cout << ((yes) ? "YES" : "NO");

    return 0;
}
