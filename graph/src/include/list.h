#ifndef LIST_H
#define LIST_H

#include <functional>

template <class T>
struct Node
{
  T value;
  Node *next;
  Node *previous;

  Node(T value)
  {
    this->value = value;
    this->next = nullptr;
    this->previous = nullptr;
  };
};

template <class T>
class List
{
private:
  int _length;
  Node<T> *head;
  Node<T> *tail;

protected:
  Node<T> *get_head();
  Node<T> *get_node_at(int position);
  Node<T> *get_tail();

public:
  List();
  ~List();

  int length();
  bool empty();
  bool has(const T &value);
  int pos(const T &value);
  void each(std::function<void(T &)> fn);
  void each_rev(std::function<void(T &)> fn);

  void push_first(T value);
  void push_last(T value);

  T at(int position);
  T first();
  T last();

  T pop_at(int position);
  T pop_first();
  T pop_last();
};

#endif
