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

    bool search_recursive(Node* current, const int& val);

    void inorder_traversal_recursive(Node* current_root);
    void preorder_traversal_recursive(Node* current_root);
    void postorder_traversal_recursive(Node* current_root);

    void postorder_delete_recursive(Node* current);

    virtual Node* inorder_preccesor(Node* current);
    virtual Node* inorder_succesor(Node* current);
private:
    Node* root;
    Node* remove_recursive(Node* current, const int& val);
    Node* insert_recursive(Node* current, const int& val);
public:
    BST();
    BST(std::initializer_list<int> tree);
    virtual ~BST();

    void bst_work_demo();

    void bst_log_demo();
    virtual void bst_lin_demo();

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
        int data;
        Node* right;
        Node* left;
        int height;
    };
    Node* root;

    Node* inorder_succesor(Node* current);
    Node* inorder_preccesor(Node* current);

    int get_height(Node* current);
    void update_height(Node* current);
    int balance_factor_f(Node* current);

    Node* insert_recursive_forAVL(Node* current, const int& val);
    Node* remove_recursive_forAVL(Node* current, const int& val);

    Node* left_rotation(Node* current);
    Node* right_rotation(Node* current);
    Node* RL_rotation(Node* current);
    Node* LR_rotation(Node* current);

public:
    AVL();
    AVL(std::initializer_list<int> tree);
    ~AVL() override;

    void insert(const int& val) override;
    void remove(const int& val) override;

    void bst_lin_demo() override;
};

// ========================================================================================================================================================================
// ========================================================================================================================================================================
//                                                                             RED BLACK TREE
// ========================================================================================================================================================================
// ========================================================================================================================================================================

class RBT : public BST {
protected:
    enum class Color {
        black,
        red
    };
private:
    struct Node : public BST::Node {
        Color color;
    };
    Node* root;
    bool validate_properties();

    Node* insert_recursive_forRBT(Node* current, const int& val);
    Node* remove_recursive_forRBT(Node* current, const int& val);

    void recoloring();

    Node* left_rotation(Node* current);
    Node* right_rotation(Node* current);
    Node* RL_rotation(Node* current);
    Node* LR_rotation(Node* current);
public:
    RBT();
    RBT(std::initializer_list<int> tree);
    ~RBT() override;

    void insert(const int& val) override;
    void remove(const int& val) override;
};

