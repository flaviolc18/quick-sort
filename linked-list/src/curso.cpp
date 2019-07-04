#include <iomanip>

#include "lista-aluno.cpp"
#include "curso.h"

Curso::Curso(int id, std::string nome, int qtd_vagas) : classificados(id), lista_espera(id)
{
  this->id = id;
  this->nome = nome;
  this->qtd_vagas = qtd_vagas;
  this->nota_corte = 0;
}

std::shared_ptr<Aluno> Curso::classificar_aluno(std::shared_ptr<Aluno> aluno)
{

  bool nota_suficiente = aluno->nota >= this->nota_corte;
  bool tem_vaga = this->qtd_vagas > this->classificados.get_length();

  if (tem_vaga)
  {
    this->classificados.insert_sorted(aluno);
    this->atualiza_nota_corte();
    return nullptr;
  }

  if (nota_suficiente)
  {
    this->classificados.insert_sorted(aluno);
    std::shared_ptr<Aluno> aluno_nao_classificado = this->classificados.remove_last();
    this->atualiza_nota_corte();
    return aluno_nao_classificado;
  }

  return aluno;
}

void Curso::inserir_lista_espera(std::shared_ptr<Aluno> aluno)
{
  this->lista_espera.insert_sorted(aluno);
}

void Curso::atualiza_nota_corte()
{
  this->nota_corte = ((this->classificados.get_length() == this->qtd_vagas) ? this->classificados.get_last()->nota : 0);
}

void Curso::print()
{
  std::cout << this->nome << " " << std::fixed << std::setprecision(2) << this->nota_corte << std::endl;
}

void Curso::print_classificados()
{
  std::cout << "Classificados" << std::endl;
  this->classificados.print();
}

void Curso::print_lista_espera()
{
  std::cout << "Lista de espera" << std::endl;
  this->lista_espera.print();
}

int Curso::get_id()
{
  return this->id;
}
