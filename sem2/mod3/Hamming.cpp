#include <climits>
#include <queue>
#include <iostream>
#include <map>


struct Edge {
    int from;
    int to;
    int capacity;
    int flow;
    int reverseIndex;
};



struct VertexInfo {
    int pattOrStr; //0 if pattern, 1 if str
    int index;

    friend bool operator<(const VertexInfo& first, const VertexInfo& second) {
        return (first.pattOrStr < second.pattOrStr) || ((first.pattOrStr == second.pattOrStr) &&
                                                        (first.index < second.index));
    }
};



class Network {
private:
    std::vector<std::vector<Edge>> edgesMatrix;
    std::vector<std::vector<int>> questionsInfo;
    std::vector<VertexInfo> numberOfQuestion;
    int hammingDistance;
    int numberOfVertices;
    int numberOfEdges;
    int source;
    int drain;
    std::string pattern;
    std::string str;

public:
    Network();
    void AddEdge(int, int);
    static Network BuildNetwork(std::string&, std::string&);
    bool BFS(std::vector<int>&);
    int DFS(std::vector<int>&, std::vector<int>&, int, int);
    int FindMaxFlow();
    void MinCutDFS(std::vector<int>&, int);
    void MinCut();
    std::string GetPattern();
    std::string GetString();
    int GetHammingDistance();
};


/*============================================================================*/
int main() {
  std::string pattern = "", str = "";
  std::cin >> str;
  std::cin >> pattern;

  Network net = Network::BuildNetwork(pattern, str);
  net.MinCut();

  std::cout << net.GetHammingDistance() << std::endl;
  std::cout << net.GetString() << std::endl;
  std::cout << net.GetPattern() << std::endl;
  return 0;
}



/*============================================================================*/
Network::Network(): numberOfVertices(2),
                    numberOfEdges(0),
                    source(0),
                    drain(1),
                    edgesMatrix(3000),
                    questionsInfo(2, std::vector<int>(3000, -1)),
                    numberOfQuestion(3000, {-1, -1}),
                    pattern(""),
                    str(""){
    numberOfQuestion[0] = {2, 2};
    numberOfQuestion[1] = {2, 2};
}

void Network::AddEdge(int from, int to) {
    Edge edge = {from, to, 1, 0, edgesMatrix[to].size()};
    Edge reverseEdge = {to, from, 1, 0, edgesMatrix[from].size()};
    edgesMatrix[from].push_back(edge);
    edgesMatrix[to].push_back(reverseEdge);
    numberOfEdges++;
}

Network Network::BuildNetwork(std::string &pattern, std::string &str) {
    Network network;
    network.hammingDistance = 0;
    network.pattern = pattern;
    network.str = str;
    int patternLength = (int) pattern.length();

    for (int strPosition = 0; strPosition < str.length() - pattern.length() + 1; strPosition++) {
        for (int pattPosition = 0; pattPosition < patternLength; pattPosition++) {

            if (pattern[pattPosition] == '1' && str[strPosition + pattPosition] == '0' ||
                pattern[pattPosition] == '0' && str[strPosition + pattPosition] == '1') {
                network.hammingDistance++;
            }

            if (pattern[pattPosition] == '?') {
                if (network.questionsInfo[0][pattPosition] == -1) {
                    network.numberOfVertices++;
                    VertexInfo temp = {0, pattPosition};
                    network.numberOfQuestion[network.numberOfVertices - 1] = temp;
                    network.questionsInfo[0][pattPosition] = network.numberOfVertices - 1;
                }
            }

            if (str[strPosition + pattPosition] == '?') {
                if (network.questionsInfo[1][strPosition + pattPosition] == -1) {
                    network.numberOfVertices++;
                    VertexInfo temp = {1, strPosition + pattPosition};
                    network.numberOfQuestion[network.numberOfVertices - 1] = temp;
                    network.questionsInfo[1][pattPosition + strPosition] = network.numberOfVertices - 1;
                }
            }

            if (pattern[pattPosition] == '?') {
                switch (str[strPosition + pattPosition]) {
                    case '0':
                        network.AddEdge(0, network.questionsInfo[0][pattPosition]);
                        break;
                    case '1':
                        network.AddEdge(network.questionsInfo[0][pattPosition], 1);
                        break;
                    case '?':
                        network.AddEdge(network.questionsInfo[0][pattPosition],
                                        network.questionsInfo[1][strPosition + pattPosition]);
                        break;
                }
            }
            if (str[strPosition + pattPosition] == '?') {
                switch (pattern[pattPosition]) {
                    case '0':
                        network.AddEdge(0, network.questionsInfo[1][strPosition + pattPosition]);
                        break;
                    case '1':
                        network.AddEdge(1, network.questionsInfo[1][strPosition + pattPosition]);
                        break;
                }
            }
        }
    }

    return network;
}

