#include <iostream>
#include <vector>

std::vector<int> f (bool b) {
    std::vector<int> result = {1, 2, 3};
    return result;
}


int main() {
    std::vector<int> v = f(true);
    return 0;
}