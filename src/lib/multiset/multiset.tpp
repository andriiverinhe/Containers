template <class Key>
multiset<Key>::multiset(std::initializer_list<value_type> const &items) {
  for (const auto &item : items) {
    insert(item);
  }
}

template <class Key>
multiset<Key>::multiset(const multiset &ms) {
  if (ms.root != nullptr) {
    root = copyNode(ms.root);
    size_ = ms.size_;
  }
}

template <class Key>
multiset<Key>::multiset(multiset &&ms) {
  *this = std::move(ms);
}

template <class Key>
multiset<Key> &multiset<Key>::operator=(multiset<Key> &&ms) {
  if (this != &ms) {
    clear();
    root = ms.root;
    size_ = ms.size_;
    ms.root = nullptr;
    ms.size_ = 0;
  }
  return *this;
}

template <class Key>
typename multiset<Key>::iterator multiset<Key>::begin() {
  return iterator(getMin(root));
}

template <class Key>
typename multiset<Key>::iterator multiset<Key>::end() {
  return iterator(nullptr);
}

template <class Key>
typename multiset<Key>::iterator multiset<Key>::insert(const_reference value) {
  Node *tmp = insertRec(root, value, nullptr);
  ++size_;
  return iterator(tmp);
}

template <class Key>
typename multiset<Key>::Node *multiset<Key>::insertRec(Node *node,
                                                       const Key &value,
                                                       Node *parent) {
  if (node == nullptr) {
    node = new Node(value, parent);
    if (root == nullptr) root = node;
    return node;
  } else if (value < node->value) {
    Node *insNode = insertRec(node->left, value, node);
    if (node->left == nullptr) node->left = insNode;
    return insNode;
  } else if (value > node->value) {
    Node *insNode = insertRec(node->right, value, node);
    if (node->right == nullptr) node->right = insNode;
    return insNode;
  } else {
    node->count++;
    return node;
  }
}

template <class Key>
typename multiset<Key>::Node *multiset<Key>::copyNode(const Node *node) {
  if (node == nullptr) return nullptr;
  Node *newNode = new Node(node->value);
  newNode->count = node->count;
  newNode->left = copyNode(node->left);
  newNode->right = copyNode(node->right);
  if (newNode->left != nullptr) newNode->left->parent = newNode;
  if (newNode->right != nullptr) newNode->right->parent = newNode;
  return newNode;
}

template <class Key>
typename multiset<Key>::Node *multiset<Key>::search(Node *node,
                                                    const_reference key) const {
  if (node == nullptr || node->value == key) {
    return node;
  } else if (key < node->value) {
    return search(node->left, key);
  } else {
    return search(node->right, key);
  }
}

template <class Key>
typename multiset<Key>::Node *multiset<Key>::deleteNode(Node *node, Key key) {
  if (node == nullptr) {
    return nullptr;
  } else if (key < node->value) {
    node->left = deleteNode(node->left, key);
  } else if (key > node->value) {
    node->right = deleteNode(node->right, key);
  } else {
    if (node->count > 1) {
      node->count--;
      size_--;
    } else if (node->left == nullptr || node->right == nullptr) {
      Node *temp = (node->left == nullptr) ? node->right : node->left;
      if (temp != nullptr) {
        temp->parent = node->parent;
      }
      delete node;
      node = temp;
      size_--;
    } else {
      Node *maxRight = getMin(node->right);
      node->value = maxRight->value;
      node->count = maxRight->count;
      maxRight->count = 1;
      node->right = deleteNode(node->right, maxRight->value);
    }
  }
  return node;
}

template <class Key>
void multiset<Key>::erase(iterator pos) {
  deleteNode(&pos, *pos);
}

template <class Key>
void multiset<Key>::merge(multiset &other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    this->insert(*it);
  }
  other.clear();
}

template <class Key>
void multiset<Key>::swap(multiset &other) {
  multiset<Key> tmp = std::move(other);
  other = std::move(*this);
  *this = std::move(tmp);
}

template <class Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(
    const_reference key) {
  Node *current = root;
  Node *result = rootEnd;
  while (current != nullptr) {
    if (current->value >= key) {
      result = current;
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return iterator(result);
}

template <class Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(
    const_reference key) {
  Node *current = root;
  Node *result = rootEnd;
  while (current != nullptr) {
    if (current->value > key) {
      result = current;
      current = current->left;
    } else {
      current = current->right;
    }
  }

  return iterator(result);
}

template <class Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key &key) {
  return std::make_pair(lower_bound(key), upper_bound(key));
}

template <class Key>
void multiset<Key>::clear() {
  clearRec(root);
  clearEnd();
  root = nullptr;
  size_ = 0;
}

template <class Key>
void multiset<Key>::clearEnd() {
  if (rootEnd) {
    rootEnd->parent->last = nullptr;
    delete rootEnd;
    rootEnd = nullptr;
  }
}

template <class Key>
void multiset<Key>::clearRec(Node *node) {
  if (node != nullptr) {
    clearRec(node->left);
    clearRec(node->right);
    delete node;
  }
}

template <class Key>
typename multiset<Key>::iterator multiset<Key>::iterator::operator++() {
  if (node->right != nullptr) {
    node = node->right;
    while (node->left != nullptr) {
      node = node->left;
    }
  } else {
    Node *tempNode = node->parent;
    Node *last = node->last;
    while (tempNode != nullptr && node == tempNode->right) {
      node = tempNode;
      tempNode = tempNode->parent;
    }
    node = tempNode;
    if (!node) {
      node = last;
    }
  }
  return *this;
}

template <class Key>
typename multiset<Key>::iterator multiset<Key>::iterator::operator++(int) {
  iterator temp = *this;
  ++(*this);
  return temp;
}

template <class Key>
typename multiset<Key>::iterator multiset<Key>::iterator::operator--() {
  if (node->left != nullptr) {
    node = node->left;
    while (node->right != nullptr) {
      node = node->right;
    }
  } else {
    Node *parent = node->parent;
    while (parent != nullptr && node == parent->left) {
      node = parent;
      parent = parent->parent;
    }
    node = parent;
  }
  return *this;
}
template <class Key>
typename multiset<Key>::iterator multiset<Key>::iterator::operator--(int) {
  iterator temp = *this;
  --(*this);
  return temp;
}