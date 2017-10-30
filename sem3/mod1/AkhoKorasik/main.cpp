#include <iostream>
#include <vector>


int const ALPHSIZE = 52; // Size of an alphabet. 26 symbols [a-z] and 26 [A-Z]. 


struct Vertex {
    int out[ALPHSIZE];    // Stores vertices indexes, connected by edges with current one
    int goes[ALPHSIZE];   // Stores indexes of vertices to go by the specified letter
    int suffixLink; // Index of the vertex with the biggest suffix to the current one
    int parent;     // Index of the parent vertex
    char parentSmb; // Symbol which leads from the parent to the current vertex
    bool isLeaf;    // Stores if the current vertex is a leaf
    std::vector<int> indexesOfSubpattern;
};



class AhoKorasikMachine {
public:
    // Constructor takes pattern and text and saves in local variables
    AhoKorasikMachine(std::string pattern, std::string text);
    // Returns a vector of subpattern begins
    std::vector<int> getNonMaskPatternsEnds();
    // Returns a vector of subpattern ends
    std::vector<int> getNonMaskPatternsBegs();
    // Adds a subpattern to the bor
    void addPattern(int, int, int);
    // Builds bor
    void buildBor();

    // Returns the index of node which is a suffix for the specified node
    int getSuffixLink(int);
    // Returns the node to go by the specified symbol
    int getLink(int, char);
    // Returns all the entries of the pattern into the text
    std::vector<int> process();
    
private:
    std::string pattern_;
    std::string text_;
    std::vector<Vertex> nodes_;
};


//==============================================================================================//
int main() {
    std::string pattern, text;
    std::cin >> pattern >> text;
    AhoKorasikMachine matchSearcher(pattern, text);
    std::vector<int> temp = matchSearcher.process();

    for (int i = 0; i < temp.size(); i++) {
        std::cout << temp[i] << " ";
    }
    return 0;
}
//==============================================================================================//



AhoKorasikMachine::AhoKorasikMachine(std::string pattern, std::string text)
        : nodes_(1)
        , pattern_(pattern)
        , text_(text)
{
    nodes_[0].parent = 0;
    for (int ind = 0; ind < ALPHSIZE; ind++) {
        nodes_[0].out[ind] = -1;
        nodes_[0].goes[ind] = -1;
    }
    nodes_[0].isLeaf = false;
    nodes_[0].parentSmb = -1;
    nodes_[0].suffixLink = 0;
}



std::vector<int> AhoKorasikMachine::getNonMaskPatternsEnds() {
    std::vector<int> ends;
    for (int pos = 0; pos < pattern_.length() - 1; pos++) {
        if (pattern_[pos + 1] == '?' && isalpha(pattern_[pos])) {
            ends.push_back(pos);
        }
    }
    if (isalpha(pattern_[pattern_.length() - 1])) {
        ends.push_back(static_cast<int>(pattern_.length() - 1));
    }
    return ends;
}



std::vector<int> AhoKorasikMachine::getNonMaskPatternsBegs() {
    std::vector<int> begs;
    if (isalpha(pattern_[0])) {
        begs.push_back(0);
    }
    for (int pos = 1; pos < pattern_.length(); pos++) {
        if (pattern_[pos - 1] == '?' && isalpha(pattern_[pos])) {
            begs.push_back(pos);
        }
    }
    return begs;
}



void AhoKorasikMachine::addPattern(int start, int end, int index) {
    int vert = 0;
    for (int pos = start; pos <= end; pos++) {
        char character = pattern_[pos] - 'a';
        if (nodes_[vert].out[character] == -1) {
            Vertex temp;
            temp.suffixLink = -1;
            temp.parentSmb = character;
            temp.isLeaf = false;
            temp.parent = vert;
            for (int ind = 0; ind < ALPHSIZE; ind++) {
                temp.out[ind] = -1;
                temp.goes[ind] = -1;
            }
            nodes_.push_back(temp);
            nodes_[vert].out[character] = static_cast<int>(nodes_.size() - 1);
        }
        vert = nodes_[vert].out[character];
    }
    nodes_[vert].isLeaf = true;
    nodes_[vert].indexesOfSubpattern.push_back(index);
}



void AhoKorasikMachine::buildBor() {
    std::vector<int> starts = getNonMaskPatternsBegs();
    std::vector<int> ends = getNonMaskPatternsEnds();

    for (int patt = 0; patt < starts.size(); patt++) {
        addPattern(starts[patt], ends[patt], patt);
    }
}



int AhoKorasikMachine::getSuffixLink(int nodeIndex) {
    if (nodes_[nodeIndex].suffixLink == -1) {
        if (nodes_[nodeIndex].parent == 0) {
            nodes_[nodeIndex].suffixLink = 0;
        } else {
            nodes_[nodeIndex].suffixLink = getLink(getSuffixLink(nodes_[nodeIndex].parent),
                                                   nodes_[nodeIndex].parentSmb);
        }
    }
    return nodes_[nodeIndex].suffixLink;
}



int AhoKorasikMachine::getLink(int node, char character) {
    if (nodes_[node].goes[character] == -1) {
        if (nodes_[node].out[character] != -1) {
            nodes_[node].goes[character] = nodes_[node].out[character];
        } else if (node == 0) {
            nodes_[node].goes[character] = 0;
        } else {
            nodes_[node].goes[character] = getLink(getSuffixLink(node), character);
        }
    }
    return nodes_[node].goes[character];
}



std::vector<int> AhoKorasikMachine::process() {
    buildBor();
    std::vector<int> ends = getNonMaskPatternsEnds();
    std::vector<int> starts = getNonMaskPatternsBegs();
    std::vector<int> entries(text_.length());
    int node = 0;
    for (int pos = 0; pos < text_.length(); pos++) {
        node = getLink(node, text_[pos] - 'a');
        int temp = node;
        do {
            if (nodes_[temp].isLeaf) {
                for (int index = 0; index < nodes_[temp].indexesOfSubpattern.size(); index++) {
                    int startIndex = pos - ends[nodes_[temp].indexesOfSubpattern[index]] +
                                     starts[nodes_[temp].indexesOfSubpattern[index]];
                    if ((startIndex - starts[nodes_[temp].indexesOfSubpattern[index]] >= 0) &&
                        (startIndex - starts[nodes_[temp].indexesOfSubpattern[index]] +
                                      pattern_.length() - 1 < text_.length())) {
                        ++entries[startIndex - starts[nodes_[temp].indexesOfSubpattern[index]]];
                    }
                }
            }
            temp = getSuffixLink(temp);
        } while (temp != 0);
    }
    std::vector<int> answer;
    for (int index = 0; index < entries.size(); index++) {
        if (entries[index] == starts.size()) {
            answer.push_back(index);
        }
    }
    return answer;
}
