#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

#include <utility>

#include "s21_list.h"

namespace s21 {
template <class T>
struct stack {
    using value_type = T;
    using reference = value_type &;
    using const_reference = value_type const &;
    using size_type = std::size_t;

    stack();
    explicit stack(std::initializer_list<value_type> const &items);
    stack(stack const &s);
    stack(stack &&s);
    ~stack();

    stack &operator=(stack &&s);

    reference top();
    const_reference top() const;

    bool empty() const;
    size_type size() const;

    void push(const_reference value);
    void pop();
    void swap(stack &s);

    template <typename... Args>
    void emplace_front(Args &&...args);

 private:
    list<T> l;
};

template <typename T>
stack<T>::stack() : l() {
}

template <typename T>
stack<T>::stack(std::initializer_list<value_type> const &items) : l(items) {
}

template <typename T>
stack<T>::stack(stack const &s) : l(s.l) {
}

template <typename T>
stack<T>::stack(stack &&s) : l(std::move(s.l)) {
}

template <typename T>
stack<T>::~stack() {
}

template <typename T>
stack<T> &stack<T>::operator=(stack &&s) {
    if (this != &s) {
        stack(std::move(s)).swap(*this);
    }
    return *this;
}

template <typename T>
typename stack<T>::reference stack<T>::top() {
    return const_cast<stack<T>::reference>(const_cast<stack<T> const *>(this)->top());
}

template <typename T>
typename stack<T>::const_reference stack<T>::top() const {
    return l.back();
}

template <typename T>
bool stack<T>::empty() const {
    return l.empty();
}

template <typename T>
typename stack<T>::size_type stack<T>::size() const {
    return l.size();
}

template <typename T>
void stack<T>::push(const_reference value) {
    l.push_back(value);
}

template <typename T>
void stack<T>::pop() {
    l.pop_back();
}

template <typename T>
void stack<T>::swap(stack &s) {
    l.swap(s.l);
}

template <typename T>
template <typename... Args>
void stack<T>::emplace_front(Args &&...args) {
    l.emplace_front(args...);
}
}  // namespace s21

#endif  // SRC_S21_STACK_H_
