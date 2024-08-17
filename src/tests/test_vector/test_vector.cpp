#include "test_vector.h"

TEST(TEST_VECTOR, DefaultConstructor_EmptyVector) {
  s21::vector<int> v;
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0);
}

TEST(TEST_VECTOR, SizeConstructor_PositiveSize) {
  const size_t size = 5;
  s21::vector<int> v(size);
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), size);
  for (size_t i = 0; i < size; ++i) {
    EXPECT_EQ(v[i], 0);
  }
}

TEST(TEST_VECTOR, SizeConstructor_ZeroSize) {
  const size_t size = 0;
  s21::vector<int> v(size);
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), size);
}

TEST(TEST_VECTOR, InitializerListConstructor_EmptyList) {
  s21::vector<int> v = {};
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0);
}

TEST(TEST_VECTOR, InitializerListConstructor_NonEmptyList) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[4], 5);
}

TEST(TEST_VECTOR, CopyConstructor_EmptyVector) {
  s21::vector<int> v1;
  s21::vector<int> v2(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0);
}

TEST(TEST_VECTOR, CopyConstructor_NonEmptyVector) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2(v1);
  EXPECT_EQ(v2.size(), v1.size());
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v2[i], v1[i]);
  }
}

TEST(TEST_VECTOR, MoveConstructor_EmptyVector) {
  s21::vector<int> v1;
  s21::vector<int> v2(std::move(v1));
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0);
}

TEST(TEST_VECTOR, MoveConstructor_NonEmptyVector) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2(std::move(v1));
  EXPECT_EQ(v2.size(), 3);
  EXPECT_TRUE(v1.empty());
}

TEST(TEST_VECTOR, Destructor_EmptyVector) {
  s21::vector<int>* v = new s21::vector<int>();
  delete v;
}

TEST(TEST_VECTOR, Destructor_NonEmptyVector) {
  s21::vector<int>* v = new s21::vector<int>{1, 2, 3};
  delete v;
}

TEST(TEST_VECTOR, MoveAssignmentOperator_EmptyToEmpty) {
  s21::vector<int> v1;
  s21::vector<int> v2;
  v2 = std::move(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0);
}

TEST(TEST_VECTOR, MoveAssignmentOperator_NonEmptyToEmpty) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2;
  v2 = std::move(v1);
  EXPECT_EQ(v2.size(), 3);
  EXPECT_TRUE(v1.empty());
}

TEST(TEST_VECTOR, MoveAssignmentOperator_EmptyToNonEmpty) {
  s21::vector<int> v1;
  s21::vector<int> v2 = {4, 5, 6};
  v2 = std::move(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0);
}

TEST(TEST_VECTOR, MoveAssignmentOperator_NonEmptyToNonEmpty) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2 = {4, 5, 6};
  v2 = std::move(v1);
  EXPECT_EQ(v2.size(), 3);
  EXPECT_TRUE(v1.empty());
}

TEST(TEST_VECTOR, At_ValidIndex) {
  s21::vector<int> mv = {1, 2, 3, 4, 5};
  std::vector<int> sv = {1, 2, 3, 4, 5};
  EXPECT_TRUE(eq_vector(mv, sv));
}

TEST(TEST_VECTOR, At_InvalidIndex) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  v.at(4);
  EXPECT_THROW(v.at(5), std::out_of_range);
  EXPECT_THROW(v.at(10), std::out_of_range);
}
TEST(TEST_VECTOR, At_InvalidIndex_2) {
  s21::vector<int> v;
  EXPECT_THROW(v.front(), std::out_of_range);
}

TEST(TEST_VECTOR, IndexOperator_ValidIndex) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[4], 5);
}

TEST(TEST_VECTOR, front_back_and_pop) {
  s21::vector<int> v21 = {1, 2, 3, 4, 5};
  std::vector<int> vstd = {1, 2, 3, 4, 5};
  EXPECT_EQ(v21.front(), vstd.front());
  EXPECT_EQ(v21.back(), vstd.back());
  v21.pop_back();
  vstd.pop_back();
  v21.pop_back();
  vstd.pop_back();
  EXPECT_EQ(v21.front(), vstd.front());
  EXPECT_EQ(v21.back(), vstd.back());
}

