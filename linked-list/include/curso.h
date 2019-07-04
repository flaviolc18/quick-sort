#ifndef CURSO_H
#define CURSO_H

#include <iostream>
#include <memory>

class Curso
{
private:
  int id;
  std::string nome;
  int qtd_vagas;
  double nota_corte;
  ListaAluno classificados;
  ListaAluno lista_espera;

public:
  Curso(int id, std::string nome, int qtd_vagas);

  std::shared_ptr<Aluno> classificar_aluno(std::shared_ptr<Aluno> aluno);
  void inserir_lista_espera(std::shared_ptr<Aluno> aluno);
  void atualiza_nota_corte();
  void print();
  void print_classificados();
  void print_lista_espera();
  int get_id();
};

#endif
