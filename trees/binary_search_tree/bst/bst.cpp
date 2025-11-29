#include <iostream>
#include "trees_lib.h"
#include "algorithms_timer.h"

int main()
{
    std::cout << "There is an example of binary search tree with int-data. " << std::endl;


    BST bst = { 50, 40, 60, 35, 45, 55, 65 };
    bst.bst_work_demo();

    std::cout << "balanced tree with O(log N)" << std::endl;
    BST bst_log;
    bst_log.bst_log_demo();

    bool node_exists;

    std::cout << "Node is in the tree: ";
    auto log_timer = [&]() {
        node_exists = bst_log.search(4999999);
    };

    std::cout << "code time for search: "
            << alg_timer::Timer::code_timer(log_timer)
            << std::endl;


    /*std::cout << "\n" << std::endl;

    std::cout << "unbalanced tree with O(N)" << std::endl;
    BST bst_lin;
    bst_lin.bst_lin_demo();

    std::cout << "code time for search: "
        << alg_timer::Timer::code_timer([&]() {
        std::cout << "Node is in the tree: " << bst_log.search(4999999);
            })
        << std::endl;*/

    return 0;
}