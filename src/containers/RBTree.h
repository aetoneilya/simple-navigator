#ifndef SRC_RBTREE_H_
#define SRC_RBTREE_H_

#include <functional>
#include <utility>

#define RBNodeLeftChild -1
#define RBNodeNotAChild 0
#define RBNodeRightChild 1

#define RBNodeBlack 0
#define RBNodeRed 1

using std::pair;

#define CMP(x, y) (x < y)

namespace s21 {
template <class T, typename _Cmp = std::less<T>>
class RBTree {
 private:
    struct _Node;
    struct _RBTree_iterator;
    struct _RBTree_const_iterator;

 public:
    using key_type = T;
    using value_type = T;
    using reference = value_type &;
    using const_reference = value_type const &;
    using iterator = _RBTree_iterator;
    using const_iterator = _RBTree_const_iterator;
    using size_type = std::size_t;

    bool compare(T a, T b, _Cmp cmp = _Cmp{}) { return cmp(a, b); }

    RBTree();
    explicit RBTree(std::initializer_list<value_type> const &items);
    RBTree(const RBTree &m);
    RBTree(RBTree &&m);
    ~RBTree();
    RBTree &operator=(RBTree &&m);

    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;

    void clear();
    std::pair<iterator, bool> insert(const value_type &value);
    void erase(iterator pos);
    void swap(RBTree<T, _Cmp> &other);
    void merge(RBTree<T, _Cmp> &other);

    iterator find(const key_type &key);
    bool contains(const key_type &key);
    size_type count(const key_type &key);
    std::pair<iterator, iterator> equal_range(const key_type &key);
    iterator lower_bound(const key_type &key);
    iterator upper_bound(const key_type &key);
    template <typename... Args>
    std::pair<iterator, bool> emplace(Args &&...args);

 private:
    size_type _size;
    _Node *_head;
    _Node *_end;

    std::allocator<_Node> _a;
    using _node_manager = std::allocator_traits<std::allocator<_Node>>;

    struct _Node {
        value_type data;
        _Node *parent;
        _Node *left;
        _Node *right;
        bool color;

        _Node()
            : parent(nullptr), left(nullptr), right(nullptr), color(RBNodeBlack) {}
        explicit _Node(const_reference _data)
            : data(_data),
              parent(nullptr),
              left(nullptr),
              right(nullptr),
              color(RBNodeBlack) {}
        explicit _Node(_Node *_parent)
            : parent(_parent), left(nullptr), right(nullptr), color(RBNodeBlack) {}
        _Node(const_reference _data, _Node *_parent)
            : data(_data),
              parent(_parent),
              left(nullptr),
              right(nullptr),
              color(RBNodeBlack) {}
        bool is_end() const { return (left != nullptr && left == right); }
        bool is_left_child() const {
            return (parent != nullptr && parent->left == this);
        }
        bool is_right_child() const {
            return (parent != nullptr && parent->right == this);
        }
        bool has_child() const { return (left != nullptr || right != nullptr); }
        bool has_both_children() const {
            return (left != nullptr && right != nullptr);
        }
        _Node *some_child() const { return ((left == nullptr) ? right : left); }
        bool is_red() { return color == RBNodeRed; }
        bool is_black() { return color == RBNodeBlack; }
        bool has_red_child() {
            return ((left != nullptr && left->is_red()) ||
                    (right != nullptr && right->is_red()));
        }
        void make_red() { color = RBNodeRed; }
        void make_black() { color = RBNodeBlack; }
        void destroy_all_children() {
            if (left != nullptr) {
                left->destroy_all_children();
            }
            if (right != nullptr) {
                right->destroy_all_children();
            }
            delete left;
            delete right;
        }
        void swap_with(_Node *other) {
            _Node *other_parent = other->parent;
            _Node *other_left = other->left;
            _Node *other_right = other->right;
            if (parent != nullptr) {
                if (is_left_child()) {
                    parent->left = other;
                } else {
                    parent->right = other;
                }
            }
            if (left != nullptr) {
                left->parent = other;
            }
            if (right != nullptr) {
                right->parent = other;
            }
            if (other_parent != nullptr) {
                if (other_parent->left == other) {
                    other_parent->left = this;
                } else {
                    other_parent->right = this;
                }
            }
            if (other_left != nullptr) {
                other_left->parent = this;
            }
            if (other_right != nullptr) {
                other_right->parent = this;
            }
            std::swap(parent, other->parent);
            std::swap(left, other->left);
            std::swap(right, other->right);
            std::swap(color, other->color);
        }
        _Node *find_sibling() {
            _Node *sibling = nullptr;
            if (is_left_child()) {
                sibling = parent->right;
            } else if (is_right_child()) {
                sibling = parent->left;
            }
            return sibling;
        }
    };

