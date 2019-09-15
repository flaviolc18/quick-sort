#include "graph.h"

#include <iostream>

template <class T>
Graph<T>::Graph(int v)
{
  this->vertex = v;

  this->nodes = new nodeg<T> *[v];
  this->adj = new List<T> *[v];

  for (int i = 0; i < v; i++)
  {
    this->nodes[i] = new nodeg<T>();
    this->adj[i] = new List<int>();
  }
}

template <class T>
Graph<T>::~Graph()
{
  //TODO: rodar valgrind
  for (int i = 0; i < this->vertex; i++)
  {
    delete this->nodes[i];
    delete this->adj[i];
  }

  delete[] this->nodes;
  delete[] this->adj;
}

template <class T>
void Graph<T>::new_node(int v, T value)
{
  this->nodes[v]->value = value;
  this->nodes[v]->empty = false;
}

template <class T>
void Graph<T>::remove_node(int v)
{
  //TODO: remover todas as arestas que apontam para este vertice
  this->nodes[v]->empty = true;
}

template <class T>
bool Graph<T>::has_node(int v)
{
  return !this->nodes[v]->empty;
}

template <class T>
bool Graph<T>::has_edge(int v1, int v2)
{
  return this->has_node(v1) && this->has_node(v2) && this->adj[v1]->has(v2);
}

template <class T>
void Graph<T>::set_edge(int v1, int v2)
{
  if (this->has_node(v1) && this->has_node(v2))
  {
    this->adj[v1]->push_last(v2);
  }
}

template <class T>
void Graph<T>::bfs(int v, std::function<void(T &)> fn)
{
  int visited[this->vertex] = {0};

  List<int> queue;

  visited[v] = 1;
  queue.push_last(v);

  while (!queue.empty())
  {
    v = queue.pop_first();
    fn(this->nodes[v]->value);

    adj[v]->each([&queue, &visited](int i) {
      if (!visited[i])
      {
        visited[i] = 1;
        queue.push_last(i);
      }
    });
  }
}

template <class T>
void Graph<T>::dfs(int v, std::function<void(T &)> fn)
{
  int visited[this->vertex] = {0};

  List<int> stack;

  stack.push_last(v);

  while (!stack.empty())
  {
    v = stack.pop_last();

    if (!visited[v])
    {
      fn(this->nodes[v]->value);
      visited[v] = 1;
    }
    adj[v]->each([&stack, &visited](int i) {
      if (!visited[i])
        stack.push_last(i);
    });
  }
}

template <class T>
bool Graph<T>::cyclic_helper(int v, int visited[], int rec_stack[])
{
  bool ans = false;
  if (!visited[v])
  {
    visited[v] = 1;
    rec_stack[v] = 1;

    adj[v]->each([&, this](int i) {
      if (!ans && !visited[i] && this->cyclic_helper(i, visited, rec_stack))
        ans = true;
      else if (rec_stack[i])
        ans = true;
    });
  }
  rec_stack[v] = 0;
  return ans;
}

template <class T>
bool Graph<T>::cyclic()
{
  int visited[this->vertex] = {0};
  int rec_stack[this->vertex] = {0};

  for (int i = 0; i < this->vertex; i++)
    if (!this->nodes[i]->empty && this->cyclic_helper(i, visited, rec_stack))
      return true;

  return false;
}

template <class T>
void Graph<T>::print()
{

  for (int i = 0; i < this->vertex; i++)
  {
    if (!this->nodes[i]->empty)
    {
      std::cout << "[ " << i << " ]";
      this->adj[i]->each([](T &val) { std::cout << " -> [ " << val << " ]"; });
      std::cout << std::endl;
    }
  }
}