TEST(TEST_VECTOR, Iterator_test) {
  s21::vector<int> v21 = {1, 2, 3, 4, 5};
  std::vector<int> vstd = {1, 2, 3, 4, 5};
  auto it1 = v21.begin();
  auto it2 = vstd.begin();
  for (; it1 != v21.end() || it2 != vstd.end(); it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(TEST_VECTOR, empty_test) {
  s21::vector<int> v21 = {1, 2, 3, 4, 5};
  std::vector<int> vstd = {1, 2, 3, 4, 5};
  for (; !v21.empty() || !vstd.empty();) {
    EXPECT_EQ(v21.back(), vstd.back());
    v21.pop_back();
    vstd.pop_back();
  }
}

TEST(TEST_VECTOR, size_eq_1) {
  s21::vector<int> v21 = {1, 2, 3, 4, 5};
  std::vector<int> vstd = {1, 2, 3, 4, 5};
  EXPECT_EQ(vstd.size(), v21.size());
}

TEST(TEST_VECTOR, size_eq_2) {
  s21::vector<char> v21 = {'1', '2', '3', '4', '5'};
  std::vector<char> vstd = {'1', '2', '3', '4', '5'};
  EXPECT_EQ(vstd.size(), v21.size());
}

TEST(TEST_VECTOR, size_eq_3) {
  s21::vector<char> v21 = {};
  std::vector<char> vstd = {};
  EXPECT_EQ(vstd.size(), v21.size());
}
TEST(TEST_VECTOR, size_not_eq_4) {
  s21::vector<char> v21 = {'1', '2', '2', '1'};
  std::vector<char> vstd = {};
  EXPECT_NE(vstd.size(), v21.size());
}
TEST(TEST_VECTOR, size_not_eq_5) {
  s21::vector<char> v21 = {'1', '2', '2', '1'};
  std::vector<char> vstd = {'1'};
  EXPECT_NE(vstd.size(), v21.size());
}

TEST(TEST_VECTOR, max_size_eq_1) {
  s21::vector<double> v21;
  std::vector<double> vstd;
  EXPECT_EQ(vstd.max_size(), v21.max_size());
}

TEST(TEST_VECTOR, max_size_eq_2) {
  s21::vector<char> v21 = {'1', '2', '3', '4', '5'};
  std::vector<char> vstd = {'1', '2', '3', '4', '5'};
  EXPECT_EQ(vstd.max_size(), v21.max_size());
}

TEST(TEST_VECTOR, max_size_eq_3) {
  s21::vector<char> v21 = {};
  std::vector<char> vstd = {};
  EXPECT_EQ(vstd.max_size(), v21.max_size());
}

TEST(TEST_VECTOR, reserve_test_0) {
  s21::vector<char> v21;
  std::vector<char> vstd;
  v21.reserve(10);
  vstd.reserve(10);
  EXPECT_EQ(vstd.size(), v21.size());
}

TEST(TEST_VECTOR, reserve_test_1) {
  s21::vector<char> v21;
  std::vector<char> vstd;
  v21.reserve(0);
  vstd.reserve(0);
  EXPECT_EQ(vstd.size(), v21.size());
}

TEST(TEST_VECTOR, reserve_test_2) {
  s21::vector<char> v21;
  std::vector<char> vstd;
  v21.reserve(239478);
  vstd.reserve(239478);
  EXPECT_EQ(vstd.size(), v21.size());
}

TEST(TEST_VECTOR, capacity_test_0) {
  s21::vector<char> v21{'1', '2', '3', '1', '2', '3',
                        '1', '2', '3', '1', '2', '3'};
  std::vector<char> vstd{'1', '2', '3', '1', '2', '3',
                         '1', '2', '3', '1', '2', '3'};
  EXPECT_EQ(vstd.capacity(), v21.capacity());
  EXPECT_TRUE(eq_vector(v21, vstd));
}

TEST(TEST_VECTOR, capacity_test_1) {
  s21::vector<char> v21;
  std::vector<char> vstd;
  EXPECT_EQ(vstd.capacity(), v21.capacity());
}

TEST(TEST_VECTOR, capacity_test_2) {
  s21::vector<int> v21{123,    12,   3,  123, 1321, 123,
                       210321, -213, -3, 3,   123,  12};
  std::vector<int> vstd{123,    12,   3,  123, 1321, 123,
                        210321, -213, -3, 3,   123,  12};
  EXPECT_EQ(vstd.capacity(), v21.capacity());
  EXPECT_TRUE(eq_vector(v21, vstd));
}

TEST(TEST_VECTOR, capacity_test_3) {
  s21::vector<double> v21{12.32, 321.312, 213.231, 123.12};
  std::vector<double> vstd{12.32, 321.312, 213.231, 123.12};
  EXPECT_EQ(vstd.capacity(), v21.capacity());
  EXPECT_TRUE(eq_vector(v21, vstd));
}

TEST(TEST_VECTOR, Capacity_shrink_to_fit_1) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  s21_v.reserve(10);
  std_v.reserve(10);
  s21_v.shrink_to_fit();
  std_v.shrink_to_fit();
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_TRUE(eq_vector(s21_v, std_v));
}

TEST(TEST_VECTOR, Capacity_shrink_to_fit_2) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  s21_v.reserve(10);
  std_v.reserve(10);
  s21_v.shrink_to_fit();
  std_v.shrink_to_fit();
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_TRUE(eq_vector(s21_v, std_v));
}

