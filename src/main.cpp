#include <iostream>
#include <memory>
#include <stdexcept>
#include <random>
#include <chrono>

#include "quick-sort.h"
#include "lista.cpp"

#define MAX_NUMBER 500000
#define NUMBER_OF_TESTS 21

std::unique_ptr<QuickSort> get_quick_sort(std::string variacao)
{
  if (variacao == "QC")
    return std::unique_ptr<QuickSort>{new QuickSort()};
  if (variacao == "QPE")
    return std::unique_ptr<QuickSort>{new QuickSortFirstElement()};
  if (variacao == "QM3")
    return std::unique_ptr<QuickSort>{new QuickSortMedianOfThree()};
  if (variacao == "QI1")
    return std::unique_ptr<QuickSort>{new QuickSort1Insertion()};
  if (variacao == "QI5")
    return std::unique_ptr<QuickSort>{new QuickSort5Insertion()};
  if (variacao == "QI10")
    return std::unique_ptr<QuickSort>{new QuickSort10Insertion()};
  if (variacao == "QNR")
    return std::unique_ptr<QuickSort>{new QuickSort()};
  throw std::invalid_argument("'variaçao' should be one of the allowed values [QC, QPE, QM3, QI1, QI5, QI10, QNR]");
}

void generate_random_array(int *array, int size)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, MAX_NUMBER);

  for (int i = 0; i < size; i++)
    array[i] = dis(gen);
}

void generate_crescent_array(int *array, int size)
{
  for (int i = 0; i < size; i++)
    array[i] = i;
}

void generate_decrescent_array(int *array, int size)
{
  for (int i = 1; i <= size; i++)
    array[i] = size - i;
}

void setup_array(std::string tipo, int size, int *array)
{
  if (tipo == "Ale")
    return generate_random_array(array, size);
  if (tipo == "OrdC")
    return generate_crescent_array(array, size);
  if (tipo == "OrdD")
    return generate_decrescent_array(array, size);
  throw std::invalid_argument("'tipo' should be one of the allowed values [Ale, OrdC, OrdD]");
}

std::chrono::duration<long, std::micro> get_execution_time(QuickSort *qs, int *array, int tamanho)
{
  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  qs->quick_sort(array, tamanho);
  std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
}

void print_array(int *arr, int size)
{
  for (int i = 0; i < size; i++)
  {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}

void process_input(std::string variacao, std::string tipo, int tamanho, bool exibir_vetor)
{
  std::unique_ptr<QuickSort> qs = get_quick_sort(variacao);

  int arrays[NUMBER_OF_TESTS][tamanho] = {0};
  unsigned long long mean_n_comp = 0, mean_n_mov = 0;

  Lista<std::chrono::duration<long, std::micro>> median_list = Lista<std::chrono::duration<long, std::micro>>();

  for (int i = 0; i < NUMBER_OF_TESTS; i++)
  {
    setup_array(tipo, tamanho, arrays[i]);

    median_list.insert_sorted(get_execution_time(qs.get(), arrays[i], tamanho));
    mean_n_comp += qs->get_n_comp();
    mean_n_mov += qs->get_n_mov();
  }
  auto median = median_list.get_at(11);
  mean_n_comp /= NUMBER_OF_TESTS;
  mean_n_mov /= NUMBER_OF_TESTS;

  std::cout << variacao << " " << tipo << " " << tamanho << " " << mean_n_comp << " " << mean_n_mov << " " << median.count() << std::endl;

  if (exibir_vetor)
    for (int i = 0; i < NUMBER_OF_TESTS; i++)
      print_array(arrays[i], tamanho);
}

int main(int argc, char *argv[])
{

  if (argc < 4)
  {
    std::cout << "Usage: <variacao> <tipo> <tamanho> [-p]" << std::endl;
    return 0;
  }
  std::string variacao = argv[1];
  std::string tipo = argv[2];
  int tamanho = atoi(argv[3]);
  bool exibir_vetor = argc >= 5 && std::string(argv[4]) == "-p";

  process_input(variacao, tipo, tamanho, exibir_vetor);

  return 0;
}
