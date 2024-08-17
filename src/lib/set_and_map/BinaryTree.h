#ifndef BINARYTREE_H_
#define BINARYTREE_H_
#include <limits>
#include <stdexcept>

namespace s21 {

template <class Key>
class BinaryTree {
 protected:
  struct Node {
    Key key_;
    Node *left = nullptr, *right = nullptr, *parent = nullptr;
    Node(Key key) : key_(key) {}
    Node(Key key, Node *parent) : key_(key), parent(parent) {}
  };

  Node *root = nullptr;
  using N = Node *;

 public:
  using key_type = Key;
  using reference = Key &;
  using const_reference = const Key &;
  using size_type = std::size_t;

  class iterator {
   public:
    iterator(Node *node, BinaryTree<Key> *tree_ = nullptr)
        : itNode(node), tree(tree_) {}
    Key &operator*() {
      if (itNode == nullptr)
        throw std::runtime_error("Невозможно достать значение из nullptr");
      return itNode->key_;
    }
    Key *operator->() { return &(itNode->key_); }
    iterator operator+(const std::size_t size);

    iterator operator++();
    iterator operator++(int);

    iterator operator--();
    iterator operator--(int);

    bool operator==(const iterator &other) const {
      return this->itNode == other.itNode;
    }
    bool operator!=(const iterator &other) const { return !(*this == other); }
    Node *getNode() { return itNode; }

   protected:
    Node *itNode;
    BinaryTree<Key> *tree;
  };

  class const_iterator {};

  BinaryTree() {}
  ~BinaryTree();
  BinaryTree(std::initializer_list<Key> const &items);
  BinaryTree(const BinaryTree &m);
  BinaryTree(BinaryTree &&m);
  BinaryTree<Key> &operator=(BinaryTree &&m);

  iterator begin();
  iterator end();

  bool empty() const { return !size_; }
  size_type size() const { return size_; }
  size_type max_size() { return std::numeric_limits<size_type>::max(); }

  void clear();
  std::pair<iterator, bool> Insert(const_reference value);
  void erase(iterator pos);
  void swap(BinaryTree &other);
  void merge(BinaryTree &other);
  iterator find(const Key &key);
  bool contains(const Key &key);

 protected:
  N insertRec(N node, const_reference value, N parrent, bool &isset);
  void clearRec(N node);
  N copyBinaryTree(N CRoot);
  Node *findMax(Node *node);
  size_type size_ = 0;
  Node *deleteNode(Node *node, Key key);
};
#include "BinaryTree.tpp"
}  // namespace s21
#endif