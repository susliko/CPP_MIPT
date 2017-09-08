#include <iostream>
#include <algorithm>


using std::swap;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::max;



class Graph
{
public:
// Constructs the graph with "size" vertex
    Graph(unsigned size);

// Adds new edge to the graph
    void add    (int b, int e);

// Calculates maximal distances from every vertex to the top
    void dfsUp  (int cur, int par);

// Calculates maximal distances from every vertex to the bottom
    void dfsDown(int cur, int par);

// Calls "dfsUp" and "dfsDown"
    void calcResult ();

// Returns the maximal distance for the specified vertex
    int  getMaxDistance(int i);

private:
    vector<vector<int>> vertex; // Stores all vertex with all neighbour vertex
    vector<int> dpDown;         // Stores maximal distances to the bottom
    vector<int> dpUp;           // Stores maximal distances to the top
};



/******************************************************************************/
int main() {

    unsigned size;
    cin >> size;
    Graph graph(size);

    for (int i = 0; i < size - 1; i++) {
        int b, e;
        cin >> b >> e;
        graph.add(b, e);
    }


    graph.calcResult();

    for (int i = 0; i < size; ++i) {
        cout << graph.getMaxDistance(i) << endl;
    }


    return 0;
}
/******************************************************************************/



Graph::Graph(unsigned size) : vertex(size), dpDown(size), dpUp(size)
{}



void Graph::add(int b, int e) {
    vertex[b].push_back(e);
    vertex[e].push_back(b);
}



void Graph::dfsUp(int cur, int par) {

    int m1Value = -1,
        m1Index = -1,
        m2Value = -1,
        m2Index = -1;

    for (int v : vertex[cur]) {

        if (v == par) continue;

        if (dpDown[v] + 1 >= m1Value) {
            swap(m1Value, m2Value);
            swap(m1Index, m2Index);
            m1Value = dpDown[v] + 1;
            m1Index = v;
        } else if (dpDown[v] + 1 >= m2Value) {
            m2Value = dpDown[v] + 1;
            m2Index = v;
        }
    }

    for (int v : vertex[cur]) {
        if (v == par) {
            continue;
        }
        if (v == m1Index) {
            dpUp[v] = max(dpUp[cur], m2Value) + 1;
        } else {
            dpUp[v] = max(dpUp[cur], m1Value) + 1;
        }
        dfsUp(v, cur);
    }
}



void Graph::dfsDown(int cur, int par) {

    for (int v : vertex[cur]) {

        if (v == par) continue;

        dfsDown(v, cur);

        dpDown[cur] = max(dpDown[cur], dpDown[v] + 1);
    }
}



void Graph::calcResult() {
    dfsDown(0, -1);
    dfsUp  (0, -1);
}



int Graph::getMaxDistance(int i) {
    return max(dpDown[i], dpUp[i]);
}
