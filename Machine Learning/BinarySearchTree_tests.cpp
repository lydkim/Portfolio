// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
#include <sstream>

using namespace std;

TEST(empty_tree) {
    BinarySearchTree<int> my_tree;

    ASSERT_EQUAL(my_tree.empty(), true);
    ASSERT_EQUAL(my_tree.size(), 0);
    ASSERT_EQUAL(my_tree.height(), 0);
    ASSERT_EQUAL(my_tree.check_sorting_invariant(), true);
    ASSERT_TRUE(my_tree.min_greater_than(1) == my_tree.end());
    ASSERT_TRUE(my_tree.find(1) == my_tree.end());

    BinarySearchTree<int>::Iterator other_finding = my_tree.find(2);
    ASSERT_TRUE(other_finding == my_tree.end());
    ASSERT_TRUE(my_tree.min_element() == my_tree.end());
    ASSERT_TRUE(my_tree.max_element() == my_tree.end());

    ostringstream oss_preorder;
    my_tree.traverse_preorder(oss_preorder);
    ASSERT_TRUE(oss_preorder.str() == "");

    ostringstream oss_inorder;
    my_tree.traverse_inorder(oss_inorder);
    ASSERT_TRUE(oss_inorder.str() == "");
    
    BinarySearchTree<int> second_tree = my_tree;
    ASSERT_EQUAL(second_tree.empty(), true);
    ASSERT_EQUAL(second_tree.empty(), true);
    ASSERT_EQUAL(second_tree.size(), 0);
    ASSERT_EQUAL(second_tree.height(), 0);
    ASSERT_EQUAL(second_tree.check_sorting_invariant(), true);

}

TEST(insert) {
    BinarySearchTree<int> my_tree;

    my_tree.insert(5);
    my_tree.insert(3);
    my_tree.insert(4);
    my_tree.insert(7);

    ASSERT_EQUAL(my_tree.empty(), false);
    ASSERT_EQUAL(my_tree.size(), 4);
    ASSERT_EQUAL(my_tree.height(), 3);
    ASSERT_EQUAL(my_tree.check_sorting_invariant(), true);
    ASSERT_TRUE(*my_tree.find(3) == 3);
    ASSERT_EQUAL(my_tree.find(2), my_tree.end());

    ASSERT_TRUE(*my_tree.max_element() == 7);
    ASSERT_TRUE(*my_tree.min_element() == 3);
    ASSERT_TRUE(*my_tree.min_greater_than(5) == 7);
    ASSERT_TRUE(my_tree.min_greater_than(8) == my_tree.end());

    ostringstream oss_preorder;
    my_tree.traverse_preorder(oss_preorder);
    ASSERT_TRUE(oss_preorder.str() == "5 3 4 7 ");

    ostringstream oss_inorder;
    my_tree.traverse_inorder(oss_inorder);
    ASSERT_TRUE(oss_inorder.str() == "3 4 5 7 ");

    BinarySearchTree<int>::Iterator iter = my_tree.min_element();
    ASSERT_EQUAL(*iter, 3);

    BinarySearchTree<int>::Iterator it = my_tree.max_element();
    ASSERT_EQUAL(*it, 7);

    BinarySearchTree<int>::Iterator iter1 = my_tree.min_greater_than(2);
    ASSERT_EQUAL(*iter1, 3);

    BinarySearchTree<int>::Iterator finding = my_tree.find(3);
    ASSERT_EQUAL(*finding, 3);

    BinarySearchTree<int>::Iterator other_finding = my_tree.find(2);
    ASSERT_TRUE(other_finding == my_tree.end());

    BinarySearchTree<int>::Iterator inserting;
    inserting = my_tree.insert(2);
    ASSERT_EQUAL(my_tree.empty(), false);
    ASSERT_EQUAL(my_tree.size(), 5);
    ASSERT_EQUAL(*my_tree.find(2), 2);
}

TEST(copy_ctor) {
    BinarySearchTree<int> my_tree;

    my_tree.insert(3);
    my_tree.insert(4);
    my_tree.insert(6);
    my_tree.insert(2);

    ASSERT_EQUAL(my_tree.empty(), false);
    ASSERT_EQUAL(my_tree.size(), 4);
    ASSERT_EQUAL(my_tree.height(), 3);
    ASSERT_EQUAL(my_tree.check_sorting_invariant(), true);

    ASSERT_TRUE(*my_tree.max_element() == 6);
    ASSERT_TRUE(*my_tree.min_element() == 2);
    ASSERT_TRUE(*my_tree.min_greater_than(1) == 2);

    BinarySearchTree<int> my_new_tree(my_tree);
    
    ASSERT_EQUAL(my_new_tree.empty(), false);
    ASSERT_EQUAL(my_new_tree.size(), 4);
    ASSERT_EQUAL(my_new_tree.height(), 3);
    ASSERT_EQUAL(my_new_tree.check_sorting_invariant(), true);
    ASSERT_EQUAL(*my_new_tree.find(3), 3);

}

