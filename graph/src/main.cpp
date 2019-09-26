#include <iostream>
#include <string>
#include <fstream>

#include "inst.h"

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    return 0;
  }

  std::ifstream file;
  file.open(argv[1]);

  if (file.is_open())
  {

    int N, M, I;
    file >> N >> M >> I;

    Graph<Member> graph = Graph<Member>(N + 1);

    for (int i = 1; i <= N; i++)
    {
      Member m;
      file >> m.age;
      m.id = i;
      graph.new_node(i, m);
    }

    for (int e1, e2, i = 0; i < M; i++)
    {
      file >> e1 >> e2;
      graph.set_edge(e1, e2);
    }

    Inst inst = Inst(&graph);
    for (int i = 0; i < I; i++)
    {
      inst.exec_inst(file);
    }

    graph.print([](Member &m) { return std::to_string(m.age); });

    file.close();
  }

  return 0;
}
