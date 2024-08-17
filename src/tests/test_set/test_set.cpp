#include "test_set.h"

#include <gtest/gtest.h>

#include <string>

TEST(TEST_SET, DefaultConstructor) {
  s21::set<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(TEST_SET, ConstructorDefaultSet) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
}

TEST(TEST_SET, InitializerListConstructor) {
  s21::set<int> s = {1, 2, 3};
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(TEST_SET, ConstructorInitializerSet) {
  s21::set<char> my_set = {'x', 'b', 'z', 'y'};
  std::set<char> orig_set = {'x', 'b', 'z', 'y'};
  EXPECT_EQ(my_set.size(), orig_set.size());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(TEST_SET, ConstructorInitializer2Set) {
  s21::set<char> my_set = {};
  std::set<char> orig_set = {};
  EXPECT_EQ(my_set.size(), orig_set.size());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(TEST_SET, ConstructorInitializer3Set) {
  s21::set<char> my_set = {'x', 'b', 'z', 'y'};
  std::set<char> orig_set = {'x', 'b', 'z', 'y'};
  EXPECT_EQ(my_set.size(), orig_set.size());
  auto my_it = --my_set.end();
  auto orig_it = --orig_set.end();
  for (; my_it != my_set.begin(); --my_it, --orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(TEST_SET, CopyConstructor) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2(s1);
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(TEST_SET, ConstructorCopySet) {
  s21::set<int> my_set = {1, 2, 3, 4, 5};
  std::set<int> orig_set = {1, 2, 3, 4, 5};
  s21::set<int> my_set_copy = my_set;
  std::set<int> orig_set_copy = orig_set;
  EXPECT_EQ(my_set_copy.size(), orig_set_copy.size());
  auto my_it = my_set_copy.begin();
  auto orig_it = orig_set_copy.begin();
  for (; my_it != my_set_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(TEST_SET, MoveConstructor) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2(std::move(s1));
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(TEST_SET, ConstructorMoveSet) {
  s21::set<int> my_set = {1, 2, 3, 4, 5};
  std::set<int> orig_set = {1, 2, 3, 4, 5};
  s21::set<int> my_set_copy = std::move(my_set);
  std::set<int> orig_set_copy = std::move(orig_set);
  EXPECT_EQ(my_set.size(), orig_set.size());
  EXPECT_EQ(my_set_copy.size(), orig_set_copy.size());
  auto my_it = my_set_copy.begin();
  auto orig_it = orig_set_copy.begin();
  for (; my_it != my_set_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(TEST_SET, BeginEnd) {
  s21::set<int> s{3, 5, 1, 4, 2};
  auto it = s.begin();
  ASSERT_EQ(*it, 1);

  it = s.end();
  ASSERT_EQ(it, nullptr);

  s.clear();
  it = s.begin();
  ASSERT_EQ(it, nullptr);
}

TEST(TEST_SET, SetIteratorsSet) {
  s21::set<std::string> my_set = {"This", "is", "my", "set"};
  std::set<std::string> orig_set = {"This", "is", "my", "set"};
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  EXPECT_TRUE(*orig_it == *my_it);
  my_it = my_set.end();
  orig_it = orig_set.end();
  --my_it;
  --orig_it;
  EXPECT_TRUE(*orig_it == *my_it);
}
TEST(TEST_SET, OperatorMinus) {
  s21::set<std::string> my_set;
  auto it = my_set.begin();
  it--;
  EXPECT_THROW(*it, std::runtime_error);
}

TEST(TEST_SET, SizeMaxSize) {
  s21::set<int> s{3, 5, 1, 4, 2};
  std::set<int> s1{3, 5, 1, 4, 2};
  ASSERT_EQ(s.size(), 5);
  ASSERT_GE(s.max_size(), s1.max_size());

  s.clear();
  ASSERT_EQ(s.size(), 0);
}

TEST(TEST_SET, CapacitySet) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('b');
  orig_empty_set.insert('c');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(TEST_SET, Erase) {
  s21::set<int> s{1, 2, 3, 4, 5};
  auto it = s.find(3);
  s.erase(it);
  EXPECT_EQ(s.size(), 4);
  EXPECT_FALSE(s.contains(3));
}

TEST(TEST_SET, Erase2) {
  s21::set<int> s;
  auto it = s.begin();
  s.erase(it);
  EXPECT_THROW(*it, std::runtime_error);
}

TEST(TEST_SET, Erase3) {
  s21::set<int> s{1, -1, 2, 10, 12, 8};
  auto it = s.find(10);
  s.erase(it);
}

TEST(TEST_SET, EraseSet) {
  s21::set<int> my_set = {5, 4, 3, 2, 7, 8, 9};
  std::set<int> orig_set = {5, 4, 3, 2, 7, 8, 9};

  my_set.erase(my_set.begin());
  orig_set.erase(orig_set.begin());
  EXPECT_EQ(my_set.size(), orig_set.size());
}

TEST(TEST_SET, Swap) {
  s21::set<int> s1{1, 2, 3};
  s21::set<int> s2{4, 5, 6};
  s1.swap(s2);
  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s1.contains(4));
}

TEST(TEST_SET, SwapSet) {
  s21::set<int> my_set = {1};
  s21::set<int> my_swap_set = {3, 4, 5};

  my_set.swap(my_swap_set);
  EXPECT_EQ(my_set.size(), 3);
  EXPECT_EQ(my_swap_set.size(), 1);
  EXPECT_EQ(*my_set.begin(), 3);
  EXPECT_EQ(*my_swap_set.begin(), 1);
}

TEST(TEST_SET, Merge) {
  s21::set<int> s1{1, 2, 3};
  s21::set<int> s2{3, 4, 5};
  s1.merge(s2);
  EXPECT_EQ(s1.size(), 5);
  EXPECT_EQ(s2.size(), 0);
  EXPECT_TRUE(s1.contains(4));
  EXPECT_FALSE(s2.contains(3));
}

TEST(TEST_SET, MergeSet) {
  s21::set<int> my_set = {1};
  s21::set<int> my_merge_set = {3, 4, 5};
  my_set.merge(my_merge_set);

  std::set<int> orig_set = {1};
  std::set<int> orig_merge_set = {3, 4, 5};
  orig_set.merge(orig_merge_set);
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
  EXPECT_EQ(orig_set.size(), my_set.size());
  EXPECT_EQ(my_merge_set.size(), orig_merge_set.size());
}

TEST(TEST_SET, Find) {
  s21::set<int> s{1, 2, 3};
  auto it1 = s.find(2);
  EXPECT_EQ(*it1, 2);
  auto it2 = s.find(4);
  EXPECT_EQ(it2, s.end());
}

TEST(TEST_SET, ClearSet) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('a');
  orig_empty_set.insert('b');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(TEST_SET, insertMany) {
  s21::set<int> my_set = {1, 2, 3, 4, 56};
  my_set.insert_many(12, 3, 4, 56, 6, 2);
}

TEST(TEST_SET, InsertSet) {
  s21::set<std::string> my_set = {"This", "is", "my", "set"};
  std::set<std::string> orig_set = {"This", "is", "my", "set"};
  auto my_pr = my_set.insert("best");
  auto orig_pr = orig_set.insert("best");
  EXPECT_TRUE(my_pr.second == orig_pr.second);
  EXPECT_TRUE(*my_pr.first == *orig_pr.first);
  my_pr = my_set.insert("is");
  orig_pr = orig_set.insert("is");
  EXPECT_TRUE(my_pr.second == orig_pr.second);
  EXPECT_TRUE(*my_pr.first == *orig_pr.first);
}

TEST(TEST_SET, FindSet) {
  s21::set<double> my_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::set<double> orig_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  auto my_it = my_set.find(2.4);
  auto orig_it = orig_set.find(2.4);
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST(TEST_SET, ContainsSet) {
  s21::set<double> my_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::set<double> orig_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  EXPECT_EQ(my_set.contains(2), orig_set.contains(2));
  EXPECT_EQ(my_set.contains(2.1), orig_set.contains(2.1));
}