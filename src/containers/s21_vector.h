#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <utility>

namespace s21 {
template <typename T>
struct vector {
 private:
    struct _Vector_iterator;
    struct _Vector_const_iterator;

 public:
    using value_type = T;
    using reference = value_type &;
    using const_reference = value_type const &;
    using iterator = _Vector_iterator;
    using const_iterator = _Vector_const_iterator;
    using size_type = std::size_t;

    vector();
    explicit vector(size_type n);
    explicit vector(std::initializer_list<value_type> const &items);
    vector(vector const &v);
    vector(vector &&v);
    ~vector();

    vector &operator=(vector &&v);

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
    void reserve(size_type size);
    size_type capacity() const noexcept;
    void shrink_to_fit();

    void clear();
    iterator insert(iterator pos, const_reference value);
    template <typename... Args>
    iterator emplace(const_iterator pos, Args &&...args);
    void erase(iterator pos);
    void push_back(const_reference value);
    template <typename... Args>
    void emplace_back(Args &&...args);
    void pop_back();
    void swap(vector &other);

 private:
    size_type _size, _capacity;
    T *_head;

    static size_type const _min_capacity = 32;

    std::allocator<T> _a;
    using _Vector_manager = std::allocator_traits<std::allocator<T>>;

    void _reserve(size_type __capacity);

    struct _Vector_iterator {
        using _Self = _Vector_iterator;

        T *_p;
        size_type _offset;

        explicit _Vector_iterator(T *p, size_type offset = 0) noexcept : _p(p), _offset(offset) {
        }

        operator _Vector_const_iterator() const {
            return _Vector_const_iterator(_p, _offset);
        }

        reference operator*() const noexcept {
            return _p[_offset];
        }

        _Self &operator++() noexcept {
            ++_offset;
            return *this;
        }

        _Self operator++(int) noexcept {
            auto it = *this;
            ++(*this);
            return it;
        }

        _Self &operator--() noexcept {
            --_offset;
            return *this;
        }

        _Self operator--(int) noexcept {
            auto it = *this;
            --(*this);
            return it;
        }

        bool operator==(_Self const &other) const noexcept {
            return _p + _offset == other._p + other._offset;
        }

        bool operator!=(_Self const &other) const noexcept {
            return _p + _offset != other._p + other._offset;
        }
    };

    struct _Vector_const_iterator {
        using _Self = _Vector_const_iterator;

        T const *_p;
        size_type _offset;

        explicit _Vector_const_iterator(T const *p, size_type offset = 0) noexcept : _p(p), _offset(offset) {
        }

        _Vector_iterator _const_cast() const noexcept {
            return _Vector_iterator(const_cast<T *>(_p), _offset);
        }

        const_reference operator*() const noexcept {
            return _p[_offset];
        }

        _Self &operator++() noexcept {
            ++_offset;
            return *this;
        }

        _Self operator++(int) noexcept {
            auto it = *this;
            ++(*this);
            return it;
        }

        _Self &operator--() noexcept {
            --_offset;
            return *this;
        }

        _Self operator--(int) noexcept {
            auto it = *this;
            --(*this);
            return it;
        }

        bool operator==(_Self const &other) const noexcept {
            return _p + _offset == other._p + other._offset;
        }

