#include <iostream>
#include "trees_lib.h"
#include "algorithms_timer.h"

int main()
{
    std::cout << "There is an example of AVL-tree with int-data.\n " << std::endl;
    std::cout << "Initializing with sorted data for demonstrating the self-balancing tree. " << std::endl;
    AVL avl = { 10, 20, 30, 40, 50, 35, 25, 15, 5, 100 };
    avl.bst_work_demo();


    std::cout << "\n" << std::endl;


    AVL avl_test;
    avl_test.bst_lin_demo();

    bool node_exists;

    auto avl_timer = alg_timer::Timer::code_timer([&]() {
        node_exists = avl_test.search(99999998);
        });
    auto avl_time_info = avl_timer.count();

    std::cout << "Node is in the tree: ";
    if (node_exists) {
        std::cout << "yes." << std::endl;
    }
    else {
        std::cout << "no." << std::endl;
    }
    std::cout << "Execution time of algorithm: " << avl_time_info << "ns." << std::endl;

    return 0;
}
