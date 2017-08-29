//============================================================================
// Name        : main.cpp
// Author      : susliko
// Version     : 1.0
// Copyright   :
// Description : Task #2_1
//============================================================================

#include <iostream>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;
using std::istream;
using std::ostream;
using std::string;



template <typename T>
class Heap
{
public:
    Heap(T* data, int length);

    void print();
    void printAsTree();
    void sort();

private:
    int  size_;
    int  length_;
    T* data_;

    int  parent(int i);
    int  left(int i);
    int  right(int i);
    void swap(int a, int b);
    void siftDown(int i, int heapSize);
    void siftUp(int i);
    void buildMaxHeap();
};



struct Visitor
{
    long beg_;
    long end_;
    long seenAds_;

    Visitor(long beg = 0, long end = 0, long seenAds = 0) :
            beg_(beg),
            end_(end),
            seenAds_(seenAds)
    {}

    bool maySee(int time)
    {
        return (time >= beg_) && (time <= end_) ? true : false;
    }

    friend bool operator>(Visitor const &  v1, Visitor const & v2);
    friend istream& operator>>(istream& is, Visitor & v);
    friend ostream& operator<<(ostream& os, Visitor const & v);
};



void optimizeAds(Visitor* visitors, long long n, int const adsToSee, long long & adsTotal) {
    Heap<Visitor> heap(visitors, n);
    heap.sort();

    long long int last = -1,
                  prevLast = -1;

//    for (int j = n - 1; j >= 0; --j) {
//        while (visitors[j].seenAds_ < adsToSee)
//        {
//            ++adsTotal;
//            int curTime = visitors[j].beg_ + adsToSee - visitors[j].seenAds_ - 1;
//            ++visitors[j].seenAds_;
//            int prev = j - 1;
//            while (prev >= 0 && visitors[prev].maySee(curTime)) {
//                ++visitors[prev].seenAds_;
//                --prev;
//            }
//        }
//
//    }

//    heap.print();
    for (long long int i = 0; i < n; ++i) {
//        if (last == prevLast && last != -1) cout << "==" << endl;
        if (last < visitors[i].beg_) {
            ++adsTotal;
            ++adsTotal;
            prevLast = visitors[i].end_ - 1;
            last = visitors[i].end_;
        } else {
            if (prevLast < visitors[i].beg_) {
//                if (last != visitors[i].end_){
                    ++adsTotal;
                    prevLast = last;
                    last = visitors[i].end_;
//                } else {
//                    ++adsTotal;
//                    prevLast = visitors[i].end_ - 1;
//                }
            }
        }
//        cout << "prev : " << prevLast << " " << last << endl;
    }
}



/******************************************************************************/
int main() {
    long long n = 0,
              adsTotal = 0;
    int const adsToSee = 2;
    cin >> n;


    Visitor* visitors = new Visitor[n];
    for (int i = 0; i < n; ++i) {
        cin >> visitors[i];
    }

    optimizeAds(visitors, n, adsToSee,adsTotal);
    cout << endl << adsTotal << endl;

    delete[] visitors;
    return 0;
}

/******************************************************************************/
template <typename T>
Heap<T>::Heap(T* data, int length)
        :length_(length)
        ,data_(data)
{
    buildMaxHeap();
}


template <typename T>
int Heap<T>::parent(int i)
{
    return (i >= 0) ? (i-1)/2 : -1;
}


template <typename T>
int Heap<T>::left(int i)
{
    return (i >= 0) ? 2*i+1 : -1;
}


template <typename T>
int Heap<T>::right(int i)
{
    return (i >= 0) ? 2*i+2 : -1;
}


template <typename T>
void Heap<T>::print()
{
    for (int i = 0; i < size_; ++i) {
        cout << data_[i] << " " ;
    }
    cout << endl;
}


template <typename T>
void Heap<T>::printAsTree()
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


template <typename T>
void Heap<T>::siftDown(int i, int heapSize)
{
    int l = left(i);
    int r = right(i);
    int largest = 0;
    if (l < heapSize && data_[l] > data_[i]) {
        largest = l;
    } else {
        largest = i;
    }
    if (r < heapSize && data_[r] > data_[largest]) {
        largest = r;
    }
    if (largest != i) {
        swap(i, largest);
        siftDown(largest, heapSize);
    }
}


template <typename T>
void Heap<T>::siftUp(int i)
{
    int p = parent(i);
    while (i > 0 && data_[i] > data_[p]) {
        swap(i, p);
        i = p;
        p = parent(i);
    }
}


template <typename T>
void Heap<T>::buildMaxHeap()
{
    size_ = length_;
    for (int i = length_ / 2 - 1; i >=0; i--) {
        siftDown(i, size_);
    }
}


template <typename T>
void Heap<T>::swap(int a, int b)
{
    T tmp = data_[a];
    data_[a] = data_[b];
    data_[b] = tmp;
}


template <typename T>
void Heap<T>::sort()
{
    int heapSize = size_;

    buildMaxHeap();
    while( heapSize > 1 ) {
        swap(0, heapSize - 1);
        --heapSize;
        siftDown(0, heapSize);
    }
}


bool operator>(Visitor const &  v1, Visitor const & v2)
{
    if (v1.end_ > v2.end_) {
        return true;
    }
    if (v1.end_ == v2.end_ && v1.beg_ < v2.beg_) {
        return true;
    }
    return false;
}



istream& operator>>(istream& is, Visitor & v) {
    is >> v.beg_ >> v.end_;
    return is;
}



ostream& operator<<(ostream& os, Visitor const & v)
{
    os << v.beg_ << " " << v.end_;
    return os;
}