TEST(TEST_VECTOR, clear_test_1) {
  s21::vector<char> v21;
  std::vector<char> vstd;
  v21.reserve(239478);
  vstd.reserve(239478);
  v21.clear();
  vstd.clear();
  EXPECT_EQ(vstd.size(), v21.size());
  EXPECT_TRUE(eq_vector(v21, vstd));
}

TEST(TEST_VECTOR, clear_test_2) {
  s21::vector<char> v21;
  std::vector<char> vstd;
  v21.clear();
  vstd.clear();
  EXPECT_EQ(vstd.size(), v21.size());
}

TEST(TEST_VECTOR, clear_test_3) {
  s21::vector<char> v21{'1', '2', '3', '1', '2', '3',
                        '1', '2', '3', '1', '2', '3'};
  std::vector<char> vstd{'1', '2', '3', '1', '2', '3',
                         '1', '2', '3', '1', '2', '3'};
  v21.clear();
  vstd.clear();
  EXPECT_EQ(vstd.size(), v21.size());
}

TEST(TEST_VECTOR, erase_test_1) {
  s21::vector<char> v21{'1', '2', '3', '1', '2', '3',
                        '1', '2', '3', '1', '2', '3'};
  std::vector<char> vstd{'1', '2', '3', '1', '2', '3',
                         '1', '2', '3', '1', '2', '3'};
  auto it = v21.begin();
  v21.erase(it);
  auto it2 = vstd.begin();
  vstd.erase(it2);
  EXPECT_EQ(vstd.size(), v21.size());
  v21.erase(it);
  vstd.erase(it2);
  EXPECT_EQ(vstd.size(), v21.size());
  it = v21.end();
  it2 = vstd.end();
  EXPECT_EQ(vstd.size(), v21.size());
  it = v21.end();
  it2 = vstd.end();
  EXPECT_EQ(vstd.size(), v21.size());
}

TEST(TEST_VECTOR, push_pop_1) {
  s21::vector<int> v21{};
  std::vector<int> vstd{1, 2, 4, 7, -1, 5, -64, -1, -334};

  v21.push_back(1);
  v21.push_back(2);
  v21.push_back(4);
  v21.push_back(7);
  v21.push_back(-1);
  v21.push_back(5);
  v21.push_back(-64);
  v21.push_back(-1);
  v21.push_back(-334);

  EXPECT_EQ(vstd[0], v21[0]);
  EXPECT_EQ(vstd[3], v21[3]);
  EXPECT_EQ(vstd[7], v21[7]);

  EXPECT_EQ(vstd.size(), v21.size());
}

TEST(TEST_VECTOR, push_pop_2) {
  s21::vector<int> v21{32, 3, 23, 2, 3};
  std::vector<int> vstd{32, 3, 23, 2, 3, 1, 2, 4, 7, -1, 5, -64, -1, -334};

  v21.push_back(1);
  v21.push_back(2);
  v21.push_back(4);
  v21.push_back(7);
  v21.push_back(-1);
  v21.push_back(5);
  v21.push_back(-64);
  v21.push_back(-1);
  v21.push_back(-334);

  EXPECT_EQ(vstd[0], v21[0]);
  EXPECT_EQ(vstd[3], v21[3]);
  EXPECT_EQ(vstd[9], v21[9]);

  EXPECT_EQ(vstd.size(), v21.size());
}

