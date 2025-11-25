#include "pch.h"
#include "bst_lib.h"

BST bst = { 50, 40, 60, 35, 45, 55, 65 };

TEST(BSTtest, BST_search_test) {
	ASSERT_TRUE(bst.search(35));
}

TEST(BSTtest, BST_insert_test) {
	bst.insert(20);
	ASSERT_TRUE(bst.search(20));
}

TEST(BSTtest, BST_remove_test) {
	bst.remove(20);
	ASSERT_TRUE(bst.search(20));
}