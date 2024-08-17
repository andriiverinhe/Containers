#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>
namespace s21 {
template <class T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  array() {}
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a);
  ~array() {}
  array<T, N> &operator=(array &&a);
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  class iterator {
   public:
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    iterator(pointer p = nullptr) : ptr(p) {}
    reference operator*() const { return *ptr; }
    iterator &operator++() {
      ++ptr;
      return *this;
    }
    iterator operator++(int) {
      iterator tmp = *this;
      ++(*this);
      return tmp;
    }
    iterator &operator--() {
      --ptr;
      return *this;
    }
    iterator operator--(int) {
      iterator tmp = *this;
      --(*this);
      return tmp;
    }
    bool operator==(const iterator &other) const { return ptr == other.ptr; }
    bool operator!=(const iterator &other) const { return ptr != other.ptr; }

   private:
    pointer ptr;
  };
  class const_iterator : public iterator {
    const_iterator(){};
    const_iterator(const iterator &node_) : iterator(node_){};
    T &operator*() const { return iterator::operator*(); };
  };
  bool empty() { return !N; }
  size_type size() { return N; }
  size_type max_size() { return 0; }
  void swap(array &other);
  void fill(const_reference value);
  iterator data() { return iterator(data_); }
  iterator begin() { return iterator(data_); }
  iterator end() { return nullptr; }
 private:
  T data_[N]{};
};
#include "s21_array.tpp"
}  // namespace s21

#endif