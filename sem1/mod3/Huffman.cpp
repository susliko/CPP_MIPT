#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <cmath>
#include "Huffman.h"

using namespace std;


struct Node
{
    char c;
    int freq;
    Node * left;
    Node * right;
    Node() {}
    Node(char c) : c(c), left(0), right(0) {}
    Node (Node * left, Node * right) : c(0), left(left), right(right)
    {}
    Node(char c, int freq, Node * left = 0, Node * right = 0)
            : right(right), c(c), left(left), freq(freq) {
    }
    ~Node()
    {
        delete left;
        delete right;
    }
};



struct nodeComparator
{
    bool operator ()(const Node * left, const Node * right) const
    {
        return left->freq < right->freq;
    }
};



void printTree(Node * root, int k = 0);


void buildTable(Node * root,
                vector<bool> & bits,
                map<char, vector<bool> >  & code);


void parseTree(Node * root, IOutputStream& compressed);
Node * unparseTree(IInputStream& compressed);



/******************************************************************************/

/******************************************************************************/
void Encode( IInputStream& original, IOutputStream& compressed )
{
    map<char, int> freqs;
    string file;
    size_t strPtr = 0;
    char c;

    // подсчёт
    while (original.Read(c)) {
        ++freqs[c];
        file += c;
    }



    // составление списка
    std::list<Node*> l;

    for (map<char, int>::iterator it = freqs.begin(); it != freqs.end() ; ++it ) {
        Node * node = new Node(it->first, it->second, 0, 0);
        l.push_back(node);
    }

    // построение дерева
    if (l.size() == 0) return;
    while(l.size() != 1) {
        l.sort(nodeComparator());
        Node * left = l.front();
        l.pop_front();
        Node * right = l.front();
        l.pop_front();
        Node * parent = new Node(0, left->freq + right->freq, left, right);
        l.push_back(parent);
    }


    Node * root = l.front();



    //построение кода Хаффмана
    vector<bool> bits;
    map<char, vector<bool> > code;
    buildTable(root, bits, code);



    //запись в файл
    int count = 0;
    char  buf = 0;


    size_t fileSize = file.size();
    for (int i = 0; i < 8; ++i) {
        char ch = (fileSize >> (i * 8));
        compressed.Write(ch);
    }

    int size = code.size();
    compressed.Write(size);
    compressed.Write(size >> 8);

    parseTree(root, compressed);


    while (strPtr < file.size()) {
        c = file[strPtr];
        ++strPtr;
        vector<bool> x = code[c];
        for (int n = 0; n < x.size(); ++n) {
            buf = buf | (x[n] << (7 - count));
            ++count;
            if (count == 8) {
                count = 0;
                compressed.Write(buf);
                buf = 0;
            }
        }
    }

    compressed.Write(buf);

    delete root;
}



void Decode( IInputStream& compressed, IOutputStream& original )
{
    size_t fileSize = 0;
    size_t filePtr = 0;
    for (int k = 0; k < 8; ++k) {
        char ch;
        compressed.Read(ch);
        if (ch > 0) {fileSize += pow(256, k) * ch;}
        else if (ch < 0) fileSize += pow(256, k) * (256 + ch);
    }



    Node * root = unparseTree(compressed);
    Node * node = root;
    if (!root) return;

    //построение кода Хаффмана
    vector<bool> bits;
    map<char, vector<bool> > code;
    buildTable(root, bits, code);


    int count = 0;
    char c;
    char buf;
    compressed.Read(c);

    while(filePtr < fileSize)
    {
        bool b = c & (1 << (7 - count++) );
        if (b) node = node->right;
        else node = node->left;
        if (!node) return;
        if (!node->left && !node->right) {
            original.Write(node->c);
            buf = node->c;
            ++filePtr;
            node = root;
        }
        if (count == 8) {
            count = 0;
            compressed.Read(c);
        }
    }

    delete root;
}



void buildTable(Node * root,
                vector<bool> & bits,
                map<char, vector<bool> > & code)
{
    if (!root) return;
    if (!root->left && !root->right) {
        code[root->c] = bits;
    }

    if (root->left) {
        bits.push_back(0);
        buildTable(root->left, bits, code);
    }

    if (root->right) {
        bits.push_back(1);
        buildTable(root->right, bits, code);
    }
    bits.pop_back();
}



void printTree(Node * root, int k)
{
    if (!root) return;
    printTree(root->left, k + 3);
    for (int i = 0; i < k; ++i) {
        cout << "  ";
    }
    if (!root->left && !root->right) {
        cout << root->freq << " (" << (int)root->c << ")" << endl;
    }
    else cout << root->freq << endl;
    printTree(root->right, k + 3);
}



void parseTree(Node * root, IOutputStream& compressed)
{
    if (!root) return;
    parseTree(root->left, compressed);
    parseTree(root->right, compressed);
    if (!root->left && !root->right) {
        compressed.Write('1');
        compressed.Write(root->c);
    } else {
        compressed.Write('0');
    }
}



Node * unparseTree(IInputStream& compressed)
{
    char charSize;
    int intSize;
    compressed.Read(charSize);
    intSize = (unsigned char)charSize;
    compressed.Read(charSize);
    intSize += (int)((unsigned char)charSize) << 8;

//    cout << "alphabet size " << intSize << endl;
    stack<Node *> s;
    int currSize = 0;
    char c;

    while (currSize < intSize|| s.size() > 1) {
        compressed.Read(c);
        if (c == '1') {
            compressed.Read(c);
            ++currSize;
            Node * newNode = new Node(c);
            s.push(newNode);
        } else if (c == '0'){
            Node * node1 = s.top();
            s.pop();
            Node * node2 = s.top();
            s.pop();

            Node * newNode = new Node(node2, node1);
            s.push(newNode);
        }
    }
    Node * root;
    if (!s.empty()) root = s.top();
    s.pop();
    return root;
}

