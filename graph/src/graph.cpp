#include "graph.h"

#include <iostream>

template <class T>
Graph<T>::Graph(int v)
{
  this->vertex = v;

  this->nodes = new nodeg<T> *[v];
  this->adj = new List<int> *[v];

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
void Graph<T>::remove_edge(int v1, int v2)
{
  if (this->has_edge(v1, v2))
  {
    int pos = this->adj[v1]->pos(v2);
    if (pos != -1)
    {
      this->adj[v1]->pop_at(pos);
    }
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
void Graph<T>::topological_sort_helper(int v, int visited[], List<T> *stack)
{
  visited[v] = 1;

  this->adj[v]->each([&, this](int i) {
    if (!visited[i])
      this->topological_sort_helper(i, visited, stack);
  });

  stack->push_last(this->nodes[v]->value);
}

template <class T>
List<T> *Graph<T>::topological_sort()
{
  List<T> *stack = new List<T>();
  int visited[this->vertex] = {0};

  for (int i = 0; i < this->vertex; i++)
    if (!visited[i] && !this->nodes[i]->empty)
      topological_sort_helper(i, visited, stack);

  return stack;
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

// TODO: find a better way to handle this, this function should be responsible for deleting the dynamically allocated graph
template <class T>
Graph<T> *Graph<T>::transpose()
{
  Graph<T> *t = new Graph<T>(this->vertex);

  for (int i = 0; i < this->vertex; i++)
    if (!this->nodes[i]->empty)
      t->new_node(i, this->nodes[i]->value);

  for (int i = 0; i < this->vertex; i++)
    if (!this->nodes[i]->empty)
      this->adj[i]->each([&](int j) {
        t->set_edge(j, i);
      });

  return t;
}

template <class T>
void Graph<T>::print(std::function<std::string(T &)> to_string)
{

  for (int i = 0; i < this->vertex; i++)
  {
    if (!this->nodes[i]->empty)
    {
      std::cout << "[ " << i << ":" << to_string(this->nodes[i]->value) << " ]";

      this->adj[i]->each([&](int &i) {
        std::cout << " -> [ " << i << " ]";
      });
      std::cout << std::endl;
    }
  }
}
