#ifndef LISTA_H
#define LISTA_H

template <typename T>
class Node
{
public:
  T value;
  Node *next;
  Node *previous;

  Node(T value)
  {
    this->value = value;
    this->next = NULL;
    this->previous = NULL;
  };
};

template <class T>
class Lista
{
private:
  Node<T> *head;
  Node<T> *tail;
  int length;
  Node<T> *get_node_at(int posicao);

protected:
  Node<T> *get_head();
  Node<T> *get_tail();

  void insert_last(T value);
  void insert_first(T value);
  void insert_after(Node<T> *node, T value);

public:
  Lista();
  ~Lista();

  T get_at(int posicao);
  T get_first();
  T get_last();

  T remove_at(int posicao);
  T remove_first();
  T remove_last();

  int get_length();
  bool is_empty();

  virtual void print() = 0;
};

#endif
