#pragma once
#include <initializer_list>
#include <random>


// ========================================================================================================================================================================
// ========================================================================================================================================================================
//                                                                             BINARY SEARCH TREE
// ========================================================================================================================================================================
// ========================================================================================================================================================================


class BST {
protected:
    struct Node {
        int data;
        Node* right;
        Node* left;
    };
    Node* root;
    size_t size;

    bool search_recursive(Node* current, const int& val);
    Node* insert_recursive(Node* current, const int& val);

    Node* inorder_preccesor(Node* current);
    Node* inorder_succesor(Node* current);
    Node* remove_recursive(Node* current, const int& val);

    void inorder_traversal_recursive(Node* current_root);
    void preorder_traversal_recursive(Node* current_root);
    void postorder_traversal_recursive(Node* current_root);

    void postorder_delete_recursive(Node* current);
public:
    BST();
    BST(std::initializer_list<int> tree);
    virtual ~BST();

    void bst_work_demo();

    void bst_log_demo();
    void bst_lin_demo();

    bool search(const int& val);
    virtual void insert(const int& val);
    virtual void remove(const int& val);
    void inorder_traversal();
    void preorder_traversal();
    void postorder_traversal();
};


// ========================================================================================================================================================================
// ========================================================================================================================================================================
//                                                                             AVL TREE
// ========================================================================================================================================================================
// ========================================================================================================================================================================


class AVL : public BST {
private:
    struct Node : public BST::Node {
        int height;
    };
public:

    AVL();
    AVL(std::initializer_list<int> tree);
    ~AVL() override;

    void insert(const int& val) override;
    void remove(const int& val) override;
};