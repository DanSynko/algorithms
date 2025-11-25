#pragma once
#include <initializer_list>
//#include <random>
//#include <chrono>

class BST {
private:
    struct Node {
        int data;
        Node* right;
        Node* left;
    };
    Node* root;
    size_t size;

    bool search_recursive(Node* current, const int& val);
    Node* insert_recursive(Node* current, const int& val);
    Node* find_Node_recursive(Node* current, const int& val);
    /*void inorder_traversal_recursive(Node* current_root);
    void preorder_traversal_recursive();
    void postorder_traversal_recursive();*/
public:
    BST();
    BST(std::initializer_list<int> tree);
    ~BST();
    void clear();
    bool search(const int& val);
    void insert(const int& val);
    void remove(const int& val);
    bool empty();
    /*void inorder_traversal();
    void preorder_traversal();
    void postorder_traversal();*/
};