    int find_parent_for_new_node(_Node *new_node, _Node *parent);
    void rebalance_after_insertion(_Node *new_node);
    void rebalance_before_deletion(_Node *node);
    void rotate_left(_Node *node);
    void rotate_right(_Node *node);

    struct _RBTree_iterator {
        using _self = _RBTree_iterator;

        _Node *node;

        explicit _RBTree_iterator(_Node *_node) noexcept : node(_node) {}

        operator _RBTree_const_iterator() const {
            return _RBTree_const_iterator(node);
        }

        reference operator*() const noexcept { return node->data; }

        _self &operator++() noexcept {
            if (node->is_end() == false) {
                if (node->right != nullptr) {
                    node = node->right;
                    while (node->left != nullptr) {
                        node = node->left;
                    }
                } else {
                    while (node->is_right_child()) {
                        node = node->parent;
                    }
                    if (node->is_end() == false) {
                        node = node->parent;
                    }
                }
            }
            return *this;
        }

        _self operator++(int) noexcept {
            auto it = *this;
            ++(*this);
            return it;
        }

        _self &operator--() noexcept {
            if (node->is_end() == false) {
                if (node->left != nullptr) {
                    node = node->left;
                    while (node->right != nullptr) {
                        node = node->right;
                    }
                } else {
                    while (node->is_left_child()) {
                        node = node->parent;
                    }
                    node = node->parent;
                }
            } else {
                while (node->right != nullptr) {
                    node = node->right;
                }
            }
            return *this;
        }

        _self operator--(int) noexcept {
            auto it = *this;
            --(*this);
            return it;
        }

        bool operator==(_self const &other) const noexcept {
            return node == other.node;
        }

        bool operator!=(_self const &other) const noexcept {
            return node != other.node;
        }
    };

    struct _RBTree_const_iterator {
        using _self = _RBTree_const_iterator;

        _Node const *node;

        explicit _RBTree_const_iterator(_Node const *_node) noexcept
            : node(_node) {}

        const_reference operator*() const noexcept { return node->data; }

        _self &operator++() noexcept {
            if (node->is_end() == false) {
                if (node->right != nullptr) {
                    node = node->right;
                    while (node->left != nullptr) {
                        node = node->left;
                    }
                } else {
                    while (node->is_right_child()) {
                        node = node->parent;
                    }
                    if (node->is_end() == false) {
                        node = node->parent;
                    }
                }
            }
            return *this;
        }

        _self operator++(int) noexcept {
            auto it = *this;
            ++(*this);
            return it;
        }

        _self &operator--() noexcept {
            if (node->is_end() == false) {
                if (node->left != nullptr) {
                    node = node->left;
                    while (node->right != nullptr) {
                        node = node->right;
                    }
                } else {
                    while (node->is_left_child()) {
                        node = node->parent;
                    }
                    node = node->parent;
                }
            } else {
                while (node->right != nullptr) {
                    node = node->right;
                }
            }
            return *this;
        }

        _self operator--(int) noexcept {
            auto it = *this;
            --(*this);
            return it;
        }

        bool operator==(_self const &other) const noexcept {
            return node == other.node;
        }

