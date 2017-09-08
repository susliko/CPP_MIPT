#include <iostream>
#include <queue>


using std::cout;
using std::cin;
using std::endl;



class AVLTree
{
private:
    struct Node {
        Node * left_;   // left node
        Node * right_;  // right node
        int value_;     // stored value
        int height_;
        int childrenL;
        int childrenR;


        //------------------------------------------------ node: construction
        Node();
        Node(int,
             Node * left,
             Node * right);
        //------------------------------------------------ node: deep copy
    };

    Node * root;  // root node

    // adds a new node to the specified subtree
    Node * insertNode(Node *, int);
    // functions to remove nodes
    Node * findMin(Node *);
    Node * removemin(Node* );
    Node * removeNode(Node *, int);

    // functions to work with heights
    int  getHeight (Node *);
    int  getBalance(Node * node);
    void fixHeight (Node * node);

    int getChildNum(Node *);
    // rotates
    Node * rightRotate(Node *);
    Node * leftRotate (Node *);
    Node * balance(Node *);


public:
    //====================================================== ctor
    // default constructor
    AVLTree             ();
    // destructor
    ~AVLTree            ();

    //====================================================== methods
    // adds a new node
    void insert(int);
    // removes node with specified value
    void remove(int);
    // returns k-statistics
    int findKStat(Node *, int, int);


    // deletes all nodes
    void clear(Node *);
    // returns root node
    Node * getRoot();

    void preorderprint(Node *);
    void levelorderPrint(Node *);
};



/******************************************************************************/
int main()
{
    AVLTree avl;


    int n, a, k;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a >> k;
        if (a < 0) avl.remove(0 - a);
        else avl.insert(a);
        cout << avl.findKStat(avl.getRoot(), k, 0) << " ";
    }


    return 0;
}



/******************************************************************************/
AVLTree::Node::Node() {}



AVLTree::Node::Node(int value,
                Node * left   = nullptr,
                Node * right  = nullptr)
        : value_(value), height_(1), childrenL(0), childrenR(0)
        , left_(left), right_(right)
    {}


//============================================================================//
AVLTree::AVLTree() : root() {}



AVLTree::~AVLTree()
{
    clear(root);
}



void AVLTree::clear(Node * root)
{
    if (root == nullptr) return;
    clear(root->left_);
    clear(root->right_);
    delete root;
}



AVLTree::Node * AVLTree::insertNode(Node * node, int value)
{
    if (!root) { return root = new Node(value); }
    if(!node) return new Node(value);
    if(value < node->value_) {
        node->left_ = insertNode(node->left_, value);
    }
    else {
        node->right_ = insertNode(node->right_, value);
    }
    root = balance(node);
    return root;
}



void AVLTree::insert(int value)
{
    insertNode(root, value);
}




AVLTree::Node * AVLTree::getRoot()
{

    return root;
}



int AVLTree::getHeight(Node *node)
{
    return node ? node->height_ : 0;
}



int AVLTree::getBalance(Node * node)
{
    return getHeight(node->right_) - getHeight(node->left_);
}



void AVLTree::fixHeight(Node * node)
{
    int leftH  = getHeight(node->left_);
    int rightH = getHeight(node->right_);
    node->height_ = ((leftH > rightH) ? leftH : rightH) + 1;
    
    node->childrenL = getChildNum(node->left_);
    node->childrenR = getChildNum(node->right_);
}



int AVLTree::getChildNum(Node * node)
{
    return (node) ? (node->childrenL + node->childrenR + 1) : 0;
}


AVLTree::Node * AVLTree::rightRotate(Node * p)
{
    Node * q = p->left_;
    p->left_ = q->right_;
    q->right_ = p;
    fixHeight(p);
    fixHeight(q);
    return q;
}



AVLTree::Node * AVLTree::leftRotate(Node * q)
{
    Node * p = q->right_;
    q->right_ = p->left_;
    p->left_ = q;
    fixHeight(q);
    fixHeight(p);
    return p;
}



AVLTree::Node * AVLTree::balance(Node* p)
{
    fixHeight(p);
    if(getBalance(p) == 2)
    {
        if(getBalance(p->right_) < 0) {
            p->right_ = rightRotate(p->right_);
        }
        return leftRotate(p);
    }
    if(getBalance(p) == -2)
    {
        if(getBalance(p->left_) > 0 ) {
            p->left_ = leftRotate(p->left_);
        }
        return rightRotate(p);
    }
    return p;
}



AVLTree::Node * AVLTree::findMin(Node *p)
{
    return p->left_? findMin(p->left_):p;
}



AVLTree::Node * AVLTree::removemin(Node * p) 
{
    if( p->left_==0 )
        return p->right_;
    p->left_ = removemin(p->left_);
    return balance(p);
}



AVLTree::Node * AVLTree::removeNode(Node * p, int value)
{
    if( !p ) return 0;
    if( value < p->value_ )
        p->left_ = removeNode(p->left_,value);
    else if( value > p->value_ )
        p->right_ = removeNode(p->right_,value);
    else //  k == p->key
    {
        Node * q = p->left_;
        Node * r = p->right_;
        delete p;
        if( !r ) return q;
        Node * min = findMin(r);
        min->right_ = removemin(r);
        min->left_ = q;
        return balance(min);
    }
    return balance(p);
}



void AVLTree::remove(int value)
{
    root = removeNode(root, value);
}



void AVLTree::preorderprint(Node * root)
{
    if (!root) return;

    cout << root->value_ << " ";
    preorderprint(root->left_);
    preorderprint(root->right_);

}



void AVLTree::levelorderPrint(Node * root)
{
    if (!root) return;
    std::queue<Node *> q;
    q.push(root);
    while (!q.empty()) {
        Node * node = q.front();
        q.pop();
        cout << "(" << node->value_ << ", " << node->childrenL << ") ";
        if (node->left_  != nullptr) q.push(node->left_);
        if (node->right_ != nullptr) q.push(node->right_);
    }
}



int AVLTree::findKStat(Node * root, int k, int sum)
{
    if (!root) return 0;

    if (root->childrenL + sum == k) {
        return root->value_;
    } else if(root->childrenL + sum > k) {
        return findKStat(root->left_, k, sum);
    } else {
        return findKStat(root->right_, k, sum + root->childrenL + 1);
    }
}


