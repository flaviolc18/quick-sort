#ifndef GRAPH_H
#define GRAPH_H

#include "../list.cpp"

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
  void topological_sort_helper(int v, int visited[], List<T> *stack);

public:
  Graph(int v);
  ~Graph();

  bool has_node(int v);
  void new_node(int v, T value);
  void remove_node(int v);

  bool has_edge(int v1, int v2);
  void set_edge(int v1, int v2);
  void remove_edge(int v1, int v2);

  void bfs(int v, std::function<void(T &)> fn);
  void dfs(int v, std::function<void(T &)> fn);
  List<T> *topological_sort();
  bool cyclic();

  Graph<T> *transpose();

  void print(std::function<std::string(T &)> to_string);
};

#endif
