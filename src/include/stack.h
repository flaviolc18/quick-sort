#ifndef STACK_H
#define STACK_H

#include "node.h"

template <class T>
class Stack
{
private:
  Node<T> *head;
  Node<T> *tail;
  int length;

public:
  Stack();
  ~Stack();

  void push(T value);
  T pop();
  bool is_empty();
};

#endif
