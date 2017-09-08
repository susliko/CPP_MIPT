//============================================================================
// Name        : main.cpp
// Author      : lamus48
// Version     : 1.0
// Copyright   :
// Description : Task #5_2
//============================================================================

#include <iostream>
#include <cstring>

using std::cout;
using std::cin;
using std::endl;
using std::string;

/******************************************************************************/
class MyStack
{
public:
    explicit MyStack(int maxSize = 4);
    ~MyStack();

    void push(int v);
    int pop();
    int peek();

    bool isFull();
    bool isEmpty();
    void print();

private:
    int  maxSize_ = 0,
         nextFree_ = 0;
    int* data_;

    void incSize();
};


bool isCorrect(char* str, char* resStr);


/******************************************************************************/
int main()
{
    char str[10000], resStr[10000];
    cin >> str >> resStr;


    cout << ((isCorrect(str, resStr)) ? "YES" : "NO") << endl;
    return 0;
}


/******************************************************************************/
bool isCorrect(char* str, char* resStr)
{
    bool correct = true;
    int t = 0;
    MyStack myStack;

    for (int i=0; i < strlen(str) ; ++i ) {
        if (str[i] != resStr[t]) {
            if (myStack.isEmpty()) {
                myStack.push(str[i]);
            }
            else {
                if (resStr[t] == myStack.peek()) {
                    myStack.pop();
                    t++;
                    i--;
                }
                else {
                    myStack.push(str[i]);
                }
            }

        } else {
            t++;
        }
    }

    while (!myStack.isEmpty()) {
        if	(resStr[t] != myStack.pop()) {
            correct = false;
            break;
        }
        t++;
    }

    return correct;
}

/******************************************************************************/
MyStack::MyStack(int maxSize)
        : maxSize_(maxSize)
        , data_(new int[maxSize])
{};


MyStack::~MyStack()
{
    delete[] data_;
}


void MyStack::push(int v)
{
    if (isFull()) incSize();
    data_[nextFree_++] = v;
}


int MyStack::pop()
{
    if (!isEmpty()) return data_[(nextFree_--) - 1];
    else {
        return  -1;
    }
}


int MyStack::peek()
{
    if (!isEmpty()) return data_[(nextFree_) - 1];
    else {
        return  -1;
    }
}


bool MyStack::isFull()
{
    return nextFree_ == maxSize_;
}


bool MyStack::isEmpty ()
{
    return nextFree_ == 0;
}


void MyStack::print()
{
    for (int i = 0; i < nextFree_; ++i) {
        cout << data_[i] << " ";
    }
    cout << endl;
}


void MyStack::incSize()
{
    maxSize_ *=2;
    int *tmp = new int[maxSize_];
    for (int i = 0; i < nextFree_; ++i) {
        tmp[i] = data_[i];
    }
    delete[] data_;
    data_ = tmp;
}

