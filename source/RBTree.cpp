#include "RBTree.h"

RBTree::RBTree()
{
    this->sz = 0;
    this->nil = new Node(-1, BLACK, NULL);
    this->root = this->nil;
}

RBTree::~RBTree()
{
    while (root != nil) erase(root);
    delete nil;
}

Node* RBTree::getNil()
{
    return nil;
}

int RBTree::size()
{
    return this->sz;
}

Node* RBTree::begin()
{
    Node *r = root, *ret = root;
    while (r != nil)
    {
        ret = r;
        r = r->left;
    }
    return ret;
}

Node* RBTree::rbegin()
{
    Node *r = root, *ret = root;
    while (r != nil)
    {
        ret = r;
        r = r->right;
    }
    return ret;
}

void RBTree::leftRotate(Node* x)
{
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nil) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nil) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RBTree::rightRotate( Node* x)
{
    Node* y = x->left;
    x->left = y->right;
    if (y->right != nil) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nil) root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void RBTree::BSTInsert(Node* &x)
{
    ++this->sz;
    Node *r = root, *y = nil;
    while (r != nil)
    {
        y = r;
        if (x->data < r->data)
            r = r->left;
        else 
            r = r->right;
    }

    if (y == nil) root = x;
    else if (x->data < y->data) y->left = x;
    else y->right = x;
    x->parent = y;
}

void RBTree::insert(int data)
{
    Node *x = new Node(data, RED, nil);
    BSTInsert(x);
    insertFix(x);
}

void RBTree::insertFix(Node* x)
{
    while (x->parent->color == RED)
        if (x->parent->parent->left == x->parent) insertFixLeft(x);
        else insertFixRight(x);

    root->color = BLACK;
}

void RBTree::insertFixLeft(Node* &x)
{
    Node* u = x->parent->parent->right;
    if (u->color == RED)
    {
        x->parent->parent->color = RED;
        x->parent->color = BLACK;
        u->color = BLACK;
        x = x->parent->parent;
        return;
    }
    
    if (x->parent->left != x) x = x->parent, leftRotate(x);
    x->parent->parent->color = RED;
    x->parent->color = BLACK;
    rightRotate(x->parent->parent);
}

void RBTree::insertFixRight(Node* &x)
{
    Node* u = x->parent->parent->left;
    if (u->color == RED)
    {
        x->parent->parent->color = RED;
        x->parent->color = BLACK;
        u->color = BLACK;
        x = x->parent->parent;
        return;
    }

    
    if (x->parent->left == x) x = x->parent, rightRotate(x);
    x->parent->parent->color = RED;
    x->parent->color = BLACK;
    leftRotate(x->parent->parent);
}

Node* RBTree::find(int data)
{
    Node* r = root;
    while (r != nil)
    {
        if (data < r->data) r = r->left;
        else if (data > r->data) r = r->right;
        else return r;
    }
    return nil;
}

Node* RBTree::predecessor(Node* x)
{
    Node *ret, *r = x->left;
    while (r != nil)
    {
        ret = r;
        r = r->right;
    }
    return ret;
}

void RBTree::erase(int data)
{
    erase(find(data));
}

void RBTree::eraseFixLeft(Node* &x)
{
    Node *w = x->parent->right;

    if (w->color == RED)
    {
        w->color = BLACK;
        x->parent->color = RED;
        leftRotate(x->parent);
        w = x->parent->right;
    }
    else if (w->left->color == BLACK && w->right->color == BLACK)
    {
        w->color = RED;
        x = x->parent;
    }
    else 
    {
        if (w->right->color == BLACK)
        {
            w->left->color = BLACK;
            w->color = RED;
            rightRotate(w);
            w = w->parent;
            
        }
        
        w->color = x->parent->color;
        x->parent->color = w->right->color = BLACK;
        leftRotate(w->parent);
        x = root;
    }
}

void RBTree::eraseFixRight(Node* &x)
{
    Node *w = x->parent->left;

    if (w->color == RED)
    {
        w->color = BLACK;
        x->parent->color = RED;
        rightRotate(x->parent);
        w = x->parent->left;
    }
    else if (w->left->color == BLACK && w->right->color == BLACK)
    {
        w->color = RED;
        x = x->parent;
    }
    else 
    {
        if (w->left->color == BLACK)
        {
            w->right->color = BLACK;
            w->color = RED;
            leftRotate(w);
            w = w->parent;
        }

        w->color = x->parent->color;
        x->parent->color = w->left->color = BLACK;
        rightRotate(w->parent);
        x = root;
    }
}

void RBTree::eraseFix(Node* x)
{
    while (x->color == BLACK && x != root)
        if (x->parent->left == x) eraseFixLeft(x);
        else eraseFixRight(x);

    x->color = BLACK;
}

void RBTree::erase(Node* x)
{
    if (x == nil) return;
    Node* y = (x->left == nil || x->right == nil)
              ? x
              : predecessor(x);
    Node *z = y->left == nil ? y->right : y->left;
    z->parent = y->parent;
    if (y->parent == nil) root = z;
    else
    {
        if (y->parent->left == y) y->parent->left = z;
        else y->parent->right = z;
    }
    x->data = y->data;
    if (y->color == BLACK) eraseFix(z);
    nil->parent = NULL;
    delete y;
    --sz;
}

Node* RBTree::lower_bound(int data)
{
    Node *r = root, *ret = nil;
    while (r != nil)
    {
        if (r->data >= data)
        {
            if (ret == nil) ret = r;
            else if (ret->data > r->data) ret = r;
            r = r->left;
        }
        else r = r->right;
    }
    return ret;
}

Node* RBTree::upper_bound(int data)
{
    Node *r = root, *ret = nil;
    while (r != nil)
    {
        if (r->data > data)
        {
            if (ret == nil) ret = r;
            else if (ret->data > r->data) ret = r;
            r = r->left;
        }
        else r = r->right;
    }
    return ret;
}

Node* RBTree::pred(int data)
{
    Node *r = root, *ret = nil;
    while (r != nil)
    {
        if (r->data < data)
        {
            if (ret == nil) ret = r;
            else if (ret->data < r->data) ret = r;
            r = r->right;
        }
        else r = r->left;
    } 
    return ret;
}

Node* RBTree::pred2(int data)
{
    Node *r = root, *ret = nil;
    while (r != nil)
    {
        if (r->data <= data)
        {
            if (ret == nil) ret = r;
            else if (ret->data < r->data) ret = r;
            r = r->right;
        }
        else r = r->left;
    } 
    return ret;
}