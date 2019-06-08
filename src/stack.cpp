#include <memory>
#include "stack.h"

template <class T>
Stack<T>::Stack()
{
  this->head = new Node<T>();
  this->tail = new Node<T>();

  this->head->next = this->tail;
  this->tail->previous = this->head;

  this->length = 0;
}

template <class T>
Stack<T>::~Stack()
{
  while (this->head->next != this->tail)
  {
    Node<T> *it = this->head->next;
    this->head->next = this->head->next->next;
    free(it);
  }
}

template <class T>
void Stack<T>::push(T value)
{
  Node<T> *new_node = new Node<T>();
  new_node->value = value;

  new_node->next = this->tail;
  new_node->previous = this->tail->previous;

  this->tail->previous->next = new_node;
  this->tail->previous = new_node;

  this->length++;
}

template <class T>
T Stack<T>::pop()
{
  Node<T> *node = this->tail->previous;
  Node<T> *previous_node = node->previous;

  previous_node->next = this->tail;
  this->tail->previous = previous_node;

  T value = node->value;

  delete node;

  this->length--;

  return value;
}

template <class T>
bool Stack<T>::is_empty()
{
  return this->length == 0;
}
