#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_

#include <functional>
#include <utility>

#include "RBTree.h"

using std::pair;

namespace s21 {
template <class Key, class T>
class map {
 public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type &;
    using const_reference = value_type const &;

    struct cmp_pair_by_key {
        bool operator()(const_reference a, const_reference b) const {
            key_type a_key = std::get<0>(a);
            key_type b_key = std::get<0>(b);
            return (a_key < b_key);
        }
    };
    using iterator = typename RBTree<value_type, cmp_pair_by_key>::iterator;
    using const_iterator =
        typename RBTree<value_type, cmp_pair_by_key>::const_iterator;
    using size_type = std::size_t;

    map() {}
    explicit map(std::initializer_list<value_type> const &items)
        : data(RBTree<value_type, cmp_pair_by_key>(items)) {}
    map(const map &m) : data(RBTree<value_type, cmp_pair_by_key>(m.data)) {}
    map(map &&m) { std::swap(data, m.data); }
    ~map() {}
    map &operator=(map &&m) {
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
    std::pair<iterator, bool> insert(const Key &key, const T &obj) {
        return data.insert(std::make_pair(key, obj));
    }
    std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
        std::pair<iterator, bool> result = data.insert(std::make_pair(key, obj));
        if (result.second == false) {
            at(key) = obj;
        }
        return result;
    }
    void erase(iterator pos) { data.erase(pos); }
    void swap(map &other) { data.swap(other.data); }
    void merge(map &other) { data.merge(other.data); }

    mapped_type &at(const key_type &key) {
        value_type tmp_pair = std::make_pair(key, mapped_type());
        auto it = (data.find(tmp_pair));
        if (it == data.end()) {
            throw std::out_of_range("no such key in current map");
        }
        return std::get<1>(*it);
    }
    mapped_type &operator[](const key_type &key) { return at(key); }
    bool contains(const key_type &key) {
        value_type tmp_pair = std::make_pair(key, mapped_type());
        return data.contains(tmp_pair);
    }

    template <typename... Args>
    std::pair<iterator, bool> emplace(Args &&...args) {
        return data.emplace(args...);
    }

 private:
    RBTree<value_type, cmp_pair_by_key> data;
};
}  // namespace s21

#endif  // SRC_S21_MAP_H_
