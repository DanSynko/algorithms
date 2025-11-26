#include <iostream>
#include "bst_lib.h"


// ========================================================================================================================================================================
// ========================================================================================================================================================================
//                                                                             BINARY SEARCH TREE
// ========================================================================================================================================================================
// ========================================================================================================================================================================


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
    postorder_delete_recursive(root);
}
// --------------------------------------------------------------------------- PRIVATE METHODS ---------------------------------------------------------------------------
bool BST::search_recursive(Node* current, const int& val) {
    if (current == nullptr) {
        return false;
    }
    if (current->data != val) {
        if (current->data > val) {
            return search_recursive(current->left, val);
        }
        else {
            return search_recursive(current->right, val);
        }
    }
    return true;
}
BST::Node* BST::remove_recursive(Node* current, const int& val) {
    if (current == nullptr) {
        return nullptr;
    }
    if (val < current->data) {
        current->left = remove_recursive(current->left, val);
    }
    else if (val > current->data) {
        current->right = remove_recursive(current->right, val);
    }
    else {
        if (current->left == nullptr) {
            Node* temp = current->right;
            delete current;
            return temp;
        }
        else if (current->right == nullptr) {
            Node* temp = current->left;
            delete current;
            return temp;
        }
    }
    return current;
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



// --------------------------------------------------------------------------- traversals ---------------------------------------------------------------------------
void BST::inorder_traversal_recursive(Node* current) {
    if (current == nullptr) {
        return;
    }
    inorder_traversal_recursive(current->left);
    std::cout << current->data << ". ";
    inorder_traversal_recursive(current->right);
}
void BST::postorder_traversal_recursive(Node* current) {
    if (current == nullptr) {
        return;
    }
    postorder_traversal_recursive(current->left);
    postorder_traversal_recursive(current->right);
    std::cout << current->data << ". ";
}
void BST::preorder_traversal_recursive(Node* current) {
    if (current == nullptr) {
        return;
    }
    std::cout << current->data << ". ";
    preorder_traversal_recursive(current->left);
    preorder_traversal_recursive(current->right);
}



void BST::postorder_delete_recursive(Node* current) {
    if (current == nullptr) {
        return;
    }
    postorder_delete_recursive(current->left);
    postorder_delete_recursive(current->right);
    delete current;
}
// --------------------------------------------------------------------------- PUBLIC METHODS ---------------------------------------------------------------------------
bool BST::search(const int& val) {
    Node* current_root = root;
    return search_recursive(current_root, val);
}
void BST::insert(const int& val) {
    Node* current_root = root;
    insert_recursive(current_root, val);
    size++;
}
void BST::remove(const int& val) {
    this->root = remove_recursive(root, val);
}
void BST::inorder_traversal() {
    inorder_traversal_recursive(root);
}
void BST::postorder_traversal() {
    postorder_traversal_recursive(root);
}
void BST::preorder_traversal() {
    preorder_traversal_recursive(root);
}