bool Network::BFS(std::vector<int>& distances) {
    for (int position = 0; position < numberOfVertices; position++) {
        distances[position] = -1;
    }

    std::queue<int> verticesQueue;
    verticesQueue.push(source);
    distances[source] = 0;

    int currentVertex;
    while (!verticesQueue.empty()) {
        currentVertex = verticesQueue.front();
        verticesQueue.pop();

        for (int position = 0; position < edgesMatrix[currentVertex].size(); position++) {

            Edge& edge = edgesMatrix[currentVertex][position];
            int vertex = edge.to;
            if (distances[vertex] == -1 && edge.flow < edge.capacity) {
                distances[vertex] = distances[currentVertex] + 1;
                verticesQueue.push(vertex);
            }
        }
    }

    return (distances[drain] != -1);
}

int Network::DFS(std::vector<int>& distances, std::vector<int>& nextVertex, int currentVertex, int minCapacity) {
    if (minCapacity == 0 || currentVertex == drain) {
        return minCapacity;
    }

    //int addFlow, newMinCapacity;
    for (int index = nextVertex[currentVertex]; index < edgesMatrix[currentVertex].size(); index++) {
        nextVertex[currentVertex]++;

        Edge& edge  = edgesMatrix[currentVertex][index];

        if (edge.capacity <= edge.flow) {
            continue;
        }

        int vertex = edge.to;
        if (distances[vertex] == distances[currentVertex] + 1) {
            int newMinCapacity = std::min(minCapacity, edge.capacity - edge.flow);
            int addFlow = DFS(distances, nextVertex, vertex, newMinCapacity);
            if (addFlow > 0) {
                edge.flow += addFlow;
                edgesMatrix[vertex][edge.reverseIndex].flow -= addFlow;
                return addFlow;
            }
        }
    }

    return 0;
}



int Network::FindMaxFlow() {
    int maxFlow = 0;
    std::vector<int> distances(numberOfVertices);
    std::vector<int> nextVertex(numberOfVertices);

    while (BFS(distances)) {
        for (int position = 0; position < numberOfVertices; position++) {
            nextVertex[position] = 0;
        }

        int currentFlow;
        do {
            currentFlow = DFS(distances, nextVertex, source, INT_MAX);
            maxFlow += currentFlow;
        } while (currentFlow != 0);
    }

    return maxFlow;
}



void Network::MinCutDFS(std::vector<int>& visited, int vertex) {
    visited[vertex] = 1;
    if (numberOfQuestion[vertex].pattOrStr == 0) {
        pattern[numberOfQuestion[vertex].index] = '0';
    }
    if (numberOfQuestion[vertex].pattOrStr == 1) {
        str[numberOfQuestion[vertex].index] = '0';
    }
    for (int index = 0; index < edgesMatrix[vertex].size(); index++) {
        Edge& edge = edgesMatrix[vertex][index];
        if (visited[edge.to] == 0 && edge.capacity > edge.flow) {
            MinCutDFS(visited, edge.to);
        }
    }
}



void Network::MinCut() {
    int maxFlow = FindMaxFlow();
    hammingDistance += maxFlow;
    std::vector<int> visited(numberOfVertices, 0);
    MinCutDFS(visited, source);
    for (int position = 0; position < pattern.length(); position++) {
        if (pattern[position] == '?') {
            pattern[position] = '1';
        }
    }
    for (int position = 0; position < str.length(); position++) {
        if (str[position] == '?') {
            str[position] = '1';
        }
    }
}



std::string Network::GetPattern() {
    return pattern;
}



std::string Network::GetString() {
    return str;
}



int Network::GetHammingDistance() {
    return hammingDistance;
}


