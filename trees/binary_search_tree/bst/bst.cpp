#include <iostream>
#include "trees_lib.h"
#include "algorithms_timer.h"

int main()
{
    std::cout << "There is an example of binary search tree with int-data. " << std::endl;


    /*BST bst = { 50, 40, 60, 35, 45, 55, 65 };
    bst.bst_work_demo();*/


    std::cout << "\n" << std::endl;


    std::cout << "balanced tree with O(log N)" << std::endl;

    BST bst_log;
    bst_log.bst_log_demo();

    bool node_exists_log;

    auto log_timer = alg_timer::Timer::code_timer([&]() {
        node_exists_log = bst_log.search(4999999);
    });
    auto log_time_info = log_timer.count();

    std::cout << "Node is in the tree: ";
    if (node_exists_log) {
        std::cout << "yes." << std::endl;
    }
    else {
        std::cout << "no." << std::endl;
    }
    std::cout << "Execution time of algorithm: " << log_time_info << "ns." << std::endl;


    /*std::cout << "\n" << std::endl;


    std::cout << "for comparison: unbalanced tree with O(N)" << std::endl;
    BST bst_lin;
    bst_lin.bst_lin_demo();

    bool node_exists_lin;

    auto lin_timer = alg_timer::Timer::code_timer([&]() {
        node_exists_lin = bst_lin.search(4999999);
    });
    auto lin_time_info = lin_timer.count();

    std::cout << "Node is in the tree: ";
    if (node_exists_lin) {
        std::cout << "yes." << std::endl;
    }
    else {
        std::cout << "no." << std::endl;
    }

    std::cout << "Execution time of algorithm: " << lin_time_info << "ns." << std::endl;*/

    return 0;
}