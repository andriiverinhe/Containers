template <class Key>
BinaryTree<Key>::~BinaryTree() {
  clear();
}

template <class Key>
BinaryTree<Key>::BinaryTree(std::initializer_list<Key> const &items) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    Insert(*it);
  }
}

template <class Key>
BinaryTree<Key>::BinaryTree(const BinaryTree &m) {
  size_ = m.size_;
  root = copyBinaryTree(m.root);
  // setNewEnd();
}

template <class Key>
BinaryTree<Key>::BinaryTree(BinaryTree &&m) {
  *this = std::move(m);
}

template <class Key>
void BinaryTree<Key>::merge(BinaryTree &other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    Insert(*it);
  }
  other.clear();
}

template <class Key>
BinaryTree<Key> &BinaryTree<Key>::operator=(BinaryTree &&m) {
  if (this != &m) {
    delete root;
    size_ = m.size_;
    root = m.root;
    m.size_ = 0;
    m.root = nullptr;
  }
  return *this;
}

template <class Key>
void BinaryTree<Key>::swap(BinaryTree &other) {
  BinaryTree<Key> tmp = std::move(other);
  other = std::move(*this);
  *this = std::move(tmp);
}

// копирование
template <class Key>
typename BinaryTree<Key>::N BinaryTree<Key>::copyBinaryTree(N CRoot) {
  if (CRoot == nullptr) {
    return nullptr;
  }
  N newNode = new Node(CRoot->key_);
  newNode->left = copyBinaryTree(CRoot->left);
  newNode->right = copyBinaryTree(CRoot->right);
  return newNode;
}

template <class Key>
std::pair<typename BinaryTree<Key>::iterator, bool> BinaryTree<Key>::Insert(
    const_reference value) {
  bool isset = true;
  N tmp = insertRec(root, value, nullptr, isset);
  if (isset) ++size_;
  return std::make_pair(iterator(tmp, this), isset);
}

template <class Key>
typename BinaryTree<Key>::N BinaryTree<Key>::insertRec(N node,
                                                       const_reference value,
                                                       N parent, bool &isset) {
  if (node == nullptr) {
    node = new Node(value, parent);
    if (root == nullptr) root = node;
    return node;
  } else if (value < node->key_) {
    N insertedNode = insertRec(node->left, value, node, isset);
    if (node->left == nullptr) node->left = insertedNode;
    return insertedNode;
  } else if (value > node->key_) {
    N insertedNode = insertRec(node->right, value, node, isset);
    if (node->right == nullptr) node->right = insertedNode;
    return insertedNode;
  } else {
    isset = false;
    return node;
  }
}

template <class Key>
typename BinaryTree<Key>::iterator BinaryTree<Key>::begin() {
  Node *node = root;
  while (node != nullptr && node->left != nullptr) {
    node = node->left;
  }
  return iterator(node, this);
}

template <class Key>
typename BinaryTree<Key>::iterator BinaryTree<Key>::end() {
  return iterator(nullptr, this);
}

template <class Key>
typename BinaryTree<Key>::iterator BinaryTree<Key>::find(const Key &key) {
  N current = root;
  while (current != nullptr) {
    if (key < current->key_) {
      current = current->left;
    } else if (key > current->key_) {
      current = current->right;
    } else {
      return iterator(current, this);
    }
  }
  return end();
}

template <class Key>
bool BinaryTree<Key>::contains(const Key &key) {
  return find(key) != end() ? true : false;
}

template <class Key>
void BinaryTree<Key>::erase(iterator pos) {
  if (pos.getNode() != nullptr) root = deleteNode(root, *pos);
}

template <class Key>
typename BinaryTree<Key>::Node *BinaryTree<Key>::deleteNode(Node *node,
                                                            Key key) {
  if (node == nullptr) {
    return nullptr;
  } else if (key < node->key_) {
    node->left = deleteNode(node->left, key);
  } else if (key > node->key_) {
    node->right = deleteNode(node->right, key);
  } else {
    if (node->left == nullptr || node->right == nullptr) {
      Node *temp = (node->left == nullptr) ? node->right : node->left;
      if (temp != nullptr) {
        temp->parent = node->parent;
      }
      delete node;
      node = temp;
      size_--;
    } else {
      Node *maxLeft = findMax(node->left);
      node->key_ = maxLeft->key_;
      node->right = deleteNode(node->right, maxLeft->key_);
    }
  }
  return node;
}

template <class Key>
void BinaryTree<Key>::clear() {
  clearRec(root);
  root = nullptr;
  size_ = 0;
}

template <class Key>
void BinaryTree<Key>::clearRec(N node) {
  if (node != nullptr) {
    clearRec(node->left);
    clearRec(node->right);
    delete node;
  }
}

template <class Key>
typename BinaryTree<Key>::iterator BinaryTree<Key>::iterator::operator+(
    const std::size_t size) {
  for (std::size_t i = 0; i < size; ++i) {
    ++(*this);
  }
  return *this;
}

template <class Key>
typename BinaryTree<Key>::iterator BinaryTree<Key>::iterator::operator++() {
  if (!itNode) return *this;
  if (itNode->right != nullptr) {
    itNode = itNode->right;
    while (itNode->left != nullptr) {
      itNode = itNode->left;
    }
  } else {
    Node *tempNode = itNode->parent;
    while (tempNode != nullptr && itNode == tempNode->right) {
      itNode = tempNode;
      tempNode = tempNode->parent;
    }
    itNode = tempNode;
  }
  return *this;
}

template <class Key>
typename BinaryTree<Key>::iterator BinaryTree<Key>::iterator::operator++(int) {
  iterator temp = *this;
  ++(*this);
  return temp;
}

template <class Key>
typename BinaryTree<Key>::iterator BinaryTree<Key>::iterator::operator--() {
  if (itNode == nullptr) {
    itNode = tree->findMax(tree->root);
  } else if (itNode->left != nullptr) {
    itNode = tree->findMax(itNode->left);
  } else {
    Node *temp = itNode->parent;
    while (temp != nullptr && itNode == temp->left) {
      itNode = temp;
      temp = temp->parent;
    }
    itNode = temp;
  }
  return *this;
}

template <class Key>
typename BinaryTree<Key>::iterator BinaryTree<Key>::iterator::operator--(int) {
  iterator temp = *this;
  --(*this);
  return temp;
}

template <class Key>
typename BinaryTree<Key>::Node *BinaryTree<Key>::findMax(Node *node) {
  if (node) {
    while (node->right != nullptr) {
      node = node->right;
    }
    return node;
  }
  return nullptr;
}