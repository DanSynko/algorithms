#pragma once
#include <iostream>
#include <initializer_list>

class BST {
private:
    struct Node {
        int data;
        Node* right;
        Node* left;
    };
    Node* root;

public:
    BST();
    BST(std::initializer_list<int> list);
    ~BST();
    void search();
    void insert(const int& val);
};