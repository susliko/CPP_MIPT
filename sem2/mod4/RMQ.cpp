#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>


// Just returns logarithm with the base of two, rounded down
unsigned getLog2(double x)
{
    return static_cast<unsigned>(log(x) / log(2));
}



// Returns a pair of pointers to two minimum elements among two specified pairs
std::pair<int*, int*> getMinsPair(std::pair<int*, int*> & p1,
                                std::pair<int*, int*> & p2)
{
    std::vector<int*> nums = {p1.first, p1.second, p2.first, p2.second};
    auto cmp = [](int * a, int * b) { return *a < *b; };
    std::sort(nums.begin(), nums.end(), cmp);

    std::pair<int*, int*> res;
    res.first = nums[0];

    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] != res.first) {
            res.second = nums[i];
            break;
        }
    }

    return res;
};



class SparseTable
{
public:
    SparseTable(std::vector<int> & input)
            : _N(static_cast<unsigned>(input.size()))
            , _Nlog2(getLog2(_N) + 1)
            , _table(_Nlog2, std::vector<std::pair<int*, int*>>(_N, std::make_pair(nullptr, nullptr)))
            , _logs(_N + 1)
    {
        // Counting logarithms
        for (int i = 0; i < _N + 1; ++i) {
            _logs[i] = getLog2(i);
        }

        // Putting input values into '0' level of our sparse table
        for (int i = 0; i < _N; ++i) {
            _table[0][i].first = &input[i];
            _table[0][i].second = &input[i];
        }

        // Filling of the remaining part of the table
        for (int i = 1; i < _Nlog2; ++i) {
            for (int j = 0; j < _N - pow(2, i) + 1; ++j) {
                _table[i][j] = getMinsPair(_table[i - 1][j], _table[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int getMinimum(unsigned l, unsigned r)
    {
        unsigned k = _logs[r - l + 1];
        // Taking needed value from the table
        return *getMinsPair(_table[k][l], _table[k][r - (1 << k) + 1]).second;
    }

private:
    unsigned _N;
    unsigned _Nlog2;
    // Sparse table itself
    std::vector<std::vector<std::pair<int*, int*>>> _table;
    // Array of pre-counted logarithms
    std::vector<unsigned> _logs;
};



int main()
{
    unsigned N; // Length of the sequence
    unsigned M; // Number of requests
    std::cin >> N >> M;
    std::vector<int> input(N);
    // Input of the sequence
    for (int i = 0; i < N; ++i) {
        std::cin >> input[i];
    }

    SparseTable table(input);

    // Processing requests
    for (int i = 0; i < M; ++i) {
        unsigned l;
        unsigned r;
        std::cin >> l >> r;
        std::cout << table.getMinimum(l - 1, r - 1) << std::endl;
    }

    return 0;
}

