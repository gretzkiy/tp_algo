// Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k.
// Найти количество таких пар индексов (i, j), что A[i] + B[j] = k. Время работы O(n + m).
// n, m ≤ 100000.

#include <iostream>
#include <assert.h>
int find_index_count(int const * A, const int n, int const * B, const int m, const int k);

int main(int argc, char const *argv[])
{
  int n = 0;
  std::cin >> n;
  assert((n >= 0) && (n <= 100000));
  int* A = new int[n];
  for (int i = 0; i < n; ++i)
    std::cin >> A[i];
  int m = 0;
  std::cin >> m;
  assert((m >= 0) && (m <= 100000));
  int* B = new int[m];
  for (int i = 0; i < m; ++i)
    std::cin >> B[i];
  int k = 0;
  std::cin >> k;
  std::cout << find_index_count(A, n, B, m, k);
  delete [] A;
  delete [] B;
  return 0;
}

int find_index_count(int const * A, const int n, int const * B, const int m, const int k)
{
  if( (n == 0) || (m == 0) )
    return 0;
  int aCounter = 0, bCounter = m - 1, index_count = 0;
  //По массиву А идем от начала к концу. При увеличении aCounter сумма элементов увеличивается.
  //По массиву B идем от конца к началу. При уменьшении bCounter сумма элементов уменьшается.
  while( (aCounter < n) && (bCounter >= 0) )
  {
    int sum = A[aCounter] + B[bCounter];
    if( sum > k )
    {
      //сумму надо уменьшить
      bCounter--;
    } else if( sum < k )
    {
      //сумму надо увеличить
      aCounter++;
    } else {
      //так как массив строго возрастающий, значит одинаковых чисел в нет, поэтому изменяем оба индекса
      index_count++;
      aCounter++;
      bCounter--;
    }
  }
  return index_count;
}