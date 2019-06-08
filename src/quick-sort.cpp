#include "quick-sort.h"
#include "stack.cpp"

QuickSort::QuickSort(int k)
{
  this->k = k;
}

void QuickSort::swap(int &a, int &b)
{
  int temp = a;
  a = b;
  b = temp;
  this->n_mov++;
}

int QuickSort::get_pivot(int ini, int end, int *array)
{
  return array[(ini + end) / 2];
}

unsigned long long QuickSort::get_n_comp()
{
  return this->n_comp;
}

unsigned long long QuickSort::get_n_mov()
{
  return this->n_mov;
}

void QuickSort::quick_sort(int *array, int size)
{
  this->n_comp = 0;
  this->n_mov = 0;
  this->sort(0, size - 1, array, size);
}

void QuickSort::sort(int ini, int end, int *array, int size)
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

void QuickSort::partition(int ini, int end, int &i, int &j, int *array)
{

  i = ini;
  j = end;
  int pivot = this->get_pivot(ini, end, array);

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

void QuickSort::insertion_sort(int ini, int end, int *array)
{

  int i, j, key;
  for (i = ini; i < end; i++)
  {
    key = array[i];
    j = i - 1;

    while (j >= 0 && array[j] > key)
    {
      array[j + 1] = array[j];
      j = j - 1;
    }
    array[j + 1] = key;
  }
}

bool QuickSort::should_use_insertion_sort(int ini, int end, int size)
{
  int sub_array_size = end - ini;
  return sub_array_size < (this->k * size) / 100;
}

int QuickSortFirstElement::get_pivot(int ini, int end, int *array)
{
  return array[ini];
}

QuickSortMedianOfThree::QuickSortMedianOfThree(int k) : QuickSort(k) {}
int QuickSortMedianOfThree::get_pivot(int ini, int end, int *array)
{
  int median_array[] = {array[ini], array[(ini + end) / 2], array[end]};
  this->insertion_sort(0, 3, median_array);
  return median_array[1];
}

QuickSort1Insertion::QuickSort1Insertion() : QuickSortMedianOfThree(1) {}
QuickSort5Insertion::QuickSort5Insertion() : QuickSortMedianOfThree(5) {}
QuickSort10Insertion::QuickSort10Insertion() : QuickSortMedianOfThree(10) {}

void QuickSortNonRecursive::sort(int ini, int end, int *array, int size)
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
