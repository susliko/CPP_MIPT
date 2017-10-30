#include <iostream>
#include <vector>

// function returns a vector with pattern entries into the specified string
std::vector<std::size_t> getEntries(std::string const & concat, unsigned tLen) {
    unsigned n = static_cast<unsigned>(concat.length());
    std::vector<std::size_t> z(n);    // z[i] stores z-function values for s[i]
    std::vector<std::size_t> entries; // stores indexes of substring entries std::size_to text

    std::size_t left = 0;
    std::size_t right = 0;
    for (std::size_t i = 1; i < n; ++i) {
        if (i <= right) {
            z[i] = std::min(right - i + 1, z[i - left]);
        }
        while (i + z[i] < n && concat[z[i]] == concat[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > right) {
            left = i;
            right = i + z[i] - 1;
        }
        if (z[i] == tLen) {
            entries.push_back(i - tLen - 1);
        }
    }
    return entries;
}



int main() {
    std::string t, s, concat;
    std::cin >> t >> s;
    concat = t + '#' + s;
    std::vector<std::size_t> entries = getEntries(concat, static_cast<unsigned>(t.length()));

    for (std::size_t i : entries) {
        std::cout << i << " ";
    }

    return 0;
}