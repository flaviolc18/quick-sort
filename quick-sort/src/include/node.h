#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
public:
  T value;
  Node *next;
  Node *previous;

  Node()
  {
    this->next = nullptr;
    this->previous = nullptr;
  };
};

#endif
