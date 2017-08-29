#include <algorithm>
#include <iostream>
#include <assert.h>
#include <queue>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::pair;


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



int BFS(ListGraph const & graph, int b, int e)
{
    queue<int> q;
    // "states[i].first" stores the minimal depth of the "i" vertex
    // "states[i].second" stores number of the shortest paths into "i" vertex
    vector<pair<int, int>> states(graph.getVerticesCount(), pair<int,int>(0,0));

    // initializing parameters for the start vertex
    q.push(b);
    states[b].first = 1;
    states[b].second = 1;

    while(!q.empty()) {

        // getting front element from the queue
        int cur = q.front();
        int depth = states[cur].first + 1;
        q.pop();

        vector<int> vertices;
        graph.getNextVertices(cur, vertices);

        // iterating all current vertex's neighbours
        for (int i : vertices) {
            // if "i" is still unvisited, push it to the queue
            if (states[i].first == 0) {
                states[i].first = depth;
                states[i].second = states[cur].second;
                q.push(i);
            // else if its depth equals to "depth", increase the number of paths
            } else
            if (states[i].first == depth) {
                states[i].second += states[cur].second;
            }
        }
    }
    return states[e].second;
}



/******************************************************************************/
int main()
{
    // input
    unsigned points, edges;
    cin >> points >> edges;
    ListGraph graph(points);
    for (int i = 0; i < edges; ++i) {
        int b, e;
        cin >> b >> e;
        graph.addEdge(b, e);
    }

    int b, e;
    cin >> b >> e;
    
    cout << BFS(graph, b, e) << endl;
}


/******************************************************************************/
ListGraph::ListGraph(unsigned _verticesCount ) :
        verticesCount( _verticesCount ),
        in( verticesCount ),
        out( verticesCount )
{}



void ListGraph::addEdge(int from, int to)
{
    assert(from >= 0 && from < verticesCount);
    assert(to >= 0 && to < verticesCount);
    assert(from != to);

    assert(std::find( in[to].begin(), in[to].end(), from ) == in[to].end());

    in[to].push_back(from);
    in[from].push_back(to);
    out[from].push_back(to);
    out[to].push_back(from);

}



void ListGraph::getNextVertices(int vertex, std::vector<int> &vertices) const
{
    assert( vertex < verticesCount);
    vertices = out[vertex];
}



void ListGraph::getPrevVertices(int vertex, std::vector<int> &vertices) const
{
    assert( vertex < verticesCount);
    vertices = in[vertex];
}
