#ifndef LISTA_ALUNO_H
#define LISTA_ALUNO_H

#include <memory>

class ListaAluno : public Lista<std::shared_ptr<Aluno>>
{

private:
  int curso_id;

  bool aluno_vem_depois(std::shared_ptr<Aluno> aluno, Node<std::shared_ptr<Aluno>> *node);

public:
  ListaAluno(int curso_id);

  void insert_sorted(std::shared_ptr<Aluno> aluno);
  virtual void print();
};

#endif