        bool operator!=(_Self const &other) const noexcept {
            return _p + _offset != other._p + other._offset;
        }
    };
};

template <typename T>
vector<T>::vector() : _size(0), _capacity(_min_capacity), _head(_Vector_manager::allocate(_a, _capacity)) {
}

template <typename T>
vector<T>::vector(size_type n) : _size(n),
                                 _capacity((_size + _min_capacity) * 2),
                                 _head(_Vector_manager::allocate(_a, _capacity)) {
    for (size_type i = 0; i < n; ++i) {
        _Vector_manager::construct(_a, _head + i);
    }
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items) : vector() {
    for (auto it = items.begin(); it != items.end(); ++it) {
        push_back(*it);
    }
}

template <typename T>
vector<T>::vector(vector const &v) : vector() {
    for (auto it = v.begin(); it != v.end(); ++it) {
        push_back(*it);
    }
}

template <typename T>
vector<T>::vector(vector &&v) : vector() {
    swap(v);
}

template <typename T>
vector<T>::~vector() {
    clear();

    _Vector_manager::deallocate(_a, _head, _capacity);
}

template <typename T>
vector<T> &vector<T>::operator=(vector &&v) {
    if (this != &v) {
        vector(std::move(v)).swap(*this);
    }
    return *this;
}

template <typename T>
void vector<T>::_reserve(size_type __capacity) {
    T *__head = _Vector_manager::allocate(_a, __capacity + 1);
    size_type __size = std::min(_size, __capacity);

    for (size_type i = 0; i < __size; ++i) {
        std::swap(_head[i], __head[i]);
    }

    for (size_type i = __capacity; i < _size; ++i) {
        _Vector_manager::destroy(_a, _head + i);
    }

    _Vector_manager::deallocate(_a, _head, _capacity);

    _size = __size;
    _capacity = __capacity;
    _head = __head;
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
    return const_cast<vector<T>::reference>(const_cast<vector<T> const *>(this)->at(pos));
}

template <typename T>
typename vector<T>::const_reference vector<T>::at(size_type pos) const {
    if (pos >= _size) {
        throw std::out_of_range("vector<T>::at: pos >= _size");
    }
    return _head[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
    return const_cast<vector<T>::reference>(const_cast<vector<T> const *>(this)->operator[](pos));
}

template <typename T>
typename vector<T>::const_reference vector<T>::operator[](size_type pos) const {
    return _head[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::front() {
    return const_cast<vector<T>::reference>(const_cast<vector<T> const *>(this)->front());
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
    return _head[0];
}

template <typename T>
typename vector<T>::reference vector<T>::back() {
    return const_cast<vector<T>::reference>(const_cast<vector<T> const *>(this)->back());
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
    return _head[_size - 1];
}

template <typename T>
T *vector<T>::data() noexcept {
    return const_cast<T *>(const_cast<vector<T> const *>(this)->data());
}

template <typename T>
T const *vector<T>::data() const noexcept {
    return _head;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() noexcept {
    return _Vector_iterator(_head);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::begin() const noexcept {
    return _Vector_const_iterator(_head);
}

template <typename T>
typename vector<T>::iterator vector<T>::end() noexcept {
    return _Vector_iterator(_head, _size);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::end() const noexcept {
    return _Vector_const_iterator(_head, _size);
}

template <typename T>
bool vector<T>::empty() const noexcept {
    return begin() == end();
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const noexcept {
    return _size;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const noexcept {
    return _Vector_manager::max_size(_a);
}

template <typename T>
void vector<T>::reserve(size_type size) {
    _reserve(size);
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const noexcept {
    return _capacity;
}

template <typename T>
void vector<T>::shrink_to_fit() {
    _reserve(_size);
}

template <typename T>
void vector<T>::clear() {
    while (!empty()) {
        pop_back();
    }
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos, const_reference value) {
    if (_capacity == 0 || _size == _capacity - 1) {
        _reserve((_capacity + _min_capacity) * 2);
    }

    for (size_type i = _size; i > pos._offset; --i) {
        std::swap(_head[i], _head[i - 1]);
    }
    _Vector_manager::construct(_a, _head + pos._offset, value);

    ++_size;

    return _Vector_iterator(_head + pos._offset);
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::emplace(const_iterator pos, Args &&...args) {
    ([&]() { insert(pos._const_cast(), args); }(), ...);
    return --pos._const_cast();
}

template <typename T>
void vector<T>::erase(iterator pos) {
    if (!empty()) {
        _Vector_manager::destroy(_a, _head + pos._offset);

        for (size_type i = pos._offset + 1; i < _size; ++i) {
            std::swap(_head[i - 1], _head[i]);
        }

        --_size;
    }
}

template <typename T>
void vector<T>::push_back(const_reference value) {
    insert(end(), value);
}

template <typename T>
template <typename... Args>
void vector<T>::emplace_back(Args &&...args) {
    ([&]() { push_back(args); }(), ...);
}

template <typename T>
void vector<T>::pop_back() {
    if (!empty()) {
        erase(--end());
    }
}

template <typename T>
void vector<T>::swap(vector &other) {
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
    std::swap(_head, other._head);
}
}  // namespace s21

#endif  // SRC_S21_VECTOR_H_
