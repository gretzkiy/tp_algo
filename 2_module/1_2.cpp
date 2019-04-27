#include <assert.h>
#include <iostream>
#include <vector>
#include <string>

const double LoadFactor = 0.75;
const int GrowFactor = 2;
const int DefaultSize = 8;

int Hash( const std::string& key, int tableSize ) {
  int hash = 0;
  for( int i = 0; i < key.size(); i++ )
    hash = (hash * 31 + key[i]) % tableSize;
  return hash;
}

template <class T>
class CHashTable {
public:
  CHashTable( T _delSign, T _nilSign, int size = DefaultSize );
  ~CHashTable();
  bool Add( const T& key );
  bool Has( const T& key );
  bool Delete( const T& key );

private:
  std::vector<T> table;
  int keysCount;
  void growTable();
  T nilSign, delSign;
};

template <class T>
CHashTable<T>::CHashTable( T _delSign, T _nilSign, int size ) {
  assert( size > 0 );
  nilSign = _nilSign;
  delSign = _delSign;
  table.resize( size, _nilSign );
  keysCount = 0;
}

template <class T>
CHashTable<T>::~CHashTable() {}

template <class T>
bool CHashTable<T>::Add( const T& key ) {
  if( double( keysCount )  >= table.size() * LoadFactor ) {
    growTable();
  }

  int hash = Hash( key, table.size() );
  int m = table.size();
  int firstDelPos = -1;
  int index = hash;
  for( int i = 0; i < m; ++i ) {
    index = ( index + i) % m;
    if( table[index] == delSign && firstDelPos == -1 ) {
      firstDelPos = index;
    }
    if( table[index] == nilSign ) {
      if( firstDelPos != -1 ) {
        table[firstDelPos] = key;
        keysCount++;
        return true;
      } else {
        table[index] = key;
        keysCount++;
        return true;
      }
    }
    if( table[index] == key ) {
      return false;
    }
  }
  table[firstDelPos] = key;
  keysCount++;
  return true;
}

template <class T>
bool CHashTable<T>::Has( const T& key ) {
  int hash = Hash( key, table.size() );
  int m = table.size();
  int index = hash;
  for( int i = 0; i < m; ++i ) {
    index = ( index + i) % m;
    if( table[index] == nilSign ) {
      return false;
    }
    if( table[index] == key ) {
      return true;
    }
  }
  return false;
}

template <class T>
bool CHashTable<T>::Delete( const T& key ) {
  int m = table.size();
  int hash = Hash( key, m );
  int index = hash;
  for( int i = 0; i < m; ++i ) {
    index = ( index + i) % m;
    if( table[index] == nilSign ) {
      return false;
    }
    if( table[index] == key ) {
      table[index] = delSign;
      keysCount--;
      return true;
    }
  }
  return false;
}

template <class T>
void CHashTable<T>::growTable() {
  std::vector<T> newTable;
  newTable.resize( GrowFactor * table.size(), nilSign );
  int m = newTable.size();
  for( int i = 0; i < table.size(); ++i ) {
    if( table[i] == delSign || table[i] == nilSign ) {
      continue;
    }

    int newHash = Hash( table[i], m );
    int index = newHash;
    for( int j = 0; j < m; ++j ) {
      index = ( index + j) % m;
      if( newTable[index] == nilSign ) {
        newTable[index] = table[i];
        break;
      }
    }
  }
  table = newTable;
}


int main(int argc, char const *argv[])
{
  CHashTable<std::string> hashTable( "DEL", "NIL" );
  char operation;
  std::string word;
  while( std::cin >> operation >> word ) {
    if( operation == '+' )
      std::cout << (hashTable.Add( word ) ? "OK" : "FAIL") << std::endl;
    if( operation == '-' )
      std::cout << (hashTable.Delete( word ) ? "OK" : "FAIL") << std::endl;
    if( operation == '?' )
      std::cout << (hashTable.Has( word ) ? "OK" : "FAIL") << std::endl;
  }
  return 0;
}