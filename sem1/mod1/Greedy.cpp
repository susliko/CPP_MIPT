//============================================================================
// Name        : main.cpp
// Author      : lamus48
// Version     : 1.0
// Copyright   :
// Description : Task #6_1
//============================================================================

#include <iostream>
#include <cassert>
#include <cmath>
#include <sys/time.h>

using std::cout;
using std::cin;
using std::endl;

/******************************************************************************/
class MyStack {
public:
    explicit MyStack(int maxSize = 4);
    ~MyStack();

    void push(int v);

    int  pop();
    bool isFull ();
    bool isEmpty ();
    int  getSize();
    void print();

private:
    int  maxSize_ = 0,
         size_ = 0;
    int* data_;

    void incSize();
};

/******************************************************************************/
class Heap
{
public:
    Heap(int *data, int length);

    int  parent(int i);
    int  left(int i);
    int  right(int i);
    int  get(int i);
    void siftDown(int i);
    void siftUp(int i);
    void print();
    void printAsTree();
    void set(int i, int v);
    void decSize();
    int  getSize();
    int  getZeroIndex();
    void swap(int a, int b);
    void buildMaxHeap();
private:

    int  size_;
    int  length_;
    int* data_;
};


long measureTime()
{
    struct timeval t;

    gettimeofday(&t, NULL);
    long mt = (long)t.tv_sec * 1000 + t.tv_usec / 1000;
    return mt;
}


int countTurns(int* data, int fruitsNumber, int mW);

/******************************************************************************/
int main()
{
    int  mW = 0,          // Maximal weight to handle
         fruitsNumber = 0;
    int* data;

    cin >> fruitsNumber;
    data = new int[fruitsNumber];
    for (int i = 0; i < fruitsNumber; i++) {
        cin >> data[i];
    }
    cin >> mW;

    cout << countTurns(data, fruitsNumber, mW);

    delete[] data;
    return 0;
}

/******************************************************************************/
int countTurns(int* data, int fruitsNumber, int mW)
{
    int  turn = 0,        // Total number of turns
            cW = 0,          // Current handling weight
            n = 0;          // Heaviest fruit
    Heap heap(data, fruitsNumber);
    MyStack stack;

    n = heap.get(0);
    while (n != 0) {
        n = heap.get(0);
        while (mW >= (cW + n) && n != 0) {
            stack.push(n);
            cW += n;
            heap.set(0, 0);
            heap.swap(0, heap.getSize() - stack.getSize());
            heap.siftDown(0);
            n = heap.get(0);
        }

        while (!stack.isEmpty()) {
            n = stack.pop() / 2;
            if (n != 0) {
                int zero = heap.getZeroIndex();
                heap.set(zero, n);
                heap.siftUp(zero);
            }
            else {
                heap.decSize();
            }
        }

        ++turn;
        cW = 0;
        n = heap.get(0);
    }
    return turn;
}


Heap::Heap(int *data, int length)
        :length_(length)
        ,data_(data)
    {
        buildMaxHeap();
    }


int Heap::parent(int i)
{
    return (i >= 0) ? (i-1)/2 : -1;
}


int Heap::left(int i)
{
    return (i >= 0) ? 2*i+1 : -1;
}


int Heap::right(int i)
{
    return (i >= 0) ? 2*i+2 : -1;
}


void Heap::print()
{
    for (int i = 0; i < size_; ++i) {
        cout << data_[i] << " ";
    }
    cout << endl;
}


void Heap::printAsTree()
{
    if (size_ != 0) {
        cout << data_[0] << endl;
        for (int i = 1; i <= log(size_)/log(2); i++) {
            for (int j = (int)(pow(2,i)-1); j <= pow(2,i+1)-2; j++) {
                if (j < size_) {
                    cout << data_[j] << " ";
                }
            }
            cout << endl;
        }
    }
}


void Heap::siftDown(int i)
{
    int l = left(i);
    int r = right(i);
    int largest = 0;
    if (l < size_ && data_[l] > data_[i]) {
        largest = l;
    } else {
        largest = i;
    }
    if (r < size_ && data_[r] > data_[largest]) {
        largest = r;
    }
    if (largest != i) {
        swap(i, largest);
        siftDown(largest);
    }
}


void Heap::siftUp(int i)
{
    int p = parent(i);
    while (i > 0 && data_[i] > data_[p]) {
        swap(i, p);
        i = p;
        p = parent(i);
    }
}


void Heap::buildMaxHeap()
{
    size_ = length_;
    for (int i = length_ / 2 - 1; i >=0; i--) {
        siftDown(i);
    }
}


void Heap::set(int i, int v)
{
    assert(i >= 0 && i < length_);
    data_[i] = v;
}


void Heap::decSize()
{
    size_--;
}


int Heap::get(int i)
{
    return data_[i];
}

int Heap::getZeroIndex()
{
    for (int i = size_ - 1; i >= 0; i--) {
        if (data_[i] == 0) return i;
    }
    return -1;
}


void Heap::swap(int a, int b)
{
    int tmp = data_[a];
    data_[a] = data_[b];
    data_[b] = tmp;
}


int Heap::getSize() {
    return  size_;
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
    data_[size_++] = v;
}


int MyStack::pop()
{
    if (!isEmpty()) return data_[(size_--) - 1];
    else {
        return  -1;
    }
}


bool MyStack::isFull ()
{
    return size_ == maxSize_;
}


bool MyStack::isEmpty ()
{
    return size_ == 0;
}


int MyStack::getSize()
{
    return size_;
}


void MyStack::print()
{
    for (int i = 0; i < size_; ++i) {
        cout << data_[i] << " ";
    }
    cout << endl;
}


void MyStack::incSize()
{
    maxSize_ *=2;
    int *tmp = new int[maxSize_];
    for (int i = 0; i < size_; ++i) {
        tmp[i] = data_[i];
    }
    delete[] data_;
    data_ = tmp;
}

