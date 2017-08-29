#include <iostream>
#include <vector>
#include <cmath>


// Functor that realizes binary raising
class LCAFinder
{
public:
    LCAFinder(int N, std::vector<int> const relations,
              std::vector<std::vector<int> > const graph,
              unsigned long long a1, unsigned long long a2,
              unsigned long long x, unsigned long long y, unsigned long long z)
            : _N(N)
            , _log2N(static_cast<int>(log(N)/ log(2)) + 1)
            , _a1(a1)
            , _a2(a2)
            , _x(x)
            , _y(y)
            , _z(z)
            , _p(relations)
            , _d(static_cast<unsigned>(_N))
            , _dp(static_cast<unsigned>(_N), std::vector<int>(static_cast<unsigned>(_log2N), 0))
            , _graph(graph)
            , _used(static_cast<unsigned>(_N))
    {
        dfs(0);
    }

    // Returns Least Common Ancestor for two specified values
    int operator()(int a, int b);

    // Calculates next request of LCA
    std::pair<int, int> nextRequest(long long v);


private:
    // Usual dfs
    void dfs(int a);
private:
    int _N;
    int _log2N;
    unsigned long long _a1;
    unsigned long long _a2;
    unsigned long long _x;
    unsigned long long _y;
    unsigned long long _z;
    // Array of parents
    std::vector<int> const _p;
    // Array of distances
    std::vector<int> _d;
    // Dynamic's table
    std::vector<std::vector<int> > _dp;
    // List graph
    std::vector<std::vector<int> > const _graph;
    // An array for usage in 'dfs' function
    std::vector<char> _used;
};



/*================================================================================*/
int main()
{
    unsigned N;
    unsigned M;
    std::cin >> N >> M;
    std::vector<int> parents(N, 0);
    std::vector<std::vector<int> > graph(N, std::vector<int>());

    // Input of parents
    for (unsigned i = 1; i < N; ++i) {
        std::cin >> parents[i];
        graph[parents[i]].push_back(i);
    }

    int a1; int a2;
    std::cin >> a1 >> a2;
    int x; int y; int z;
    std::cin >> x >> y >> z;

    LCAFinder finder(N, parents, graph, a1, a2, x, y, z);

    int lastRes = finder(a1 % N, a2 % N);
    int res = lastRes;

    // Processing M requests
    for (unsigned i = 1; i < M; ++i) {
        std::pair<int, int> p = finder.nextRequest(lastRes);
        lastRes = finder(p.first, p.second);
        res += lastRes;
    }

    std::cout << res;

    return 0;
}
/*================================================================================*/


int LCAFinder::operator()(int a, int b)
{
    if (_d[a] > _d[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }

    for (int i = _log2N - 1; i >= 0; --i) {
        if (_d[b] - _d[a] >= (1 << i)) b = _dp[b][i];
    }

    if (a == b) {
        return a;
    }

    for (int i = _log2N - 1; i >= 0; --i) {
        if (_dp[a][i] != _dp[b][i]) {
            a = _dp[a][i];
            b = _dp[b][i];
        }
    }
    return _p[a];
}



void LCAFinder::dfs(int a)
{
    _used[a] = 0;

    _dp[a][0] = _p[a];

    for (int j = 1; j < _log2N - 1; ++j) {
            _dp[a][j] = _dp[_dp[a][j - 1]][j - 1];
    }

    for (int i : _graph[a]) {
        _d[i] = _d[a] + 1;
        dfs(i);
    }
}



std::pair<int, int> LCAFinder::nextRequest(long long v)
{
    _a1 = (_x * _a1 + _y * _a2 + _z) % _N;
    _a2 = (_x * _a2 + _y * _a1 + _z) % _N;
    return std::pair<int, int>((_a1 + v) % _N, _a2);
}


