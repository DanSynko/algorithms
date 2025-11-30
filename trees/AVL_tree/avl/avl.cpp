#include <iostream>
#include "trees_lib.h"
//#include "algorithms_timer.h"

int main()
{
    std::cout << "There is an example of AVL-tree with int-data.\n " << std::endl;

    std::cout << "Initializing with sorted data for demonstrating the self-balancing tree. " << std::endl;
    AVL avl = { 10, 20, 30, 40, 50, 35, 25, 15, 5, 100 };
    avl.insert(7);
    avl.inorder_traversal();
    std::cout << std::endl;
    avl.postorder_traversal();
    std::cout << std::endl;
    avl.preorder_traversal();
    std::cout << std::endl;
    /*avl.bst_work_demo();*/

    return 0;
}
