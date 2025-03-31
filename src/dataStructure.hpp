/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#pragma once

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
      tail = tail->getPre();
      remove(0);
    }
    delete head;
  }
  DoublyLL_Node *getIndex(int);
  void remove(int);
  void insert(int, float);
  float pop_head(void);
  void push_back(float);

 private:
  DoublyLL_Node *head, *tail;
  int len;
};
