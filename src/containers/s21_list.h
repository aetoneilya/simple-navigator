#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

#include <memory>
#include <utility>

namespace s21 {
template <typename T>
struct list {
 private:
    struct _List_node;
    struct _List_iterator;
    struct _List_const_iterator;

 public:
    using value_type = T;
    using reference = value_type &;
    using const_reference = value_type const &;
    using iterator = _List_iterator;
    using const_iterator = _List_const_iterator;
    using size_type = std::size_t;

    list();
    explicit list(size_type n);
    explicit list(std::initializer_list<value_type> const &items);
    list(list const &l);
    list(list &&l);
    ~list();

    list &operator=(list &&l);

    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;

    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;

    void clear();
    iterator insert(iterator pos, const_reference value);
    template <typename... Args>
    iterator emplace(const_iterator pos, Args &&...args);
    void erase(iterator pos);
    void push_back(const_reference value);
    template <typename... Args>
    void emplace_back(Args &&...args);
    void pop_back();
    void push_front(const_reference value);
    template <typename... Args>
    void emplace_front(Args &&...args);
    void pop_front();
    void swap(list &other);

    void merge(list &other);
    void splice(const_iterator pos, list &other);
    void reverse() noexcept;
    void unique();
    void sort();

 private:
    size_type _size;
    _List_node *_head;

    std::allocator<_List_node> _a;
    using _List_node_manager = std::allocator_traits<std::allocator<_List_node>>;

    void insert(iterator _pos, _List_node *_node = nullptr) noexcept;

    struct _List_node {
        _List_node *_prev;
        _List_node *_next;
        value_type _data = {};

        _List_node() noexcept : _prev(this), _next(this) {
        }

        explicit _List_node(const_reference data) : _prev(this), _next(this), _data(data) {
        }

        ~_List_node() noexcept {
            _prev->_next = _next;
            _next->_prev = _prev;
        }
    };

    struct _List_iterator {
        using _Self = _List_iterator;

        _List_node *_node;

        explicit _List_iterator(_List_node *node) noexcept : _node(node) {
        }

        operator _List_const_iterator() const {
            return _List_const_iterator(_node);
        }

        reference operator*() const noexcept {
            return _node->_data;
        }

        _Self &operator++() noexcept {
            _node = _node->_next;
            return *this;
        }

        _Self operator++(int) noexcept {
            auto it = *this;
            ++(*this);
            return it;
        }

        _Self &operator--() noexcept {
            _node = _node->_prev;
            return *this;
        }

        _Self operator--(int) noexcept {
            auto it = *this;
            --(*this);
            return it;
        }

        bool operator==(_Self const &other) const noexcept {
            return _node == other._node;
        }

        bool operator!=(_Self const &other) const noexcept {
            return _node != other._node;
        }
    };

    struct _List_const_iterator {
        using _Self = _List_const_iterator;

        _List_node const *_node;

        explicit _List_const_iterator(_List_node const *node) noexcept : _node(node) {
        }

        _List_iterator _const_cast() const noexcept {
            return _List_iterator(const_cast<_List_node *>(_node));
        }

        const_reference operator*() const noexcept {
            return _node->_data;
        }

        _Self &operator++() noexcept {
            _node = _node->_next;
            return *this;
        }

        _Self operator++(int) noexcept {
            auto it = *this;
            ++(*this);
            return it;
        }

        _Self &operator--() noexcept {
            _node = _node->_prev;
            return *this;
        }

        _Self operator--(int) noexcept {
            auto it = *this;
            --(*this);
            return it;
        }

        bool operator==(_Self const &other) const noexcept {
            return _node == other._node;
        }

        bool operator!=(_Self const &other) const noexcept {
            return _node != other._node;
        }
    };

    struct _List_sort {
        _List_sort() {
        }
        ~_List_sort() {
        }

        static _List_node *_sort(_List_node *_lhs) {
            if (_lhs == nullptr || _lhs->_next == nullptr) {
                return _lhs;
            }
            _List_node *_rhs = _split(_lhs);

            _lhs = _sort(_lhs);
            _rhs = _sort(_rhs);

            return _merge(_lhs, _rhs);
        }

     private:
        static _List_node *_split(_List_node *_lhs) {
            _List_node *_f = _lhs;
            _List_node *_s = _lhs;

            while (_f->_next != nullptr && _f->_next->_next != nullptr) {
                _f = _f->_next->_next;
                _s = _s->_next;
            }

            _List_node *_t = _s->_next;
            _s->_next = nullptr;

            return _t;
        }