TEST(TEST_VECTOR, swap_test_1) {
  s21::vector<int> v21_1{32, 3, 23, 2, 3};
  s21::vector<int> v21_2{32, 3, 23, 2, 3, 1, 2, 4, 7, -1, 5, -64, -1, -334};
  std::vector<int> vstd_1{32, 3, 23, 2, 3};
  std::vector<int> vstd_2{32, 3, 23, 2, 3, 1, 2, 4, 7, -1, 5, -64, -1, -334};
  v21_1.swap(v21_2);
  vstd_1.swap(vstd_2);
  EXPECT_TRUE(eq_vector(v21_1, vstd_1));
  EXPECT_TRUE(eq_vector(v21_2, vstd_2));
  vstd_1.swap(vstd_2);
  v21_1.swap(v21_2);
  EXPECT_TRUE(eq_vector(v21_1, vstd_1));
  EXPECT_TRUE(eq_vector(v21_2, vstd_2));
  v21_1.swap(v21_2);
  EXPECT_FALSE(eq_vector(v21_1, vstd_1));
  EXPECT_FALSE(eq_vector(v21_2, vstd_2));
}

TEST(TEST_VECTOR, swap_test_2) {
  s21::vector<int> v21_1;
  s21::vector<int> v21_2;
  std::vector<int> vstd_1;
  std::vector<int> vstd_2;
  v21_1.swap(v21_2);
  vstd_1.swap(vstd_2);
  EXPECT_TRUE(eq_vector(v21_1, vstd_1));
  EXPECT_TRUE(eq_vector(v21_2, vstd_2));
  vstd_1.swap(vstd_2);
  v21_1.swap(v21_2);
  EXPECT_TRUE(eq_vector(v21_1, vstd_1));
  EXPECT_TRUE(eq_vector(v21_2, vstd_2));
  v21_1.swap(v21_2);
  EXPECT_TRUE(eq_vector(v21_1, vstd_1));
  EXPECT_TRUE(eq_vector(v21_2, vstd_2));
}

TEST(TEST_VECTOR, InsertMany) {
  s21::vector<int> vec = {1, 2, 3, 7, 8};
  s21::vector<int>::iterator pos = vec.begin();
  pos++;
  pos++;
  pos++;
  vec.insert_many(pos, 4, 5, 6);

  EXPECT_EQ(vec.size(), 8);

  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 6);
  EXPECT_EQ(vec[4], 5);
  EXPECT_EQ(vec[5], 4);
  EXPECT_EQ(vec[6], 7);
  EXPECT_EQ(vec[7], 8);
}

TEST(TEST_VECTOR, InsertMany2) {
  s21::vector<int> vec = {1, 2, 3, 7, 8};
  s21::vector<int>::iterator pos = vec.begin();
  vec.insert_many(pos, 4, 5, 6);

  EXPECT_EQ(vec.size(), 8);

  EXPECT_EQ(vec[0], 6);
  EXPECT_EQ(vec[1], 5);
  EXPECT_EQ(vec[2], 4);
  EXPECT_EQ(vec[3], 1);
  EXPECT_EQ(vec[4], 2);
  EXPECT_EQ(vec[5], 3);
  EXPECT_EQ(vec[6], 7);
  EXPECT_EQ(vec[7], 8);
}

TEST(TEST_VECTOR, InsertMany3) {
  s21::vector<int> vec = {1, 2, 3, 7, 8};
  s21::vector<int>::iterator pos = vec.end();
pos--;
  vec.insert_many(pos, 4, 5, 6);

  EXPECT_EQ(vec.size(), 8);

  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 7);
  EXPECT_EQ(vec[4], 6);
  EXPECT_EQ(vec[5], 5);
  EXPECT_EQ(vec[6], 4);
  EXPECT_EQ(vec[7], 8);
}

TEST(TEST_VECTOR, InsertManyBack) {
  s21::vector<int> vec = {1, 2, 3};

  vec.insert_many_back(4, 5, 6);

  EXPECT_EQ(vec.size(), 6);

  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
  EXPECT_EQ(vec[5], 6);
}