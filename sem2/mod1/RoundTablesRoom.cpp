#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <queue>
#include <iomanip>


using std::abs;
using std::cin;
using std::pair;
using std::cout;
using std::endl;
using std::queue;
using std::vector;
using std::unordered_set;



// this struct represents a column with "x" and "y" coordinates
struct Column
{
    Column() {}
    Column(int x, int y) : x(x), y(y) {}
    int x, y;
};



class ListGraph {
public:
    explicit ListGraph( int _verticesCount );

    virtual void addEdge(int from, int to);

    virtual unsigned getVerticesCount() const { return verticesCount; }

    virtual void getNextVertices(int vertex, std::vector<int> &vertices) const;
    virtual void getPrevVertices(int vertex, std::vector<int> &vertices) const;

    void clearEdges();

private:
    unsigned verticesCount;
    vector<vector<int>> in;
    vector<vector<int>> out;
};



// adds edges between the columns by the specified table's diameter "D"
void fillGraph(double D, int R, vector<Column> const & columns, ListGraph & graph)
{
    unsigned n = columns.size();
    for(int i = 1; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            double distance = sqrt(pow(columns[i].x - columns[j].x, 2)
                                 + pow(columns[i].y - columns[j].y, 2)) - 2 * R;
            if (distance < D) {
                graph.addEdge(i, j);
            }
        }
    }
    for(int i = 1; i < n - 1; i++) {
        if(columns[i].x - columns[0].x - R < D)
            graph.addEdge(i, 0);
        if(columns[n - 1].x - columns[i].x - R < D)
            graph.addEdge(i, n - 1);
    }
}


// this BFS realization is taken from the task "B"
// it searches the number of shortest ways from "b" point to "e" point
int BFS(ListGraph const & graph, int b, int e)
{
    queue<int> q;
    vector<pair<int, int>> states (graph.getVerticesCount(), pair<int, int>(0,0));

    q.push(b);
    states[b].first = 1;
    states[b].second = 1;

    while(!q.empty()) {

        int cur = q.front();
        int depth = states[cur].first + 1;
        q.pop();

        vector<int> vertices;
        graph.getNextVertices(cur, vertices);

        for (int i : vertices) {
            if (states[i].first == 0) {
                states[i].first = depth;
                states[i].second = states[cur].second;
                q.push(i);
            } else
            if (states[i].first == depth) {
                states[i].second += states[cur].second;
            }
        }
    }
    return states[e].second;
}



// this function realizes the algorithm of table's diameter binary search
double binSearch(int XL, int XR, int R, ListGraph & graph,
                 vector<Column> const &columns)
{
    double a = 0;
    double b = XR - XL;
    unsigned N = columns.size();


    while(b - a > 5e-5){
        double c = (a + b) / 2;
        // preparing our graph for manipulations
        graph.clearEdges();
        fillGraph(c, R, columns, graph);


        /* 0 and N-1 points represent left and right borders respectively
         * if the number of shortest way between them is not zero, then there
         * is obviously a path between them */

        if(BFS(graph, 0, N - 1) > 0) b = c;
        else a = c;
    }
    return a;
}

/*
                                             /~\
                                            |oo ) - Did you hear that?
                                            _\=/_
                            ___            /  _  \
                           / ()\ - Bip.   //|/.\|\\
                         _|_____|_        \\ \_/  ||
                        | | === | |        \|\ /| ||
                        |_|  O  |_|        # _ _/ #
                         ||  O  ||          | | |
                         ||__*__||          | | |
                        |~ \___/ ~|         []|[]
                        /=\ /=\ /=\         | | |
________________________[_]_[_]_[_]________/_]_[_\_________________________
*/



/*============================================================================*/
int main()
{
    // initialization
    int XL, XR, R;
    unsigned N;

    cin >> XL >> XR >> R >> N;
    vector<Column> columns(N + 2, Column());
    ListGraph graph(N + 2);
    for (int i = 1; i <= N; ++i) {
        cin >> columns[i].x >> columns[i].y;
    }
    columns[0].x     = XL;
    columns[N + 1].x = XR;


    // printing the result
    cout << std::fixed << std::setprecision(3)
         << binSearch(XL, XR, R, graph, columns)<< endl;


    return 0;
}



/*============================================================================*/
ListGraph::ListGraph( int _verticesCount ) :
        verticesCount( _verticesCount ),
        in( verticesCount ),
        out( verticesCount )
{}



void ListGraph::addEdge(int from, int to)
{
    assert( from >= 0 && from < verticesCount );
    assert( to >= 0 && to < verticesCount );
    assert( from != to );


    in[to].push_back( from );
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



void ListGraph::clearEdges() {
    in.clear();
    out.clear();
    in.resize(verticesCount);
    out.resize(verticesCount);
}

