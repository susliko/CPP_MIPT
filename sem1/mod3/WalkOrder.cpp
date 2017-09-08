#include <iostream>
using std::cout;
using std::cin;


//template <typename T>
class BST
{
public:
    //====================================================== ctor, copy, move
    // default constructor
    BST             ();
    // copy constructor
    BST             (BST const &);
    // assignment operator
    BST& operator = (BST const &);
    // destructor
    ~BST            ();

    //====================================================== methods
    // returns "true" if value exists in the tree
    bool contains(int const &) const ;
    // adds a new node
    void insert  (int const &);
    // returns "true" if value was found and successfully deleted
    bool remove  (int const &);
    // deleting all nodes
    struct Node;
    void clear(Node * node);

    void inorderPrint(Node * node);
    void preorderPrint(Node * node);
    void postorderPrint(Node * node);

    Node * root;      // root node
protected:
    size_t count; // total number of nodes

};



//template <typename T>
struct BST::Node {
    Node * left_;   // left node
    Node * right_;  // right node
    Node * parent_; // parent node
    int value_;       // stored value

    //------------------------------------------------ node: construction
    Node();
    Node(int const &,
         Node * left,
         Node * right,
         Node * parent);
    //------------------------------------------------ node: deep copy
    //	Make a deep copy of all nodes.
    static Node * copy(Node *, Node *);

};
/******************************************************************************/
int main() {
    BST bst;
    int n, k;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> k;
        bst.insert(k);
    }

    bst.inorderPrint(bst.root);
    return 0;
}

/******************************************************************************/
BST::Node::Node() {}



//template <typename T>
BST::Node::Node(int const & value,
                Node * left   = nullptr,
                Node * right  = nullptr,
                Node * parent = nullptr)
        : value_(value), left_(left), right_(right), parent_(parent) {}


//template <typename T>
BST::Node * BST::Node::copy(Node * node, Node * parent = nullptr)
{
    if (!node) {
        return nullptr;
    } else {
        Node* newNode = new Node;
        newNode->value_ = node->value_;
        newNode->parent_ = node->parent_;
        copy(node->left_, newNode);
        copy(node->right_, newNode);
        return newNode;
    }
}


//============================================================================//
BST::BST() : root(nullptr), count(0) {}



//template <typename T>
BST::BST(BST const &bst) : root(BST::Node::copy(bst.root)), count(bst.count) {}



BST& BST::operator = (BST const & bst)
{
    this->clear(root);
    this->root = BST::Node::copy(bst.root);
    this->count = bst.count;
    return *this;
}



BST::~BST()
{
    clear(root);
}



//template <typename T>
void BST::clear(Node * node)
{
    if (node == nullptr) return;
    clear(node->left_);
    node->right_;
    delete node;
}



//template <typename T>
void BST::insert(int const & value)
{
    Node * parent = nullptr;
    Node * node = root;

    while (node != nullptr) {
        parent = node;
        if (value < node->value_) {
            node = node->left_;
        } else  {
            node = node->right_;
        }
    }

    Node * newNode = new Node(value, nullptr, nullptr, parent);

    if (parent == nullptr) {
        root = newNode;
    } else if (newNode->value_ < parent->value_) {
        parent->left_ = newNode;
    } else {
        parent->right_ = newNode;
    }
}



//template <typename T>
void BST::inorderPrint(Node * node)
{
    if (node != nullptr) {
        inorderPrint(node->left_);
        cout << node->value_ << " ";
        inorderPrint(node->right_);
    }
}



void BST::preorderPrint(Node *node){
    if (node != nullptr) {
        cout << node->value_ << " ";
        preorderPrint(node->left_);
        preorderPrint(node->right_);
    }
}



void BST::postorderPrint(Node *node){
    if (node != nullptr) {
        postorderPrint(node->left_);
        postorderPrint(node->right_);
        cout << node->value_ << " ";
    }
}


