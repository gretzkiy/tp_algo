// Binary MSD для long long.
// Дан массив неотрицательных целых 64-разрядных чисел.
// Количество чисел не больше 106.
// Отсортировать массив методом MSD по битам (бинарный QuickSort).


#include <iostream>
#include <assert.h>

int getRadix( const unsigned long long value, const int radix );
void BinMSD( unsigned long long* arr, int n, int radix );
int partition( unsigned long long* arr, int n, const int radix );

int main(int argc, char const *argv[])
{
    int n = 0;
    std::cin >> n;
    assert( n > 0 && n <= 1e+6 );
    
    unsigned long long* arr = new unsigned long long[n];
    for( int i = 0; i < n; ++i ) {
        std::cin >> arr[i];
    }
    
    BinMSD( arr, n, 63 );
    
    for( int i = 0; i < n; ++i ) {
        std::cout << arr[i] << " ";
    }

    delete [] arr;
    return 0;
}

void BinMSD( unsigned long long* arr, int n, int radix ) {
    if( n <= 1 ) {
        return;
    }
    
    if( radix < 0 ) {
        return;
    }
    
    // partition по номеру бита
    int part = partition( arr, n, radix );
    
    if( part > 0 ) {
        BinMSD( arr, part, radix - 1 );
    }
    
    if( part + 1 < n ) {
        BinMSD( arr + part, n - part, radix - 1 );
    }
}

int partition( unsigned long long* arr, int n, const int radix ) {

    int pivot = 1;
    int i = 0, j = n - 1;

    while( i <= j ) {
        while( getRadix( arr[i], radix ) < pivot && ( i < n - 1 ) ) {
            i++;
        }
        
        while( !( getRadix( arr[j], radix ) < pivot ) && ( j >= 0 ) ) {
            j--;
        }

        if( i <= j ) {
            std::swap( arr[i++], arr[j--] );
        }
    }

    return i;
}

int getRadix( const unsigned long long value, const int radix ) {
    return (value >> radix) & 1;
}