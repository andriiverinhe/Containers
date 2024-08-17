template <class T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  size_type count = 0;
  for (auto &item : items) {
    if (count >= N) break;
    data_[count++] = item;
  }
}

template <class T, std::size_t N>
array<T, N>::array(const array &a) {
  for (size_type i = 0; i < N; ++i) {
    data_[i] = a.data_[i];
  }
}

template <class T, std::size_t N>
array<T, N>::array(array &&a) {
  *this = std::move(a);
}

template <class T, std::size_t N>
array<T, N> &array<T, N>::operator=(array &&a) {
  for (size_type i = 0; i < N; ++i) {
    data_[i] = std::move(a.data_[i]);
  }
  return *this;
}

template <class T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("array::at: index out of range");
  }
  return data_[pos];
}

template <class T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return at(pos);
}

template <class T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() {
  return at(0);
}

template <class T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() {
  return at(N - 1);
}

template <class T, std::size_t N>
void array<T, N>::swap(array &other) {
  array<T, N> tmp = std::move(other);
  other = std::move(*this);
  *this = std::move(tmp);
}

template <class T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < N; ++i) {
    data_[i] = value;
  }
}