TEST(operator_iterator) {
    BinarySearchTree<int> my_tree;
    my_tree.insert(2);
    my_tree.insert(1);
    my_tree.insert(3);
    my_tree.insert(4);
    my_tree.insert(7);
    my_tree.insert(6);
    my_tree.insert(8);
    my_tree.insert(5);
    BinarySearchTree<int>::Iterator iter = my_tree.begin();
    ASSERT_EQUAL(*iter, 1);
    ++iter;
    ASSERT_EQUAL(*iter, 2);
    ++iter;
    ASSERT_EQUAL(*iter, 3);
    ++iter;
    ASSERT_EQUAL(*iter, 4);
    ++iter;
    ASSERT_EQUAL(*iter, 5);

    ASSERT_EQUAL(my_tree.empty(), false);
    ASSERT_EQUAL(my_tree.size(), 8);
    ASSERT_EQUAL(my_tree.height(), 6);
    ASSERT_EQUAL(my_tree.check_sorting_invariant(), true);
    
    BinarySearchTree<int> new_tree = my_tree;
    ASSERT_EQUAL(new_tree.empty(), false);
    ASSERT_EQUAL(new_tree.size(), 8);
    ASSERT_EQUAL(new_tree.height(), 6);
    ASSERT_EQUAL(new_tree.check_sorting_invariant(), true);

    ostringstream oss_inorder;
    my_tree.traverse_inorder(oss_inorder);
    ASSERT_TRUE(oss_inorder.str() == "1 2 3 4 5 6 7 8 ");
}

TEST(increase_iterator) {
    BinarySearchTree<std::pair<int, double>> tree;
    auto it = tree.insert({ 3, 4.1 });
    ASSERT_EQUAL(it->first, 3);
    ASSERT_EQUAL(it->second, 4.1);
}

TEST(one_node) {
    BinarySearchTree<int> my_tree;
    my_tree.insert(1);

    ASSERT_EQUAL(my_tree.empty(), false);
    ASSERT_EQUAL(my_tree.size(), 1);
    ASSERT_EQUAL(my_tree.height(), 1);
    ASSERT_EQUAL(my_tree.check_sorting_invariant(), true);

    my_tree.insert(10);
    BinarySearchTree<int>::Iterator iter = my_tree.begin();
    BinarySearchTree<int>::Iterator it = my_tree.begin();
    ++it;
    ASSERT_TRUE(*iter != *it);
    ASSERT_FALSE(*iter == *it);

    my_tree.insert(2);
    my_tree.insert(3);
    it = my_tree.begin();
    ++iter;
    iter = my_tree.insert(4);
    ASSERT_EQUAL(my_tree.size(), 5);
    ASSERT_EQUAL(my_tree.check_sorting_invariant(), true);

    ++iter;
    iter = my_tree.insert(100);
    ASSERT_EQUAL(my_tree.size(), 6);
    ASSERT_EQUAL(my_tree.check_sorting_invariant(), true);
}

TEST(two_nodes) {
    BinarySearchTree<int> my_tree;
    my_tree.insert(1);
    my_tree.insert(2);

    ASSERT_EQUAL(my_tree.empty(), false);
    ASSERT_EQUAL(my_tree.size(), 2);
    ASSERT_EQUAL(my_tree.height(), 2);
    ASSERT_EQUAL(my_tree.check_sorting_invariant(), true);

    my_tree.insert(3);
    my_tree.insert(4);
    my_tree.insert(5);
    my_tree.insert(6);
    my_tree.insert(7);

    ASSERT_EQUAL(my_tree.empty(), false);
    ASSERT_EQUAL(my_tree.size(), 7);
    ASSERT_EQUAL(my_tree.height(), 7);
    ASSERT_TRUE(my_tree.size() == my_tree.height());
    ASSERT_EQUAL(my_tree.check_sorting_invariant(), true);
}

//min greater than tested
TEST(triange) {
    BinarySearchTree<int> my_tree;
    my_tree.insert(2);
    my_tree.insert(1);
    my_tree.insert(3);

    ASSERT_EQUAL(my_tree.empty(), false);
    ASSERT_EQUAL(my_tree.size(), 3);
    ASSERT_EQUAL(my_tree.height(), 2);
    ASSERT_EQUAL(my_tree.check_sorting_invariant(), true);

    my_tree.insert(5);
    my_tree.insert(0);
    my_tree.insert(6);
    my_tree.insert(7);

    ASSERT_TRUE(*my_tree.min_greater_than(4) == 5);

    *my_tree.begin() = 5;
    ASSERT_EQUAL(my_tree.check_sorting_invariant(), false);

}

TEST(unsigned_literal) {
    BinarySearchTree<int> b;
    ASSERT_EQUAL(b.height(), 0u);
}

TEST(sorting_invariant_false) {
    BinarySearchTree<int> b;
    b.insert(1);
    b.insert(0);
    // change first datum to 2, resulting in the first broken tree above
    *b.begin() = 2;
    ASSERT_FALSE(b.check_sorting_invariant());
}

TEST(test_stub) {
    // Add your tests here
    ASSERT_TRUE(true);
}

TEST_MAIN()
