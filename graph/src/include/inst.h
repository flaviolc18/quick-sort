#ifndef INST_H
#define INST_H

#include <fstream>
#include "../graph.cpp"

struct member
{
  int id;
  int age;
};

class Inst
{
  //TODO: shared_ptr?
  Graph<member> *graph;

  void swap(const int &a, const int &b);
  void commander(const int &a);
  void meeting();

public:
  Inst(Graph<member> *graph);

  void exec_inst(std::ifstream &file);
};

#endif
