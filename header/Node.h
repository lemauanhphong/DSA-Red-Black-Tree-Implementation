#pragma once
#include <bits/stdc++.h>

using namespace std;

class Node
{
    private:
        int data;
        int color;
        Node* parent;
        Node* left;
        Node* right;

    public:
        Node(int data, int color, Node* init);
        int getData();
        int getColor();

        friend class RBTree;
};