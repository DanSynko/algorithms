#include <iostream>
#include "bst_lib.h"

int main()
{
    std::cout << "There is an example of binary search tree with int-data. " << std::endl;

    // balanced tree with O(log N)
    BST bst = { 50, 40, 60, 35, 45, 55, 65 };

    std::cout << "search(51); " << std::endl;
    if (bst.search(51)) {
        std::cout << "This element exists. " << std::endl;
    }
    else {
        std::cout << "This element NOT exists. " << std::endl;
    }
    std::cout << "insert(20); " << std::endl;
    bst.insert(20);
    std::cout << "remove(20); " << std::endl;
    bst.remove(20);
    std::cout << "inorder_traversal(); " << std::endl;
    bst.inorder_traversal();
    std::cout << std::endl;
    std::cout << "preorder_traversal(); " << std::endl;
    bst.preorder_traversal();
    std::cout << std::endl;
    std::cout << "postorder_traversal(); " << std::endl;
    bst.postorder_traversal();

    return 0;
}