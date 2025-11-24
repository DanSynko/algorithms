#include <iostream>
#include "bst.h"

bool BST::search_recursive(Node* current, const int& val) {
    Node* current_root = current;
    if (current_root == nullptr) {
        return false;
    }
    if (current_root->data != val) {
        if (current_root->data > val) {
            return search_recursive(current_root->left, val);
        }
        else {
            return search_recursive(current_root->right, val);
        }
    }
    return true;
}
BST::Node* BST::insert_recursive(Node* current, const int& val) {
    if (current == nullptr) {
        return new Node{ val, nullptr, nullptr };
    }
    else {
        if (current->data > val) {
            current->left = insert_recursive(current->left, val);
        }
        else {
            current->right = insert_recursive(current->right, val);
        }
    }
    return current;
}






BST::BST() : root(nullptr), size(0) {}

BST::BST(std::initializer_list<int> tree) : root(nullptr), size(0) {
    for (const int& i : tree) {
        Node* newNode = new Node{ i, nullptr, nullptr };
        if (root == nullptr) {
            root = newNode;
        }
        else {
            insert(i);
        }
    }
}

BST::~BST() {
    
}





void BST::clear() {

}
bool BST::search(const int& val) {
    Node* current_root = root;
    return search_recursive(current_root, val);
}
void BST::insert(const int& val) {
    Node* current_root = root;
    insert_recursive(current_root, val);
    size++;
}
bool BST::empty() {
    return !root;
}
void BST::inorder_traversal() {

}



int main()
{
    std::cout << "There is an example of binary search tree with int-data. " << std::endl;

    // balanced tree with O(log N)
    BST bst = { 50, 49, 51 };
    std::cout << "search(51); " << std::endl;
    if (bst.search(51)) {
        std::cout << "This element exists. " << std::endl;
    }
    else {
        std::cout << "This element NOT exists. " << std::endl;
    }
    std::cout << "insert(20); " << std::endl;
    bst.insert(20);

    return 0;
}
