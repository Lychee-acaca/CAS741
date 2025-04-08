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

class DoublyLL_Node {
 public:
  DoublyLL_Node(float data, DoublyLL_Node *pre = nullptr,
                DoublyLL_Node *next = nullptr)
      : data(data), pre(pre), next(next) {}
  ~DoublyLL_Node(void) {}
  void setPre(DoublyLL_Node *node) { pre = node; }
  void setNext(DoublyLL_Node *node) { next = node; }
  void setData(float data) { this->data = data; }
  DoublyLL_Node *getPre(void) { return pre; }
  DoublyLL_Node *getNext(void) { return next; }
  float getData(void) { return data; }

 private:
  friend class DoublyLL;
  float data;
  DoublyLL_Node *pre, *next;
};

class DoublyLL {
 public:
  DoublyLL(void) : len(0) {
    tail = head = new DoublyLL_Node(0, nullptr, nullptr);
  }
  ~DoublyLL(void) {
    while (head != tail) {
      pop_back();
    }
    delete head;
  }
  DoublyLL(const DoublyLL &d) : len(0) {
    tail = head = new DoublyLL_Node(0, nullptr, nullptr);
    DoublyLL_Node *d_ptr = d.head->getNext();
    while (d_ptr != nullptr) {
      this->push_back(d_ptr->getData());
      d_ptr = d_ptr->getNext();
    }
  }
  DoublyLL_Node *getIndex(int);

  int getLen(void) { return len; }
  void remove(int);
  void insert(int, float);
  float pop_head(void);
  float pop_back(void);
  void push_head(float);
  void push_back(float);

  class Iterator {
   private:
    DoublyLL_Node *current;

   public:
    using value_type = float;
    using difference_type = std::ptrdiff_t;
    using pointer = float *;
    using reference = float &;
    using iterator_category = std::bidirectional_iterator_tag;

    explicit Iterator(DoublyLL_Node *node) : current(node) {}

    float &operator*() { return current->data; }

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
  DoublyLL_Node *head, *tail;
  int len;
};
