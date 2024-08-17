#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_
#include "../ContainerBase/ContainerBase.h"

namespace s21 {

template <typename T>
class queue : public ContainerBase<T> {
 public:
  using typename ContainerBase<T>::size_type;
  using typename ContainerBase<T>::value_type;
  using typename ContainerBase<T>::reference;
  using typename ContainerBase<T>::const_reference;

  queue() {}
  ~queue() {}
  queue(std::initializer_list<value_type> const &items)
      : ContainerBase<T>(items) {}
  queue(const queue &q) : ContainerBase<T>(q) {}
  queue(queue &&q) : ContainerBase<T>(std::move(q)) {}

  queue<T> &operator=(queue &&q) {
    ContainerBase<T>::operator=(std::move(q));
    return *this;
  }

  queue<T> &operator=(queue const &q) {
    ContainerBase<T>::operator=(q);
    return *this;
  }

  const_reference front() const {
    this->VoidCheck();
    return this->data_[0];
  }

  const_reference back() const { return this->ContainerBack(); }

  void pop() {
    this->VoidCheck();
    for (size_type i = 0; i < this->size_ - 1; ++i) {
      this->data_[i] = this->data_[i + 1];
    }
    this->size_--;
  };

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    ([&] { this->push(std::forward<Args>(args)); }(), ...);
  }
};
}  // namespace s21

#endif