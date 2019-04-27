#include <assert.h>
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

template <class T>
struct CAvlNode {
  T Key;
  unsigned char Height;
  CAvlNode* Left;
  CAvlNode* Right;
  CAvlNode* Parent;
  
  CAvlNode() : Left(nullptr), Right(nullptr), Parent(nullptr) {}
  CAvlNode( const T& key, CAvlNode* parent = nullptr ) : Key(key), Height(1), Left(nullptr), Right(nullptr), Parent(parent) {}
  
  int GetHeight( CAvlNode<T>* node ) {
    return node == nullptr ? 0 : node->Height;
  };
  
  int GetSize( CAvlNode<T>* node ) {
    return node == nullptr ? 0 : GetSize( node->Left ) + GetSize( node->Right ) + 1;
  }
  
  int BalanceFactor( CAvlNode<T>* node ) {
    if( node == nullptr ) {
      return 0;
    }
    return GetHeight( node->Right ) - GetHeight( node->Left );
  };
  
  void FixHeight( CAvlNode<T>* node ) {
    unsigned char hl = GetHeight( node->Left );
    unsigned char hr = GetHeight( node->Right );
    node->Height = (hl > hr ? hl : hr ) + 1;
  }
};


template <class T>
class CAvlTree {
public:
  CAvlTree();
  ~CAvlTree();
  void Add( const T& key );
  void Delete( const T& key );
  int GetKStatistics( int& k );
private:
  CAvlNode<T>* root;
  CAvlNode<T>* rotateRight( CAvlNode<T>* node );
  CAvlNode<T>* rotateLeft( CAvlNode<T>* node );
  CAvlNode<T>* balance( CAvlNode<T>* node );
  const int moveNextMin( CAvlNode<T>* node );
};

template <class T>
CAvlTree<T>::CAvlTree() {
  root = nullptr;
}

template <class T>
CAvlTree<T>::~CAvlTree() {
  if( root != nullptr ) {
    std::queue<CAvlNode<T>*> q;
    q.push( root );
    while( !q.empty() ) {
      CAvlNode<T>* node = q.front();
      q.pop();
      if( node->Left != nullptr ) {
        q.push( node->Left );
      }
      if( node->Right != nullptr ) {
        q.push( node->Right );
      }
      delete node;
    }
  }
}

template <class T>
CAvlNode<T>* CAvlTree<T>::rotateRight( CAvlNode<T>* node ) {
  CAvlNode<T>* newRoot = node->Left;
  newRoot->Parent = node->Parent;
  node->Parent = newRoot;
  node->Left = newRoot->Right;
  if( node->Left != nullptr ) {
    node->Left->Parent = node;
  }
  newRoot->Right = node;
  node->FixHeight( node );
  newRoot->FixHeight( newRoot );
  return newRoot;
}

template <class T>
CAvlNode<T>* CAvlTree<T>::rotateLeft( CAvlNode<T>* node ) {
  CAvlNode<T>* newRoot = node->Right;
  newRoot->Parent = node->Parent;
  node->Parent = newRoot;
  node->Right = newRoot->Left;
  if( node->Right != nullptr ) {
    node->Right->Parent = node;
  }
  newRoot->Left = node;
  node->FixHeight( node );
  newRoot->FixHeight( newRoot );
  return newRoot;
}

template <class T>
CAvlNode<T>* CAvlTree<T>::balance( CAvlNode<T>* node ) {
  node->FixHeight( node );
  
  if( node->BalanceFactor( node ) == 2 ) {
    if( node->Right->BalanceFactor( node->Right ) < 0 ) {
      node->Right = rotateRight( node->Right );
    }
    return rotateLeft( node );
  }
  
  if( node->BalanceFactor( node ) == -2 ) {
    if( node->Left->BalanceFactor( node->Left ) > 0  ) {
      node->Left = rotateRight( node->Left );
    }
    return rotateRight( node );
  }
  return node;
}

template <class T>
void CAvlTree<T>::Add( const T& key ) {
  CAvlNode<T>* currentNode = root, *parentNode = nullptr;
  while( currentNode != nullptr ) {
    parentNode = currentNode;
    if( key < currentNode->Key ) {
      currentNode = currentNode->Left;
    } else {
      currentNode = currentNode->Right;
    }
  }
  
  CAvlNode<T>* newNode = new CAvlNode<T>( key, parentNode );
  if( parentNode == nullptr ) {
    root = newNode;
  } else if( key < parentNode->Key ) {
    parentNode->Left = newNode;
  } else {
    parentNode->Right = newNode;
  }
  
  while( parentNode != nullptr ) {
    parentNode = balance( parentNode );
    if( parentNode->Parent == nullptr ) {
      root = parentNode;
    }
    parentNode = parentNode->Parent;
  }
}

template <class T>
void CAvlTree<T>::Delete( const T& key ) {
  CAvlNode<T> *currentNode = root, *parentNode = nullptr;
  
  while( currentNode != nullptr && currentNode->Key != key ) {
    parentNode = currentNode;
    if( key < currentNode->Key ) {
      currentNode = currentNode->Left;
    } else {
      currentNode = currentNode->Right;
    }
  }
  // Не найден
  if( currentNode == nullptr ) {
    return;
  }
  // Лист или одно поддерево
  if( currentNode->Left == nullptr || currentNode->Right == nullptr ) {
    if( parentNode == nullptr ) {
      root = (currentNode->Left == nullptr ? currentNode->Right : currentNode->Left);
      return;
    }
    if( parentNode->Key > key ) {
      parentNode->Left = (currentNode->Left == nullptr ? currentNode->Right : currentNode->Left);
    } else {
      parentNode->Right = (currentNode->Left == nullptr ? currentNode->Right : currentNode->Left);
    }
    delete currentNode;
    return;
  }
  // Два поддерева. Функция удаляет min и возвращает его key.
  currentNode->Key = moveNextMin( currentNode );
  currentNode = balance( currentNode );
  while( parentNode != nullptr ) {
    parentNode = balance( parentNode );
    parentNode = parentNode->Parent;
  }
}

template <class T>
const int CAvlTree<T>::moveNextMin( CAvlNode<T>* node ) {
  CAvlNode<T> *currentNode = node->Left, *parentNode = node;
  while( currentNode->Right != nullptr ) {
    parentNode = currentNode;
    currentNode = currentNode->Right;
  }
  T nextMin = currentNode->Key;
  if( parentNode != root ) {
    parentNode->Right = nullptr;
  } else {
    parentNode->Left = nullptr;
  }
  delete currentNode;
  return nextMin;
}

template <class T>
int CAvlTree<T>::GetKStatistics( int& k ) {
  CAvlNode<T> *currentNode = root;
  while( currentNode != nullptr ) {
    int LHeight = currentNode->Left->GetSize( currentNode->Left );
    if( LHeight == k ) {
      return currentNode->Key;
    }
    
    if( LHeight < k ) {
      currentNode = currentNode->Right;
      k -= LHeight + 1;
    } else {
      currentNode = currentNode->Left;
    }
  }
  return -1;
}


int main( int argc, char const *argv[] ) {
  int n = 0;
  std::cin >> n;
  assert( n > 0 );
  
  CAvlTree<int> tree;
  for( int i = 0; i < n; ++i ) {
    int key = 0, k = 0;
    std::cin >> key >> k;
    if( key < 0 ) {
      tree.Delete( abs(key) );
    } else {
      tree.Add( key );
    }
   std::cout << tree.GetKStatistics( k ) << std::endl;
  }
  return 0;
}