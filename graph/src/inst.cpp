#include "inst.h"

#include <iostream>

#define MAX_AGE 100

Inst::Inst(Graph<member> *graph)
{
  this->graph = graph;
}

void Inst::exec_inst(std::ifstream &file)
{
  char type;
  file >> type;

  int p1, p2;
  switch (type)
  {
  case 'S':
    file >> p1 >> p2;
    return this->swap(p1, p2);
  case 'C':
    file >> p1;
    return this->commander(p1);
  case 'M':
    return this->meeting();

  default:
    return;
  }
}

void Inst::swap(const int &a, const int &b)
{
  if (this->graph->has_edge(a, b))
  {
    this->graph->remove_edge(a, b);
    this->graph->set_edge(b, a);

    if (!this->graph->cyclic())
    {
      std::cout << "S T" << std::endl;
      return;
    }

    graph->remove_edge(b, a);
    graph->set_edge(a, b);
  }
  std::cout << "S N" << std::endl;
}

void Inst::commander(const int &a)
{
  Graph<member> *transpose = this->graph->transpose();

  int min_age = MAX_AGE;
  bool first_skipped = false;

  transpose->bfs(a, [&](member m) {
    if (first_skipped)
      min_age = m.age < min_age ? m.age : min_age;
    else
      first_skipped = true;
  });

  delete transpose;

  if (min_age == MAX_AGE)
    std::cout << "C *" << std::endl;
  else
    std::cout << "C " << min_age << std::endl;
}

void Inst::meeting()
{
  std::cout << "M ";
  List<member> *sorted = this->graph->topological_sort();
  sorted->each_rev([](member &m) {
    std::cout << m.id << " ";
  });
  std::cout << std::endl;

  delete sorted;
}
