#ifndef S21_VECTOR_H
#define S21_VECTOR_H
#include <limits>

#include "../ContainerBase/ContainerBase.h"

namespace s21 {
template <typename T>
class ContainerBase;

template <typename T>
class vector : public ContainerBase<T> {
 public:
  using typename ContainerBase<T>::size_type;
  using typename ContainerBase<T>::value_type;
  using typename ContainerBase<T>::reference;
  using typename ContainerBase<T>::const_reference;
  using typename ContainerBase<T>::iterator;
  using typename ContainerBase<T>::const_iterator;
  using ContainerBase<T>::clear;

  vector() {}
  ~vector() {}
  vector(size_type n) {
    this->size_ = n;
    this->capacity_ = n;
    this->data_ = new T[n]();
  }
  vector(std::initializer_list<value_type> const &items)
      : ContainerBase<T>(items) {}
  vector(const vector &v) : ContainerBase<T>(v) {}
  vector(vector &&v) : ContainerBase<T>(std::move(v)) {}

  vector<T> &operator=(vector &&v) {
    ContainerBase<T>::operator=(std::move(v));
    return *this;
  }
  vector<T> &operator=(vector const &q) {
    ContainerBase<T>::operator=(q);
    return *this;
  }

  reference at(size_type pos) {
    this->VoidCheck(pos);
    return this->data_[pos];
  }
  reference operator[](size_type pos) { return this->data_[pos]; }

  const_reference front() const {
    this->VoidCheck();
    return this->data_[0];
  }
  const_reference back() const { return this->ContainerBack(); }

  T *data() { return this->data_; }

  iterator begin() { return this->data_; }
  iterator end() { return this->data_ + this->size_; }

  size_type max_size() const {
    return std::numeric_limits<long>::max() / sizeof(T);
  }

  void reserve(size_type size) { this->allocateMemory(size); }
  size_type capacity() { return this->capacity_; }
  void shrink_to_fit() { this->TrimCapacity(); }

  iterator insert(iterator pos, const_reference value) {
    size_type index = pos - this->data_;
    this->VoidCheck(index);
    this->allocateMemory();
    for (size_type i = this->size_; i > index; i--) {
      this->data_[i] = this->data_[i - 1];
    }
    this->data_[index] = value;
    this->size_++;
    return this->data_ + index;
  }

  void erase(iterator pos) {
    size_type index = pos - this->data_;
    this->VoidCheck(index);
    this->size_--;
    for (size_type i = index; i < this->size_; ++i) {
      this->data_[i] = this->data_[i + 1];
    }
  }

  void push_back(const_reference value) { this->push(value); }
  void pop_back() {
    this->VoidCheck();
    this->size_--;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    ([&] { push_back(std::forward<Args>(args)); }(), ...);
  }
  template <typename... Args>
  iterator insert_many(iterator pos, Args &&...args) {
    iterator res = pos;
    ([&] { res = insert(res, std::forward<Args>(args)); }(), ...);
    return res;
  }

 private:
  using ContainerBase<T>::push;
};
}  // namespace s21
#endif