// На числовой прямой окрасили N отрезков.
// Известны координаты левого и правого концов каждого отрезка (Li и Ri).
// Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.


#include <iostream>
#include <assert.h>

struct Point
{
  int x;
  bool left;
  Point() : x(0), left(false) {}
  Point( int _x, bool _left ) : x(_x), left(_left) {}
};


bool operator <= ( const Point& l, const Point& r ) {
  return l.x <= r.x;
}

bool IsPointLessOrEqual( const Point& l, const Point& r ) {
  return l <= r;
}

template<class T>
bool IsLessDefault( const T& l, const T& r ) {
  return l < r;
}

template<class T, class Comparator>
void Merge( T* arr, int l, int m, int r, Comparator cmp ) {
  int nL = m - l + 1; // количество элементов в левом подмассиве
  int nR = r - m; // количество элементов в правом подмассиве

  T* tmpL = new T[nL];  // буферный массив для левого подмассива
  T* tmpR = new T[nR];  // буферный массив для правого подмассива

  //  копирование левого подмассива в буфер
  for( int i = 0; i < nL; ++i ) {
    tmpL[i] = *(arr + l + i);
  }

  //  копирование правого подмассива в буфер
  for( int i = 0; i < nR; ++i ) {
    tmpR[i] = *(arr + m + 1 + i);
  }

  //  слияние массивов
  int counterL = 0, counterR = 0, counter = l;
  while( (counterL < nL) && (counterR < nR) ) {
    if( cmp( tmpL[counterL], tmpR[counterR] ) ) {
      arr[counter] = tmpL[counterL++];
    } else {
      arr[counter] = tmpR[counterR++];
    }
    counter++;
  }

  //  вставка оставшейся части одного из массивов
  while( counterL < nL ) {
    arr[counter++] = tmpL[counterL++];
  }
  while( counterR < nR ) {
    arr[counter++] = tmpR[counterR++];
  }

  delete [] tmpL;
  delete [] tmpR;
}

template<class T, class Comparator>
void MergeSort( T* arr, int l, int r, Comparator cmp ) {
  if( !(l < r) ) {
    return;
  }

  int m = (l + r) / 2;

  MergeSort( arr, l, m, cmp );
  MergeSort( arr, m + 1, r, cmp );

  Merge( arr, l, m, r, cmp );
}

int FindOneLayer( Point* points, const int n ) {
  MergeSort( points, 0, n - 1, IsPointLessOrEqual );

  int result = 0, currentLayers = 1;

  for( int i = 1; i < n; ++i ) {
    if( points[i].left ) {
      currentLayers++;
      if( currentLayers == 2 ) {
        result += points[i].x - points[i - 1].x;
      }
    } else {
      currentLayers--;
      if( currentLayers == 0 ) {
        result += points[i].x - points[i - 1].x;
      }
    }
  }

  return result;
}

int main(int argc, char const *argv[])
{
  int n = 0;
  std::cin >> n;
  assert( n > 0 );
  n *= 2; // количество точек

  Point* points = new Point[n];
  for( int i = 0; i < n; ++i ) {
    std::cin >> points[i].x;
    if( i % 2 == 0) {
      points[i].left = true;
    } else {
      points[i].left = false;
    }
  }

  std::cout << FindOneLayer( points, n );
  
  delete [] points;
  return 0;
}