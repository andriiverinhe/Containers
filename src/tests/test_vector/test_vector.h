#pragma once

#include <gtest/gtest.h>

#include "../../lib/vector/s21_vector.h"
#include "vector"

template <typename T>
bool eq_vector(s21::vector<T> &s21_l, std::vector<T> &std_l) {
  if (s21_l.size() != std_l.size()) return false;
  auto it_s21_l = s21_l.begin();
  auto it_std_l = std_l.begin();
  for (; (it_s21_l != s21_l.end()) || (it_std_l != std_l.end());
       it_s21_l++, it_std_l++)
    if (*it_s21_l != *it_std_l) return false;
  return true;
}

class TEST_VECTOR : public testing::Test {};