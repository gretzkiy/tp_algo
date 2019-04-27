#include <iostream>
#include "CListGraph.hpp"
#include "CMatrixGraph.hpp"
#include "CSetGraph.hpp"
#include "CArcGraph.hpp"
#include <queue>

void BFS( const IGraph& graph, int vertex, void (*visit)(int) ) {
  std::vector<bool> visited( graph.VerticesCount(), false );
  std::queue<int> qu;
  qu.push( vertex );
  visited[vertex] = true;
  
  while( qu.size() != 0 ) {
    int current = qu.front();
    qu.pop();
    visit( current );
    std::vector<int> adjacentVertices;
    graph.GetNextVertices( current, adjacentVertices );
    for( int i = 0; i < adjacentVertices.size(); i++ ) {
      if( !visited[adjacentVertices[i]] ) {
        qu.push( adjacentVertices[i] );
        visited[adjacentVertices[i]] = true;
      }
    }
  }
}

int main() {
  CListGraph graph1List( 7 );
  graph1List.AddEdge( 0, 1 );
  graph1List.AddEdge( 0, 5 );
  graph1List.AddEdge( 1, 2 );
  graph1List.AddEdge( 1, 3 );
  graph1List.AddEdge( 1, 5 );
  graph1List.AddEdge( 1, 6 );
  graph1List.AddEdge( 3, 2 );
  graph1List.AddEdge( 3, 6 );
  graph1List.AddEdge( 4, 3 );
  graph1List.AddEdge( 5, 4 );
  graph1List.AddEdge( 5, 6 );
  graph1List.AddEdge( 6, 4 );
  std::cout << "Original graph:" << std::endl;
  BFS( graph1List, 5, [](int vertex){ std::cout << vertex << " "; } );
  CMatrixGraph graph1Matrix( graph1List );
  CSetGraph graph1Set( graph1Matrix );
  CArcGraph graph1Arc( graph1Set );
  std::cout << std::endl << "Copied graph:" << std::endl;
  BFS( graph1Arc, 5, [](int vertex){ std::cout << vertex << " "; } );
  std::cout << std::endl;
  return 0;
}
