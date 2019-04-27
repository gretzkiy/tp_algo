// Реализуйте стратегию выбора опорного элемента “случайный элемент”.
// Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.

#include <iostream>
#include <assert.h>
#include <time.h>

int FindKStat( int* arr, int n, int k );
int Partition( int* arr, int left, int right );


int main() {
  int n = 0, k = 0;
  std::cin >> n >> k;
  assert( n > 0 && k >= 0 && k < n );

  int* arr = new int[n];
  for( int i = 0; i < n; ++i ) {
    std::cin >> arr[i];
  }

  std::cout << FindKStat(arr, n, k);

  delete [] arr;
  return 0;
}

int FindKStat( int* arr, int n, int k ) {
  int pivot = 0;

  // индексы границ массива
  int left = 0;
  int right = n - 1;

  pivot = Partition( arr, left, right );
  
  while( pivot != k ) {
    // правая граница области поиска смещается 
    if( pivot > k ) {
      right = pivot - 1;
    }
    // левая граница области поиска смещается
    if( pivot < k ) {
      left = pivot + 1;
    }

    pivot = Partition( arr, left, right );
  }

  return arr[pivot];
}

int Partition( int* arr, int left, int right ) {
  int n = right - left + 1;

  if( n <= 1 ) {
    return left;
  }

  srand( time( NULL ) );
  int pivotIndex = left + rand() % n;
  std::swap( arr[left], arr[pivotIndex] );
  pivotIndex = left;

  int i = right, j = right;

  while( j > pivotIndex ) {
    if( arr[j] >= arr[pivotIndex] ) {
      std::swap( arr[j], arr[i] );
      i--;
    }
    j--;
  }

  std::swap( arr[pivotIndex], arr[i] );

  return i;
}
