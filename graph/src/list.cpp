#include "list.h"

template <class T>
List<T>::List()
{
  this->head = new ListNode<T>(T());
  this->tail = new ListNode<T>(T());

  this->head->next = this->tail;
  this->tail->previous = this->head;

  this->_length = 0;
}

template <class T>
List<T>::~List()
{
  while (this->head->next != this->tail)
  {
    ListNode<T> *it = this->head->next;
    this->head->next = this->head->next->next;
    delete it;
  }
  delete this->head;
  delete this->tail;
}

template <class T>
ListNode<T> *List<T>::get_head()
{
  return this->head;
};
template <class T>
ListNode<T> *List<T>::get_tail()
{
  return this->tail;
};

template <class T>
ListNode<T> *List<T>::get_node_at(int position)
{
  if (position < 0 || position >= this->_length)
  {
    //FIXME: implementar exceção
    throw std::invalid_argument("não pode migão");
    ;
  }

  int distancia_head = position + 1;
  int distancia_tail = this->_length - position;

  if (distancia_head <= distancia_tail)
  {
    ListNode<T> *node = this->head;
    for (int i = 0; i <= position; i++)
    {
      node = node->next;
    }
    return node;
  }
  else
  {
    ListNode<T> *node = this->tail;
    for (int i = this->_length; i > position; i--)
    {
      node = node->previous;
    }
    return node;
  }
}

template <class T>
T List<T>::at(int position)
{
  return get_node_at(position)->value;
}

template <class T>
T List<T>::first()
{
  return get_node_at(0)->value;
}

template <class T>
T List<T>::last()
{
  return get_node_at(this->_length - 1)->value;
}

template <class T>
void List<T>::push_first(T value)
{
  ListNode<T> *new_node = new ListNode<T>(value);

  new_node->next = this->head->next;
  new_node->previous = this->head;

  this->head->next->previous = new_node;
  this->head->next = new_node;

  this->_length++;
}

template <class T>
void List<T>::push_last(T value)
{
  ListNode<T> *new_node = new ListNode<T>(value);

  new_node->next = this->tail;
  new_node->previous = this->tail->previous;

  this->tail->previous->next = new_node;
  this->tail->previous = new_node;

  this->_length++;
}

template <class T>
T List<T>::pop_at(int position)
{
  ListNode<T> *node = this->get_node_at(position);

  ListNode<T> *previous_node = node->previous;
  ListNode<T> *next_node = node->next;

  previous_node->next = next_node;
  next_node->previous = previous_node;

  T value = node->value;

  delete node;

  this->_length--;

  return value;
}

template <class T>
T List<T>::pop_first()
{
  return pop_at(0);
}

template <class T>
T List<T>::pop_last()
{
  return pop_at(this->_length - 1);
}

template <class T>
bool List<T>::empty()
{
  return this->_length == 0;
}

template <class T>
int List<T>::length()
{
  return this->_length;
}

template <class T>
int List<T>::pos(const T &value)
{
  int count = 0;
  ListNode<T> *node = this->head->next;
  while (node != this->tail && node->value != value)
  {
    node = node->next;
    count++;
  }
  return node == this->tail ? -1 : count;
}

template <class T>
bool List<T>::has(const T &value)
{

  return this->pos(value) != -1;
}

template <class T>
void List<T>::each(std::function<void(T &)> fn)
{

  ListNode<T> *node = this->head->next;
  while (node != this->tail)
  {
    fn(node->value);
    node = node->next;
  }
}

template <class T>
void List<T>::each_rev(std::function<void(T &)> fn)
{

  ListNode<T> *node = this->tail->previous;
  while (node != this->head)
  {
    fn(node->value);
    node = node->previous;
  }
}
