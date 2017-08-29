#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <map>
#include <cmath>
#include <unordered_map>

using std::pair;
using std::cout;
using std::endl;
using std::cin;
using std::map;
using std::queue;
using std::priority_queue;
using std::vector;
using std::unordered_map;


typedef unsigned long long ull;


class Position
{
public:
    explicit Position(std::string const & source);
    Position Up() const;
    Position Down() const;
    Position Left() const;
    Position Right() const;

    unsigned long long getData() const {return data;}
    int getNullPlace() const { return nullPlace; }
    void print();
    unsigned char getAt(int place) const;
private:
    unsigned long long data;
    int nullPlace;

    void setAt(int place, unsigned char value);
};


typedef pair<Position, int> Pi;


struct Comparator
{
    bool operator()(Pi const & p1,
                    Pi const & p2)
    {
        return p1.second > p2.second;
    }
};



int countHeuristics(Position const & pos)
{
    int res = 0;

    for (int i = 0; i < 16; ++i) {
        unsigned char c = pos.getAt(i);
        int x = i / 4;
        int y = i % 4;
        int rx = 0;
        int ry = 0;
        if (c != 0) {
            rx = (c - 1) / 4;
            ry = (c - 1) % 4;
        }
        res += abs(x - rx) + abs(y - ry);
    }
    return res * 10;
}



bool isPossiblePos(Position const &pos)
{
    int inversions = 0;
    for(int i = 0; i < 16; i++)
        for(int j = i + 1; j < 16; j++)
            if(pos.getAt(i) != 0 &&
               pos.getAt(j) !=0 &&
               pos.getAt(i) > pos.getAt(j))
                inversions++;
    return (inversions % 2 == 0) == (pos.getNullPlace() / 4 % 2 == 1);
}



vector<char> Dijkstra(Position const &start, Position const &end)
{
    unordered_map<ull, pair<ull, char>> p;
    unordered_map<ull, int> d;
    priority_queue<Pi, vector<Pi>, Comparator> q;

    q.push(Pi(start, 0));
    d[start.getData()] = 0;
    p[start.getData()] = pair<ull, char>(start.getData(), 'N');

    while (true) {
        Position const cur = q.top().first;
        int dpth = d[q.top().first.getData()];
        q.pop();

        Position empty("");
        Position tmp = cur.Up();
        if (tmp.getData() != empty.getData() &&
            (p.find(tmp.getData()) == p.end())) {
            d[tmp.getData()] = dpth + 1;
            q.push(Pi(tmp, dpth + countHeuristics(tmp)));
            p[tmp.getData()] = pair<ull, char>(cur.getData(), 'D');
            if (tmp.getData() == end.getData()) break;
        }
        tmp = cur.Down();
        if (tmp.getData() != empty.getData() &&
            (p.find(tmp.getData()) == p.end())) {
            d[tmp.getData()] = dpth + 1;
            q.push(Pi(tmp, dpth + countHeuristics(tmp)));
            p[tmp.getData()] = pair<ull, char>(cur.getData(), 'U');
            if (tmp.getData() == end.getData()) break;
        }
        tmp = cur.Left();
        if (tmp.getData() != empty.getData() &&
            (p.find(tmp.getData()) == p.end())) {
            d[tmp.getData()] = dpth + 1;
            q.push(Pi(tmp, dpth + countHeuristics(tmp)));
            p[tmp.getData()] = pair<ull, char>(cur.getData(), 'R');
            if (tmp.getData() == end.getData()) break;
        }
        tmp = cur.Right();
        if (tmp.getData() != empty.getData() &&
            (p.find(tmp.getData()) == p.end())) {
            d[tmp.getData()] = dpth + 1;
            q.push(Pi(tmp, dpth + countHeuristics(tmp)));
            p[tmp.getData()] = pair<ull, char>(cur.getData(), 'L');
            if (tmp.getData() == end.getData()) break;
        }
    }


    vector<char> parents;

    ull pos = end.getData();
    if (p.find(pos) == p.end()) return parents;


    while (p[pos].second != 'N') {
        parents.push_back(p[pos].second);
        pos = p[pos].first;
    }
    return parents;
}



