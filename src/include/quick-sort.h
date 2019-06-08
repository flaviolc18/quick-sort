#ifndef QUICK_SORT_H
#define QUICK_SORT_H

struct Item
{
  int ini;
  int end;

  Item() {}
  Item(int ini, int end)
  {
    this->ini = ini;
    this->end = end;
  }
};

class QuickSort
{
private:
  int k;

public:
  QuickSort(int k = 0);

  void quick_sort(int *array, int size);
  unsigned long long get_n_comp();
  unsigned long long get_n_mov();

protected:
  unsigned long long n_comp;
  unsigned long long n_mov;

  void partition(int ini, int end, int &i, int &j, int *array);
  void insertion_sort(int ini, int end, int *array);
  bool should_use_insertion_sort(int ini, int end, int size);
  void swap(int &a, int &b);

  virtual void sort(int ini, int end, int *array, int size);
  virtual int get_pivot(int ini, int end, int *array);
};

class QuickSortFirstElement : public QuickSort
{
  virtual int get_pivot(int ini, int end, int *array);
};

class QuickSortMedianOfThree : public QuickSort
{
  virtual int get_pivot(int ini, int end, int *array);

public:
  QuickSortMedianOfThree(int k = 0);
};

class QuickSort1Insertion : public QuickSortMedianOfThree
{
public:
  QuickSort1Insertion();
};

class QuickSort5Insertion : public QuickSortMedianOfThree
{
public:
  QuickSort5Insertion();
};

class QuickSort10Insertion : public QuickSortMedianOfThree
{
public:
  QuickSort10Insertion();
};

class QuickSortNonRecursive : public QuickSort
{
  virtual void sort(int ini, int end, int *array, int size);
};

#endif
