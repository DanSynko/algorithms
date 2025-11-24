#include "pch.h"
#include "bst.h"

TEST(BSTtest, BST_search_test) {
	BST bst = { 50, 49, 51 };
	ASSERT_TRUE(bst.search(51));
}