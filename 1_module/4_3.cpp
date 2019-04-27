// На вокзале есть некоторое количество тупиков, куда прибывают электрички.
// Этот вокзал является их конечной станцией.
// Дано расписание движения электричек, в котором для каждой электрички указано время ее прибытия,
// а также время отправления в следующий рейс.
// Электрички в расписании упорядочены по времени прибытия.
// Когда электричка прибывает, ее ставят в свободный тупик с минимальным номером.
// При этом если электричка из какого-то тупика отправилась в момент времени X,
// то электричку, которая прибывает в момент времени X, в этот тупик ставить нельзя,
// а электричку, прибывающую в момент X+1 — можно.
// В данный момент на вокзале достаточное количество тупиков для работы по расписанию.
// Напишите программу, которая по данному расписанию определяет,
// какое минимальное количество тупиков требуется для работы вокзала.
// Формат входных данных. Вначале вводится n - количество электричек в расписании.
// Затем вводится n строк для каждой электрички, в строке - время прибытия и время отправления.
// Время - натуральное число от 0 до 10^9. Строки в расписании упорядочены по времени прибытия.
// Формат выходных данных. Натуральное число - минимальное количеством тупиков.
// Максимальное время: 50мс, память: 5Мб.

// возвращение объекта const &
#include <iostream>
#include <assert.h>

#define INITIAL_BUFFER_SIZE 4;

struct Train
{
  int arrivalTime, departureTime;
  Train() : arrivalTime(0), departureTime(0) {}
  Train( int _arrivalTime, int _departureTime ) {
    arrivalTime = _arrivalTime; 
    departureTime = _departureTime;
  }
};

bool operator < ( const Train& l, const Train& r) {
  return l.departureTime < r.departureTime;
}

bool operator >= ( const Train& l, const Train& r) {
  return l.departureTime >= r.departureTime;
}

class CPriorityQueue
{
public:
  CPriorityQueue();
  CPriorityQueue( const Train* array, int n );
  ~CPriorityQueue();
  bool IsEmpty();
  void Enqueue( const Train& train );
  const Train& Dequeue();
  const Train& ReadTop();
  int GetSize();
private:
  Train* buffer;
  int bufferSize, size;
  void bufferGrow();
  void swap( Train& val1, Train& val2 );
  void siftDown( int i );
  void siftUp( int i );
  CPriorityQueue( const CPriorityQueue& obj ) = delete;
};

CPriorityQueue::CPriorityQueue() {
  bufferSize = INITIAL_BUFFER_SIZE;
  buffer = new Train[bufferSize];
  size = 0;
}

CPriorityQueue::CPriorityQueue( const Train* array, int n ) {
  size = n;
  bufferSize = n;

  buffer = new Train[bufferSize];
  for( int i = 0; i < size; ++i )
    buffer[i] = array[i];

  for( int i = size / 2 - 1; i >= 0; --i ) {
    siftDown(i);
  }
}

CPriorityQueue::~CPriorityQueue() {
  delete [] buffer;
}

void CPriorityQueue::bufferGrow() {
  bufferSize *= 2;
  Train* cpy_buffer = new Train[bufferSize];
  for( int i = 0; i < size; ++i )
    cpy_buffer[i] = buffer[i];

  delete [] buffer;
  buffer = cpy_buffer;
}

void CPriorityQueue::swap(Train& val1, Train& val2) {
  Train tmp = val1;
  val1 = val2;
  val2 = tmp;
}

bool CPriorityQueue::IsEmpty() {
  return size == 0;
}

void CPriorityQueue::siftDown(int i) {
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  int largest = i;
  if( left < size && buffer[left] < buffer[i] ) //Поезд, отправляющийся раньше, имеет бОльший приоритет
    largest = left;
  if( right < size && buffer[right] < buffer[largest] )
    largest = right;
  if( largest != i ) {
    swap( buffer[i], buffer[largest] );
    siftDown(largest);
  }
}

void CPriorityQueue::siftUp(int i) {
  while( i > 0 ) {
    int parent = (i - 1) / 2;
    if( buffer[i] >= buffer[parent] ) //если приоритет меньше, чем у родительского, значит дерево уже является кучей
      return;
    swap(buffer[i], buffer[parent]);
    i = parent;
  }
}

void CPriorityQueue::Enqueue(const Train& train) {
  if( size == bufferSize )
    bufferGrow();
  buffer[size++] = train;
  siftUp(size - 1); //ставим последний добавленный элемент на место, продвигая его вверх
}

const Train& CPriorityQueue::Dequeue() {  //извлекаем элемент с наивысшим приоритетом
  Train result = buffer[0]; 
  buffer[0] = buffer[--size]; //ставим вместо корня последний элемент и уменьшаем size
  if( !IsEmpty() )  //восстанавливаем свойства кучи
    siftDown(0);
  return result;
}

const Train& CPriorityQueue::ReadTop() { //"просмотр" корневого элемента
  return buffer[0];
}

int CPriorityQueue::GetSize() {
  return size;
}

int main(int argc, char const *argv[])
{
  int n = 0;
  int maxTrains = 0; //маскимальное количество поездов, одновременно находящихся на вокзале
  std::cin >> n;
  assert( n >= 0 );
  CPriorityQueue schedule;
  for( int i = 0; i < n; ++i )
  {
    Train train;
    std::cin >> train.arrivalTime >> train.departureTime;
    assert( train.arrivalTime >= 0 && train.departureTime >= 0 );

    if( !schedule.IsEmpty() ) { //удаляем из очереди все поезда, которые уже уехали к моменту train.arrivalTime
      while( !schedule.IsEmpty() && schedule.ReadTop().departureTime < train.arrivalTime )
        schedule.Dequeue();
    }

    schedule.Enqueue(train); //добавляем прибывший поезд

    int currentTrains = schedule.GetSize();
    if( currentTrains > maxTrains ) {
      maxTrains = currentTrains;
    }
  }
  std::cout << maxTrains;
  return 0;
}