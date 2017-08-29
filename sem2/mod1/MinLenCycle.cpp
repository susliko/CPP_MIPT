#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <queue>

using std::unordered_set;
using std::vector;
using std::queue;
using std::cout;
using std::endl;
using std::pair;
using std::cin;



class SetGraph {
public:
    explicit SetGraph(unsigned _verticesCount);

    virtual void addEdge(int from, int to);

    virtual unsigned getVerticesCount() const { return verticesCount; }

    virtual void getNextVertices(int vertex, std::vector<int> &vertices) const;
    virtual void getPrevVertices(int vertex, std::vector<int> &vertices) const;

private:
    unsigned verticesCount;
    vector<unordered_set<int>> table;
};



// BFS-based function, returns the length of the first found cycle
int searchCycle(SetGraph const &graph, int b)
{
    // "q" is a service queue for BFS
    queue<int> q;
    
    // "used[i]" stores "true" if vertex "i" is "grey" or "black" now
    vector<bool> used(graph.getVerticesCount(), false);
    
    // "depths[i]" stores the depth of first discovering for vertex "i"
    vector<int> depths(graph.getVerticesCount(), 0);
    
    // configuring parameters for the start vertex
    q.push(b);
    used[b] = true;
    depths[b] = 0;

    while(!q.empty()) {

        // taking front vertex from the queue
        int cur = q.front();
        int depth = depths[cur] + 1;
        q.pop();

        vector<int> vertices;
        graph.getNextVertices(cur, vertices);

        // iterating over the neighbours of the "cur" vertex
        for (int i : vertices) {
            if (used[i] == true && depths[i] >= depth - 1) {
                int len = depth + depths[i];
                return len ;
            }
            else if (!used[i]) {
                q.push(i);
                used[i] = true;
                depths[i] = depth;
            }
        }


    }
    return INFINITY;
}



/*============================================================================*/
int main()
{
    // input
    int points, edges;
    scanf("%d%d",&points,&edges);
    SetGraph graph(points);

    for (int i = 0; i < edges; ++i) {
        int b, e;
        scanf("%d%d",&b,&e);
        graph.addEdge(b, e);
    }

    // setting "minLen" value higher than really possible
    int minLen = points + 1;

    // running the search of cycles from every vertex
    for (int i = 0; i < graph.getVerticesCount(); ++i) {
        int len = searchCycle(graph, i);
        if (minLen > len) minLen = len;
    }

    // if "minLen" value hasn't changed there are no cycles in the graph
    if (minLen == points + 1) minLen = -1;
    
    // printing of the result
    cout  << minLen;

    return 0;
}


/*============================================================================*/
SetGraph::SetGraph(unsigned _verticesCount) :
        verticesCount(_verticesCount),
        table(_verticesCount)
{}



void SetGraph::addEdge(int from, int to)
{
    assert( from >= 0 && from < verticesCount );
    assert( to >= 0 && to < verticesCount );
    assert( from != to );

    assert( table[from].find(to) == table[from].end() );
    assert( table[to].find(from) == table[to].end() );


    table[from].insert(to);
    table[to].insert(from);
}



void SetGraph::getNextVertices(int vertex, std::vector<int> &vertices) const
{
    assert( vertex < verticesCount);

    for (unordered_set<int>::const_iterator it = table[vertex].begin();
         it !=  table[vertex].end();
         ++it)
    {
        vertices.push_back(*it);
    }
}



void SetGraph::getPrevVertices(int vertex, std::vector<int> &vertices) const
{
    assert( vertex < verticesCount);

    for (int i = 0; i < verticesCount; ++i) {
        if (table[i].find(vertex) != table[i].end()) {
            vertices.push_back(i);
        }
    }
}
