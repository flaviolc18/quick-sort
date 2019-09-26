#ifndef GRAPH_H
#define GRAPH_H

#include "../list.cpp"

template <typename T>
struct GraphNode
{
  T value;
  bool empty;

  GraphNode()
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
  GraphNode<T> **nodes;

  bool cyclic_helper(int v, int visited[], int rec_stack[]);
  void topological_sort_helper(int v, int visited[], std::shared_ptr<List<T>> stack);

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
  std::shared_ptr<List<T>> topological_sort();
  bool cyclic();

  std::unique_ptr<Graph<T>> transpose();

  void print(std::function<std::string(T &)> to_string);
};

#endif
