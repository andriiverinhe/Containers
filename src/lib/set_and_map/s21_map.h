#ifndef S21_MAP_H_
#define S21_MAP_H_
// #include <utility>
#include <stdexcept>

#include "BinaryTree.h"
namespace s21 {
template <class Key, class T>
class map : public BinaryTree<std::pair<Key, T>> {
 public:
  using value_type = std::pair<Key, T>;
  using typename BinaryTree<value_type>::key_type;
  using typename BinaryTree<value_type>::reference;
  using typename BinaryTree<value_type>::const_reference;
  using typename BinaryTree<value_type>::iterator;
  using typename BinaryTree<value_type>::const_iterator;
  using typename BinaryTree<value_type>::size_type;
  using typename BinaryTree<value_type>::Node;

  map() {}
  ~map() {}
  map(std::initializer_list<value_type> const &items)
      : BinaryTree<value_type>(items) {}
  map(const map &m) : BinaryTree<value_type>(m) {}
  map(map &&m) : BinaryTree<value_type>(std::move(m)) {}
  T &at(const Key &key) {
    auto it = search(key);
    if (it != this->end()) {
      return it->second;
    } else {
      throw std::out_of_range("Нету такого ключа");
    }
  }
  T &operator[](const Key &key) {
    auto it = search(key);
    if (it != this->end()) {
      return it->second;
    } else {
      auto pair = insert(std::make_pair(key, T()));
      return pair.first->second;
    }
  }

  std::pair<iterator, bool> insert(const value_type &value) {
    iterator findNode = search(value.first);
    std::pair<iterator, bool> result = std::make_pair(findNode, bool());
    if (!findNode.getNode()) {
      result = this->Insert(value);
    } else {
      result.first = findNode;
      result.second = false;
    }
    return result;
  }
  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    return insert(std::make_pair(key, obj));
  }
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    auto it = insert(std::make_pair(key, obj));
    if (!it.second) {
      it.first->second = obj;
    }
    return it;
  }

  bool contains(const Key &key) {
    return search(key) != this->end() ? true : false;
  }
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> results;
    (
        [&] {
          results.push_back(insert(std::forward<Args>(args)));
        }(),
        ...);
    return results;
  }

 private:
  iterator search(const Key &key) {
    return iterator(searchRec(this->root, key), this);
  }
  Node *searchRec(Node *node, const Key &key) {
    if (node == nullptr || node->key_.first == key) {
      return node;
    }
    if (key < node->key_.first) {
      return searchRec(node->left, key);
    } else {
      return searchRec(node->right, key);
    }
  }

  Node *findMax(Node *node) {
    if (node) {
      while (node->right != nullptr) {
        node = node->right;
      }
      return node;
    }
    return nullptr;
  }
};
}  // namespace s21
#endif