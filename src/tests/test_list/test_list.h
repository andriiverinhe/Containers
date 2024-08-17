#pragma once

#include <gtest/gtest.h>

#include <list>

#include "../../s21_containers.h"

template <typename T>
bool eq_list(s21::list<T> &s21_l, std::list<T> &std_l) {
  if (s21_l.size() != std_l.size()) return false;
  auto it_s21_l = s21_l.begin();
  auto it_std_l = std_l.begin();
  for (; (it_s21_l != s21_l.end()) || (it_std_l != std_l.end());
       it_s21_l++, it_std_l++)
    if (*it_s21_l != *it_std_l) return false;
  return true;
}

template <class T>
void print_list(T l) {
  std::cout << "List:" << std::endl;
  for (auto it = l.begin(); it != l.end(); it++) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

class TEST_LIST : public ::testing::Test {};