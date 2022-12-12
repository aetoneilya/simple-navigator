#ifndef SRC_S21_QUEUE_H_
#define SRC_S21_QUEUE_H_

#include <utility>

#include "s21_list.h"

namespace s21 {
template <class T>
struct queue {
    using value_type = T;
    using reference = value_type &;
    using const_reference = value_type const &;
    using size_type = std::size_t;

    queue();
    explicit queue(std::initializer_list<value_type> const &items);
    queue(queue const &s);
    queue(queue &&s);
    ~queue();

    queue &operator=(queue &&s);

    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    bool empty() const;
    size_type size() const;

    void push(const_reference value);
    void pop();
    void swap(queue &s);

    template <typename... Args>
    void emplace_back(Args &&...args);

 private:
    list<T> l;
};

template <typename T>
queue<T>::queue() : l() {
}

template <typename T>
queue<T>::queue(std::initializer_list<value_type> const &items) : l(items) {
}

template <typename T>
queue<T>::queue(queue const &s) : l(s.l) {
}

template <typename T>
queue<T>::queue(queue &&s) : l(std::move(s.l)) {
}

template <typename T>
queue<T>::~queue() {
}

template <typename T>
queue<T> &queue<T>::operator=(queue &&s) {
    if (this != &s) {
        queue(std::move(s)).swap(*this);
    }
    return *this;
}

template <typename T>
typename queue<T>::reference queue<T>::front() {
    return const_cast<queue<T>::reference>(const_cast<queue<T> const *>(this)->front());
}

template <typename T>
typename queue<T>::const_reference queue<T>::front() const {
    return l.front();
}

template <typename T>
typename queue<T>::reference queue<T>::back() {
    return const_cast<queue<T>::reference>(const_cast<queue<T> const *>(this)->back());
}

template <typename T>
typename queue<T>::const_reference queue<T>::back() const {
    return l.back();
}

template <typename T>
bool queue<T>::empty() const {
    return l.empty();
}

template <typename T>
typename queue<T>::size_type queue<T>::size() const {
    return l.size();
}

template <typename T>
void queue<T>::push(const_reference value) {
    l.push_back(value);
}

template <typename T>
void queue<T>::pop() {
    l.pop_front();
}

template <typename T>
void queue<T>::swap(queue &s) {
    l.swap(s.l);
}

template <typename T>
template <typename... Args>
void queue<T>::emplace_back(Args &&...args) {
    l.emplace_back(args...);
}
}  // namespace s21

#endif  // SRC_S21_QUEUE_H_
