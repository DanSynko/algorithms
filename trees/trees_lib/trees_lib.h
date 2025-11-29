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

        // for AVL-tree
        int height = 0;
    };
    Node* root;

    bool search_recursive(Node* current, const int& val);

    void inorder_traversal_recursive(Node* current_root);
    void preorder_traversal_recursive(Node* current_root);
    void postorder_traversal_recursive(Node* current_root);

    void postorder_delete_recursive(Node* current);

    Node* inorder_preccesor(Node* current);
    Node* inorder_succesor(Node* current);
private:
    Node* remove_recursive(Node* current, const int& val);
    Node* insert_recursive(Node* current, const int& val);
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
    /*struct Node : public BST::Node {
        int height;
    };*/

    int get_height(Node* current);
    void update_height(Node* current);
    int balance_factor_f(Node* current);

    Node* insert_recursive_forAVL(Node* current, const int& val);
   // Node* remove_recursive_forAVL(Node* current, const int& val);

    Node* left_rotation(Node* current, int balance_factor);
    Node* right_rotation(Node* current);

public:
    AVL();
    AVL(std::initializer_list<int> tree);
    ~AVL() override;

    void insert(const int& val) override;
    //void remove(const int& val) override;
};