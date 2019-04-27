#include<vector>
#include<iostream>
#include<queue>
#include<assert.h>

using std::vector;
using std::cout;
using std::queue;

struct IGraph {
  virtual ~IGraph() {}
  
  // Добавление ребра от from к to.
  virtual void AddEdge(int from, int to) = 0;

  virtual int VerticesCount() const  = 0;
  virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const = 0;
  virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const = 0;
};

class ListGraph : public IGraph {
public:
  ListGraph(int count);
  ListGraph(const IGraph& graph);
  virtual ~ListGraph();
  
  // Добавление ребра от from к to.
  virtual void AddEdge(int from, int to);

  virtual int VerticesCount() const;
  virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const;
  virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const;

private:
  vector<vector<int>> adjacencyLists;
};

ListGraph::ListGraph(int count)
{
  adjacencyLists.resize(count);
}

ListGraph::ListGraph(const IGraph& graph)
{
  adjacencyLists.resize(graph.VerticesCount());
  for( int from = 0; from < adjacencyLists.size(); from++ )
    graph.GetNextVertices(from, adjacencyLists[from]);
}

ListGraph::~ListGraph()
{
}
  
void ListGraph::AddEdge(int from, int to)
{
  assert( from >= 0 && from < adjacencyLists.size() );
  assert( to >= 0 && to < adjacencyLists.size() );
  adjacencyLists[from].push_back(to);
}

int ListGraph::VerticesCount() const
{
  return adjacencyLists.size();
}

void ListGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const
{
  assert( vertex >= 0 && vertex < adjacencyLists.size() );
  vertices = adjacencyLists[vertex];
}

void ListGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const
{
  assert( vertex >= 0 && vertex < adjacencyLists.size() );

  vertices.clear();
  for( int from = 0; from < adjacencyLists.size(); from++ )
    for( int i = 0; i < adjacencyLists[from].size(); i++ )
      if( adjacencyLists[from][i] == vertex )
        vertices.push_back(from);
}

void BFS(const IGraph& graph, int vertex, void (*visit)(int))
{
  vector<bool> visited(graph.VerticesCount(), false);
  queue<int> qu;
  qu.push(vertex);
  visited[vertex] = true;

  while( qu.size() != 0 ) {
    int current = qu.front();
    qu.pop();
    visit(current);
    vector<int> adjacentVertices;
    graph.GetNextVertices(current, adjacentVertices);
    for( int i = 0; i < adjacentVertices.size(); i++ ) {
      if( !visited[adjacentVertices[i]] ) {
        qu.push(adjacentVertices[i]);
        visited[adjacentVertices[i]] = true;
      }
    }
  }
}

int main()
{
  ListGraph graph(7);
  graph.AddEdge(0, 1);
  graph.AddEdge(0, 5);
  graph.AddEdge(1, 2);
  graph.AddEdge(1, 3);
  graph.AddEdge(1, 5);
  graph.AddEdge(1, 6);
  graph.AddEdge(3, 2);
  graph.AddEdge(3, 6);
  graph.AddEdge(4, 3);
  graph.AddEdge(5, 4);
  graph.AddEdge(5, 6);
  graph.AddEdge(6, 4);

  BFS(graph, 5, [](int vertex){ cout << vertex << " "; });
  return 0;
}