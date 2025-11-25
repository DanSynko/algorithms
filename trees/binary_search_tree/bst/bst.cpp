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
    bst.remove(20);

    return 0;
}