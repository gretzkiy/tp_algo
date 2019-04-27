//  Дан массив целых чисел А[0..n-1].
//  Известно, что на интервале [0, m] значения массива строго возрастают,
//  а на интервале [m, n-1] строго убывают. Найти m за O(log m).
//  2 ≤ n ≤ 10000.

#include <iostream>
#include <assert.h>

int find_peak( int const * array, const int n );
int binary_search_max( int const * array, int left, int right );

int main( int argc, char const *argv[] )
{
    int n = 0;
    std::cin >> n;
    assert( (n >= 2) && (n <= 10000) );
    
    int* array = new int[n];
    for( int i = 0; i < n; ++i )
        std::cin >> array[i];
    
    std::cout << find_peak( array, n );
    
    delete [] array;
    return 0;
}

// функция находит отрезок, на котором содержится максимальный элемент,
// и вызывает для этого отрезка бинарный поиск максимума.
int find_peak( int const * array, const int n )
{
    int i = 1;
    int left = 0, right = n - 1;
    bool found = false;
    // поиск границ отрезка пока не дойдем до конца массива,
    // либо пока не "перейдем" через максимум
    while( (i < n) && !found )
    {
        if( array[i] > array[i + 1] ) { // если максимум остался "слева"
            left = i / 2;
            right = i;
            found = true;
        }
        i *= 2;
    }
    // если максимум в находится в "последнем разбиении"
    if( !found ) {
        left = i / 2;
    }
    return binary_search_max( array, left, right );
}

// бинарный поиск максимума, возвращает индекс максимума
int binary_search_max( int const * array, int left, int right )
{
    // если только один элемент в массиве, возвращаем его индекс
    if( left == right )
        return left;
    
    // если только два элемента в массиве, возвращаем индекс бОльшего
    if( right == left + 1 ) {
        if( array[left] > array[right] ) {
            return left;
        } else {
            return right;
        }
    }
    
    int mid = (left + right) / 2;
    
    // если средний элемент больше обоих соседних, то он - максимум
    if( (array[mid] > array[mid - 1]) && (array[mid] > array[mid + 1]) )
        return mid;
    
    // в какой части массива продолжать поиск
    if( (array[mid] > array[mid + 1]) && (array[mid] < array[mid - 1]) ) {
        return binary_search_max(array, left, mid - 1);
    } else {
        return binary_search_max(array, mid + 1, right);
    }
}