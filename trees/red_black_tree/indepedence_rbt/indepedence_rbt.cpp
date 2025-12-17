#include <iostream>
#include <initializer_list>
//#include <random>
//#include "algorithms_timer.h"

class RedBlackTree {
protected:
    enum Color {
        black,
        red
    };
private:
    struct Node {
        int data;
        Node* right;
        Node* left;
        Node* parent;
        Color color;
    };
    Node* root;


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



    Node* search_recursive(Node* current, const int val) {
        if (current == nullptr) {
            return nullptr;
        }
        if (current->data != val) {
            if (current->data > val) {
                return search_recursive(current->left, val);
            }
            else {
                return search_recursive(current->right, val);
            }
        }
        return current;
    }



    Node* fixup_properties_insert(Node* current) {
        // left rotation
        if ((current->right != nullptr && current->right->right != nullptr) && (current->right->color == Color::red && current->right->right->color == Color::red)) {
            if (current->left == nullptr) {
                current = left_rotation(current);
                current->color = Color::black;
                current->left->color = Color::red;
                current->right->color = Color::red;
            }
            else if (current->left->color == Color::black) {
                current = left_rotation(current);
                recoloring(current->left);
            }
            else {
                recoloring(current->left);
            }
        }
        // right rotation
        else if ((current->left != nullptr && current->left->left != nullptr) && (current->left->color == Color::red && current->left->left->color == Color::red)) {
            if (current->right == nullptr) {
                current = right_rotation(current);
                current->color = Color::black;
                current->right->color = Color::red;
                current->left->color = Color::red;
            }
            else if (current->left->color == Color::black) {
                current = right_rotation(current);
                recoloring(current->right);
            }
            else {
                recoloring(current->right);
            }
        }
        // RL
        else if ((current->right != nullptr && current->right->left != nullptr) && (current->right->color == Color::red && current->right->left->color == Color::red)) {
            if (current->left == nullptr) {
                current = RL_rotation(current);
                current->color = Color::black;
                current->left->color = Color::red;
                current->right->color = Color::red;
            }
            else if (current->left->color == Color::black) {
                current = RL_rotation(current);
                //recoloring(current->left);
                current->left->color = Color::red;
                current->left->parent->color = Color::black;
            }
            else {
                recoloring(current->left);
            }
        }
        // LR
        else if ((current->left != nullptr && current->left->right != nullptr) && (current->left->color == Color::red && current->left->right->color == Color::red)) {
            if (current->right == nullptr) {
                current = LR_rotation(current);
                current->color = Color::black;
                current->right->color = Color::red;
                current->left->color = Color::red;
            }
            else if (current->right->color == Color::black) {
                current = LR_rotation(current);
                recoloring(current->right);
            }
            else {
                recoloring(current->right);
            }
        }
        return current;
    }

