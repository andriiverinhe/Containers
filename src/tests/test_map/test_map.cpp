#include "test_map.h"

#include <string>

TEST(TEST_MAP, DefaultConstruct) {
  s21::map<int, std::string> m;
  EXPECT_EQ(m.size(), 0);
  EXPECT_TRUE(m.empty());
}

TEST(TEST_MAP, DefaultConstructor) {
  s21::map<int, int> m;
  EXPECT_EQ(m.size(), 0);
}

TEST(TEST_MAP, ConstructorDefaultMap) {
  s21::map<int, char> my_empty_map;
  std::map<int, char> orig_empty_map;
  EXPECT_EQ(my_empty_map.empty(), orig_empty_map.empty());
}

TEST(TEST_MAP, InitializerListConstructor) {
  s21::map<int, int> m{{1, 2}, {3, 4}, {5, 6}};
  EXPECT_EQ(m.size(), 3);
  EXPECT_EQ(m[1], 2);
  EXPECT_EQ(m[3], 4);
  EXPECT_EQ(m[5], 6);
}

TEST(TEST_MAP, ConstructorInitializerMap) {
  s21::map<int, char> my_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  std::map<int, char> orig_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  EXPECT_EQ(my_map.size(), orig_map.size());
  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(TEST_MAP, insertMany) {
  s21::map<int, int> my_set = {{1, 4}, {3, 5}, {23, 5}, {32, 43}};
  my_set.insert_many(std::make_pair(12, 3), std::make_pair(132, 43), std::make_pair(22, 34));
}

TEST(TEST_MAP, ConstructorInitializer2Map) {
  s21::map<int, char> my_map = {};
  std::map<int, char> orig_map = {};
  EXPECT_EQ(my_map.size(), orig_map.size());
  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(TEST_MAP, CopyConstructor) {
  s21::map<int, int> originalMap;
  originalMap.insert(std::make_pair(1, 100));
  originalMap.insert(std::make_pair(2, 200));

  s21::map<int, int> copiedMap(originalMap);

  EXPECT_EQ(copiedMap.size(), originalMap.size());
  EXPECT_EQ(copiedMap[1], 100);
  EXPECT_EQ(copiedMap[2], 200);
}

TEST(TEST_MAP, ConstructorCopyMap) {
  s21::map<int, int> my_map = {{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> orig_map = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> my_map_copy = my_map;
  std::map<int, int> orig_map_copy = orig_map;
  EXPECT_EQ(my_map_copy.size(), orig_map_copy.size());
  auto my_it = my_map_copy.begin();
  auto orig_it = orig_map_copy.begin();
  for (; my_it != my_map_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(TEST_MAP, MoveConstructor) {
  s21::map<int, int> originalMap;
  originalMap.insert(std::make_pair(1, 100));
  originalMap.insert(std::make_pair(2, 200));

  s21::map<int, int> movedMap(std::move(originalMap));

  EXPECT_EQ(movedMap.size(), 2);
  EXPECT_EQ(movedMap[1], 100);
  EXPECT_EQ(movedMap[2], 200);
  EXPECT_TRUE(originalMap.empty());
}

TEST(TEST_MAP, ConstructorMoveMap) {
  s21::map<int, int> my_map = {{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> orig_map = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> my_map_copy = std::move(my_map);
  std::map<int, int> orig_map_copy = std::move(orig_map);
  EXPECT_EQ(my_map.size(), orig_map.size());
  EXPECT_EQ(my_map_copy.size(), orig_map_copy.size());
  auto my_it = my_map_copy.begin();
  auto orig_it = orig_map_copy.begin();
  for (; my_it != my_map_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(TEST_MAP, MoveAssignmentOperator) {
  s21::map<int, int> originalMap;
  originalMap.insert(std::make_pair(1, 100));
  originalMap.insert(std::make_pair(2, 200));

  s21::map<int, int> movedMap = std::move(originalMap);

  EXPECT_EQ(movedMap.size(), 2);
  EXPECT_EQ(movedMap[1], 100);
  EXPECT_EQ(movedMap[2], 200);

  EXPECT_TRUE(originalMap.empty());
}

TEST(TEST_MAP, MapOperator) {
  s21::map<char, std::string> my_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  std::map<char, std::string> orig_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  my_map['a'] = "Alisa";
  orig_map['a'] = "Alisa";
  orig_map['b'] = "Ben";
  EXPECT_TRUE(my_map['a'] == orig_map['a']);
  EXPECT_FALSE(my_map['b'] == orig_map['b']);
  EXPECT_TRUE(my_map['c'] == orig_map['c']);
}

TEST(TEST_MAP, AtMethod) {
  s21::map<int, int> myMap;
  myMap.insert(std::make_pair(1, 100));
  myMap.insert(std::make_pair(2, 200));

  EXPECT_EQ(myMap.at(1), 100);
  EXPECT_EQ(myMap.at(2), 200);

  EXPECT_THROW(myMap.at(3), std::out_of_range);
}

TEST(TEST_MAP, SubscriptOperator) {
  s21::map<int, int> myMap;

  myMap[1] = 100;
  myMap[2] = 200;

  EXPECT_EQ(myMap[1], 100);
  EXPECT_EQ(myMap[2], 200);

  myMap[3] = 300;
  EXPECT_EQ(myMap[3], 300);

  EXPECT_EQ(myMap.size(), 3);
}

TEST(TEST_MAP, MapAtOperatorException) {
  s21::map<char, std::string> my_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  EXPECT_THROW(my_map.at('g') = "Alisa", std::out_of_range);
}

TEST(TEST_MAP, MapAtOperator) {
  s21::map<char, std::string> my_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  std::map<char, std::string> orig_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  my_map.at('a') = "Alisa";
  orig_map.at('a') = "Alisa";
  orig_map.at('b') = "Ben";
  EXPECT_TRUE(my_map['a'] == orig_map['a']);
  EXPECT_FALSE(my_map['b'] == orig_map['b']);
  EXPECT_TRUE(my_map['c'] == orig_map['c']);
}

TEST(TEST_MAP, BeginMethod) {
  s21::map<int, int> myMap;
  myMap.insert(std::make_pair(1, 100));
  myMap.insert(std::make_pair(2, 200));

  auto it = myMap.begin();
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, 100);
}

TEST(TEST_MAP, EndMethod) {
  s21::map<int, int> myMap;
  myMap.insert(std::make_pair(1, 100));
  myMap.insert(std::make_pair(2, 200));

  auto it = myMap.end();

  --it;
  EXPECT_EQ(it->first, 2);
  EXPECT_EQ(it->second, 200);
}

TEST(TEST_MAP, EmptyMapBeginEnd) {
  s21::map<int, int> myMap;

  EXPECT_EQ(myMap.begin(), myMap.end());
}

TEST(TEST_MAP, Empty) {
  s21::map<int, int> myMap;

  EXPECT_TRUE(myMap.empty());

  myMap.insert({1, 42});

  EXPECT_FALSE(myMap.empty());
}

TEST(TEST_MAP, Size) {
  s21::map<int, int> myMap;

  EXPECT_EQ(myMap.size(), 0);

  myMap.insert({1, 10});
  myMap.insert({2, 20});

  EXPECT_EQ(myMap.size(), 2);
}

TEST(TEST_MAP, MapCapacity) {
  s21::map<char, std::string> my_map;
  std::map<char, std::string> orig_map;
  EXPECT_TRUE(my_map.empty() == orig_map.empty());
  my_map.insert('z', "wow");
  EXPECT_FALSE(my_map.empty() == orig_map.empty());
  EXPECT_EQ(my_map.size(), 1);
}

TEST(TEST_MAP, InitializerListConstruc) {
  s21::map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(m.size(), 3);
  EXPECT_FALSE(m.empty());
  EXPECT_EQ(m.at(1), "one");
  EXPECT_EQ(m.at(2), "two");
  EXPECT_EQ(m.at(3), "three");
}

TEST(TEST_MAP, CopyConstruct) {
  s21::map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
  s21::map<int, std::string> copy_m(m);
  EXPECT_EQ(copy_m.size(), 3);
  EXPECT_FALSE(copy_m.empty());
  EXPECT_EQ(copy_m.at(1), "one");
}

TEST(TEST_MAP, InsertKeyValue) {
  s21::map<int, std::string> map;

  map.insert(1, "one");

  EXPECT_EQ(map.size(), 1);

  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");

  map.insert(2, "two");

  EXPECT_EQ(map.size(), 2);

  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map.contains(2), true);
  EXPECT_EQ(map[2], "two");
}

TEST(TEST_MAP, InsertPair) {
  s21::map<int, std::string> map;

  map.insert(std::make_pair(1, "one"));

  EXPECT_EQ(map.size(), 1);

  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");

  map.insert(std::make_pair(2, "two"));

  EXPECT_EQ(map.size(), 2);

  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map.contains(2), true);
  EXPECT_EQ(map[2], "two");
}
TEST(TEST_MAP, InsertOrAssign) {
  s21::map<int, std::string> map;

  auto [it1, inserted1] = map.insert_or_assign(1, "one");
  EXPECT_TRUE(inserted1);
  EXPECT_EQ(it1->first, 1);
  EXPECT_EQ(it1->second, "one");

  auto [it2, inserted2] = map.insert_or_assign(1, "ONE");
  EXPECT_FALSE(inserted2);
  EXPECT_EQ(it2->first, 1);
  EXPECT_EQ(it2->second, "ONE");

  map.insert_or_assign(2, "two");
  map.insert_or_assign(3, "three");
  map.insert_or_assign(4, "four");
  map.insert_or_assign(5, "five");
  EXPECT_EQ(map.size(), 5);
  EXPECT_EQ(map[1], "ONE");
  EXPECT_EQ(map[2], "two");
  EXPECT_EQ(map[3], "three");
  EXPECT_EQ(map[4], "four");
  EXPECT_EQ(map[5], "five");
}
TEST(TEST_MAP, AtAndOperatorBrackets) {
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_EQ(map.at(1), "one");
  EXPECT_EQ(map[2], "two");
  EXPECT_THROW(map.at(4), std::out_of_range);
  map[4] = "four";
  EXPECT_EQ(map[4], "four");
  map[2] = "TWO";
  EXPECT_EQ(map[2], "TWO");
}

TEST(TEST_MAP, EmptyAndSize) {
  s21::map<int, std::string> empty_map;
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_TRUE(empty_map.empty());
  EXPECT_EQ(empty_map.size(), 0);

  EXPECT_FALSE(map.empty());
  EXPECT_EQ(map.size(), 3);
}

TEST(TEST_MAP, MaxSize) {
  s21::map<int, std::string> map;
  std::map<int, std::string> map1;

  EXPECT_GT(map.max_size(), map1.max_size());
}
TEST(TEST_MAP, Erase_1) {
  s21::map<int, std::string> map;

  map.insert({1, "one"});
  map.insert({2, "two"});
  map.insert({3, "three"});
  map.insert({5, "five"});

  auto it1 = map.begin()++;
  map.erase(it1);
  EXPECT_EQ(map.size(), 3);
  EXPECT_FALSE(map.contains(1));
}

TEST(TEST_MAP, Erase_2) {
  s21::map<int, std::string> map = {{3, "k"}, {1, "f"}, {5, "f"}, {8, "i"}};

  auto it1 = map.begin();
  map.erase(it1++);
  EXPECT_EQ(map.size(), 3);
  EXPECT_FALSE(map.contains(1));
  map.erase(it1++);
  map.erase(it1++);
  map.erase(it1);
  EXPECT_TRUE(map.empty());
}
TEST(TEST_MAP, Erase_3) {
  s21::map<int, std::string> map = {{3, "k"}, {1, "f"}, {5, "f"}, {8, "i"}};
  auto it1 = map.begin();
  map.erase(it1++);
  EXPECT_EQ(map.size(), 3);
  EXPECT_FALSE(map.contains(1));
  map.erase(it1++);
  map.insert({12, "one"});
  map.erase(it1++);
  map.insert({1, "one"});
  map.erase(it1);
  map.insert({145, "one"});
  EXPECT_TRUE(!map.empty());
}

TEST(TEST_MAP, MapErase) {
  s21::map<int, char> my_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  std::map<int, char> orig_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  EXPECT_EQ(my_map.size(), orig_map.size());
  my_map.erase(my_map.begin());
  orig_map.erase(orig_map.begin());
  EXPECT_EQ(my_map.size(), orig_map.size());
  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(TEST_MAP, Swap) {
  s21::map<int, std::string> map1;
  map1.insert({1, "one"});
  map1.insert({2, "two"});

  s21::map<int, std::string> map2;
  map2.insert({3, "three"});
  map2.insert({4, "four"});

  map1.swap(map2);

  EXPECT_EQ(map1.size(), 2);
  EXPECT_TRUE(map1.contains(3));
  EXPECT_TRUE(map1.contains(4));

  EXPECT_EQ(map2.size(), 2);
  EXPECT_TRUE(map2.contains(1));
  EXPECT_TRUE(map2.contains(2));
}

TEST(TEST_MAP, SwapMap) {
  s21::map<int, int> my_map = {{1, 1}};
  s21::map<int, int> my_swap_map = {{3, 3}, {4, 4}};

  my_map.swap(my_swap_map);
  EXPECT_EQ(my_map.size(), 2);
  EXPECT_EQ(my_swap_map.size(), 1);
  auto x = (*(my_map.begin())).first;
  auto y = (*(my_swap_map.begin())).first;
  EXPECT_EQ(x, 3);
  EXPECT_EQ(y, 1);
}

TEST(TEST_MAP, Merge) {
  s21::map<int, std::string> map1;
  map1.insert({1, "one"});
  map1.insert({2, "two"});

  s21::map<int, std::string> map2;
  map2.insert({3, "three"});
  map2.insert({4, "four"});

  map1.merge(map2);

  EXPECT_EQ(map1.size(), 4);
  EXPECT_TRUE(map1.contains(1));
  EXPECT_TRUE(map1.contains(2));
  EXPECT_TRUE(map1.contains(3));
  EXPECT_TRUE(map1.contains(4));
}

TEST(TEST_MAP, Contains) {
  s21::map<int, std::string> map;

  map.insert({1, "one"});
  map.insert({2, "two"});
  EXPECT_TRUE(map.contains(2));
  EXPECT_FALSE(map.contains(3));
}

TEST(TEST_MAP, clear_test) {
  s21::map<int, int> my_map{{1, 2}, {3, 4}, {5, 6}};
  my_map.clear();
  EXPECT_TRUE(my_map.empty());
  my_map.clear();
  EXPECT_TRUE(my_map.empty());
}

TEST(TEST_MAP, MapClear) {
  s21::map<int, int> my_map;
  std::map<int, int> orig_map;
  my_map.clear();
  orig_map.clear();
  EXPECT_EQ(my_map.empty(), orig_map.empty());
  my_map.insert(std::make_pair(1, 1));
  orig_map.insert(std::make_pair(1, 1));
  EXPECT_EQ(my_map.empty(), orig_map.empty());
  my_map.clear();
  orig_map.clear();
  EXPECT_EQ(my_map.empty(), orig_map.empty());
}

TEST(TEST_MAP, MapInsert1) {
  s21::map<int, char> my_map;
  std::map<int, char> orig_map;
  my_map.insert(std::make_pair(1, 'a'));
  my_map.insert(std::make_pair(2, 'a'));
  my_map.insert(std::make_pair(3, 'a'));
  orig_map.insert(std::make_pair(1, 'a'));
  orig_map.insert(std::make_pair(2, 'a'));
  orig_map.insert(std::make_pair(3, 'a'));

  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }

  auto pr1 = my_map.insert(std::make_pair(1, 'a'));
  auto pr2 = orig_map.insert(std::make_pair(1, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(TEST_MAP, MapInsert2) {
  s21::map<int, char> my_map;
  std::map<int, char> orig_map;
  my_map.insert(1, 'a');
  my_map.insert(2, 'a');
  my_map.insert(3, 'a');
  orig_map.insert(std::make_pair(1, 'a'));
  orig_map.insert(std::make_pair(2, 'a'));
  orig_map.insert(std::make_pair(3, 'a'));

  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }

  auto pr1 = my_map.insert(1, 'a');
  auto pr2 = orig_map.insert(std::make_pair(1, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(TEST_MAP, MapInsert3) {
  s21::map<int, char> my_map;
  std::map<int, char> orig_map;
  my_map.insert(1, 'a');
  my_map.insert(2, 'a');
  my_map.insert(3, 'a');
  orig_map.insert(std::make_pair(1, 'a'));
  orig_map.insert(std::make_pair(2, 'a'));
  orig_map.insert(std::make_pair(3, 'a'));

  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }

  auto pr1 = my_map.insert_or_assign(1, 'b');
  auto i = orig_map.begin();
  EXPECT_TRUE((*pr1.first).first == (*i).first);
  EXPECT_FALSE((*pr1.first).second == (*i).second);
}