        static _List_node *_merge(_List_node *_lhs, _List_node *_rhs) {
            if (_lhs == nullptr) {
                return _rhs;
            }
            if (_rhs == nullptr) {
                return _lhs;
            }

            if (_lhs->_data < _rhs->_data) {
                _lhs->_next = _merge(_lhs->_next, _rhs);
                _lhs->_next->_prev = _lhs;
                _lhs->_prev = nullptr;
                return _lhs;
            } else {
                _rhs->_next = _merge(_lhs, _rhs->_next);
                _rhs->_next->_prev = _rhs;
                _rhs->_prev = nullptr;
                return _rhs;
            }
        }
    };
};

template <typename T>
list<T>::list() : _size(0), _head(_List_node_manager::allocate(_a, 1)) {
    _head->_prev = _head;
    _head->_next = _head;
}

template <typename T>
list<T>::list(size_type n) : list() {
    while (n--) {
        auto node = _List_node_manager::allocate(_a, 1);
        _List_node_manager::construct(_a, node);

        insert(end(), node);
    }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items) : list() {
    for (auto it = items.begin(); it != items.end(); ++it) {
        push_back(*it);
    }
}

template <typename T>
list<T>::list(list const &l) : list() {
    for (auto it = l.begin(); it != l.end(); ++it) {
        push_back(*it);
    }
}

template <typename T>
list<T>::list(list &&l) : list() {
    swap(l);
}

template <typename T>
list<T>::~list() {
    clear();

    _List_node_manager::deallocate(_a, _head, 1);
}

template <typename T>
list<T> &list<T>::operator=(list &&l) {
    if (this != &l) {
        list(std::move(l)).swap(*this);
    }
    return *this;
}

template <typename T>
typename list<T>::reference list<T>::front() {
    return const_cast<list<T>::reference>(const_cast<list<T> const *>(this)->front());
}

template <typename T>
typename list<T>::const_reference list<T>::front() const {
    return _head->_next->_data;
}

template <typename T>
typename list<T>::reference list<T>::back() {
    return const_cast<list<T>::reference>(const_cast<list<T> const *>(this)->back());
}

template <typename T>
typename list<T>::const_reference list<T>::back() const {
    return _head->_prev->_data;
}

template <typename T>
typename list<T>::iterator list<T>::begin() noexcept {
    return _List_iterator(_head->_next);
}

template <typename T>
typename list<T>::const_iterator list<T>::begin() const noexcept {
    return _List_const_iterator(_head->_next);
}

template <typename T>
typename list<T>::iterator list<T>::end() noexcept {
    return _List_iterator(_head);
}

template <typename T>
typename list<T>::const_iterator list<T>::end() const noexcept {
    return _List_const_iterator(_head);
}

template <typename T>
bool list<T>::empty() const noexcept {
    return begin() == end();
}

template <typename T>
typename list<T>::size_type list<T>::size() const noexcept {
    return _size;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const noexcept {
    return _List_node_manager::max_size(_a);
}

template <typename T>
void list<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos, const_reference value) {
    auto node = _List_node_manager::allocate(_a, 1);
    _List_node_manager::construct(_a, node, value);

    insert(pos, node);

    return _List_iterator(node);
}

template <typename T>
void list<T>::insert(iterator _pos, _List_node *_node) noexcept {
    auto pos = _pos._node->_prev;

    _node->_prev = pos;
    _node->_next = pos->_next;

    pos->_next->_prev = _node;
    pos->_next = _node;

    ++_size;
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::emplace(const_iterator pos, Args &&...args) {
    ([&]() { insert(pos._const_cast(), args); }(), ...);
    return --pos._const_cast();
}

template <typename T>
void list<T>::erase(iterator pos) {
    if (!empty()) {
        _List_node_manager::destroy(_a, pos._node);
        _List_node_manager::deallocate(_a, pos._node, 1);

        --_size;
    }
}

template <typename T>
void list<T>::push_back(const_reference value) {
    insert(end(), value);
}

template <typename T>
template <typename... Args>
void list<T>::emplace_back(Args &&...args) {
    ([&]() { push_back(args); }(), ...);
}

template <typename T>
void list<T>::pop_back() {
    if (!empty()) {
        erase(--end());
    }
}

template <typename T>
void list<T>::push_front(const_reference value) {
    insert(begin(), value);
}

template <typename T>
template <typename... Args>
void list<T>::emplace_front(Args &&...args) {
    ([&]() { push_front(args); }(), ...);
}

template <typename T>
void list<T>::pop_front() {
    erase(begin());
}

template <typename T>
void list<T>::swap(list &other) {
    std::swap(_head, other._head);
    std::swap(_size, other._size);
}

template <typename T>
void list<T>::merge(list &other) {
    _List_node *b1 = _head->_next;
    _List_node *b2 = other._head->_next;
    while (b2 != other._head) {
        if (b1 == _head || b2->_data < b1->_data) {
            _List_node *tmp = b2->_next;

            b2->_prev->_next = b2->_next;
            b2->_next->_prev = b2->_prev;
            --other._size;

            insert(_List_iterator(b1), b2);

            b2 = tmp;
        } else {
            b1 = b1->_next;
        }
    }
}

template <typename T>
void list<T>::splice(const_iterator pos, list &other) {
    _List_iterator position = pos._const_cast();

    _List_node *prev = position._node->_prev;
    _List_node *curr = position._node;

    _List_node *head = other._head;

    prev->_next = head->_next;
    head->_next->_prev = prev;

    prev = head->_prev;
    head->_prev->_next = curr;

    _size += other._size;

    head->_prev = head;
    head->_next = head;
    other._size = 0;
}

template <typename T>
void list<T>::reverse() noexcept {
    _List_node *prev = _head->_prev;
    _List_node *curr = _head;
    _List_node *next = _head->_next;
    do {
        curr->_next = prev;
        curr->_prev = next;
        prev = curr;
        curr = next;
        next = next->_next;
    } while (curr != _head);
}

template <typename T>
void list<T>::unique() {
    _List_node *curr = _head->_next;
    while (curr->_next != _head) {
        if (curr->_data == curr->_next->_data) {
            erase(_List_iterator(curr->_next));
        } else {
            curr = curr->_next;
        }
    }
}

template <typename T>
void list<T>::sort() {
    if (!empty()) {
        _head->_next->_prev = nullptr;
        _head->_prev->_next = nullptr;

        _head->_next = _List_sort::_sort(_head->_next);

        _head->_next->_prev = _head;
        _List_node *node = _head->_next;
        while (node->_next != nullptr) {
            node = node->_next;
        }
        node->_next = _head;
        _head->_prev = node;
    }
}
}  // namespace s21

#endif  // SRC_S21_LIST_H_
