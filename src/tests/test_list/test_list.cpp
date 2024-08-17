#include "test_list.h"

#include <iostream>
#include <string>

TEST(TEST_LIST, test_constructor_1) {
  s21::list<int> a;
  std::list<int> b;
  EXPECT_EQ(a.empty(), b.empty());
}

TEST(TEST_LIST, test_constructor_2) {
  s21::list<int> a(15);
  std::list<int> b(15);
  EXPECT_EQ(a.size(), b.size());
}

TEST(TEST_LIST, test_constructor_3) {
  s21::list<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  std::list<int> b{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  EXPECT_TRUE(eq_list(a, b));
}
TEST(TEST_LIST, test_constructor_4) {
  s21::list<int> a{1};
  std::list<int> b{1};
  EXPECT_TRUE(eq_list(a, b));
}
TEST(TEST_LIST, test_constructor_5) {
  s21::list<int> a{1, 2, 431, 2, 321, 321312, 123, 21, 3, 12, 312, 3, 12};
  std::list<int> b{1, 2, 431, 2, 321, 321312, 123, 21, 3, 12, 312, 3, 12};

  EXPECT_TRUE(eq_list(a, b));
}

TEST(TEST_LIST, test_constructor_6) {
  s21::list<int> a{1, 2, 431, -2, 321, -321312, 123, 21, 3, -12, 312, -3, 12};
  std::list<int> b{1, 2, 431, -2, 321, -321312, 123, 21, 3, -12, 312, -3, 12};

  EXPECT_TRUE(eq_list(a, b));
}

TEST(TEST_LIST, test_constructor_7) {
  s21::list<int> a{1, 2, 431, -2, 321, -321312, 123, 21, 3, -12, 312, -3, 12};
  std::list<int> b{1, 2, 431, -2, 321, -321312, 123, 21, 3, -12, 312, -3, 12};
  s21::list<int> a_copy_list(a);
  std::list<int> b_copy_list(b);

  EXPECT_TRUE(eq_list(a_copy_list, b_copy_list));
}

TEST(TEST_LIST, test_constructor_8) {
  s21::list<int> a{1, 2, 431, 2, 321, 321312, 123, 21, 3, 12, 312, 3, 12};
  std::list<int> b{1, 2, 431, 2, 321, 321312, 123, 21, 3, 12, 312, 3, 12};
  s21::list<int> a_copy_list(a);
  std::list<int> b_copy_list(b);

  EXPECT_TRUE(eq_list(a_copy_list, b_copy_list));
}

TEST(TEST_LIST, test_constructor_9) {
  s21::list<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  std::list<int> b{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  s21::list<int> a_copy_list(a);
  std::list<int> b_copy_list(b);

  EXPECT_TRUE(eq_list(a_copy_list, b_copy_list));
}

TEST(TEST_LIST, test_constructor_10) {
  s21::list<int> a(15);
  std::list<int> b(15);
  s21::list<int> a_copy_list(a);
  std::list<int> b_copy_list(b);

  EXPECT_TRUE(eq_list(a_copy_list, b_copy_list));
}

TEST(TEST_LIST, test_constructor_11) {
  s21::list<int> a{1, 2, 431, -2, 321, -321312, 123, 21, 3, -12, 312, -3, 12};
  std::list<int> b{1, 2, 431, -2, 321, -321312, 123, 21, 3, -12, 312, -3, 12};
  s21::list<int> a_copy_list(std::move(a));
  std::list<int> b_copy_list(std::move(b));

  EXPECT_TRUE(eq_list(a_copy_list, b_copy_list));
  EXPECT_EQ(a.empty(), b.empty());
}

TEST(TEST_LIST, test_constructor_12) {
  s21::list<int> a{1, 2, 431, 2, 321, 321312, 123, 21, 3, 12, 312, 3, 12};
  std::list<int> b{1, 2, 431, 2, 321, 321312, 123, 21, 3, 12, 312, 3, 12};
  s21::list<int> a_copy_list(std::move(a));
  std::list<int> b_copy_list(std::move(b));

  EXPECT_TRUE(eq_list(a_copy_list, b_copy_list));
  EXPECT_EQ(a.empty(), b.empty());
}

TEST(TEST_LIST, test_constructor_13) {
  s21::list<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  std::list<int> b{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  s21::list<int> a_copy_list(std::move(a));
  std::list<int> b_copy_list(std::move(b));

  EXPECT_TRUE(eq_list(a_copy_list, b_copy_list));
  EXPECT_EQ(a.empty(), b.empty());
}

TEST(TEST_LIST, test_constructor_14) {
  s21::list<int> a(15);
  std::list<int> b(15);
  s21::list<int> a_copy_list(std::move(a));
  std::list<int> b_copy_list(std::move(b));

  EXPECT_TRUE(eq_list(a_copy_list, b_copy_list));
  EXPECT_EQ(a.empty(), b.empty());
}

TEST(TEST_LIST, test_constructor_15) {
  s21::list<int> a{1, 2, 431, -2, 321, -321312, 123, 21, 3, -12, 312, -3, 12};
  std::list<int> b{1, 2, 431, -2, 321, -321312, 123, 21, 3, -12, 312, -3, 12};
  s21::list<int> a_copy_list = std::move(a);
  std::list<int> b_copy_list = std::move(b);

  EXPECT_TRUE(eq_list(a_copy_list, b_copy_list));
  EXPECT_EQ(a.empty(), b.empty());
}


TEST(TEST_LIST, test_constructor_16) {
  s21::list<int> a{1, 2, 431, 2, 321, 321312, 123, 21, 3, 12, 312, 3, 12};
  std::list<int> b{1, 2, 431, 2, 321, 321312, 123, 21, 3, 12, 312, 3, 12};
  s21::list<int> a_copy_list = std::move(a);
  std::list<int> b_copy_list = std::move(b);

  EXPECT_TRUE(eq_list(a_copy_list, b_copy_list));
  EXPECT_EQ(a.empty(), b.empty());
}

TEST(TEST_LIST, test_constructor_17) {
  s21::list<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  std::list<int> b{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  s21::list<int> a_copy_list = std::move(a);
  std::list<int> b_copy_list = std::move(b);

  EXPECT_TRUE(eq_list(a_copy_list, b_copy_list));
  EXPECT_EQ(a.empty(), b.empty());
}

TEST(TEST_LIST, test_constructor_18) {
  s21::list<int> a(15);
  std::list<int> b(15);
  s21::list<int> a_copy_list = std::move(a);
  std::list<int> b_copy_list = std::move(b);

  EXPECT_TRUE(eq_list(a_copy_list, b_copy_list));
  EXPECT_EQ(a.empty(), b.empty());
}

TEST(TEST_LIST, test_front_1) {
  s21::list<char> a;
  std::list<char> b;
  a.push_front('1');
  b.push_front('1');

  EXPECT_EQ(a.front(), b.front());
  EXPECT_EQ(a.back(), b.back());
  a.push_front('2');
  b.push_front('2');
  EXPECT_EQ(a.front(), b.front());
  EXPECT_EQ(a.back(), b.back());
  a.push_front('3');
  b.push_front('3');
  EXPECT_EQ(a.front(), b.front());
  EXPECT_EQ(a.back(), b.back());
}

TEST(TEST_LIST, test_back_1) {
  s21::list<int> a;
  std::list<int> b;
  a.push_back('1');
  b.push_back('1');
  EXPECT_EQ(a.front(), b.front());
  EXPECT_EQ(a.back(), b.back());
  a.push_back('2');
  b.push_back('2');
  EXPECT_EQ(a.front(), b.front());
  EXPECT_EQ(a.back(), b.back());
  a.push_back('3');
  b.push_back('3');
  EXPECT_EQ(a.front(), b.front());
  EXPECT_EQ(a.back(), b.back());
}

TEST(TEST_LIST, test_pop_front) {
  s21::list<int> our_list;
  std::list<int> std_list;
  our_list.push_back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.pop_front();
  std_list.pop_front();
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  EXPECT_TRUE(eq_list(our_list, std_list));
}

TEST(TEST_LIST, test_pop_back) {
  s21::list<int> our_list;
  std::list<int> std_list;
  our_list.push_back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.pop_back();
  std_list.pop_back();
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  EXPECT_TRUE(eq_list(our_list, std_list));
}

TEST(TEST_LIST, test_iterator_begin_1) {
  s21::list<int> a{1, 2, 431, -2, 321, -321312, 123, 21, 3, -12, 312, -3, 12};
  std::list<int> b{1, 2, 431, -2, 321, -321312, 123, 21, 3, -12, 312, -3, 12};
  EXPECT_EQ(*(a.begin()), *(b.begin()));
  a.pop_front();
  b.pop_front();
  EXPECT_EQ(*(a.begin()), *(b.begin()));
  a.pop_front();
  b.pop_front();
  a.pop_front();
  b.pop_front();
  a.pop_front();
  b.pop_front();
  EXPECT_EQ(*(a.begin()), *(b.begin()));
}

TEST(TEST_LIST, test_iterator_begin_2) {
  s21::list<int> a{1};
  std::list<int> b{1};
  EXPECT_EQ(*(a.begin()), *(b.begin()));
}

TEST(TEST_LIST, test_front_2) {
  s21::list<int> a;
  EXPECT_THROW(a.front(), std::logic_error);
}

TEST(TEST_LIST, test_insert_1) {
  s21::list<double> our_list;
  std::list<double> std_list;
  s21::list<double>::iterator our_it;
  our_it = our_list.begin();
  std::list<double>::iterator std_it;
  std_it = std_list.begin();
  our_list.insert(our_it, 5.2321);
  std_list.insert(std_it, 5.2321);
  EXPECT_TRUE(eq_list(our_list, std_list));
  our_list.insert(our_it, 75.2321);
  std_list.insert(std_it, 75.2321);
  our_list.insert(our_it, 975.2321);
  std_list.insert(std_it, 975.2321);
  EXPECT_TRUE(eq_list(our_list, std_list));
}

TEST(TEST_LIST, test_insert_2) {
  s21::list<double> our_list = {1.231, 21.231, 321.231, 4321.231, 54321.231};
  std::list<double> std_list = {1.231, 21.231, 321.231, 4321.231, 54321.231};

  s21::list<double>::iterator our_it;
  our_it = our_list.begin();
  std::list<double>::iterator std_it;
  std_it = std_list.begin();
  our_it++;
  our_it++;
  std_it++;
  std_it++;
  our_list.insert(our_it, 75.2321);
  std_list.insert(std_it, 75.2321);
  our_list.insert(our_it, 6.2321);
  std_list.insert(std_it, 6.2321);
  EXPECT_TRUE(eq_list(our_list, std_list));
  our_it--;
  our_it--;
  std_it--;
  std_it--;
  our_list.insert(our_it, -75.2321);
  std_list.insert(std_it, -75.2321);
  our_list.insert(our_it, -6.2321);
  std_list.insert(std_it, -6.2321);
  EXPECT_TRUE(eq_list(our_list, std_list));
}

TEST(TEST_LIST, test_erase_1) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  our_list.erase(our_list.begin());
  std_list.erase(std_list.begin());
  EXPECT_TRUE(eq_list(our_list, std_list));

  EXPECT_THROW(our_list.erase(--our_list.begin()), std::logic_error);

  s21::list<int>::iterator our_it;
  our_it = our_list.begin();
  ++our_it;
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  ++std_it;
  our_list.erase(our_it);
  std_list.erase(std_it);
  EXPECT_TRUE(eq_list(our_list, std_list));
}

TEST(TEST_LIST, test_swap) {
  s21::list<int> s21_list1 = {6, 7, 8, 9, 10};
  s21::list<int> s21_list2 = {1, 2, 3, 4, 5};
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  std::list<int> std_list2 = {6, 7, 8, 9, 10};

  EXPECT_FALSE(eq_list(s21_list1, std_list1));
  EXPECT_FALSE(eq_list(s21_list2, std_list2));
  s21_list1.swap(s21_list2);
  EXPECT_TRUE(eq_list(s21_list1, std_list1));
  EXPECT_TRUE(eq_list(s21_list2, std_list2));
  std_list1.swap(std_list2);
  s21_list1.swap(s21_list2);
  EXPECT_TRUE(eq_list(s21_list1, std_list1));
  EXPECT_TRUE(eq_list(s21_list2, std_list2));
  std_list1.swap(std_list2);
  std_list1.swap(std_list2);
  std_list1.swap(std_list2);
  s21_list1.swap(s21_list2);
  s21_list1.swap(s21_list2);
  s21_list1.swap(s21_list2);
  EXPECT_TRUE(eq_list(s21_list1, std_list1));
  EXPECT_TRUE(eq_list(s21_list2, std_list2));
}

TEST(TEST_LIST, test_merge_1) {
  s21::list<std::string> s21_list1 = {"Hello, "};
  s21::list<std::string> s21_list2 = {"Wordl!"};
  std::list<std::string> std_list1 = {"Hello, "};
  std::list<std::string> std_list2 = {"Wordl!"};
  s21_list1.merge(s21_list2);
  std_list1.merge(std_list2);
  EXPECT_TRUE(eq_list(s21_list1, std_list1));
}
TEST(TEST_LIST, test_merge_2) {
  s21::list<std::string> s21_list1 = {"Hello, "};
  s21::list<std::string> s21_list2 = {"Hello!"};
  std::list<std::string> std_list1 = {"Hello, "};
  std::list<std::string> std_list2 = {"Wordl!"};
  s21_list1.merge(s21_list2);
  std_list1.merge(std_list2);
  EXPECT_FALSE(eq_list(s21_list1, std_list1));
}
TEST(TEST_LIST, test_merge_3) {
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 9, 90, 0};
  s21::list<int> s21_list2 = {1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 9, 90, 0};
  std::list<int> std_list1 = {1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 9, 90, 0};
  std::list<int> std_list2 = {1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 9, 90, 0};
  s21_list1.merge(s21_list2);
  std_list1.merge(std_list2);
  EXPECT_TRUE(eq_list(s21_list1, std_list1));
}

TEST(TEST_LIST, test_merge_4) {
  s21::list<double> s21_list1 = {1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 9, 90, 0};
  s21::list<double> s21_list2 = {1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 9, 90, 0};
  std::list<double> std_list1 = {1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 9, 90, 0};
  std::list<double> std_list2 = {1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 9, 90, 0};
  s21_list1.merge(s21_list2);
  std_list1.merge(std_list2);
  EXPECT_TRUE(eq_list(s21_list1, std_list1));
}

TEST(TEST_LIST, test_merge_5) {
  s21::list<double> s21_list1 = {};
  s21::list<double> s21_list2 = {};
  std::list<double> std_list1 = {};
  std::list<double> std_list2 = {};
  s21_list1.merge(s21_list2);
  std_list1.merge(std_list2);
  EXPECT_TRUE(eq_list(s21_list1, std_list1));
}

TEST(TEST_LIST, test_merge_6) {
  s21::list<double> s21_list1{1, 2, 3, 5};
  s21::list<double> s21_list2{4, 5, 10, 5};
  std::list<double> std_list1{1, 2, 3, 5};
  std::list<double> std_list2{4, 5, 10, 5};
  s21_list1.merge(s21_list2);
  std_list1.merge(std_list2);
  EXPECT_TRUE(eq_list(s21_list1, std_list1));
}

TEST(TEST_LIST, test_merge_7) {
  s21::list<double> s21_list1{1, 2, 3, 5};
  s21::list<double> s21_list2{-54, 5, 10, 5};
  std::list<double> std_list1{1, 2, 3, 5};
  std::list<double> std_list2{-54, 5, 10, 5};
  s21_list1.merge(s21_list2);
  std_list1.merge(std_list2);
  EXPECT_TRUE(eq_list(s21_list1, std_list1));
}
TEST(TEST_LIST, test_splice_1) {
  s21::list<int> our_list_first = {1};
  s21::list<int> our_list_second = {2, 3, 4, 5};
  std::list<int> std_list_first = {1};
  std::list<int> std_list_second = {2, 3, 4, 5};
  s21::list<int>::iterator our_it = our_list_first.begin();
  std::list<int>::iterator std_it = std_list_first.begin();
  our_list_first.splice(our_it, our_list_second);
  std_list_first.splice(std_it, std_list_second);
  EXPECT_EQ(our_list_first.front(), std_list_first.front());
  EXPECT_EQ(our_list_first.back(), std_list_first.back());
}

TEST(TEST_LIST, test_splice_2) {
  s21::list<int> our_list_first = {1};
  s21::list<int> our_list_second = {2, 3, 4, 5};
  std::list<int> std_list_first = {1};
  std::list<int> std_list_second = {2, 3, 4, 5};
  s21::list<int>::iterator our_it = --our_list_first.begin();
  std::list<int>::iterator std_it = --std_list_first.begin();
  our_list_first.splice(our_it, our_list_second);
  std_list_first.splice(std_it, std_list_second);
  EXPECT_EQ(our_list_first.front(), std_list_first.front());
  EXPECT_EQ(our_list_first.back(), std_list_first.back());
}

TEST(TEST_LIST, test_reverce_1) {
  s21::list<int> s21_l1 = {1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 9, 90, 0};
  std::list<int> std_l1 = {1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 9, 90, 0};
  s21_l1.reverse();
  std_l1.reverse();
  EXPECT_TRUE(eq_list(s21_l1, std_l1));
}

TEST(TEST_LIST, test_reverce_2) {
  s21::list<char> s21_l1 = {'1', '2', '3', '4', '5', '6',
                            '7', '7', '8', '9', '9', '0'};
  std::list<char> std_l1 = {'1', '2', '3', '4', '5', '6',
                            '7', '7', '8', '9', '9', '0'};
  s21_l1.reverse();
  std_l1.reverse();
  EXPECT_TRUE(eq_list(s21_l1, std_l1));
}
TEST(TEST_LIST, test_reverce_3) {
  s21::list<int> s21_l1 = {};
  std::list<int> std_l1 = {};
  s21_l1.reverse();
  std_l1.reverse();
  EXPECT_TRUE(eq_list(s21_l1, std_l1));
}
TEST(TEST_LIST, test_unique_1) {
  s21::list<int> s21_l1 = {1, 2, 3, 3, 3, 3, 3, 4, 5, 6, 7, 7, 8, 9, 9, 90, 0};
  std::list<int> std_l1 = {1, 2, 3, 3, 3, 3, 3, 4, 5, 6, 7, 7, 8, 9, 9, 90, 0};
  s21_l1.unique();
  std_l1.unique();
  EXPECT_TRUE(eq_list(s21_l1, std_l1));
}

TEST(TEST_LIST, test_unique_2) {
  s21::list<char> s21_l1 = {'1', '2', '2', '2', '2', '2', '2', '3', '4', '4',
                            '4', '4', '5', '6', '7', '7', '8', '9', '9', '0'};
  std::list<char> std_l1 = {'1', '2', '2', '2', '2', '2', '2', '3', '4', '4',
                            '4', '4', '5', '6', '7', '7', '8', '9', '9', '0'};
  s21_l1.unique();
  std_l1.unique();
  EXPECT_TRUE(eq_list(s21_l1, std_l1));
}

TEST(TEST_LIST, test_unique_3) {
  s21::list<int> s21_l1 = {9, 23, 23, 231212, 3, 123, 12, 3123, 1, 2, 3,  3, 3,
                           3, 3,  4,  5,      6, 7,   7,  8,    9, 9, 90, 0};
  std::list<int> std_l1 = {9, 23, 23, 231212, 3, 123, 12, 3123, 1, 2, 3,  3, 3,
                           3, 3,  4,  5,      6, 7,   7,  8,    9, 9, 90, 0};
  s21_l1.unique();
  std_l1.unique();
  EXPECT_TRUE(eq_list(s21_l1, std_l1));
}
TEST(TEST_LIST, test_unique_4) {
  s21::list<int> s21_l1 = {};
  std::list<int> std_l1 = {};
  s21_l1.unique();
  std_l1.unique();
  EXPECT_TRUE(eq_list(s21_l1, std_l1));
}
TEST(TEST_LIST, test_sort_1) {
  s21::list<int> a{1, 2, 431, 2, 321, 321312, 123, 21, 3, 12, 312, 3, 12};
  std::list<int> b{1, 2, 431, 2, 321, 321312, 123, 21, 3, 12, 312, 3, 12};
  a.sort();
  b.sort();

  EXPECT_TRUE(eq_list(a, b));
}

TEST(TEST_LIST, test_sort_2) {
  s21::list<int> a{};
  std::list<int> b{};
  a.sort();
  b.sort();

  EXPECT_TRUE(eq_list(a, b));
}

TEST(TEST_LIST, test_sort_3) {
  s21::list<int> a{87321, 321, 123, 2, 5,     4356, 345, 6, 132, 12, 3,
                   123,   213, 12,  3, 43645, 6,    45,  6, 54,  6};
  std::list<int> b{87321, 321, 123, 2, 5,     4356, 345, 6, 132, 12, 3,
                   123,   213, 12,  3, 43645, 6,    45,  6, 54,  6};
  a.sort();
  b.sort();

  EXPECT_TRUE(eq_list(a, b));
}

TEST(TEST_LIST, test_max_size_1) {
  s21::list<char> a;
  std::list<char> b;
  EXPECT_EQ(a.max_size(), b.max_size());
}

TEST(TEST_LIST, test_max_size_2) {
  s21::list<int> a;
  std::list<int> b;
  EXPECT_EQ(a.max_size(), b.max_size());
}

TEST(TEST_LIST, test_max_size_3) {
  s21::list<double> a;
  std::list<double> b;
  EXPECT_EQ(a.max_size(), b.max_size());
}

TEST(TEST_LIST, Insert) {
  s21::list<int> our_list;
  std::list<int> std_list;
  s21::list<int>::iterator our_it;
  our_it = our_list.begin();
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  our_list.insert(our_it, 5);
  std_list.insert(std_it, 5);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.insert(our_it, 7);
  std_list.insert(std_it, 7);
  our_list.insert(our_it, 9);
  std_list.insert(std_it, 9);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(TEST_LIST, Erase) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  our_list.erase(our_list.begin());
  std_list.erase(std_list.begin());
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  s21::list<int>::iterator our_it;
  our_it = our_list.begin();
  ++our_it;
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  ++std_it;
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(TEST_LIST, Splice) {
  s21::list<int> our_list_first = {1};
  s21::list<int> our_list_second = {2, 3, 4, 5};
  std::list<int> std_list_first = {1};
  std::list<int> std_list_second = {2, 3, 4, 5};
  s21::list<int>::iterator our_it = our_list_first.begin();
  std::list<int>::iterator std_it = std_list_first.begin();
  our_list_first.splice(our_it, our_list_second);
  std_list_first.splice(std_it, std_list_second);
  EXPECT_EQ(our_list_first.front(), std_list_first.front());
  EXPECT_EQ(our_list_first.back(), std_list_first.back());
}

TEST(TEST_LIST, Merge) {
  s21::list<int> our_list_first = {1};
  s21::list<int> our_list_second = {2, 3, 4, 5};
  std::list<int> std_list_first = {1};
  std::list<int> std_list_second = {2, 3, 4, 5};
  our_list_first.merge(our_list_second);
  std_list_first.merge(std_list_second);
  EXPECT_EQ(our_list_first.front(), std_list_first.front());
  EXPECT_EQ(our_list_first.back(), std_list_first.back());
  EXPECT_EQ(our_list_second.empty(), std_list_second.empty());
}

TEST(TEST_LIST, Reverse) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  our_list.reverse();
  std_list.reverse();
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(TEST_LIST, Unique) {
  s21::list<int> our_list = {1, 2, 2, 3, 3};
  std::list<int> std_list = {1, 2, 2, 3, 3};
  s21::list<int>::iterator our_it;
  std::list<int>::iterator std_it;
  our_list.unique();
  std_list.unique();
  our_it = our_list.begin();
  std_it = std_list.begin();
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(TEST_LIST, Sort) {
  s21::list<int> our_list = {2, 4, 1, 3, 5};
  std::list<int> std_list = {2, 4, 1, 3, 5};
  s21::list<int>::iterator our_it;
  std::list<int>::iterator std_it;
  our_list.sort();
  std_list.sort();
  our_it = our_list.begin();
  std_it = std_list.begin();
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);

  auto iterEnd = our_list.end();
  iterEnd++;
  iterEnd++;
  EXPECT_EQ(iterEnd, nullptr);
  auto iterBegin = our_list.begin();
  iterBegin--;
  iterBegin--;
  EXPECT_EQ(iterBegin, nullptr);
}

TEST(TEST_LIST, test_insert_many) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator our_it = our_list.begin();
  ++our_it;
  our_list.insert_many(our_it, 7, 8, 9);
  our_it = our_list.begin();
  EXPECT_EQ(*our_it, 1);
  ++our_it;
  EXPECT_EQ(*our_it, 7);
  ++our_it;
  EXPECT_EQ(*our_it, 8);
  ++our_it;
  EXPECT_EQ(*our_it, 9);
  ++our_it;
  EXPECT_EQ(*our_it, 2);
}

TEST(TEST_LIST, Insert_Many_Back) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator our_it;
  our_list.insert_many_back(7, 8, 9);
  EXPECT_EQ(our_list.back(), 9);
  our_list.pop_back();
  EXPECT_EQ(our_list.back(), 8);
  our_list.pop_back();
  EXPECT_EQ(our_list.back(), 7);
  our_list.pop_back();
  EXPECT_EQ(our_list.back(), 5);
  our_list.pop_back();
  EXPECT_EQ(our_list.back(), 4);
}

TEST(TEST_LIST, Insert_Many_Front) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator our_it;
  our_list.insert_many_front(7, 8, 9);
  our_it = our_list.begin();
  EXPECT_EQ(*our_it, 9);
  ++our_it;
  EXPECT_EQ(*our_it, 8);
  ++our_it;
  EXPECT_EQ(*our_it, 7);
  ++our_it;
  EXPECT_EQ(*our_it, 1);
  ++our_it;
  EXPECT_EQ(*our_it, 2);
}

TEST(TEST_LIST, Insert_Many_Back2) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator our_it;
  our_list.insert_many_back();
  EXPECT_EQ(our_list.back(), 5);
  our_list.pop_back();
  EXPECT_EQ(our_list.back(), 4);
  our_list.pop_back();
  EXPECT_EQ(our_list.back(), 3);
  our_list.pop_back();
  EXPECT_EQ(our_list.back(), 2);
  our_list.pop_back();
  EXPECT_EQ(our_list.back(), 1);
}

TEST(TEST_LIST, Insert_Many_Front_2) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator our_it;
  our_list.insert_many_front();
  our_it = our_list.begin();
  EXPECT_EQ(*our_it, 1);
  ++our_it;
  EXPECT_EQ(*our_it, 2);
  ++our_it;
  EXPECT_EQ(*our_it, 3);
  ++our_it;
  EXPECT_EQ(*our_it, 4);
  ++our_it;
  EXPECT_EQ(*our_it, 5);
}