    void fixup_properties_remove(Node* double_black_node, Node* deleted_parent, int double_black_node_data, Color deleted_color) {
        if (deleted_color == Color::red) {
            return;
        }
        else if (deleted_color == Color::black && (double_black_node != nullptr && double_black_node->color == Color::red)) {
            double_black_node->color = Color::black;
            return;
        }


        if (double_black_node != nullptr && double_black_node == root) {
            double_black_node->color = Color::black;
            return;
        }


        Node* brother;
        if (double_black_node != root && deleted_parent != nullptr) {
            brother = (double_black_node_data < deleted_parent->data) ? deleted_parent->right : deleted_parent->left;
        }
        else {
            if (root != nullptr) root->color = Color::black;
            return;
        }


        if (brother->color == Color::red) {
            deleted_parent = left_rotation(deleted_parent);
            deleted_parent->color = brother->color;
            brother->color = Color::black;
        }
        else if (brother->color == Color::black && (brother->left != nullptr && brother->left->color == Color::red)) {
            Color sibling_color = brother->color;
            Color sibling_child_color = brother->left->color;
            brother->color = sibling_child_color;
            brother->left->color = sibling_color;
            brother = right_rotation(brother);
        }
        if (brother->color == Color::black && (brother->right != nullptr && brother->right->color == Color::red)) {
            deleted_parent = left_rotation(deleted_parent);
            deleted_parent->color = brother->color;
            deleted_parent->left->color = Color::black;
            deleted_parent->right->color = Color::black;
        }
        else if (brother->color == Color::black && (brother->left != nullptr && brother->right != nullptr && (brother->left->color == Color::black && brother->right->color == Color::black))) {
            if (deleted_parent->color == Color::red) {
                brother->color = Color::red;
                deleted_parent->color = Color::black;
            }
            else {
                fixup_properties_remove(deleted_parent, deleted_parent->parent, double_black_node_data, Color::black);
            }
        }
        else if (brother->color == Color::black && (brother->left == nullptr && brother->right == nullptr)) {
            if (deleted_parent->color == Color::red) {
                brother->color = Color::red;
                deleted_parent->color = Color::black;
            }
            else {
                brother->color = Color::red;
                fixup_properties_remove(deleted_parent, deleted_parent->parent, double_black_node_data, Color::black);
            }
        }
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
        return fixup_properties_insert(current);
    }
    void remove_iterative(Node* current, const int& val) {
        while (current != nullptr && current->data != val) {
            if (val < current->data) {
                current = current->left;
            }
            else if (val > current->data) {
                current = current->right;
            }
        }


        if (current == nullptr) {
            return;
        }
        else if (current == root && (root->right == nullptr && root->left == nullptr)) {
            delete root;
            root = nullptr;
            return;
        }
        else {
            if (current->left != nullptr && current->right != nullptr) {
                Node* temp = inorder_preccesor(current->left);
                int temp_data = temp->data;
                Node* current_parent = current->parent;
                Color current_color = current->color;
                remove_iterative(temp, temp->data);
                current->data = temp_data;
            }
            else if (current->left == nullptr) {
                Color current_color = current->color;
                Node* temp = current->right;
                Node* current_parent = current->parent;
                if (current->data < current->parent->data) {
                    current->parent->left = nullptr;
                }
                else {
                    current->parent->right = nullptr;
                }
                int current_data = current->data;
                delete current;
                fixup_properties_remove(temp, current_parent, current_data, current_color);
            }
            else {
                Color current_color = current->color;
                Node* temp = current->left;
                Node* current_parent = current->parent;
                int current_data = current->data;
                delete current;
                fixup_properties_remove(temp, current_parent, current_data, current_color);
            }
        }
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
    }


    Node* left_rotation(Node* current) {
        Node* old_parent = current;
        Node* new_parent = current->right;
        Node* subtree = new_parent->left;
        if (subtree != nullptr) {
            subtree->parent = old_parent;
        }
        if (old_parent->parent != nullptr) {
            if (old_parent == old_parent->parent->left) {
                old_parent->parent->left = new_parent;
            }
            else {
                old_parent->parent->right = new_parent;
            }
        }
        else {
            root = new_parent;
        }
        new_parent->left = old_parent;
        old_parent->right = subtree;
        new_parent->parent = old_parent->parent;
        old_parent->parent = new_parent;
        return new_parent;
    }
    Node* right_rotation(Node* current) {
        Node* old_parent = current;
        Node* new_parent = current->left;
        Node* subtree = new_parent->right;
        if (subtree != nullptr) {
            subtree->parent = old_parent;
        }
        if (old_parent->parent != nullptr) {
            if (old_parent == old_parent->parent->left) {
                old_parent->parent->left = new_parent;
            }
            else {
                old_parent->parent->right = new_parent;
            }
        }
        else {
            root = new_parent;
        }
        new_parent->right = old_parent;
        old_parent->left = subtree;
        new_parent->parent = old_parent->parent;
        old_parent->parent = new_parent;
        return new_parent;
    }
    Node* RL_rotation(Node* current) {
        Node* old_parent = current;
        Node* new_parent = current->right->left;
        Node* subnode = current->right;
        subnode = right_rotation(subnode);
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



    /*void rbt_time() {
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
    }*/



    Node* search(const int& val) {
        return search_recursive(root, val);
    }
    void insert(const int& val) {
        Node* next_parent = root;
        root = insert_recursive(root, next_parent, val);
    }
    void remove(const int& val) {
        remove_iterative(root, val);
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


    /*void full_black_tree() {
        RedBlackTree rbt = { 10, 20, 12, 30, 5, 25, 17, 16, 15, 40, 29, 50 };
        rbt.remove(50);
        rbt.remove(5);
        rbt.remove(15);
        rbt.remove(30);
        rbt.remove(40);
    }*/
};



int main()
{
    std::cout << "There is an example of red-black-tree with int-data. " << std::endl;

    RedBlackTree rbt = { 10, 20, 12, 30, 5, 25, 17, 16, 15, 40, 29, 50 };

    rbt.remove(50);
    rbt.remove(5);
    rbt.remove(15);
    rbt.remove(30);
    rbt.remove(40);

    rbt.remove(17);

    rbt.remove(25);
    return 0;
}