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

template <class T>
class QuickSort
{
private:
  int k;

public:
  QuickSort(int k = 0);

  void quick_sort(T *array, int size);
  unsigned long long get_n_comp();
  unsigned long long get_n_mov();

protected:
  unsigned long long n_comp;
  unsigned long long n_mov;

  void partition(int ini, int end, int &i, int &j, T *array);
  void insertion_sort(int ini, int end, T *array);
  bool should_use_insertion_sort(int ini, int end, int size);
  void swap(T &a, T &b);

  virtual void sort(int ini, int end, T *array, int size);
  virtual T get_pivot(int ini, int end, T *array);
};

template <class T>
class QuickSortFirstElement : public QuickSort<T>
{
  virtual T get_pivot(int ini, int end, T *array);
};

template <class T>
class QuickSortMedianOfThree : public QuickSort<T>
{
  virtual T get_pivot(int ini, int end, T *array);

public:
  QuickSortMedianOfThree(int k = 0);
};

template <class T>
class QuickSort1Insertion : public QuickSortMedianOfThree<T>
{
public:
  QuickSort1Insertion();
};

template <class T>
class QuickSort5Insertion : public QuickSortMedianOfThree<T>
{
public:
  QuickSort5Insertion();
};

template <class T>
class QuickSort10Insertion : public QuickSortMedianOfThree<T>
{
public:
  QuickSort10Insertion();
};

template <class T>
class QuickSortNonRecursive : public QuickSort<T>
{
  virtual void sort(int ini, int end, T *array, int size);
};

#endif
