#include <iomanip>

#include "aluno.h"
#include "../src/lista.cpp"
#include "lista-aluno.h"

ListaAluno::ListaAluno(int curso_id)
{
  this->curso_id = curso_id;
};

bool ListaAluno::aluno_vem_depois(std::shared_ptr<Aluno> aluno, Node<std::shared_ptr<Aluno>> *node)
{

  bool eh_segunda_opcao_novo_aluno = aluno->opcao_curso2 == this->curso_id;
  bool eh_primeira_opcao_aluno_classificado = node->value->opcao_curso1 == this->curso_id;

  bool inserir_novo_aluno_depois = eh_primeira_opcao_aluno_classificado || eh_segunda_opcao_novo_aluno;

  return inserir_novo_aluno_depois;
}

void ListaAluno::insert_sorted(std::shared_ptr<Aluno> aluno)
{
  Node<std::shared_ptr<Aluno>> *node = this->get_head();
  if (!this->is_empty())
  {
    while (node->next != this->get_tail() && (aluno->nota < node->next->value->nota || (aluno->nota == node->next->value->nota && this->aluno_vem_depois(aluno, node->next))))
    {
      node = node->next;
    };
  }
  Lista::insert_after(node, aluno);
};

void ListaAluno::print()
{
  Node<std::shared_ptr<Aluno>> *it = this->get_head()->next;
  while (it != this->get_tail())
  {
    std::cout << it->value->nome << " " << std::fixed << std::setprecision(2) << it->value->nota << std::endl;
    it = it->next;
  }
};
