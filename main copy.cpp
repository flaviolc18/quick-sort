#include <iostream>

#include "list.cpp"
#include "graph.cpp"

int main()
{
  Graph<int> g = Graph<int>(8);
  g.new_node(0, 0);
  g.new_node(1, 1);
  g.new_node(2, 2);
  g.new_node(3, 3);
  g.new_node(4, 4);
  g.new_node(5, 5);
  g.new_node(6, 6);
  g.new_node(7, 7);

  g.set_edge(0, 1);
  g.set_edge(0, 5);
  g.set_edge(0, 2);
  g.set_edge(1, 3);
  g.set_edge(2, 4);
  g.set_edge(3, 5);
  g.set_edge(3, 7);
  g.set_edge(4, 6);
  g.set_edge(6, 3);
  g.set_edge(7, 0);

  g.bfs(0, [](int &val) { std::cout << " " << val << " "; });
  std::cout << std::endl;

  g.dfs(0, [](int &val) { std::cout << " " << val << " "; });
  std::cout << std::endl;

  std::cout << "has cycle: = " << g.cyclic() << std::endl;

  g.print();
  return 0;
}
