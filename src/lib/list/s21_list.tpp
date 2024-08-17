#include "s21_list.h"
namespace s21 {

// ITERATOR

template <typename T>
T& list<T>::ListIterator::operator*() const {
  if (node_ == nullptr)
    throw std::runtime_error(
        "Segmentation fault: Attempted to access invalid memory");
  return node_->value;
}

template <typename T>
typename list<T>::ListIterator& list<T>::ListIterator::operator++() {
  if (node_ != nullptr) node_ = node_->next;
  return *this;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator++(int) {
  iterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T>
typename list<T>::ListIterator& list<T>::ListIterator::operator--() {
  if (node_ != nullptr) node_ = node_->prev;
  return *this;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator--(int) {
  iterator temp = *this;
  --(*this);
  return temp;
}
// ITERATOR

// LIST
template <typename value_type>
list<value_type>::list(size_type n) {
  for (size_type i = 0; i < n; ++i) {
    push_back(value_type());
  }
}

template <typename value_type>
list<value_type>::list(std::initializer_list<value_type> const& items) {
  for (const auto& item : items) {
    push_back(item);
  }
}

template <typename value_type>
list<value_type>::list(const list& l) {
  *this = l;
}

template <typename value_type>
list<value_type>::list(list&& l) {
  *this = std::move(l);
}

template <typename value_type>
list<value_type>& list<value_type>::operator=(const list& l) {
  clear();
  Node* current = l.head_;
  while (current != nullptr) {
    push_back(current->value);
    current = current->next;
  }
  return *this;
}

template <typename value_type>
list<value_type>& list<value_type>::operator=(list&& l) {
  if (this != &l) {
    clear();
    head_ = l.head_;
    tail_ = l.tail_;
    size_ = l.size_;
    l.head_ = l.tail_ = nullptr;
    l.size_ = 0;
  }
  return *this;
}

template <typename value_type>
typename list<value_type>::const_reference list<value_type>::front() const {
  checkSize();
  return head_->value;
}

template <typename value_type>
typename list<value_type>::const_reference list<value_type>::back() const {
  checkSize();
  return tail_->value;
}

template <typename value_type>
void list<value_type>::clear() {
  Node* current = head_;
  while (current != nullptr) {
    Node* next = current->next;
    delete current;
    current = next;
  }
  head_ = tail_ = nullptr;
  size_ = 0;
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::insert(
    iterator pos, const_reference value) {
  Node* newNode = new Node(value);
  if (head_ == nullptr) {
    head_ = tail_ = newNode;
  } else if (pos == begin()) {
    newNode->next = head_;
    head_->prev = newNode;
    head_ = newNode;
  } else if (pos == end()) {
    tail_->next = newNode;
    newNode->prev = tail_;
    tail_ = newNode;
  } else {
    Node* current = pos.get_node()->prev;
    newNode->next = current->next;
    newNode->prev = current;
    current->next->prev = newNode;
    current->next = newNode;
  }
  ++size_;
  return iterator(newNode);
}

template <typename value_type>
void list<value_type>::erase(iterator pos) {
  checkSize();
  Node* nodeToDelete = findNode(pos);
  if (nodeToDelete == nullptr) {
    throw std::logic_error("Элемент не найден");
  }
  if (nodeToDelete == head_) {
    head_ = head_->next;
    if (head_) head_->prev = nullptr;
  } else if (nodeToDelete == tail_) {
    tail_ = nodeToDelete->prev;
    tail_->next = nullptr;
  } else {
    nodeToDelete->prev->next = nodeToDelete->next;
    if (nodeToDelete->next) {
      nodeToDelete->next->prev = nodeToDelete->prev;
    }
  }
  delete nodeToDelete;
  nodeToDelete = nullptr;
  --size_;
  if (size_ == 0) tail_ = head_ = nullptr;
}

template <typename value_type>
void list<value_type>::push_back(const_reference value) {
  insert(end(), value);
}

template <typename value_type>
void list<value_type>::pop_back() {
  erase(iterator(tail_));
}

template <typename value_type>
void list<value_type>::push_front(const_reference value) {
  insert(begin(), value);
}

template <typename value_type>
void list<value_type>::pop_front() {
  erase(iterator(head_));
}

template <typename value_type>
void list<value_type>::swap(list& other) {
  list<value_type> tmp = std::move(other);
  other = std::move(*this);
  *this = std::move(tmp);
}

template <typename value_type>
void list<value_type>::merge(list<value_type>& other) {
  if (this != &other) {
    iterator it_this = begin();
    iterator it_other = other.begin();
    while (!other.empty()) {
      if (this->empty() || (it_this == end() || *it_other < *it_this)) {
        insert(it_this, *it_other);
        other.erase(it_other++);
      } else {
        it_this++;
      }
    }
  }
}

template <typename value_type>
void list<value_type>::splice(const_iterator pos, list& other) {
  if (!other.size()) return;
  Node* splicePos = pos.get_node();
  if (splicePos == nullptr) {
    tail_->next = other.head_;
    other.head_->prev = tail_;
    tail_ = other.tail_;
  } else {
    Node* prevPos = splicePos->prev;
    prevPos ? prevPos->next = other.head_ : head_ = other.head_;
    other.head_->prev = prevPos;
    splicePos->prev = other.tail_;
    other.tail_->next = splicePos;
  }
  size_ += other.size();
  other.size_ = 0;
  other.head_ = other.tail_ = nullptr;
}

template <typename value_type>
void list<value_type>::reverse() {
  if (!empty()) {
    Node* tmpChange = this->head_;

    while (tmpChange->next) {
      Node* tmpNext = tmpChange->next;
      std::swap(tmpChange->prev, tmpChange->next);
      tmpChange = tmpNext;
    }
    std::swap(tmpChange->prev, tmpChange->next);
    std::swap(head_, tail_);
  }
}

template <typename value_type>
void list<value_type>::unique() {
  if (!empty()) {
    auto it = this->begin();
    while ((it != this->end()) && ((it.get_node())->next)) {
      if (*it == (it.get_node())->next->value) {
        auto tmp = it++;
        erase(tmp);
      } else {
        it++;
      }
    }
  }
}

template <typename value_type>
void list<value_type>::sort() {
  if (!empty()) {
    Node* temp = head_;
    while (temp->next) {
      if (temp->value > temp->next->value) {
        std::swap(temp->value, temp->next->value);
        temp = temp->next;
        sort();
      } else
        temp = temp->next;
    }
  }
}

template <typename value_type>
template <typename... Args>
typename list<value_type>::iterator list<value_type>::insert_many(
    iterator pos, Args&&... args) {
  return ([&] { return insert(pos, std::forward<Args>(args)); }(), ...);
}

template <typename value_type>
template <typename... Args>
void list<value_type>::insert_many_back(Args&&... args) {
  ([&] { push_back(std::forward<Args>(args)); }(), ...);
}

template <typename value_type>
template <typename... Args>
void list<value_type>::insert_many_front(Args&&... args) {
  ([&] { push_front(std::forward<Args>(args)); }(), ...);
}

// HELPERS
template <typename value_type>
void list<value_type>::split(list<value_type>& source, list<value_type>& left,
                             list<value_type>& right) {
  left.clear();
  right.clear();
  if (source.size_ == 1) {
    left.head_ = left.tail_ = source.head_;
  } else {
    Node* slow = source.head_;
    Node* fast = source.head_->next;
    while (fast != nullptr) {
      fast = fast->next;
      if (fast != nullptr) {
        slow = slow->next;
        fast = fast->next;
      }
    }
    left.head_ = source.head_;
    left.tail_ = slow;
    right.head_ = slow->next;
    right.tail_ = source.tail_;
    slow->next = nullptr;
    if (right.head_) right.head_->prev = nullptr;
  }
}

template <typename value_type>
void list<value_type>::checkSize() const {
  if (!size_) {
    throw std::logic_error("Список пуст");
  }
}

template <typename value_type>
typename list<value_type>::Node* list<value_type>::findNode(iterator pos) {
  Node* current = head_;
  while (current != nullptr && iterator(current) != pos) {
    current = current->next;
  }
  return current;
}

}  // namespace s21