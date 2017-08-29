#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <queue>
#include <stack>


using std::abs;
using std::cin;
using std::pair;
using std::cout;
using std::endl;
using std::stack;
using std::queue;
using std::vector;
using std::unordered_set;



class ListGraph {
public:
    explicit ListGraph(unsigned _verticesCount);

    virtual void addEdge(int from, int to);

    virtual unsigned getVerticesCount() const { return verticesCount; }

    virtual void getNextVertices(int vertex, std::vector<int> &vertices) const;
    virtual void getPrevVertices(int vertex, std::vector<int> &vertices) const;

private:
    unsigned verticesCount;
    vector<vector<int>> in;
    vector<vector<int>> out;
};



// Tarjan algorithm implementation
void dfs(int u, ListGraph & graph, vector<int> & components, int & time,
         vector<bool> & visited, vector<int> & lowLink,
         stack<int> & st, int & compNum) {

    // setting needed parameters for "u" point
    lowLink[u] = time++;
    visited[u] = true;
    st.push(u);
    bool isComponentRoot = true;

    vector<int> vertices;
    graph.getNextVertices(u, vertices);

    // visiting all neighbours of the current vertex "u"
    for (int v : vertices) {
        // if the neighbour wasn't visited, call dfs from him
        if (!visited[v])
            dfs(v, graph, components, time, visited, lowLink, st, compNum);
        // if this condition is true, we have found a SCC
        if (lowLink[u] > lowLink[v]) {
            lowLink[u] = lowLink[v];
            isComponentRoot = false;
        }
    }

    // discovering all the points which are in this SCC
    if (isComponentRoot) {
        while (true) {
            int x = st.top();
            st.pop();
            components[x] = compNum;
            lowLink[x] = INFINITY;
            if (x == u)
                break;
        }
        ++compNum;
    }
}



// this function discovers the components of strong connection
void Tarjan(ListGraph &graph, vector<int> &components, int &compNum) {
    int time = 0;
    stack<int> st;
    int n = graph.getVerticesCount();
    vector<bool> visited(n);
    vector<int> lowLink(n);

    // call of "bfs" from every unvisited point
    for (int u = 0; u < n; u++) {
        if (!visited[u])
        {
            dfs(u, graph, components, time, visited, lowLink, st, compNum);
        }
    }
}



int getResult(int compNum, int points, ListGraph & graph, vector<int> components)
{
    ListGraph conGraph(compNum);

    // creating condensed graph
    for (int i = 0; i < points; ++i) {
        vector<int> vertices;
        graph.getNextVertices(i, vertices);
        for (int j : vertices) {
            if (components[i] != components[j]) {
                conGraph.addEdge(components[i], components[j]);
            }
        }
    }


    int begs = 0, ends = 0;

    // counting begin and end points
    for (int j = 0; j < conGraph.getVerticesCount(); ++j) {
        vector<int> vertices;
        conGraph.getNextVertices(j, vertices);
        if (vertices.size() == 0) {
            ++ends;
        }
        conGraph.getPrevVertices(j, vertices);
        if (vertices.size() == 0) {
            ++begs;
        }
    }

    // calculating result
    int res = std::max(begs, ends);
    if (compNum == 1) res = 0;

    return res;
}



/*============================================================================*/
int main()
{
    int points,
        edges;
    cin >> points;
    cin >> edges;

    ListGraph graph(points);
    for (int i = 0; i < edges; ++i) {
        int b,
            e;
        cin >> b;
        cin >> e;
        graph.addEdge(b - 1, e - 1);
    }
    vector<int> components(points);
    int compNum = 0;


    Tarjan(graph, components, compNum);

    int res = getResult(compNum, points, graph, components);

    cout << res;

}



/*============================================================================*/
ListGraph::ListGraph(unsigned _verticesCount) :
        verticesCount( _verticesCount ),
        in( verticesCount ),
        out( verticesCount )
{}



void ListGraph::addEdge(int from, int to)
{
    in[to].push_back( from );
    out[from].push_back( to );
}



void ListGraph::getNextVertices(int vertex, std::vector<int> &vertices) const
{
    vertices = out[vertex];
}



void ListGraph::getPrevVertices(int vertex, std::vector<int> &vertices) const
{
    vertices = in[vertex];
}

