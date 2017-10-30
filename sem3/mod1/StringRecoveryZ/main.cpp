#include <iostream>
#include <vector>

// builds a lexicographically minimal string by the specified vector of Z-function values
std::string buildFromZ(std::vector<std::size_t> const & z, std::vector<char> const & alphabet) {
    std::size_t const ALPHLEN = alphabet.size();
    std::string resStr = ""; // result string
    std::size_t prefLen = 0;    // remaining length of currently found prefix
    std::size_t prevLen = 0;    // length of the last found prefix
    std::size_t prevBeg = 0;    // begin index of the last found prefix
    std::size_t curIndex;       // cell with this index stores the next value to copy

    std::vector<char> usedSymbols(ALPHLEN, 0); // [i] - element is 0 if ('a'+i) was not usedIndexes yet
    std::vector<std::size_t> usedIndexes;              // stores indexes which are used to calculate used  symbols

    for (std::size_t i = 0; i < z.size(); ++i) {
        if (z[i] == 0 && prefLen == 0) {
            if (i == 0) {
                resStr += alphabet[0]; // obviously, the first symbol should be the first symbol of an alphabet
            } else if (prevBeg + prevLen == i) {
                // if we have reached a cell with '0' value we should exclude some symbols from observed variants
                for (std::size_t n : usedIndexes) {
                    usedSymbols[resStr[n] - alphabet[0]] = 1;
                }
                std::size_t unusedInd = 1;
                while (usedSymbols[unusedInd]) {
                    ++unusedInd;
                }
                resStr += alphabet[unusedInd];

            } else {
                resStr += alphabet[1];
            }
        }

        if (prefLen == 0) {
            // bringing vectors back to the initial state
            usedSymbols.assign(ALPHLEN, 0);
            usedIndexes.clear();
        }

        if (z[i] > prefLen) {
            prevBeg = i;
            prefLen = prevLen = z[i];
            usedIndexes.push_back(z[i]);
            curIndex = 0;
        }

        if (z[i] == prefLen) {
            usedIndexes.push_back(z[i]);
        }

        if (prefLen > 0) {
            resStr += resStr[curIndex];
            ++curIndex;
            --prefLen;
        }
    }

    return resStr;
}



std::size_t main() {
    std::vector<char> alphabet;
    for (char i = 'a'; i <= 'z'; ++i) {
        alphabet.push_back(i);
    }

    std::vector<std::size_t> z = {};
    std::size_t c;
    while (std::cin >> c) {
        z.push_back(c);
    }
    z[0] = 0;

    std::cout << buildFromZ(z, alphabet);
    return 0;
}