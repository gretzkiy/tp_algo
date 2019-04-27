// Дано число N < 106 и последовательность пар целых чисел из [-2^31..2^31] длиной N.
// Построить декартово дерево из N узлов, характеризующихся парами чисел {Xi, Yi}.
// Каждая пара чисел {Xi, Yi} определяет ключ Xi и приоритет Yi в декартовом дереве.
// Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции.
// Построить также наивное дерево поиска по ключам Xi методом из задачи 2.

// 3_2. Вычислить количество узлов в самом широком слое декартового дерева
// и количество узлов в самом широком слое наивного дерева поиска.
// Вывести их разницу. Разница может быть отрицательна.


#include <assert.h>
#include <iostream>
#include <queue>
#include <vector>


template <class T>
struct CTreapNode {
  T Key;
  int Priority;
  CTreapNode* Left;
  CTreapNode* Right;
  CTreapNode() : Left(nullptr), Right(nullptr) {}
  CTreapNode( const T& key, const int& priority ) : Key(key), Priority(priority), Left(nullptr), Right(nullptr) {}
};


template <class T>
class CTreapTree {
public:
  CTreapTree();
  ~CTreapTree();
  void Add( const T& key, const int& priority );
  int MaxWidth();
private:
  void split( CTreapNode<T>* currentNode, const T& key, CTreapNode<T>*& left, CTreapNode<T>*& right );
  CTreapNode<T>* merge( CTreapNode<T>* left, CTreapNode<T>* right );
  CTreapNode<T>* root;
};

template <class T>
CTreapTree<T>::CTreapTree() {
  root = nullptr;
}

template <class T>
CTreapTree<T>::~CTreapTree() {
  if( root != nullptr ) {
    std::queue<CTreapNode<T>*> q;
    q.push( root );
    while( !q.empty() ) {
      CTreapNode<T>* node = q.front();
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
void CTreapTree<T>::split( CTreapNode<T>* currentNode, const T& key, CTreapNode<T>*& left, CTreapNode<T>*& right ) {
  if( currentNode == nullptr ) {
    left = nullptr;
    right = nullptr;
  } else if( currentNode->Key <= key ) {
    split( currentNode->Right, key, currentNode->Right, right );
    left = currentNode;
  } else {
    split( currentNode->Left, key, left, currentNode->Left );
    right = currentNode;
  }
}

template <class T>
CTreapNode<T>* CTreapTree<T>::merge( CTreapNode<T>* left, CTreapNode<T>* right ) {
  if( left == nullptr || right == nullptr ) {
    return left == nullptr ? right : left;
  }

  if( left->Priority > right->Priority ) {
    left->Right = merge( left->Right, right );
    return left;
  } else {
    right->Left = merge( left, right->Left );
    return right;
  }
}

template <class T>
void CTreapTree<T>::Add( const T& key, const int& priority ) {
  CTreapNode<T>* newNode = new CTreapNode<T>( key, priority );

  if( root == nullptr ) {
    root = newNode;
    return;
  }

  CTreapNode<T>* currentNode = root;
  CTreapNode<T>* parentNode = nullptr;

  while( currentNode != nullptr && currentNode->Priority > priority ) {
    parentNode = currentNode;
    if( key < currentNode->Key ) {
      currentNode = currentNode->Left;
    } else {
      currentNode = currentNode->Right;
    }
  }

  if( currentNode == nullptr ) {
    if( key < parentNode->Key ) {
      parentNode->Left = newNode;
    } else {
      parentNode->Right = newNode;
    }
  } else {
    split( currentNode, key, newNode->Left, newNode->Right );
    currentNode = newNode;
    if( parentNode == nullptr ) {
      root = currentNode;
    } else if( key < parentNode->Key ) {
      parentNode->Left = currentNode;
    } else {
      parentNode->Right = currentNode;
    }
  }
}

template <class T>
int CTreapTree<T>::MaxWidth() {
  int maxWidth = 0;
  std::queue<CTreapNode<T>*> layer;
  layer.push( root );
  while( !layer.empty() ) {
    int width = layer.size();
    if( width > maxWidth ) {
      maxWidth = width;
    }
    for( int i = 0; i < width; ++i ) {
      CTreapNode<T>* node = layer.front();
      layer.pop();
      if( node->Left != nullptr ) {
        layer.push( node->Left);
      }
      if( node->Right != nullptr ) {
        layer.push( node->Right );
      }
    }
  }
  return maxWidth;
}



template <class T>
struct CBinaryNode {
  T data;
  CBinaryNode* Left;
  CBinaryNode* Right;
  CBinaryNode() : Left(nullptr), Right(nullptr) {}
  CBinaryNode( const T& data ) : data(data), Left(nullptr), Right(nullptr) {}
};

template <class T>
class CBinaryTree {
public:
  CBinaryTree();
  ~CBinaryTree();
  void Add( const T& _data );
  int MaxWidth();
private:
  CBinaryNode<T>* root;
};

template <class T>
CBinaryTree<T>::CBinaryTree() {
  root = nullptr;
}

template <class T>
CBinaryTree<T>::~CBinaryTree() {
  if( root != nullptr ) {
    std::queue<CBinaryNode<T>*> q;
    q.push( root );
    while( !q.empty() ) {
      CBinaryNode<T>* node = q.front();
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
void CBinaryTree<T>::Add( const T& _data ) {
  if( root == nullptr ) {
    root = new CBinaryNode<T>( _data );
    root->Left = nullptr;
    root->Right = nullptr;
    return;
  }
  CBinaryNode<T>* parentNode = root;
  while( true ) {
    if( _data < parentNode->data ) {
      if( parentNode->Left == nullptr ) {
        break;
      } else {
        parentNode = parentNode->Left;
        continue;
      }
    } else {
      if( parentNode->Right == nullptr ) {
        break;
      } else {
        parentNode = parentNode->Right;
        continue;
      }
    }
  }
  if( _data < parentNode->data ) {
    CBinaryNode<T>* newNode = new CBinaryNode<T>( _data );
    parentNode->Left = newNode;
  } else {
    CBinaryNode<T>* newNode = new CBinaryNode<T>( _data );
    parentNode->Right = newNode;
  }
}

template <class T>
int CBinaryTree<T>::MaxWidth() {
  int maxWidth = 0;
  std::queue<CBinaryNode<T>*> layer;
  layer.push( root );
  while( !layer.empty() ) {
    int width = layer.size();
    if( width > maxWidth ) {
      maxWidth = width;
    }
    for( int i = 0; i < width; ++i ) {
      CBinaryNode<T>* node = layer.front();
      layer.pop();
      if( node->Left != nullptr ) {
        layer.push( node->Left);
      }
      if( node->Right != nullptr ) {
        layer.push( node->Right );
      }
    }
  }
  return maxWidth;
}



int main( int argc, char const *argv[] ) {
  long n = 0;
  std::cin >> n;
  assert( n > 0 );

  CBinaryTree<int> binTree;
  CTreapTree<int> treapTree;
  int key, priority;
  for( long i = 0; i < n; ++i ) {
    std::cin >> key >> priority;
    treapTree.Add( key, priority );
    binTree.Add( key );
  }

  std::cout << treapTree.MaxWidth() - binTree.MaxWidth();
  return 0;
}