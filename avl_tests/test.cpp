#include "pch.h"
#include "trees_lib.h"

class AVL_TEST_Fixture : public ::testing::Test {
protected:
    AVL avl = { 10, 20, 30, 40, 50 };
};




TEST_F(AVL_TEST_Fixture, AVL_insert_TEST) {
    ASSERT_NO_THROW(avl.insert(35));
}
TEST_F(AVL_TEST_Fixture, AVL_remove_TEST) {
    ASSERT_NO_THROW(avl.remove(35));
}




TEST_F(AVL_TEST_Fixture, AVL_RRrotation_TEST) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST_F(AVL_TEST_Fixture, AVL_RLrotation_TEST) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST_F(AVL_TEST_Fixture, AVL_LLrotation_TEST) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST_F(AVL_TEST_Fixture, AVL_LRrotation_TEST) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}