        bool operator!=(_self const &other) const noexcept {
            return node != other.node;
        }
    };
};

template <class T, typename _Cmp>
RBTree<T, _Cmp>::RBTree() : _size(0), _head(nullptr), _end(new _Node()) {}

template <class T, typename _Cmp>
RBTree<T, _Cmp>::RBTree(std::initializer_list<value_type> const &items)
    : RBTree() {
    for (auto it = items.begin(); it != items.end(); ++it) {
        insert(*it);
    }
}

template <class T, typename _Cmp>
RBTree<T, _Cmp>::RBTree(const RBTree &m) : RBTree() {
    for (auto it = m.begin(); it != m.end(); ++it) {
        insert(*it);
    }
}

template <class T, typename _Cmp>
RBTree<T, _Cmp>::RBTree(RBTree &&m)
    : _size(m._size), _head(m._head), _end(m._end) {
    m._head = nullptr;
    m._end = nullptr;
    m._size = 0;
}

template <class T, typename _Cmp>
RBTree<T, _Cmp>::~RBTree() {
    clear();

    delete _end;
}

template <class T, typename _Cmp>
RBTree<T, _Cmp> &RBTree<T, _Cmp>::operator=(RBTree &&m) {
    if (this != &m) {
        _head = m._head;
        _size = m._size;
        _end = m._end;
        m._head = nullptr;
        m._end = nullptr;
        m._size = 0;
    }
    return *this;
}

template <class T, typename _Cmp>
typename RBTree<T, _Cmp>::iterator RBTree<T, _Cmp>::begin() noexcept {
    _Node *first = _head;
    if (first == nullptr) {
        first = _end;
    } else {
        while (first->left != nullptr) {
            first = first->left;
        }
    }
    return _RBTree_iterator(first);
}

template <class T, typename _Cmp>
typename RBTree<T, _Cmp>::const_iterator RBTree<T, _Cmp>::begin()
    const noexcept {
    _Node *first = _head;
    if (first == nullptr) {
        first = _end;
    } else {
        while (first->left != nullptr) {
            first = first->left;
        }
    }
    return _RBTree_const_iterator(first);
}

template <class T, typename _Cmp>
typename RBTree<T, _Cmp>::iterator RBTree<T, _Cmp>::end() noexcept {
    return _RBTree_iterator(_end);
}

template <class T, typename _Cmp>
typename RBTree<T, _Cmp>::const_iterator RBTree<T, _Cmp>::end() const noexcept {
    return _RBTree_const_iterator(_end);
}

template <class T, typename _Cmp>
bool RBTree<T, _Cmp>::empty() const noexcept {
    return (_head == nullptr);
}

template <class T, typename _Cmp>
typename RBTree<T, _Cmp>::size_type RBTree<T, _Cmp>::size() const noexcept {
    return _size;
}

template <class T, typename _Cmp>
typename RBTree<T, _Cmp>::size_type RBTree<T, _Cmp>::max_size() const noexcept {
    return _node_manager::max_size(_a);
}

template <class T, typename _Cmp>
void RBTree<T, _Cmp>::clear() {
    if (_head != nullptr) {
        _head->destroy_all_children();
        delete _head;
        _head = nullptr;
        _size = 0;
    }
    if (_end != nullptr) {
        _end->left = _end->right = nullptr;
    }
}

template <class T, typename _Cmp>
std::pair<typename RBTree<T, _Cmp>::iterator, bool> RBTree<T, _Cmp>::insert(
    const RBTree<T, _Cmp>::value_type &value) {
    /*  insetrion algorithm described here:
     * https://www.youtube.com/watch?v=UaLIHuR1t8Q  */
    bool result = true;
    _Node *new_node = new _Node(value);
    new_node->make_red();
    if (_head == nullptr) {
        _head = new_node;
        _end->left = _end->right = _head;
        _head->parent = _end;
    } else {
        _Node *cur_node = _head;
        int node_status = find_parent_for_new_node(new_node, cur_node);
        if (node_status == RBNodeNotAChild) {
            result = false;
            delete new_node;
            new_node = cur_node;
        }
    }
    if (result == true) {
        rebalance_after_insertion(new_node);
        while (_head->parent != _end) {
            _head = _head->parent;
        }
        _end->left = _end->right = _head;
    }
    _size += result;
    RBTree<T, _Cmp>::iterator iter(new_node);
    return std::make_pair(iter, result);
}

template <class T, typename _Cmp>
int RBTree<T, _Cmp>::find_parent_for_new_node(_Node *new_node, _Node *parent) {
    int node_status = RBNodeNotAChild;
    while (node_status == RBNodeNotAChild) {
        if (compare(parent->data, new_node->data) == true) {
            if (parent->right == nullptr) {
                node_status = RBNodeRightChild;
                parent->right = new_node;
                new_node->parent = parent;
            } else {
                parent = parent->right;
            }
        } else if (compare(new_node->data, parent->data) == true) {
            if (parent->left == nullptr) {
                node_status = RBNodeLeftChild;
                parent->left = new_node;
                new_node->parent = parent;
            } else {
                parent = parent->left;
            }
        } else {
            break;
        }
    }
    return node_status;
}

template <class T, typename _Cmp>
void RBTree<T, _Cmp>::rebalance_after_insertion(_Node *new_node) {
    if (new_node->parent == _end) {
        new_node->make_black();
    } else if (new_node->parent->is_red()) {
        _Node *grand_parent = new_node->parent->parent;
        _Node *uncle = nullptr;
        if (new_node->parent->is_left_child()) {
            uncle = grand_parent->right;
        } else {
            uncle = grand_parent->left;
        }

        if (uncle != nullptr && uncle->is_red()) {
            uncle->make_black();
            new_node->parent->make_black();
            if (grand_parent->parent != nullptr) {
                grand_parent->make_red();
                rebalance_after_insertion(grand_parent);
            }
        } else {
            if (new_node->is_left_child() && new_node->parent->is_right_child()) {
                rotate_right(new_node->parent);
                new_node = new_node->right;
                grand_parent = new_node->parent->parent;
            } else if (new_node->is_right_child() &&
                       new_node->parent->is_left_child()) {
                rotate_left(new_node->parent);
                new_node = new_node->left;
                grand_parent = new_node->parent->parent;
            }
            if (new_node->is_right_child()) {
                rotate_left(grand_parent);
                grand_parent->make_red();
                grand_parent->parent->make_black();
            } else {
                rotate_right(grand_parent);
                grand_parent->make_red();
                grand_parent->parent->make_black();
            }
        }
    }
}

template <class T, typename _Cmp>
void RBTree<T, _Cmp>::rotate_right(_Node *node) {
    _Node *left_child = node->left;
    if (left_child != nullptr) {
        node->left = left_child->right;
        if (left_child->right != nullptr) {
            left_child->right->parent = node;
        }
        left_child->right = node;
        left_child->parent = node->parent;
        if (node->is_left_child()) {
            left_child->parent->left = left_child;
        } else if (node->is_right_child()) {
            left_child->parent->right = left_child;
        }
        node->parent = left_child;
    }
}

template <class T, typename _Cmp>
void RBTree<T, _Cmp>::rotate_left(_Node *node) {
    _Node *right_child = node->right;
    if (right_child != nullptr) {
        node->right = right_child->left;
        if (right_child->left != nullptr) {
            right_child->left->parent = node;
        }
        right_child->left = node;
        right_child->parent = node->parent;

        if (node->is_left_child()) {
            right_child->parent->left = right_child;
        } else if (node->is_right_child()) {
            right_child->parent->right = right_child;
        }
        node->parent = right_child;
    }
}

template <class T, typename _Cmp>
void RBTree<T, _Cmp>::erase(iterator pos) {
    /*  deletion algorithm described here:
     * https://youtu.be/CTvfzU_uNKE  */
    if (pos.node->has_both_children()) {
        _Node *min_on_the_right = pos.node->right;
        while (min_on_the_right->left != nullptr) {
            min_on_the_right = min_on_the_right->left;
        }
        pos.node->swap_with(min_on_the_right);
        while (_head->parent != _end) {
            _head = _head->parent;
        }
        _end->left = _end->right = _head;
    }
    if (pos.node->has_child()) {
        _Node *child = pos.node->some_child();
        pos.node->swap_with(child);
        child->left = child->right = nullptr;
        while (_head->parent != _end) {
            _head = _head->parent;
        }
        _end->left = _end->right = _head;
    } else {
        if (pos.node->is_black()) {
            rebalance_before_deletion(pos.node);
        }
        _Node *parent = pos.node->parent;
        if (pos.node->is_left_child()) {
            parent->left = nullptr;
        } else if (pos.node->is_right_child()) {
            parent->right = nullptr;
        }
    }
    delete pos.node;
    _size--;
}

template <class T, typename _Cmp>
void RBTree<T, _Cmp>::rebalance_before_deletion(_Node *node) {
    if (node->parent == _end) {
        _head = nullptr;
        _end->left = _end->right = _head;
    } else {
        _Node *parent_ = node->parent;
        _Node *sibling = node->find_sibling();
        if (sibling != nullptr && sibling->is_red()) {
            if (node->is_left_child()) {
                rotate_left(parent_);
            } else {
                rotate_right(parent_);
            }
            if (sibling->parent == _end) {
                _head = sibling;
                _end->left = _end->right = _head;
            }
            parent_->make_red();
            sibling->make_black();
        }
        sibling = node->find_sibling();
        if (parent_->is_black() && sibling != nullptr && sibling->is_black() &&
            sibling->has_red_child() == false) {
            sibling->make_red();
            rebalance_before_deletion(parent_);
        } else if (parent_->is_red() && sibling != nullptr && sibling->is_black() &&
                   sibling->has_red_child() == false) {
            parent_->make_black();
            sibling->make_red();
        } else {
            if (node->is_left_child() && sibling->right != nullptr &&
                sibling->right->is_black() && sibling->left != nullptr &&
                sibling->left->is_red()) {
                rotate_right(sibling);
                sibling->parent->make_black();
                sibling->make_red();
            } else if (node->is_right_child() && sibling->right != nullptr &&
                       sibling->right->is_red() && sibling->left != nullptr &&
                       sibling->left->is_black()) {
                rotate_left(sibling);
                sibling->parent->make_black();
                sibling->make_red();
            }
            sibling = node->find_sibling();
            if (node->is_left_child()) {
                rotate_left(parent_);
            } else {
                rotate_right(parent_);
            }
            sibling->color = parent_->color;
            parent_->make_black();
            if (sibling->parent == _end) {
                _head = sibling;
                _end->left = _end->right = _head;
            }
        }
    }
}

template <class T, typename _Cmp>
void RBTree<T, _Cmp>::swap(RBTree<T, _Cmp> &other) {
    _Node *tmp = _head;
    _head = other._head;
    other._head = tmp;
    tmp = _end;
    _end = other._end;
    other._end = tmp;
}

template <class T, typename _Cmp>
void RBTree<T, _Cmp>::merge(RBTree<T, _Cmp> &other) {
    for (auto it = other.begin(); it != other.end(); it++) {
        insert(*it);
    }
}

template <class T, typename _Cmp>
typename RBTree<T, _Cmp>::iterator RBTree<T, _Cmp>::find(const key_type &key) {
    _Node *res = _head;
    while (res != nullptr) {
        if (compare(res->data, key) == compare(key, res->data)) {
            break;
        } else if (compare(res->data, key)) {
            res = res->right;
        } else if (compare(key, res->data)) {
            res = res->left;
        }
    }
    if (res == nullptr) {
        res = _end;
    }
    return iterator(res);
}

template <class T, typename _Cmp>
bool RBTree<T, _Cmp>::contains(const key_type &key) {
    return find(key) != end();
}

template <class T, typename _Cmp>
typename RBTree<T, _Cmp>::size_type RBTree<T, _Cmp>::count(
    const key_type &key) {
    size_type res = 0;
    for (auto it = begin(); it != end(); it++) {
        if (compare(*it, key) == compare(key, *it)) {
            res++;
        }
    }
    return res;
}

template <class T, typename _Cmp>
std::pair<typename RBTree<T, _Cmp>::iterator,
          typename RBTree<T, _Cmp>::iterator>
RBTree<T, _Cmp>::equal_range(const key_type &key) {
    iterator start = end();
    iterator finish = end();
    for (auto it = begin(); it != end(); it++) {
        if (compare(*it, key) == compare(key, *it)) {
            if (start == end()) {
                start = it;
            }
            finish = it;
        } else if (start != end()) {
            break;
        }
    }
    return std::make_pair(start, finish);
}

template <class T, typename _Cmp>
typename RBTree<T, _Cmp>::iterator RBTree<T, _Cmp>::lower_bound(
    const key_type &key) {
    iterator res = begin();
    for (auto it = begin(); it != end(); it++) {
        if (compare(key, *it) == true || compare(*it, key) == false) {
            res = it;
            break;
        }
    }
    return res;
}

template <class T, typename _Cmp>
typename RBTree<T, _Cmp>::iterator RBTree<T, _Cmp>::upper_bound(
    const key_type &key) {
    iterator res = begin();
    for (auto it = begin(); it != end(); it++) {
        if (compare(*it, key) == false && compare(key, *it) == true) {
            res = it;
            break;
        }
    }
    return res;
}

template <class T, typename _Cmp>
template <typename... Args>
std::pair<typename RBTree<T, _Cmp>::iterator, bool> RBTree<T, _Cmp>::emplace(
    Args &&...args) {
    std::pair<iterator, bool> res(begin(), false);
    const int sum_argc = sizeof...(Args);
    value_type buffer[sum_argc] = {args...};
    for (int i = 0; i < sum_argc; i++) {
        res = insert(buffer[i]);
    }
    return res;
}

}  // namespace s21

#endif  // SRC_RBTREE_H_
