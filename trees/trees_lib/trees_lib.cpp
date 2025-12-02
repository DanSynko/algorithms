#include <iostream>
#include "trees_lib.h"


// ========================================================================================================================================================================
// ========================================================================================================================================================================
//                                                                             BINARY SEARCH TREE
// ========================================================================================================================================================================
// ========================================================================================================================================================================


BST::BST() : root(nullptr) {}

BST::BST(std::initializer_list<int> tree) : root(nullptr) {
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



void BST::bst_work_demo() {
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


void BST::bst_log_demo() {
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<int> dist(0, 4999999);
    const int elements = 4999999;
    std::vector<int> elements_vec;
    elements_vec.reserve(elements);
    for (int i = 0; i < elements; i++) {
        elements_vec.push_back(dist(engine));
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

void BST::bst_lin_demo() {
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
// --------------------------------------------------------------------------- PROTECTED METHODS ---------------------------------------------------------------------------
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


BST::Node* BST::inorder_preccesor(Node* current) {
    while (current != nullptr && current->right != nullptr) {
        current = current->right;
    }
    return current;
}
BST::Node* BST::inorder_succesor(Node* current) {
    if (current->left == nullptr) {
        return current;
    }
    inorder_succesor(current->left);
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

// --------------------------------------------------------------------------- PRIVATE METHODS ---------------------------------------------------------------------------
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
// --------------------------------------------------------------------------- PUBLIC METHODS ---------------------------------------------------------------------------
bool BST::search(const int& val) {
    return search_recursive(root, val);
}
void BST::insert(const int& val) {
    insert_recursive(root, val);
}
void BST::remove(const int& val) {
    root = remove_recursive(root, val);
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



// ========================================================================================================================================================================
// ========================================================================================================================================================================
//                                                                             AVL TREE
// ========================================================================================================================================================================
// ========================================================================================================================================================================

AVL::AVL() : root(nullptr) {}
AVL::AVL(std::initializer_list<int> tree) : root(nullptr) {
    for (const int& i : tree) {
        Node* newNode = new Node{ i, nullptr, nullptr, 0 };
        if (root == nullptr) {
            root = newNode;
        }
        else {
            insert(i);
        }
    }
}

AVL::~AVL() {
    postorder_delete_recursive(root);
    root = nullptr;
}
// --------------------------------------------------------------------------- PRIVATE METHODS ----------------------------------------------------------------------------
int AVL::get_height(Node* current) {
    return (current == nullptr) ? -1 : current->height;
}
void AVL::update_height(Node* current) {
    current->height = 1 + std::max(get_height(current->left), get_height(current->right));
}


int AVL::balance_factor_f(Node* current) {
    int leftheight = -1;
    int rightheight = -1;
    if (current->left != nullptr) {
        leftheight = current->left->height;
    }
    if (current->right != nullptr) {
        rightheight = current->right->height;
    }
    return leftheight - rightheight;
}

AVL::Node* AVL::insert_recursive_forAVL(Node* current, const int& val) {
    if (current == nullptr) {
        return new Node{ val, nullptr, nullptr, 0 };
    }
    else {
        if (current->data > val) {
            current->left = insert_recursive_forAVL(current->left, val);
        }
        else {
            current->right = insert_recursive_forAVL(current->right, val);
        } 
    }
    update_height(current);
    int balance_factor = balance_factor_f(current);
    if (balance_factor == -2) {
        if (balance_factor_f(current->right) == 1) {
            current = RL_rotation(current);
        }
        else if (balance_factor_f(current->right) == -1) {
            current = left_rotation(current);
        }
    }
    else if (balance_factor == 2) {
        if (balance_factor_f(current->left) == -1) {
            current = LR_rotation(current);
        }
        else if (balance_factor_f(current->left) == 1) {
            current = right_rotation(current);
        }
    }
    return current;
}
AVL::Node* AVL::remove_recursive_forAVL(Node* current, const int& val) {
    if (current == nullptr) {
        return nullptr;
    }
    if (val < current->data) {
        current->left = remove_recursive_forAVL(current->left, val);
    }
    else if (val > current->data) {
        current->right = remove_recursive_forAVL(current->right, val);
    }
    else {
        if (current->left != nullptr && current->right != nullptr) {
            Node* temp = inorder_succesor(current->right);
            current->data = temp->data;
            current->right = remove_recursive_forAVL(current->right, temp->data);
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
    update_height(current);
    int balance_factor = balance_factor_f(current);
    if (balance_factor == -2) {
        if (balance_factor_f(current->right) == 1) {
            current = RL_rotation(current);
        }
        else if (balance_factor_f(current->right) == -1) {
            current = left_rotation(current);
        }
    }
    else  if (balance_factor == 2) {
        if (balance_factor_f(current->left) == -1) {
            current = LR_rotation(current);
        }
        else if (balance_factor_f(current->left) == 1) {
            current = right_rotation(current);
        }
    }
    return current;
}

AVL::Node* AVL::left_rotation(Node* current) {
    Node* old_parent = current;
    Node* new_parent = current->right;
    Node* subtree = new_parent->left;
    new_parent->left = old_parent;
    old_parent->right = subtree;
    update_height(old_parent);
    update_height(new_parent);
    return new_parent;
}
AVL::Node* AVL::right_rotation(Node* current) {
    Node* old_parent = current;
    Node* new_parent = current->left;
    Node* subtree = new_parent->right;
    new_parent->right = old_parent;
    old_parent->left = subtree;
    update_height(old_parent);
    update_height(new_parent);
    return new_parent;
}
AVL::Node* AVL::RL_rotation(Node* current) {
    Node* old_parent = current;
    Node* new_parent = current->right->left;
    Node* subnode = current->right;
    subnode = right_rotation(subnode);
    old_parent->right = subnode;
    old_parent = left_rotation(old_parent);
    return new_parent;
}
AVL::Node* AVL::LR_rotation(Node* current) {
    Node* old_parent = current;
    Node* new_parent = current->left->right;
    Node* subnode = current->left;
    subnode = left_rotation(subnode);
    old_parent->left = subnode;
    old_parent = right_rotation(old_parent);
    return new_parent;
}


AVL::Node* AVL::inorder_succesor(Node* current) {
    if (current->left == nullptr) {
        return current;
    }
    inorder_succesor(current->left);
}
// ----------------------------------------------------------------------- OVERRIDED PUBLIC METHODS -----------------------------------------------------------------------
void AVL::insert(const int& val) {
    root = insert_recursive_forAVL(root, val);
}
void AVL::remove(const int& val) {
    root = remove_recursive_forAVL(root, val);
}

void AVL::bst_lin_demo() {
    const int elements = 19999999;
    std::vector<int> elements_vec;
    elements_vec.reserve(elements);
    for (int i = 0; i < elements; i++) {
        elements_vec.push_back(i);
    }
    for (const int& i : elements_vec) {
        Node* newNode = new Node{ i, nullptr, nullptr, 0 };
        if (root == nullptr) {
            root = newNode;
        }
        else {
            insert(i);
        }
    }
}

//AVL::Node* AVL::inorder_succesor(Node* current) {}
//AVL::Node* AVL::inorder_preccesor(Node* current) {}

// ========================================================================================================================================================================
// ========================================================================================================================================================================
//                                                                             RED BLACK TREE
// ========================================================================================================================================================================
// ========================================================================================================================================================================

RBT::RBT() : root(nullptr) {}

RBT::RBT(std::initializer_list<int> tree) : root(nullptr) {
    for (const int& i : tree) {
        Node* newNode = new Node{ i, nullptr, nullptr, Color::black };
        if (root == nullptr) {
            root = newNode;
        }
        else {
            insert(i);
        }
    }
}
RBT::~RBT() {
    postorder_delete_recursive(root);
    root = nullptr;
}
//bool RBT::validate_properties() {
//
//}
// --------------------------------------------------------------------------- PRIVATE METHODS ----------------------------------------------------------------------------
RBT::Node* RBT::insert_recursive_forRBT(Node* current, const int& val) {
    if (current == nullptr) {
        return new Node{ val, nullptr, nullptr, Color::red };
    }
    else {
        if (current->data > val) {
            current->left = insert_recursive_forRBT(current->left, val);
        }
        else {
            current->right = insert_recursive_forRBT(current->right, val);
        }
    }
}
//RBT::Node* RBT::remove_recursive_forRBT(Node* current, const int& val) {
//
//}
// ----------------------------------------------------------------------- OVERRIDED PUBLIC METHODS -----------------------------------------------------------------------
void RBT::insert(const int& val) {
    root = insert_recursive_forRBT(root, val);
}
//void RBT::remove(const int& val) {
//    root = remove_recursive_forRBT(root, val);
//}