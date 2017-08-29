#include <iostream>
#include <queue>


using std::cout;
using std::cin;
using std::queue;
using std::string;



//============================================================================//
class Treap
{
private:
    struct Node {
        Node * left_;     // left node
        Node * right_;    // right node
        Node * parent_;   // parent node
        int    key_;      // stored value
        int    priority_; // stored priority
        int    count_;    // number of nodes in a subtree
        string value_;    // stored string

        //------------------------------------------------ node: construction
        Node();
        Node(int const,
             int const,
             Node * left,
             Node * right,
             Node * parent,
             string);

        int getCount();
        void fixCount();
    };

    Node * root;  // root node
    size_t count; // total number of nodes

private:
    // splits the current tree by the specified key
    void split(Node *, int, Node * &, Node * &);
    // merges two trees
    Node * merge(Node *, Node *);

public:
    //====================================================== ctor
    // default constructor
    Treap();
    // destructor
    ~Treap();

    //====================================================== methods
    // adds a new node
    void insert  (int const, int const);
    // returns "true" if value was found and successfully deleted
    bool remove  (int const);
    // returns tree's height
    int getHeight(Node *);
    // deletes all nodes
    void clear(Node *);
    // returns root node
    Node * getRoot();
    // returns count
    size_t getCount();

    void preorderPrint(Node * root);

};



/******************************************************************************/
int main() {


    return 0;
}


/******************************************************************************/
Treap::Node::Node() {}



Treap::Node::Node(int const key,
                  int const priority,
                  Node * left   = nullptr,
                  Node * right  = nullptr,
                  Node * parent = nullptr,
                  string value)
        : key_(key), priority_(priority),
          left_(left), right_(right), parent_(parent), count_(0), value_(value) {}



int Treap::Node::getCount()
{
    return 0;
}



void Treap::Node::fixCount()
{

}


//============================================================================//
Treap::Treap() : root(nullptr), count(0) {}



Treap::~Treap()
{
    clear(root);
}



void Treap::clear(Node * root)
{
    if (root == nullptr) return;
    clear(root->left_);
    clear(root->right_);
    delete root;
}



Treap::Node * Treap::getRoot()
{

    return root;
}



size_t Treap::getCount()
{
    return count;
}




void Treap::preorderPrint(Node * root)
{
    if (root != nullptr) {
        cout << "(" << root->key_ << ", " << root->priority_ << ") ";
        preorderPrint(root->left_);
        preorderPrint(root->right_);
    }
}



void Treap::split(Node * current, int key, Node * & left, Node * & right)
{
    if (!current) {
        left = nullptr;
        right = nullptr;
    } else if (current->key_ <= key) {
        split(current->right_, key, current->right_, right);
        left = current;
    } else {
        split(current->left_, key, left, current->left_);
        right = current;
    }
}



Treap::Node * Treap::merge(Node * left, Node * right)
{
    if (!left || !right) {
        return (!left) ? right : left;
    }

    if (left->priority_ > right->priority_) {
        left->right_ = merge(left->right_, right);
        return left;
    }

    right->left_ = merge(left, right->left_);
    return right;
}



void Treap::insert(int const key, int const priority)
{
    Node * parent = nullptr;
    Node * node = root;
    while (node != nullptr && node->priority_ >= priority) {
        parent = node;
        node = (node->key_ < key) ?
               node->right_: node->left_;
    }

    Node * left;
    Node * right;

    split(node, key, left, right);
    Node * newNode = new Node(key, priority, left, right, parent);

    ++count;
    if (!parent) root = newNode;
    if (parent) {
        if (parent->key_ > newNode->key_) parent->left_ = newNode;
        else parent->right_ = newNode;
    }
}



bool Treap::remove(int const key)
{
    if (!root) return false;

    Node * node = root;
    while (node && node->key_ != key) {
        node = (node->key_ < key) ?
               node->right_: node->left_;
    }

    if(!node) return false;

    Node * merged = merge(node->left_, node->right_);
    if (!node->parent_) root = merged;
    else {
        if (node->parent_->right_ == node) node->parent_->right_ = merged;
        else node->parent_->left_ = merged;
    }
    delete node;
    if (node == root) root = nullptr;
    --count;
    return true;
};




int Treap::getHeight(Node *node)
{
    if(node == 0)
        return 0;
    int left, right;
    if (node->left_ != nullptr) {
        left = getHeight(node->left_);
    }else
        left = -1;
    if (node->right_ != nullptr) {
        right = getHeight(node->right_);
    }else
        right = -1;
    int max = left > right ? left : right;
    return max+1;
}

//============================================================================//

