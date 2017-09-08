#include <iostream>
#include <algorithm>
#include <fstream>


using std::ostream;
using std::istream;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::sort;



struct Conversation
{
    int b;
    int e;

    //----------------------------------------------------- ctors
    Conversation()
    {}
    Conversation(int b, int e) : b(b), e(e)
    {}

    //----------------------------------------------------- in/out operators
    friend istream & operator >> (istream &, Conversation &);
    friend ostream & operator << (ostream &, Conversation &);

};



struct ConversationComparator
{
    bool operator () (Conversation const &,
                      Conversation const &);
};



// returns the maximum number of conversations
int countResult(vector<Conversation> & arr);



/******************************************************************************/
int main() {

    vector<Conversation> arr;

    // getting the information about conversational applications
    while (!cin.eof()) {
        Conversation buf;
        cin >> buf;
        arr.push_back(buf);
    }


    cout << countResult(arr) << endl;

    return 0;
}



/******************************************************************************/
istream & operator >> (istream & is, Conversation & c)
{
    is >> c.b;
    is >> c.e;

    return is;
}



ostream & operator << (ostream & os, Conversation & c)
{
    os << "(" << c.b << ", " << c.e << ") ";
    return os;
}



bool ConversationComparator::operator()(Conversation const & c1,
                                        Conversation const & c2)
{
    return (c1.e < c2.e);
}



int countResult(vector<Conversation> & arr)
{
    
// sorting all applications by their end
    ConversationComparator comparator;
    sort(arr.begin(), arr.end(), comparator);


    int total = 1;
    int curr = 0;


// counting the result
    for (int j = 0; j < arr.size(); ++j) {
        if (arr[j].b >= arr[curr].e) {
            ++total;
            curr = j;
        }
    }

    return total;
}
