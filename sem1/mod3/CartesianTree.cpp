#include <iostream>
#include <queue>


using std::cout;
using std::cin;
using std::queue;



//============================================================================//
class Treap
{
private:
    struct Node {
        Node * left_;     // left node
        Node * right_;    // right node
        Node * parent_;   // parent node
        int    key_;       // stored value
        int    priority_; //stored priority

        //------------------------------------------------ node: construction
        Node();
        Node(int const,
             int const,
             Node * left,
             Node * right,
             Node * parent);
        //------------------------------------------------ node: deep copy
        //	Make a deep copy of all nodes.
        static Node * copy(Node *, Node *);

    };

    Node * root;  // root node
    size_t count; // total number of nodes

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




//============================================================================//
class BST
{
private:
    struct Node {
        Node * left_;   // left node
        Node * right_;  // right node
        Node * parent_; // parent node
        int value_;     // stored value

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
    Node * root;  // root node
    size_t count; // total number of nodes

    // returns "true" if value was found and successfully deleted
    bool removeNode  (Node * &, int const);

public:
    //====================================================== ctor, copy
    // default constructor
    BST             ();
    // destructor
    ~BST            ();

    //====================================================== methods
    // adds a new node
    void insert  (int const &);
    // public version of "removeNode"
    bool remove(int const value);
    // returns tree's height
    int getHeight(Node *);
    // deletes all nodes
    void clear(Node * root);
    // returns root node
    Node * getRoot();
    // returns count
    size_t getCount();

    void preorderPrint(Node * root);
};







/******************************************************************************/
int main() {
    int n, k, p;
    BST bst;
    Treap treap;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> k >> p;
        bst.insert(k);
        treap.insert(k, p);
    }

    cout << bst.getHeight(bst.getRoot()) - treap.getHeight(treap.getRoot());


    return 0;
}


/******************************************************************************/
Treap::Node::Node() {}



Treap::Node::Node(int const value,
                  int const priority,
                  Node * left   = nullptr,
                  Node * right  = nullptr,
                  Node * parent = nullptr)
        : key_(value), priority_(priority),
          left_(left), right_(right), parent_(parent) {}



Treap::Node * Treap::Node::copy(Node * node, Node * parent = nullptr)
{
    if (!node) {
        return nullptr;
    } else {
        Node* newNode = new Node;
        newNode->key_ = node->key_;
        newNode->parent_ = parent;

        if (parent) {
            if (node->parent_->left_ == node) {
                parent->left_ = newNode;
            } else {
                parent->right_ = newNode;
            }
        }
        copy(node->left_, newNode);
        copy(node->right_, newNode);
        return newNode;
    }
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
    if (node->left_ != NULL) {
        left = getHeight(node->left_);
    }else
        left = -1;
    if (node->right_ != NULL) {
        right = getHeight(node->right_);
    }else
        right = -1;
    int max = left > right ? left : right;
    return max+1;
}

//============================================================================//

BST::Node::Node() {}



BST::Node::Node(int const & value,
                Node * left   = nullptr,
                Node * right  = nullptr,
                Node * parent = nullptr)
        : value_(value), left_(left), right_(right), parent_(parent) {}



BST::Node * BST::Node::copy(Node * node, Node * parent = nullptr)
{
    if (!node) {
        return nullptr;
    } else {
        Node* newNode = new Node;
        newNode->value_ = node->value_;
        newNode->parent_ = parent;

        if (parent) {
            if (node->parent_->left_ == node) {
                parent->left_ = newNode;
            } else {
                parent->right_ = newNode;
            }
        }
        copy(node->left_, newNode);
        copy(node->right_, newNode);
        return newNode;
    }
}



//============================================================================//
BST::BST() : root(nullptr), count(0) {}



BST::~BST()
{
    clear(root);
}



void BST::clear(Node * root)
{
    if (root == nullptr) return;
    clear(root->left_);
    clear(root->right_);
    delete root;
}



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

    ++count;
}



bool BST::remove(int const value)
{
    return removeNode(root, value);
}



BST::Node * BST::getRoot()
{

    return root;
}



size_t BST::getCount()
{
    return count;
}



bool BST::removeNode(Node * & node, int const value)
{

    if(!node) return false;

    if (node->value_ == value) {

        if (!node->left_) {
            Node * right = node->right_;
            delete node;
            node = right;
        } else if (!node->right_) {
            Node * left = node->left_;
            delete node;
            node = left;
        } else {
            Node * minParent = node;
            Node * min = node->right_;
            while (min->left_) {
                minParent = min;
                min = min->left_;
            }
            (minParent->left_ == min ? minParent->left_ : minParent->right_)
                    = min->right_;
            node->value_ = min->value_;
            delete min;
        }
        --count;
        return true;
    }

    return removeNode((node->value_ > value) ?
                      node->left_: node->right_, value);

};




void BST::preorderPrint(Node * root)
{
    if (root != nullptr) {
        cout << root->value_ << " ";
        preorderPrint(root->left_);
        preorderPrint(root->right_);
    }
}




int BST::getHeight(Node *node)
{
    if(node == 0)
        return 0;
    int left, right;
    if (node->left_ != NULL) {
        left = getHeight(node->left_);
    }else
        left = -1;
    if (node->right_ != NULL) {
        right = getHeight(node->right_);
    }else
        right = -1;
    int max = left > right ? left : right;
    return max+1;
}
