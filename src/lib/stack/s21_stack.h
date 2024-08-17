#ifndef S21_STACK_H_
#define S21_STACK_H_
#include <stdexcept>

#include "../ContainerBase/ContainerBase.h"

namespace s21 {
template <typename T>
class stack : public ContainerBase<T> {
 public:
  using typename ContainerBase<T>::size_type;
  using typename ContainerBase<T>::value_type;
  using typename ContainerBase<T>::reference;
  using typename ContainerBase<T>::const_reference;

  stack() {}
  ~stack() {}
  stack(std::initializer_list<value_type> const& items)
      : ContainerBase<T>(items) {}
  stack(const stack& s) : ContainerBase<T>(s) {}
  stack(stack&& s) : ContainerBase<T>(std::move(s)) {}

  stack<T>& operator=(const stack<T>& other) {
    ContainerBase<T>::operator=(other);
    return *this;
  }

  stack<T>& operator=(stack<T>&& other) {
    ContainerBase<T>::operator=(std::move(other));
    return *this;
  }

  const_reference top() const { return this->ContainerBack(); }

  void pop() {
    this->VoidCheck();
    this->size_--;
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    ([&] { this->push(std::forward<Args>(args)); }(), ...);
  }
};
}  // namespace s21

#endif