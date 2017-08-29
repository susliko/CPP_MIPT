#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using std::swap;
using std::pair;
using std::vector;
using std::make_pair;


class DSU
{
public:
    DSU(int n) : n(n), p(n, 0), size(n, 0)
    {
        for (int i = 0; i < n; i++) {
            makeSet(i);
        }
    }

    void unionSets(int x, int y)
    {
        int xs = findSet(x);
        int ys = findSet(y);
        if (xs != ys) {
            if (size[xs] < size[ys])
                swap(xs, ys);
            p[ys] = xs;
            size[xs] += ys;
        }
    }

    int findSet(int x)
    {
        if (p[x] == x)
            return x;
        else
            return p[x] = findSet(p[x]);
    }
private:
    void makeSet(int x)
    {
        p[x] = x;
        size[x] = 1;
    }

    int n;
    vector<int> p;
    vector<int> size;

};



bool cmp(pair<std::pair<int, int>, int>& first,
         pair<std::pair<int, int>, int>& second) {
    return first.second < second.second;
}




int getMSTWeight(vector<pair<pair<int, int>, int> > &graph, int n, int m)
{
    int weight = 0;
    DSU dsu(n);
    sort(graph.begin(), graph.end(), cmp);

    for (int i = 0; i < m; ++i) {
        int first = dsu.findSet(graph[i].first.first);
        int second = dsu.findSet(graph[i].first.second);
        if (first != second) {
            dsu.unionSets(first, second);
            weight += graph[i].second;
        }
    }
    return weight;
}



int main() {
    std::ifstream in("kruskal.in");
    std::ofstream out("kruskal.out");

    int n, m;
    in >> n;
    in >> m;
    vector<pair<pair<int,int>, int> > graph;

    for (int i = 0; i < m; ++i) {
        int a, b, w;
        in >> a >> b >> w;
        graph.push_back(make_pair(make_pair(a-1, b-1), w));
    }

    out << getMSTWeight(graph, n, m);

    out.close();
    in.close();

    return 0;
}
