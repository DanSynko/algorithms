#include <iostream>
#include <initializer_list>
#include <random>
//#include "algorithms_timer.h"

class RedBlackTree {
protected:
    enum Color {
        black,
        red
    };
    struct Node {
        int data;
        Node* right;
        Node* left;
        Node* parent;
        Color color;
    };
    Node* root;

    bool valide_properties() {

    }


    void inorder_traversal_recursive(Node* current) {
        if (current == nullptr) {
            return;
        }
        inorder_traversal_recursive(current->left);
        std::cout << current->data << ". ";
        inorder_traversal_recursive(current->right);
    }
    void postorder_traversal_recursive(Node* current) {
        if (current == nullptr) {
            return;
        }
        postorder_traversal_recursive(current->left);
        postorder_traversal_recursive(current->right);
        std::cout << current->data << ". ";
    }
    void preorder_traversal_recursive(Node* current) {
        if (current == nullptr) {
            return;
        }
        std::cout << current->data << ". ";
        preorder_traversal_recursive(current->left);
        preorder_traversal_recursive(current->right);
    }




    Node* inorder_preccesor(Node* current) {
        while (current != nullptr && current->right != nullptr) {
            current = current->right;
        }
        return current;
    }
    Node* inorder_succesor(Node* current) {
        if (current->left == nullptr) {
            return current;
        }
        inorder_succesor(current->left);
    }



    bool search_recursive(Node* current, const int& val) {
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
    Node* insert_recursive(Node* current, Node* current_parent, const int& val) {
        if (current == nullptr) {
            return new Node{ val, nullptr, nullptr, current_parent, Color::red };
        }
        else {
            if (current->data > val) {
                current->left = insert_recursive(current->left, current, val);
            }
            else {
                current->right = insert_recursive(current->right, current, val);
            }
        }
        if (current->parent != nullptr) {
            if (current->color == Color::red && current->right->color == Color::red) {
                Node* grandparent = current->parent->parent;
                Node* left_uncle = nullptr;
                Node* right_uncle = nullptr;
                if (grandparent != nullptr) {
                    if (grandparent->data < current->data) {
                        left_uncle = current->parent->parent->left;
                        if (left_uncle->color == Color::black || left_uncle == nullptr) {
                            current = left_rotation(current);
                            recoloring(left_uncle);
                        }
                        else {
                            recoloring(left_uncle);
                        }
                    }
                    else {
                        right_uncle = current->parent->parent->left;
                        if (right_uncle->color == Color::black || right_uncle == nullptr) {
                            current = left_rotation(current);
                            recoloring(right_uncle);
                        }
                        else {
                            recoloring(right_uncle);
                        }
                    }
                }
                else {
                    left_uncle = current->parent->left;
                    if (left_uncle->color == Color::black || left_uncle == nullptr) {
                        current = left_rotation(current);
                        recoloring(left_uncle);
                    }
                    else {
                        recoloring(left_uncle);
                    }
                }
            }
        }
        return current;
    }
    Node* remove_recursive(Node* current, const int& val) {
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
            if (current->left != nullptr && current->right != nullptr) {
                Node* temp = inorder_succesor(current->right);
                current->data = temp->data;
                current->right = remove_recursive(current->right, temp->data);
            }
            else if (current->left == nullptr) {
                Node* temp = current->right;
                delete current;
                return temp;
            }
            else {
                Node* temp = current->left;
                delete current;
                return temp;
            }
        }
        return current;
    }


    void recoloring(Node* uncle) {
        if (uncle->color == Color::red) {
            if (uncle->parent == root) {
                uncle->parent->color = Color::black;
            }
            else {
                uncle->parent->color = Color::red;
            }
            uncle->color = Color::black;
            if (uncle->data < uncle->parent->data) {
                uncle->parent->right->color = Color::black;
            }
            else {
                uncle->parent->left->color = Color::black;
            }
        }
        else if (uncle == nullptr || uncle->color == Color::black) {
            // ...
        }
    }


    Node* left_rotation(Node* current) {
        Node* old_parent = current;
        Node* new_parent = current->right;
        Node* subtree = new_parent->left;
        new_parent->left = old_parent;
        old_parent->right = subtree;
        return new_parent;
    }
    Node* right_rotation(Node* current) {
        Node* old_parent = current;
        Node* new_parent = current->left;
        Node* subtree = new_parent->right;
        new_parent->right = old_parent;
        old_parent->left = subtree;
        return new_parent;
    }
    Node* RL_rotation(Node* current) {
        Node* old_parent = current;
        Node* new_parent = current->right->left;
        Node* subnode = current->right;
        subnode = right_rotation(subnode);
        old_parent->right = subnode;
        old_parent = left_rotation(old_parent);
        return new_parent;
    }
    Node* LR_rotation(Node* current) {
        Node* old_parent = current;
        Node* new_parent = current->left->right;
        Node* subnode = current->left;
        subnode = left_rotation(subnode);
        old_parent->left = subnode;
        old_parent = right_rotation(old_parent);
        return new_parent;
    }


    void postorder_delete_recursive(Node* current) {
        if (current == nullptr) {
            return;
        }
        postorder_delete_recursive(current->left);
        postorder_delete_recursive(current->right);
        delete current;
    }
public:
    RedBlackTree() : root(nullptr) {}

    RedBlackTree(std::initializer_list<int> tree) : root(nullptr) {
        for (const int& i : tree) {
            if (root == nullptr) {
                root = new Node{ i, nullptr, nullptr, nullptr, Color::black };
            }
            else {
                insert(i);
            }
        }
    }
    ~RedBlackTree() {
        postorder_delete_recursive(root);
        root = nullptr;
    }

    void rbt_work_demo() {
        std::cout << "search(51); " << std::endl;
        if (search(51)) {
            std::cout << "This element exists. " << std::endl;
        }
        else {
            std::cout << "This element NOT exists. " << std::endl;
        }
        std::cout << "insert(20); " << std::endl;
        insert(20);
        std::cout << "remove(40); " << std::endl;
        remove(40);
        std::cout << "inorder_traversal(); " << std::endl;
        inorder_traversal();
        std::cout << std::endl;
        std::cout << "preorder_traversal(); " << std::endl;
        preorder_traversal();
        std::cout << std::endl;
        std::cout << "postorder_traversal(); " << std::endl;
        postorder_traversal();
    }



    void rbt_time() {
        std::vector<int> elements_vec;
        const int elements = 4999999;
        elements_vec.reserve(elements);
        for (int i = 0; i < elements; i++) {
            elements_vec.push_back(i);
        }
        for (const int& i : elements_vec) {
            Node* newNode = new Node{ i, nullptr, nullptr };
            if (root == nullptr) {
                root = newNode;
            }
            else {
                insert(i);
            }
        }
    }



    bool search(const int& val) {
        return search_recursive(root, val);
    }
    void insert(const int& val) {
        Node* next_parent = root;
        root = insert_recursive(root, next_parent, val);
    }
    void remove(const int& val) {
        root = remove_recursive(root, val);
    }
    void inorder_traversal() {
        inorder_traversal_recursive(root);
    }
    void postorder_traversal() {
        postorder_traversal_recursive(root);
    }
    void preorder_traversal() {
        preorder_traversal_recursive(root);
    }
};



int main()
{
    std::cout << "There is an example of red-black-tree with int-data. " << std::endl;
    RedBlackTree rbt = { 10, 20, 5 };
    rbt.insert(30);
    return 0;
}