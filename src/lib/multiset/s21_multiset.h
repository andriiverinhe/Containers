#ifndef MULTISET_
#define MULTISET_
#include <vector>
namespace s21 {
template <class Key>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;

 private:
  struct Node {
    Key value;
    unsigned int count = 1;
    Node *left = nullptr, *right = nullptr, *parent, *last = nullptr;
    Node(const_reference val, Node* par = nullptr) : value(val), parent(par) {}
  };

 public:
  using size_type = std::size_t;
  class iterator {
   public:
    iterator(Node* node_) : node(node_) {}
    reference operator*() const { return node->value; }
    Node& operator->() const { return *node; }
    Node* operator&() const { return node; }
    iterator operator++();
    iterator operator++(int);
    iterator operator--();
    iterator operator--(int);
    bool operator==(const iterator& other) const { return node == &other; }
    bool operator!=(const iterator& other) const { return !(*this == other); }

   private:
    Node* node;
  };
  class const_iterator : public iterator {
    const_iterator(){};
    const_iterator(const iterator& node_) : iterator(node_){};
    Key& operator*() const { return iterator::operator*(); };
  };
  multiset() {}
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& ms);
  multiset(multiset&& ms);
  ~multiset() { clear(); }
  multiset& operator=(multiset&& ms);
  void erase(iterator pos);
  iterator begin();
  iterator end();
  bool empty() { return !size_; }
  size_type size() { return size_; }
  size_type max_size() {
    return std::numeric_limits<long>::max() / sizeof(Node);
  }
  void merge(multiset& other);
  void swap(multiset& other);
  iterator insert(const_reference value);
  void clear();
  size_type count(const_reference key) const {
    Node* node1 = search(root, key);
    return (node1 != nullptr) ? node1->count : 0;
  }
  iterator find(const_reference key) { return iterator(search(root, key)); }
  bool contains(const_reference key) const {
    return search(root, key) != nullptr;
  }
  std::pair<iterator, iterator> equal_range(const Key& key);
  iterator lower_bound(const_reference key);
  iterator upper_bound(const_reference key);
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> results;
    (
        [&] {
          auto res = insert(std::forward<Args>(args));
          results.push_back(std::make_pair(res, true));
        }(),
        ...);
    return results;
  }

 private:
  Node* root = nullptr;
  Node* rootEnd = nullptr;
  size_type size_ = 0;
  Node* insertRec(Node* node, const_reference value, Node* parent);
  void clearRec(Node* node);
  void clearEnd();
  Node* getMin(Node* node) {
    if (node == nullptr) return nullptr;
    if (node->left == nullptr) return node;
    return getMin(node->left);
  }
  Node* search(Node* node, const_reference key) const;
  Node* copyNode(const Node* node);
  Node* deleteNode(Node* node, Key key);
};
#include "multiset.tpp"
}  // namespace s21

#endif