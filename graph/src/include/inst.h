#ifndef INST_H
#define INST_H

#include <fstream>
#include "../graph.cpp"

struct Member
{
  int id;
  int age;
};

class Inst
{
  std::shared_ptr<Graph<Member>> graph;

  void swap_helper(const int &a, const int &b);
  void swap(const int &a, const int &b);
  void commander(const int &a);
  void meeting();

public:
  Inst(std::shared_ptr<Graph<Member>> graph);

  void exec_inst(std::ifstream &file);
};

#endif
