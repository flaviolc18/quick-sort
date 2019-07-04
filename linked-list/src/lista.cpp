#include <string.h>

#include "lista.h"

template <class T>
Lista<T>::~Lista()
{
  while (this->head->next != this->tail)
  {
    Node<T> *it = this->head->next;
    this->head->next = this->head->next->next;
    free(it);
  }
}

template <class T>
Lista<T>::Lista()
{
  this->head = new Node<T>(T());
  this->tail = new Node<T>(T());

  this->head->next = this->tail;
  this->tail->previous = this->head;

  this->length = 0;
}

template <class T>
Node<T> *Lista<T>::get_head()
{
  return this->head;
};
template <class T>
Node<T> *Lista<T>::get_tail()
{
  return this->tail;
};

template <class T>
Node<T> *Lista<T>::get_node_at(int posicao)
{
  if (posicao < 0 || posicao >= this->length)
  {
    //FIXME: implementar exceção
    throw "não pode migão";
  }

  int distancia_head = posicao + 1;
  int distancia_tail = this->length - posicao;

  if (distancia_head <= distancia_tail)
  {
    Node<T> *node = this->head;
    for (int i = 0; i <= posicao; i++)
    {
      node = node->next;
    }
    return node;
  }
  else
  {
    Node<T> *node = this->tail;
    for (int i = this->length; i > posicao; i--)
    {
      node = node->previous;
    }
    return node;
  }
}

template <class T>
T Lista<T>::get_at(int posicao)
{
  return get_node_at(posicao)->value;
}

template <class T>
T Lista<T>::get_first()
{
  return get_node_at(0)->value;
}

template <class T>
T Lista<T>::get_last()
{
  return get_node_at(this->length - 1)->value;
}

template <class T>
void Lista<T>::insert_first(T value)
{
  Node<T> *new_node = new Node<T>(value);

  new_node->next = this->head->next;
  new_node->previous = this->head;

  this->head->next->previous = new_node;
  this->head->next = new_node;

  this->length++;
}

template <class T>
void Lista<T>::insert_last(T value)
{
  Node<T> *new_node = new Node<T>(value);

  new_node->next = this->tail;
  new_node->previous = this->tail->previous;

  this->tail->previous->next = new_node;
  this->tail->previous = new_node;

  this->length++;
}

template <class T>
void Lista<T>::insert_after(Node<T> *node, T value)
{
  Node<T> *new_node = new Node<T>(value);
  new_node->next = node->next;
  new_node->previous = node;

  node->next->previous = new_node;
  node->next = new_node;

  this->length++;
}

template <class T>
T Lista<T>::remove_at(int posicao)
{
  Node<T> *node = this->get_node_at(posicao);
  Node<T> *previous_node = node->previous;
  Node<T> *next_node = node->next;

  previous_node->next = next_node;
  next_node->previous = previous_node;

  T value = node->value;

  delete node;

  this->length--;

  return value;
}

template <class T>
T Lista<T>::remove_first()
{
  return remove_at(0);
}

template <class T>
T Lista<T>::remove_last()
{
  return remove_at(this->length - 1);
}

template <class T>
bool Lista<T>::is_empty()
{
  return this->length == 0;
}

template <class T>
int Lista<T>::get_length()
{
  return this->length;
}
