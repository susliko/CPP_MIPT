#include <iostream>
#include <vector>


using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;




class HashTable
{
private:
    // constants for calculating samples
    const float c1 = 0.5;
    const float c2 = 0.5;


    // struct describing elements of the table
    struct Node
    {
        bool   deleted;
        string value;

        Node() : deleted(false)
        {}
        Node (string s) : value(s),  deleted(false)
        {}
    };


    unsigned     size;     // stores the size of the table
    int          currSize; // stores the current size of the table
    double       alpha;    // stores the value of fullness coefficient
    double const maxAlpha; // stores the maximum possible value for 'alpha'

    vector<Node*> array;   // table itself


    // increases the 'array' size *2 and copies reindexes all elements
    void reHash();

    // calculates the index by the specified string
    int indexCalc (string) const;


public:
    HashTable();
    ~HashTable();

    void print() const; // prints only filled fields

    // adds the specified string to the table
    bool add     (string);

    // removes the specified string from the table if it presents
    bool remove  (string);

    // returns 'true' if the specified string presents in the table
    bool contains(string) const;
};



/******************************************************************************/
int main()
{
    HashTable hashTable;

    while (!cin.eof()) {

        char   command;
        string str;
        bool   isOK;

        cin >> command;
        cin >> str;

        if (str.empty()) break;

        if (command == '+') {
            isOK = hashTable.add(str);
        } else if (command == '-') {
            isOK = hashTable.remove(str);
        } else if (command == '?') {
            isOK = hashTable.contains(str);
        }


        cout << ((isOK) ? "OK" : "FAIL") << endl;
        
    }
    return 0;
}



/******************************************************************************/
HashTable::HashTable() : size(8), maxAlpha(3.0/4.0),
                         alpha(0), currSize(0)
{
    array.assign(size, nullptr);
}



HashTable::~HashTable()
{
    for (int i = 0; i < size; ++i) {
        if (array[i]) delete array[i];
    }
}



bool HashTable::add(string key)
{
    if (contains(key)) return false;

    int    index = indexCalc(key);
    bool success = false;
    int   sample = 0;

    while (sample < size) {
        index = (index + sample) % size;

        if (array[index] == nullptr) {
            success = true;
            array[index] = new Node(key);
        } else if (array[index]->deleted) {
            success = true;
            array[index]->value = key;
            array[index]->deleted = false;
        }

        if (success) {
            ++currSize;
            alpha = (double) currSize/size;
            if (alpha >= maxAlpha) {
                reHash();
            }
            return true;
        }
        ++sample;
    }
    return false;
}



bool HashTable::remove(string key)
{
    int sample = 0;
    int index = indexCalc(key);

    if (!contains(key))
        return false;

    while (sample < array.size()) {
        index = (index + sample) % size;

        if (array[index]->value == key && !array[index]->deleted) {
            array[index]->deleted = true;
            --currSize;
            alpha = (double) currSize/size;
            break;
        }
        ++sample;
    }

    return true;
}



bool HashTable::contains(string key) const
{
    int sample  = 0;
    int index   = indexCalc(key);
    Node * node = array[index];

    while (node && sample < size) {

        if (!node->deleted && node->value.compare(key) == 0) {
            return true;
        }

        ++sample;
        index = (index + sample) % size;
        node  = array[index];
    }

    return false;
}



void HashTable::reHash()
{
    vector<Node*> oldArray = array;

    size *= 2;
    array.assign(size, nullptr);
    currSize = 0;

    for (size_t i = 0; i < oldArray.size(); ++i) {
        if (oldArray[i] != nullptr && !oldArray[i]->deleted) {
            add(oldArray[i]->value);
            delete oldArray[i];
        }
    }
}



int HashTable::indexCalc(string key) const
{
    int index = 0;
    int const a = 127;

    for (size_t i = 0; i < key.length(); ++i) {
        index = (index + a * key[i]) % size;
    }

    return index;
}



void HashTable::print() const
{
    cout << "size : " << size << " alpha : " << alpha << endl;
    for (int i = 0; i < size; ++i) {
        if (array[i])
            cout << "i=" << i << " " << array[i]->value << " deleted : " << array[i]->deleted << endl;
    }
}

