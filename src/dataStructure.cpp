/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include "src/dataStructure.hpp"

DoublyLL_Node *DoublyLL::getIndex(int index) {
  if (index == -1) {
    return head;
  }

  if (index <= len / 2) {
    DoublyLL_Node *now = head->getNext();
    for (int i = 0; i < index; ++i) {
      if (now == nullptr) {
        return nullptr;
      }
      now = now->getNext();
    }
    return now;
  } else {
    DoublyLL_Node *now = tail;
    for (int i = 0; i < len - index - 1; ++i) {
      if (now == head) {
        return nullptr;
      }
      now = now->getPre();
    }
    return now;
  }
}

void DoublyLL::remove(int index) {
  DoublyLL_Node *target = getIndex(index);
  if (target == nullptr) {
    return;
  }
  target->getPre()->setNext(target->getNext());
  if (target->getNext() != nullptr) {
    target->getNext()->setPre(target->getPre());
  }
  delete target;
  --len;
}

void DoublyLL::insert(int index, float data) {
  DoublyLL_Node *pre = getIndex(index - 1);
  DoublyLL_Node *newNode = new DoublyLL_Node(data, pre, pre->getNext());
  if (pre->getNext() != nullptr) {
    pre->getNext()->setPre(newNode);
  }
  pre->setNext(newNode);
  ++len;
}

float DoublyLL::pop_head(void) {
  float res = getIndex(0)->getData();
  remove(0);
  return res;
}

void DoublyLL::push_back(float data) {
  insert(len, data);
  tail = tail->getNext();
}
