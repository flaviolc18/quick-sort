#ifndef LISTA_H
#define LISTA_H

#include "node.h"

template <class T>
class Lista
{
private:
  Node<T> *head;
  Node<T> *tail;
  int length;

  Node<T> *get_node_at(int posicao);

public:
  Lista();
  ~Lista();

  void insert_sorted(T value);
  T get_at(int posicao);
  T remove_at(int posicao);

  int get_length();
  bool is_empty();
};

#endif
