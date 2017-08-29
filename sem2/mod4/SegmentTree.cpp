#include <iostream>
#include <vector>
#include <cmath>



class SegmentTree
{
public:
    // Constructor takes a vector and builds the tree
    SegmentTree(std::vector<int> & arr);
    // Returns maximum on the specified subsegment
    int getMax(unsigned l, unsigned r);
    // Increases all elements in the specified range by 'value'
    void add(unsigned l, unsigned r, int value);

private:
    // Recursive realisations of public'add' and 'getMax' functions
    void add(unsigned l, unsigned r, unsigned lb, unsigned rb, unsigned pos, int value);
    int getMax(unsigned l, unsigned r, unsigned lb, unsigned rb, unsigned pos);

private:
    // '_size' - number of nodes in the tree
    unsigned _size;
    // '_num' - number of elements in the whole segment
    unsigned _num;
    // '_arr' - tree itself
    std::vector<std::pair<int, int>> _arr;
};



/*============================================================================================*/
int main()
{
    unsigned N;
    std::cin >> N;
    std::vector<int> arr(N - 1);

    // Segment initialization
    for (int i = 0; i < N - 1; ++i) {
        std::cin >> arr[i];
    }

    // Initialization of the train's capacity and number of requests total
    unsigned maxCapacity;
    unsigned requestsNum;
    std::cin >> maxCapacity >> requestsNum;

    SegmentTree segmentTree(arr);

    // Processing requests
    for (int i = 0; i < requestsNum; ++i) {
        unsigned l;
        unsigned r;
        int val;
        std::cin >> l >> r >> val;

        if (segmentTree.getMax(l, r - 1) + val <= maxCapacity) {
            segmentTree.add(l, r - 1, val);
        } else {
            std::cout << i << std::endl;
        }
    }
    return 0;
}


/*============================================================================================*/
SegmentTree::SegmentTree(std::vector<int> & arr)
        : _size(static_cast<unsigned>(2 * (1 << static_cast<int>(log(arr.size()) / log(2) + 1)) - 1))
        , _num(static_cast<unsigned>      (1 << static_cast<int>(log(arr.size()) / log(2) + 1)))
        , _arr(_size, std::make_pair(0, 0))
{
    // Copying start array to the end of out tree
    for (int i = 0; i < arr.size(); ++i) {
        _arr[i + (_size + 1) / 2 - 1].first = arr[i];
    }

    // Updating other nodes in the tree
    for (int i = _size / 2 - 1; i >= 0 ; --i) {
        _arr[i].first = std::max(_arr[i * 2 + 1].first, _arr[i * 2 + 2].first);
    }
}



int SegmentTree::getMax(unsigned l, unsigned r)
{
    return getMax(l, r, 0, _num - 1, 0);
}



void SegmentTree::add(unsigned l, unsigned r, int value)
{
    add(l, r, 0, _num - 1, 0, value);
}



void SegmentTree::add(unsigned l, unsigned r, unsigned lb, unsigned rb, unsigned pos, int value)
{
    // If the node with 'pos' position has its interval
    // lying in requested segment, process it and return
    if (lb >= l && rb <= r) {
        _arr[pos].second += value;
        return;
    }

    // If it's interval doesn't intersects at all, return
    if (rb < l || lb > r) {
        return;
    }
    unsigned left = 2 * pos + 1;
    unsigned right = 2 * pos + 2;
    // Updating left and right nodes recursively
    add(l, r, lb, lb + (rb - lb + 1) / 2 - 1, left, value);
    add(l, r, lb + (rb - lb + 1) / 2, rb, 2 * pos + 2, value);
    // Maintaining max value in consistent state
    _arr[pos].first = std::max(_arr[left].first + _arr[left].second,
                               _arr[right].first + _arr[right].second);
}



int SegmentTree::getMax(unsigned l, unsigned r, unsigned lb, unsigned rb, unsigned pos)
{
    // If the node with 'pos' position has its interval
    // lying in requested segment, process it and return
    if (lb >= l && rb <= r) {
        return _arr[pos].first + _arr[pos].second;
    }

    // If it's interval doesn't intersects at all, return 0
    if (rb < l || lb > r) {
        return 0;
    }

    // Returning relevant value of maximum on a specified subsegment
    return std::max(getMax(l, r, lb, lb + (rb - lb + 1) / 2 - 1, 2 * pos + 1),
                    getMax(l, r, lb + (rb - lb + 1) / 2, rb, 2 * pos + 2)) + _arr[pos].second;
}