#include "CMatrixGraph.hpp"

CMatrixGraph::CMatrixGraph( int count ) {
  adjacencyMatrix.resize( count );
  for( int i = 0; i < adjacencyMatrix.size(); i++ ) {
    adjacencyMatrix[i].resize( count, false );
  }
}

CMatrixGraph::CMatrixGraph( const IGraph &graph ) {
  int count = graph.VerticesCount();
  adjacencyMatrix.resize( count );
  for( int i = 0; i < adjacencyMatrix.size(); i++ ) {
    adjacencyMatrix[i].resize( count, false );
  }
  
  for( int i = 0; i < adjacencyMatrix.size(); i++ ) {
    std::vector<int> tempVertices;
    graph.GetNextVertices( i, tempVertices );
    for( auto vertex : tempVertices ) {
      adjacencyMatrix[i][vertex] = true;
    }
  }
}

void CMatrixGraph::AddEdge( int from, int to ) {
  assert( from >= 0 && from < adjacencyMatrix.size() );
  assert( to >= 0 && to < adjacencyMatrix.size() );
  adjacencyMatrix[from][to] = true;
}

int CMatrixGraph::VerticesCount() const {
  return adjacencyMatrix.size();
}

void CMatrixGraph::GetNextVertices( int vertex, std::vector<int> &vertices ) const {
  assert( vertex >= 0 && vertex < adjacencyMatrix.size() );
  vertices.clear();
  
  for( int i = 0; i < adjacencyMatrix[vertex].size(); i++ ) {
    if( adjacencyMatrix[vertex][i] ) {
      vertices.push_back( i );
    }
  }
}

void CMatrixGraph::GetPrevVertices( int vertex, std::vector<int> &vertices ) const {
  assert( vertex >= 0 && vertex < adjacencyMatrix.size() );
  vertices.clear();
  
  for(int i = 0; i < adjacencyMatrix.size(); i++) {
    if( adjacencyMatrix[i][vertex] ) {
      vertices.push_back( i );
    }
  }
}
