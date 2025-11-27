#include "pch.h"
#include "trees_lib.h"

class BST_TEST_Fixture : public ::testing::Test {
protected:
    BST bst = { 50, 40, 60, 35, 45, 55, 65 };
    /*virtual void SetUp() override {
        BST bst = { 50, 40, 60, 35, 45, 55, 65 };
    }*/
};



TEST_F(BST_TEST_Fixture, BST_search_TEST) {
	ASSERT_TRUE(bst.search(35));
}

TEST_F(BST_TEST_Fixture, BST_insert_TEST) {
	bst.insert(20);
	ASSERT_TRUE(bst.search(20));
}



TEST_F(BST_TEST_Fixture, BST_remove_leafnode_TEST) {
    ASSERT_NO_THROW(bst.remove(35));
    ASSERT_TRUE(bst.search(40));
}
TEST_F(BST_TEST_Fixture, BST_remove_onechild_TEST) {
    bst.insert(20);
    ASSERT_NO_THROW(bst.remove(35));
    ASSERT_TRUE(bst.search(20));
}
TEST_F(BST_TEST_Fixture, BST_remove_twochild_TEST) {
    bst.insert(20);
    bst.insert(25);
    ASSERT_NO_THROW(bst.remove(35));
    ASSERT_TRUE(bst.search(20));
    ASSERT_TRUE(bst.search(25));
}