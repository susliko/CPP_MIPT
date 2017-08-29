#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <map>

using std::pair;
using std::cout;
using std::endl;
using std::cin;
using std::map;
using std::queue;
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
    void print();
    unsigned char getAt(int place) const;
private:
    unsigned long long data;
    int nullPlace;

    void setAt(int place, unsigned char value);
};



int countSwaps(Position const & pos)
{
    int res = 0;
    for (int i = 0; i < 9; ++i) {
        for (int j = i; j < 9; ++j) {
            if (pos.getAt(i) != '0' &&
                pos.getAt(j) != '0' &&
                pos.getAt(i) > pos.getAt(j))
            ++res;
        }
    }
    return res;
}



vector<char> BFS(Position const & start, Position const & end)
{
    queue<Position> q;
    map<ull, bool> u;
    map<ull, pair<ull, char>> p;

    q.push(start);
    u[start.getData()] = true;
    p[start.getData()] = pair<ull, char>(start.getData(), 'N');


    while (!q.empty()) {
        Position cur = q.front();
        q.pop();

        Position empty("");
        Position tmp = cur.Up();
        if (tmp.getData() != empty.getData() && !u[tmp.getData()]) {
            q.push(tmp);
            u[tmp.getData()] = true;
            p[tmp.getData()] = pair<ull, char>(cur.getData(), 'U');
            if (tmp.getData() == end.getData()) break;
        }
        tmp = cur.Down();
        if (tmp.getData() != empty.getData() && !u[tmp.getData()]) {
            q.push(tmp);
            u[tmp.getData()] = true;
            p[tmp.getData()] = pair<ull, char>(cur.getData(), 'D');
            if (tmp.getData() == end.getData()) break;
        }
        tmp = cur.Left();
        if (tmp.getData() != empty.getData() && !u[tmp.getData()]) {
            q.push(tmp);
            u[tmp.getData()] = true;
            p[tmp.getData()] = pair<ull, char>(cur.getData(), 'L');
            if (tmp.getData() == end.getData()) break;
        }
        tmp = cur.Right();
        if (tmp.getData() != empty.getData() && !u[tmp.getData()]) {
            q.push(tmp);
            u[tmp.getData()] = true;
            p[tmp.getData()] = pair<ull, char>(cur.getData(), 'R');
            if (tmp.getData() == end.getData()) break;
        }
    }


    vector<char> parents;

    if (!u[end.getData()]) return parents;

    ull pos = end.getData();

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
    in.open("puzzle.in");
    std::ofstream out;
    out.open("puzzle.out");

    std::string s = "";
    for (int i = 0; i < 9; ++i) {
        int a;
        in >> a;
        s += a + '0';
        s += " ";
    }


//    bool res = false;
    Position start(s);

    Position end("1 2 3 4 5 6 7 8 0");


//    if (countSwaps(start) % 2 == 0) {
//        res = true;
//    }
//
//    if (!res) {
//        out << -1;
//        return 0;
//    }

    vector<char> l = BFS(start, end);
    if (l.size() == 0) {
        out << -1;
        return 0;
    }
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
    for (int i = 0; i < 9; ++i) {
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
    data = (data & AntiMasks[place]) | (static_cast<long long>(value) << (place * 4));
}



unsigned char Position::getAt(int place) const
{
    return static_cast<unsigned char> ( (data & Masks[place]) >> (place * 4));
}



Position Position::Up() const
{
    if (nullPlace <= 2) return Position("");

    Position result(*this);
    unsigned char buf = getAt(nullPlace - 3);
    // Setting 0 above
    result.setAt(nullPlace - 3, 0);
    result.setAt(nullPlace, buf);
    result.nullPlace -= 3;
    return result;
}



Position Position::Down() const
{
    if (nullPlace >= 6) return Position("");

    Position result(*this);
    unsigned char buf = getAt(nullPlace + 3);
    // Setting 0 below
    result.setAt(nullPlace + 3, 0);
    result.setAt(nullPlace, buf);
    result.nullPlace += 3;
    return result;
}



Position Position::Left() const
{
    if (nullPlace % 3 == 0) return Position("");

    Position result(*this);
    unsigned char buf = getAt(nullPlace - 1);
    // Setting 0 left
    result.setAt(nullPlace - 1, 0);
    result.setAt(nullPlace, buf);
    result.nullPlace -= 1;
    return result;
}


Position Position::Right() const
{
    if (nullPlace % 3 == 2) return Position("");

    Position result(*this);
    unsigned char buf = getAt(nullPlace + 1);
    // Setting 0 right
    result.setAt(nullPlace + 1, 0);
    result.setAt(nullPlace, buf);
    result.nullPlace += 1;
    return result;
}



void Position::print() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << (int)getAt(i * 3 + j) << " ";
        }
        std::cout << std::endl;
    }
}

