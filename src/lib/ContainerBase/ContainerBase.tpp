template <typename T>
ContainerBase<T>::ContainerBase(
    std::initializer_list<value_type> const& items) {
  size_ = items.size();
  allocateMemory(size_);
  std::copy(items.begin(), items.end(), data_);
}

template <typename T>
ContainerBase<T>::ContainerBase(const ContainerBase& other) {
  size_ = other.size_;

  allocateMemory(size_);
  CopyElements(data_, other.data_);
}

template <typename T>
ContainerBase<T>::ContainerBase(ContainerBase&& s) {
  move(s);
}

template <typename T>
ContainerBase<T>& ContainerBase<T>::operator=(ContainerBase&& s) noexcept {
  move(s);
  return *this;
}

template <typename T>
ContainerBase<T>& ContainerBase<T>::operator=(ContainerBase const& s) {
  ContainerBase tmp(s);
  move(tmp);
  return *this;
}

template <typename T>
void ContainerBase<T>::push(const_reference value) {
  allocateMemory();
  data_[size_++] = value;
}

template <typename T>
void ContainerBase<T>::swap(ContainerBase& other) {
  ContainerBase temp(*this);
  *this = other;
  other = temp;
}

template <typename T>
typename ContainerBase<T>::const_reference ContainerBase<T>::ContainerBack()
    const {
  VoidCheck();
  return data_[size_ - 1];
}

template <typename T>
void ContainerBase<T>::allocateMemory(size_type new_capacity) {
  if (new_capacity || size_ >= capacity_) {
    if (!new_capacity) {
      new_capacity = capacity_ ? capacity_ * 2 : 16;
    }
    capacity_ = new_capacity;
    T* newData = new T[capacity_];
    if (data_ != nullptr) {
      size_ = capacity_ < size_ ? capacity_ : size_;
      CopyElements(newData, data_);
      delete[] data_;
    }
    data_ = newData;
  }
}

template <typename T>
void ContainerBase<T>::TrimCapacity() {
  if (size_ < capacity_) {
    capacity_ = size_;
    T* newData = new T[capacity_];
    CopyElements(newData, data_);
    delete[] data_;
    data_ = newData;
  }
}

template <typename T>
void ContainerBase<T>::CopyElements(T* dest, const T* source) {
  for (size_type i = 0; i < size_; i++) {
    dest[i] = source[i];
  }
}

template <typename T>
void ContainerBase<T>::move(ContainerBase& s) {
  if (this != &s) {
    delete[] this->data_;
    data_ = s.data_;
    size_ = s.size_;
    capacity_ = s.capacity_;
    s.data_ = nullptr;
    s.size_ = 0;
    s.capacity_ = 0;
  }
}

template <typename T>
void ContainerBase<T>::clear() {
  delete[] data_;
  data_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <typename T>
void ContainerBase<T>::VoidCheck() const {
  if (!size_) {
    throw std::out_of_range("Контейнер пуст");
  }
}

template <typename T>
void ContainerBase<T>::VoidCheck(size_type const& pos) const {
  if (pos >= size_) {
    throw std::out_of_range("Индекс вне диапазона");
  }
}