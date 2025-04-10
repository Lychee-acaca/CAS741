/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#pragma once

#include <cstddef>
#include <iterator>

template <typename T>
class DoublyLL;

template <typename T>
class DoublyLL_Node {
 public:
  DoublyLL_Node(T data, DoublyLL_Node<T> *pre = nullptr,
                DoublyLL_Node<T> *next = nullptr)
      : data(data), pre(pre), next(next) {}
  ~DoublyLL_Node(void) {}
  void setPre(DoublyLL_Node<T> *node) { pre = node; }
  void setNext(DoublyLL_Node<T> *node) { next = node; }
  void setData(T data) { this->data = data; }
  DoublyLL_Node<T> *getPre(void) { return pre; }
  DoublyLL_Node<T> *getNext(void) { return next; }
  T getData(void) { return data; }

 private:
  friend class DoublyLL<T>;
  T data;
  DoublyLL_Node<T> *pre, *next;
};

template <typename T>
class DoublyLL {
 public:
  DoublyLL(void) : len(0) {
    tail = head = new DoublyLL_Node<T>(T(), nullptr, nullptr);
  }
  ~DoublyLL(void) {
    while (head != tail) {
      pop_back();
    }
    delete head;
  }
  DoublyLL(const DoublyLL &d) : len(0) {
    tail = head = new DoublyLL_Node<T>(T(), nullptr, nullptr);
    DoublyLL_Node<T> *d_ptr = d.head->getNext();
    while (d_ptr != nullptr) {
      this->push_back(d_ptr->getData());
      d_ptr = d_ptr->getNext();
    }
  }
  DoublyLL_Node<T> *getIndex(int index) {
    if (index == -1) {
      return head;
    }

    if (index <= len / 2) {
      DoublyLL_Node<T> *now = head->getNext();
      for (int i = 0; i < index; ++i) {
        if (now == nullptr) {
          return nullptr;
        }
        now = now->getNext();
      }
      return now;
    } else {
      DoublyLL_Node<T> *now = tail;
      for (int i = 0; i < len - index - 1; ++i) {
        if (now == head) {
          return nullptr;
        }
        now = now->getPre();
      }
      return now;
    }
  }

  int getLen(void) { return len; }
  void remove(int index) {
    DoublyLL_Node<T> *target = getIndex(index);
    if (target == nullptr) {
      return;
    }
    if (index == len - 1) {
      tail = tail->getPre();
    }
    target->getPre()->setNext(target->getNext());
    if (target->getNext() != nullptr) {
      target->getNext()->setPre(target->getPre());
    }
    delete target;
    --len;
  }

  void insert(int index, T data) {
    DoublyLL_Node<T> *pre = getIndex(index - 1);
    DoublyLL_Node<T> *newNode = new DoublyLL_Node<T>(data, pre, pre->getNext());
    if (pre->getNext() != nullptr) {
      pre->getNext()->setPre(newNode);
    }
    pre->setNext(newNode);
    if (index == len) {
      tail = tail->getNext();
    }
    ++len;
  }

  T pop_head(void) {
    T res = getIndex(0)->getData();
    remove(0);
    return res;
  }

  T pop_back(void) {
    T res = getIndex(len - 1)->getData();
    remove(len - 1);
    return res;
  }

  void push_head(T data) { insert(0, data); }
  void push_back(T data) { insert(len, data); }

  class Iterator {
   private:
    DoublyLL_Node<T> *current;

   public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;
    using iterator_category = std::bidirectional_iterator_tag;

    explicit Iterator(DoublyLL_Node<T> *node) : current(node) {}

    T &operator*() { return current->data; }

    Iterator &operator++() {
      if (current) current = current->getNext();
      return *this;
    }

    Iterator operator++(int) {
      Iterator temp = *this;
      ++(*this);
      return temp;
    }

    Iterator &operator--() {
      if (current) current = current->getPre();
      return *this;
    }

    Iterator operator--(int) {
      Iterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const Iterator &other) const {
      return current == other.current;
    }
    bool operator!=(const Iterator &other) const {
      return current != other.current;
    }
  };

  Iterator begin() { return Iterator(head->getNext()); }
  Iterator end() { return Iterator(nullptr); }

 private:
  DoublyLL_Node<T> *head, *tail;
  int len;
};
