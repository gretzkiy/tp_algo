// Дано число N < 10^6 и последовательность целых чисел из [-2^31..2^31] длиной N.
// Требуется построить бинарное дерево, заданное наивным порядком вставки.
// Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
// то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
// Рекурсия запрещена.
// Выведите элементы в порядке level-order (по слоям, “в ширину”).


#include <assert.h>
#include <iostream>
#include <queue>
#include <vector>

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
  std::vector<T> TraversBFS();
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
  CBinaryNode<T>* newNode = new CBinaryNode<T>( _data );
  if( _data < parentNode->data ) {
    parentNode->Left = newNode;
  } else {
    parentNode->Right = newNode;
  }
}

template <class T>
std::vector<T> CBinaryTree<T>::TraversBFS() {
  std::vector<T> v;
  v.resize(0);
  if( root == nullptr ) {
    return v;
  }
  std::queue<CBinaryNode<T>*> q;
  q.push( root );
  while( !q.empty() ) {
    CBinaryNode<T>* node = q.front();
    q.pop();
    v.push_back( node->data );
    if( node->Left != nullptr ) {
      q.push( node->Left );
    }
    if( node->Right != nullptr ) {
      q.push( node->Right );
    }
  }
  return v;
}


int main( int argc, char const *argv[] ) {
  CBinaryTree<int> tree;
  long n = 0;
  std::cin >> n;
  assert( n > 0 );
  for( int i = 0; i < n; ++i ) {
    int data = 0;
    std::cin >> data;
    tree.Add( data );
  }
  std::vector<int> v = tree.TraversBFS();
  for( auto node : v )
    std::cout << node << " ";
  return 0;
}