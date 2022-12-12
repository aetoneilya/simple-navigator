#ifndef SRC_S21_ARRAY_H_
#define SRC_S21_ARRAY_H_

#include <algorithm>
#include <utility>

namespace s21 {
template <typename T, std::size_t N>
struct array {
    using value_type = T;
    using reference = value_type &;
    using const_reference = value_type const &;
    using iterator = value_type *;
    using const_iterator = value_type const *;
    using size_type = std::size_t;

    array();
    explicit array(std::initializer_list<value_type> const &items);
    array(array const &a);
    array(array &&a);
    ~array();

    array &operator=(array &&a);

    reference at(size_type pos);
    const_reference at(size_type pos) const;
    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    T *data() noexcept;
    T const *data() const noexcept;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;

    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;

    void swap(array &other);
    void fill(const_reference value);

 private:
    T _head[N + 1];
};

template <typename T, std::size_t N>
array<T, N>::array() {
}

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
    std::copy_n(items.begin(), size(), begin());
}

template <typename T, std::size_t N>
array<T, N>::array(array const &a) {
    std::copy(a.begin(), a.end(), begin());
}

template <typename T, std::size_t N>
array<T, N>::array(array &&a) {
    swap(a);
}

template <typename T, std::size_t N>
array<T, N>::~array() {
}

template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(array &&a) {
    if (this != &a) {
        array(std::move(a)).swap(*this);
    }
    return *this;
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
    return const_cast<array<T, N>::reference>(const_cast<array<T, N> const *>(this)->at(pos));
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::at(size_type pos) const {
    if (pos >= size()) {
        throw std::out_of_range("array<T, N>::at: pos >= size");
    }
    return _head[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
    return const_cast<array<T, N>::reference>(const_cast<array<T, N> const *>(this)->operator[](pos));
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::operator[](size_type pos) const {
    return _head[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::front() {
    return const_cast<array<T, N>::reference>(const_cast<array<T, N> const *>(this)->front());
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() const {
    return _head[0];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::back() {
    return const_cast<array<T, N>::reference>(const_cast<array<T, N> const *>(this)->back());
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
    return _head[size() - 1];
}

template <typename T, std::size_t N>
T *array<T, N>::data() noexcept {
    return const_cast<T *>(const_cast<array<T, N> const *>(this)->data());
}

template <typename T, std::size_t N>
T const *array<T, N>::data() const noexcept {
    return _head;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() noexcept {
    return iterator(data());
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::begin() const noexcept {
    return const_iterator(data());
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() noexcept {
    return iterator(data() + size());
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::end() const noexcept {
    return iterator(data() + size());
}

template <typename T, std::size_t N>
bool array<T, N>::empty() const noexcept {
    return size() == 0;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() const noexcept {
    return N;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const noexcept {
    return size();
}

template <typename T, std::size_t N>
void array<T, N>::swap(array &other) {
    std::swap_ranges(begin(), end(), other.begin());
}

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
    std::fill_n(begin(), size(), value);
}
}  // namespace s21

#endif  // SRC_S21_ARRAY_H_
