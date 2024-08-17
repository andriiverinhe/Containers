#ifndef S21_SET_H_
#define S21_SET_H_

#include "BinaryTree.h"
namespace s21 {
template <class Key>
class set : public s21::BinaryTree<Key> {
 public:
  using typename BinaryTree<Key>::key_type;
  using typename BinaryTree<Key>::reference;
  using typename BinaryTree<Key>::const_reference;
  using typename BinaryTree<Key>::iterator;
  using typename BinaryTree<Key>::const_iterator;
  using typename BinaryTree<Key>::size_type;
  using value_type = Key;
  set() {}
  ~set() {}
  set(std::initializer_list<value_type> const &items)
      : BinaryTree<Key>(items) {}
  set(const set &s) : BinaryTree<Key>(s) {}
  set(set &&s) : BinaryTree<Key>(std::move(s)) {}
  std::pair<iterator, bool> insert(const value_type &value) {
    return this->Insert(value);
  }
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> results;
    (
        [&] {
          auto res = insert(std::forward<Args>(args));
          results.push_back(res);
        }(),
        ...);
    return results;
  }

 private:
};
}  // namespace s21
#endif