#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;


struct Edge
{
    Edge(int a, int b, int weight) :
            a(a), b(b), weight(weight)
    {}
    int a;
    int b;
    int weight;
};



bool Ford(vector<Edge> & edges, size_t currencies)
{
    vector<double> d(currencies, 0);
    d[0] = 1;

    for (int i = 0; i < currencies - 1; ++i) {
        bool relaxed = false;
        for (Edge const & edge : edges) {
            if (d[edge.b] < d[edge.a] * edge.weight) {
                d[edge.b] = d[edge.a] * edge.weight;
                relaxed = true;
            }
        }
        if (!relaxed) break;
    }

    for (Edge const & edge : edges) {
        if (d[edge.a] < d[edge.b] * edge.weight) {
            return true;
        }
    }

    return false;
}


/*============================================================================*/
int main() {

    size_t currencies;
    cin >> currencies;
    vector<Edge> edges;

    for (int i = 0; i < currencies; ++i) {
        for (int j = 0; j < currencies; ++j) {
            if (i != j) {
                double weight;
                cin >> weight;
                edges.push_back(Edge(i, j, weight));
            }
        }
    }

    cout << (Ford(edges, currencies) ? "YES" : "NO");

    return 0;
}
