#pragma once
#include "Node.h"

const int BLACK = 1, RED = 0;

class RBTree
{
    private:
        Node *nil;
        Node *root;
        int sz;

        void rotateLeft(Node* x);
        void rotateRight(Node* x);
        void leftRotate(Node* x);
        void rightRotate(Node* x);

        void BSTInsert(Node* &x);
        void insertFix(Node* x);
        void insertFixLeft(Node* &x);
        void insertFixRight(Node* &x);

        void eraseFix(Node* x);
        void eraseFixLeft(Node* &x);
        void eraseFixRight(Node* &x);

        Node* predecessor(Node* x);

    public:
        RBTree();
        ~RBTree();
        Node* getNil();
        int size();
        void insert(int data);
        Node* find(int data);
        void erase(Node* x);
        void erase(int data);
        Node* begin();
        Node* rbegin();
        Node* lower_bound(int data);
        Node* upper_bound(int data);
        Node* pred(int data);
        Node* pred2(int data);
};
