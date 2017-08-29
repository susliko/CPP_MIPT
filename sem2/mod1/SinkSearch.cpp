#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;


//                       "walk" function work
//
//  0 * * * * *   * * * * * *   * * j * *
//  * 1 * * * *   * * * * * *   * * j * *
//  * * 2 * * *   i i d i i i   * * d * *
//  * * * 3 * *   * * * * * *   * * j * *
//  * * * * 4 *   * * * * * *   * * j * *
//  * * * * * 5   * * * * * *   * * j * *
//     pic.1         pic.2        pic.3
//
//  "d" takes the number which corresponds to a diagonal cell(pic.1)
//
//  if "d" is still our variant, "j" starts to iterate horizontal line
// corresponding to "d" (pic.2)
//
//  if the "brake" method wasn't called "i" starts to iterate vertical line
// corresponding to "d" (pic.3)
//

void walk(vector<vector<int>> & table, vector<bool> & stillOption)
{
    int n = (unsigned) table.size();
    int d = 0;

    while (d < n) {
        if (!stillOption[d]) {
            ++d;
            continue;
        }
        bool checkVertical = true;

        for (int j = (d+1)%n; j != d; j = (j+1)%n) {
            if (table[d][j] == 0) {
                stillOption[j] = false;
            }
            else {
                stillOption[d] = false;
                checkVertical = false;
                break;
            }
        }

        if (checkVertical) {
            for (int i = 0; i < n; ++i) {
                if (i != d && table[i][d] == 0) {
                    stillOption[d] = false;
                    return;
                }
            }
        }
        ++d;
    }
}



int main() {

    // initialization
    unsigned n;
    cin >> n;
    vector<vector<int>> table(n, vector<int>(n, 0));
    vector<bool> stillOption (n, true);


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> table[i][j];
        }
    }

    // call of the main function
    walk(table, stillOption);


    bool success = false;

    // checking if there are any stock vertices
    for (bool b : stillOption) {
        if (b) success = true;
    }

    cout << ((success) ? "YES" : "NO");

    return 0;
}