/*============================================================================*/
int main()
{
    std::ifstream in;
    in.open("input.txt");
    std::ofstream out;
    out.open("output.txt");

    std::string s = "";
    std::ostringstream oss;
    for (int i = 0; i < 16; ++i) {
        int a;
        in >> a;
        oss << a << ' ';
    }
    s = oss.str();

    Position start(s);

    Position end("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 0");
//    cout << "res " << countHeuristics(start);


    if (!isPossiblePos(start)) {
        out << -1;
        return 0;
    }
    vector<char> l = Dijkstra(start, end);

    out << l.size() << endl;
    for (int i = l.size() - 1; i >= 0; --i) {
        out << l[i];
    }

    in.close();
    out.close();

    return 0;
}

/*============================================================================*/


const unsigned long long AntiMasks[] = { 0xFFFFFFFFFFFFFFF0, 0xFFFFFFFFFFFFFF0F,
                                         0xFFFFFFFFFFFFF0FF, 0xFFFFFFFFFFFF0FFF,
                                         0xFFFFFFFFFFF0FFFF, 0xFFFFFFFFFF0FFFFF,
                                         0xFFFFFFFFF0FFFFFF, 0xFFFFFFFF0FFFFFFF,
                                         0xFFFFFFF0FFFFFFFF, 0xFFFFFF0FFFFFFFFF,
                                         0xFFFFF0FFFFFFFFFF, 0xFFFF0FFFFFFFFFFF,
                                         0xFFF0FFFFFFFFFFFF, 0xFF0FFFFFFFFFFFFF,
                                         0xF0FFFFFFFFFFFFFF, 0x0FFFFFFFFFFFFFFF,};

const unsigned long long Masks[] = { 0x000000000000000F, 0x00000000000000F0,
                                     0x0000000000000F00, 0x000000000000F000,
                                     0x00000000000F0000, 0x0000000000F00000,
                                     0x000000000F000000, 0x00000000F0000000,
                                     0x0000000F00000000, 0x000000F000000000,
                                     0x00000F0000000000, 0x0000F00000000000,
                                     0x000F000000000000, 0x00F0000000000000,
                                     0x0F00000000000000, 0xF000000000000000,};

Position::Position(std::string const & source) :
        data(0),
        nullPlace(0)
{
    std::istringstream stringStream(source);
    for (int i = 0; i < 16; ++i) {
        unsigned short value = 0;
        stringStream >> value;
        setAt(i, static_cast<unsigned char>(value));
        if (value == 0) {
            nullPlace = i;
        }
    }
}



void Position::setAt(int place, unsigned char value)
{
    data = (data & AntiMasks[place]) | (static_cast<long long>(value) << (place << 2));
}



unsigned char Position::getAt(int place) const
{
    return static_cast<unsigned char> ( (data & Masks[place]) >> (place << 2));
}



Position Position::Up() const
{
    if (nullPlace <= 3) return Position("");

    Position result(*this);
    unsigned char buf = getAt(nullPlace - 4);
    // Setting 0 above
    result.setAt(nullPlace - 4, 0);
    // Setting то, что было, вместо нуля
    result.setAt(nullPlace, buf);
    result.nullPlace -= 4;
    return result;
}



Position Position::Down() const
{
    if (nullPlace >= 13) return Position("");

    Position result(*this);
    unsigned char buf = getAt(nullPlace + 4);
    // Setting 0 below
    result.setAt(nullPlace + 4, 0);
    // Setting то, что было, вместо нуля
    result.setAt(nullPlace, buf);
    result.nullPlace += 4;
    return result;
}



Position Position::Left() const
{
    if (nullPlace % 4 == 0) return Position("");

    Position result(*this);
    unsigned char buf = getAt(nullPlace - 1);
    // Setting 0 left
    result.setAt(nullPlace - 1, 0);
    // Setting то, что было, вместо нуля
    result.setAt(nullPlace, buf);
    result.nullPlace -= 1;
    return result;
}



Position Position::Right() const
{
    if (nullPlace % 4 == 3) return Position("");

    Position result(*this);
    unsigned char buf = getAt(nullPlace + 1);
    // Setting 0 right
    result.setAt(nullPlace + 1, 0);
    // Setting то, что было, вместо нуля
    result.setAt(nullPlace, buf);
    result.nullPlace += 1;
    return result;
}



void Position::print() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << (int)getAt(i * 4 + j) << " ";
        }
        std::cout << std::endl;
    }
}

