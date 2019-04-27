// Реализовать очередь с помощью двух стеков.
// Использовать стек, реализованный с помощью динамического буфера.
// Формат выходных данных.
// В первой строке количество команд n. n ≤ 1000000.
// Каждая команда задаётся как 2 целых числа: a b.
// a = 1 - push front
// a = 2 - pop front
// a = 3 - push back
// a = 4 - pop back
// Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
// Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
// Если дана команда pop*, то число b - ожидаемое значение.
// Если команда pop вызвана для пустой структуры данных, то ожидается “-1”. 
// Формат выходных данных.
// Требуется напечатать YES - если все ожидаемые значения совпали.
// Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

#include <iostream>
#include <assert.h>

class Stack
{
public:
  Stack();
  Stack(int initial_bufsize);
  ~Stack();
  void Push(int data);
  int Pop();
  bool IsEmpty() const;
private:
  int* buffer;
  int buffer_size, size;

  // Stack(const Stack&);
};

Stack::Stack()
{
  buffer = new int[4];
  buffer_size = 4;
  size = 0;
}

Stack::Stack(int initial_bufsize)
{
  buffer = new int[initial_bufsize];
  buffer_size = initial_bufsize;
  size = 0;
}

void Stack::Push(int data)
{
  if( size <= buffer_size ) {
    buffer[size++] = data;
  } else {
    buffer_size *= 2;
    int* cpy_buffer = new int[buffer_size];
    for( int i = 0; i < size; ++i )
      cpy_buffer[i] = buffer[i];

    delete [] buffer;
    buffer = cpy_buffer;

    buffer[size++] = data;
  }
}

int Stack::Pop()
{
  assert( size > 0 );
  return buffer[--size];
}

Stack::~Stack()
{
  delete [] buffer;
}

bool Stack::IsEmpty() const
{
  return size == 0;
}

//Очередь на двух стеках.
class Queue
{
public:
  Queue();
  ~Queue();
  void Enqueue(int data);
  int Dequeue();
private:
  Stack *pushStack, *popStack; //стеки для добавления и извлечения элементов из очереди
};

Queue::Queue()
{
  pushStack = new Stack;
  popStack = new Stack;
};

Queue::~Queue()
{
  delete popStack;
  delete pushStack;
};

void Queue::Enqueue(int data)
{
  pushStack->Push(data);
}

int Queue::Dequeue()
{
  if( popStack->IsEmpty() && pushStack->IsEmpty() ) //если оба стека пустые, значит очередь пуста
    return -1;
  if( popStack->IsEmpty() )  //если стек для извлечени путой, переносим в него все элементы из другого стека
    while( !pushStack->IsEmpty() )
      popStack->Push(pushStack->Pop());
  return popStack->Pop();
}

int main(int argc, char const *argv[])
{
  int n = 0;
  std::cin >> n;
  assert( (n >= 2) && (n <= 1000000) );
  Queue queue;
  for( int i = 0; i < n; ++i ) {
    int operation = 0;
    int data = 0;
    std::cin >> operation >> data;
    switch( operation ) {
      case 2:
        //pop front
        if( data != queue.Dequeue() ) {
          std::cout << "NO";
          return 0;
        }
        break;
      case 3:
        //push back
        assert( data >= 0 );
        queue.Enqueue(data);
        break;
    }
  }
  std::cout << "YES";
  return 0;
}