#include "quick-sort.h"
#include "stack.cpp"

template <class T>
QuickSort<T>::QuickSort(int k)
{
  this->k = k;
}

template <class T>
void QuickSort<T>::swap(T &a, T &b)
{
  T temp = a;
  a = b;
  b = temp;
  this->n_mov++;
}

template <class T>
T QuickSort<T>::get_pivot(int ini, int end, T *array)
{
  return array[(ini + end) / 2];
}

template <class T>
unsigned long long QuickSort<T>::get_n_comp()
{
  return this->n_comp;
}

template <class T>
unsigned long long QuickSort<T>::get_n_mov()
{
  return this->n_mov;
}

template <class T>
void QuickSort<T>::quick_sort(T *array, int size)
{
  this->n_comp = 0;
  this->n_mov = 0;
  this->sort(0, size - 1, array, size);
}

template <class T>
void QuickSort<T>::sort(int ini, int end, T *array, int size)
{

  if (this->should_use_insertion_sort(ini, end + 1, size))
  {
    this->insertion_sort(ini, end + 1, array);
    return;
  }

  int i, j;
  this->partition(ini, end, i, j, array);
  if (ini < j)
    this->sort(ini, j, array, size);
  if (i < end)
    this->sort(i, end, array, size);
}

template <class T>
void QuickSort<T>::partition(int ini, int end, int &i, int &j, T *array)
{

  i = ini;
  j = end;
  T pivot = this->get_pivot(ini, end, array);

  do
  {
    while (pivot > array[i])
    {
      this->n_comp++;
      (i)++;
    }
    while (pivot < array[j])
    {
      this->n_comp++;
      (j)--;
    }
    if (i <= j)
    {
      swap(array[i], array[j]);
      i++;
      j--;
    }
  } while (i <= j);
}

template <class T>
void QuickSort<T>::insertion_sort(int ini, int end, T *array)
{

  int i, j;
  T key;
  for (i = ini; i < end; i++)
  {
    key = array[i];
    j = i - 1;

    while (j >= 0 && array[j] > key)
    {
      array[j + 1] = array[j];
      j = j - 1;
      this->n_comp++;
      this->n_mov++;
    }
    array[j + 1] = key;
    this->n_mov++;
  }
}

template <class T>
bool QuickSort<T>::should_use_insertion_sort(int ini, int end, int size)
{
  int sub_array_size = end - ini;
  return sub_array_size < (this->k * size) / 100;
}

template <class T>
T QuickSortFirstElement<T>::get_pivot(int ini, int end, T *array)
{
  return array[ini];
}

template <class T>
QuickSortMedianOfThree<T>::QuickSortMedianOfThree(int k) : QuickSort<T>(k) {}

template <class T>
T QuickSortMedianOfThree<T>::get_pivot(int ini, int end, T *array)
{
  int median_array[] = {array[ini], array[(ini + end) / 2], array[end]};
  this->insertion_sort(0, 3, median_array);
  return median_array[1];
}

template <class T>
QuickSort1Insertion<T>::QuickSort1Insertion() : QuickSortMedianOfThree<T>(1) {}
template <class T>
QuickSort5Insertion<T>::QuickSort5Insertion() : QuickSortMedianOfThree<T>(5) {}
template <class T>
QuickSort10Insertion<T>::QuickSort10Insertion() : QuickSortMedianOfThree<T>(10) {}

template <class T>
void QuickSortNonRecursive<T>::sort(int ini, int end, T *array, int size)
{
  int i, j;
  Stack<Item> stack = Stack<Item>();
  stack.push(Item(ini, end));

  do
    if (end > ini)
    {
      this->partition(ini, end, i, j, array);
      if ((j - ini) > (end - i))
      {
        stack.push(Item(ini, j));
        ini = i;
      }
      else
      {
        stack.push(Item(i, end));
        end = j;
      }
    }
    else
    {
      Item item = stack.pop();
      end = item.end;
      ini = item.ini;
    }
  while (!stack.is_empty());
}
