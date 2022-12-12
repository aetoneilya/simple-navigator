#ifndef SRC_S21_MULTISET_H_
#define SRC_S21_MULTISET_H_

#include <functional>
#include <utility>

#include "RBTree.h"

namespace s21 {
template <class T>
class multiset {
 public:
    using key_type = T;
    using value_type = T;
    using reference = value_type &;
    using const_reference = value_type const &;
    using iterator =
        typename RBTree<value_type, std::less_equal<key_type>>::iterator;
    using const_iterator =
        typename RBTree<value_type, std::less_equal<key_type>>::const_iterator;
    using size_type = std::size_t;

    multiset() {}
    explicit multiset(std::initializer_list<value_type> const &items)
        : data(RBTree<value_type, std::less_equal<key_type>>(items)) {}
    multiset(const multiset &m)
        : data(RBTree<value_type, std::less_equal<key_type>>(m.data)) {}
    multiset(multiset &&m) { std::swap(data, m.data); }
    ~multiset() {}
    multiset &operator=(multiset &&m) {
        std::swap(data, m.data);
        return *this;
    }

    iterator begin() noexcept { return data.begin(); }
    iterator end() noexcept { return data.end(); }
    const_iterator begin() const noexcept { return data.begin(); }
    const_iterator end() const noexcept { return data.end(); }

    bool empty() const noexcept { return data.empty(); }
    size_type size() const noexcept { return data.size(); }
    size_type max_size() const noexcept { return data.max_size(); }

    void clear() { data.clear(); }
    std::pair<iterator, bool> insert(const value_type &value) {
        return data.insert(value);
    }
    void erase(iterator pos) { data.erase(pos); }
    void swap(multiset &other) { data.swap(other.data); }
    void merge(multiset &other) { data.merge(other.data); }

    iterator find(const key_type &key) { return data.find(key); }
    bool contains(const key_type &key) { return data.contains(key); }
    size_type count(const key_type &key) { return data.count(key); }
    std::pair<iterator, iterator> equal_range(const key_type &key) {
        return data.equal_range(key);
    }
    iterator lower_bound(const key_type &key) { return data.lower_bound(key); }
    iterator upper_bound(const key_type &key) { return data.upper_bound(key); }

    template <typename... Args>
    std::pair<iterator, bool> emplace(Args &&...args) {
        return data.emplace(args...);
    }

 private:
    RBTree<value_type, std::less_equal<key_type>> data;
};
}  // namespace s21

#endif  // SRC_S21_MULTISET_H_
