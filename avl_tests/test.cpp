#include "pch.h"
#include "trees_lib.h"

class AVL_TEST_Fixture : public ::testing::Test {
protected:
    AVL avl = { 10, 20 };
};




TEST_F(AVL_TEST_Fixture, AVL_insert_TEST) {
    ASSERT_NO_THROW(avl.insert(30));
}
//TEST_F(AVL_TEST_Fixture, AVL_remove_TEST) {
//    ASSERT_NO_THROW(avl.remove(30));
//}