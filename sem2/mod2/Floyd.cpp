#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

typedef vector<vector<float> > floatMatrix;
typedef vector<float> floatLine;



void Floyd(floatMatrix & d)
{
    for (int k = 0; k < d.size(); ++k) {
        for (int i = 0; i < d.size(); ++i) {
            for (int j = 0; j < d.size(); ++j) {
                d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}



/*============================================================================*/
int main() {
    std::ifstream in;
    in.open("floyd.in");
    std::ofstream out;
    out.open("floyd.out");

    size_t vertex = 0;
    in >> vertex;
    floatMatrix edges(vertex, floatLine(vertex, 0));

    for (int i = 0; i < vertex; ++i) {
        for (int j = 0; j < vertex; ++j) {
            float a = 0;
            in >> a;
            edges[i][j] = a;
        }
    }

    Floyd(edges);

    for (int i = 0; i < vertex; ++i) {
        for (int j = 0; j < vertex; ++j) {
            out << edges[i][j] << " ";
        }
        out << '\n';
    }

    out.close();
    in.close();
    return 0;
}
