#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"

template <typename T>
struct nodeg
{
  T value;
  bool empty;

  nodeg()
  {
    this->empty = true;
  };
};

template <class T>
class Graph
{
private:
  int vertex;
  List<int> **adj;
  nodeg<T> **nodes;

  bool cyclic_helper(int v, int visited[], int rec_stack[]);

public:
  Graph(int v);
  ~Graph();

  void new_node(int v, T value);
  void remove_node(int v);
  bool has_node(int v);

  bool has_edge(int v1, int v2);
  void set_edge(int v1, int v2);

  void bfs(int v, std::function<void(T &)> fn);
  void dfs(int v, std::function<void(T &)> fn);
  bool cyclic();

  void print();
};

#endif
