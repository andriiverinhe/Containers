#ifndef CONTAINER_BASE_H_
#define CONTAINER_BASE_H_

#include <stdexcept>

namespace s21 {

template <typename T>
class ContainerBase {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;
  using iterator = T*;
  using const_iterator = const T*;

  ContainerBase() {}
  ~ContainerBase() {
    delete[] data_;
    data_ = nullptr;
  }
  ContainerBase(std::initializer_list<value_type> const& items);
  ContainerBase(const ContainerBase& other);
  ContainerBase(ContainerBase&& s);

  ContainerBase<T>& operator=(ContainerBase&& s) noexcept;
  ContainerBase<T>& operator=(ContainerBase const& s);

  void push(const_reference value);
  bool empty() { return !this->size_; }
  size_type size() const { return this->size_; };
  void swap(ContainerBase& other);

 protected:
  T* data_ = nullptr;
  size_type size_ = 0;
  size_type capacity_ = 0;

  void allocateMemory(size_type new_capacity = 0);
  void CopyElements(T* dest, const T* source);
  void move(ContainerBase& s);
  void VoidCheck() const;
  void VoidCheck(size_type const& pos) const;
  const_reference ContainerBack() const;
  void TrimCapacity();
  void clear();
};
#include "ContainerBase.tpp"
}  // namespace s21
#endif