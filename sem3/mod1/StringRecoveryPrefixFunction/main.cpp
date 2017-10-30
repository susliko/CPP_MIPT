#include <iostream>
#include <vector>

// restores lexicographically minimal string by the specified values of prefix-function
std::string buildFromPrefix(std::vector<std::size_t> const & prefix, std::vector<char> const & alphabet) {
    std::size_t const ALPLEN = prefix.size();
    std::string resStr;
    resStr += alphabet[0];

    for (std::size_t i = 1; i < ALPLEN; ++i) {
        std::vector<char> used(ALPLEN, 0);

        if (prefix[i] != 0) {
            resStr += resStr[prefix[i] - 1];
        } else {
            std::size_t k = prefix[i - 1];
            while (k > 0) {
                used[resStr[k] - alphabet[0]] = 1;
                k = prefix[k - 1];
            }

            char c = alphabet[1];
            while (used[c - alphabet[0]]){
                ++c;
            };
            resStr += c;
        }
    }
    return resStr;
}



int main() {
    std::vector<char> alphabet;
    for (char i = 'a'; i <= 'z'; ++i) {
        alphabet.push_back(i);
    }

    std::size_t x;
    std::vector<std::size_t> prefix = {};
    while (std::cin >> x) {
        prefix.push_back(x);
    }

    std::cout << buildFromPrefix(prefix, alphabet);
    return 0;
}