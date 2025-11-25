#include "bst_lib.h"

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
BST::Node* BST::find_Node_recursive(Node* current, const int& val) {
    if (current == nullptr) {
        return nullptr;
    }
    if (current->left->data == val || current->right->data == val) {
        return current;
    }
    else {
        if (current->data > val) {
            return find_Node_recursive(current->left, val);
        }
        else {
            return find_Node_recursive(current->right, val);
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




//void BST::inorder_traversal_recursive() {
//    Node* current = root;
//    if (current == nullptr) {
//        std::cout << "Binary Search Tree is empty" << std::endl;
//    }
//    else {
//        if (current->left != nullptr) {
//            std::cout << current->left->data;
//        }
//        std::cout << current->data;
//            if (current->right != nullptr) {
//                std::cout << current->right->data;
//            }
//    }
//}





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
    size = 0;
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
void BST::remove(const int& val) {
    Node* current_parent = find_Node_recursive(root, val);
    if (current_parent == nullptr) {
        return;
    }
    Node* current_left_chield = nullptr;
    Node* current_right_chield = nullptr;
    if (current_parent->left != nullptr && current_parent->right != nullptr) {
        current_left_chield = current_parent->left;
        current_right_chield = current_parent->right;
        if (current_left_chield->data == val) {
            delete current_left_chield;
            current_parent->left = nullptr;
        }
        else if (current_right_chield->data == val) {
            delete current_right_chield;
            current_parent->right = nullptr;
        }
        else {
            /*if (current_left_chield->left == nullptr && current_right_chield->right == nullptr) {
                delete current_parent;
            }*/
            return;
        }
    }
    else {
        return;
    }
    size--;
}
bool BST::empty() {
    return !root;
}
//void BST::inorder_traversal() {
//    Node* current_root = root;
//    inorder_traversal_recursive(current_root);
//}