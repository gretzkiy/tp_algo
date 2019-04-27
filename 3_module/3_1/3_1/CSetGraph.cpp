#include "CSetGraph.hpp"

CSetGraph::CSetGraph( int count ) {
  adjacencySetList.resize( count );
}

CSetGraph::CSetGraph( const IGraph &graph ) {
  int count = graph.VerticesCount();
  adjacencySetList.resize( count );
  
  for( int from = 0; from < count; from++ ) {
    std::vector<int> tempVertices;
    graph.GetNextVertices( from, tempVertices );
    
    for ( auto to : tempVertices) {
      adjacencySetList[from].insert( to );
    }
  }
}

void CSetGraph::AddEdge( int from, int to ) {
  assert( from >= 0 && from < adjacencySetList.size() );
  assert( to >= 0 && to < adjacencySetList.size() );
  
  adjacencySetList[from].insert( to );
}

int CSetGraph::VerticesCount() const {
  return adjacencySetList.size();
}

void CSetGraph::GetNextVertices( int vertex, std::vector<int> &vertices ) const {
  assert( vertex >= 0 && vertex < adjacencySetList.size() );
  vertices.clear();
  
  for( auto vertice : adjacencySetList[vertex] ) {
    vertices.push_back( vertice );
  }
}

void CSetGraph::GetPrevVertices( int vertex, std::vector<int> &vertices ) const {
  assert( vertex >= 0 && vertex < adjacencySetList.size() );
  vertices.clear();
  
  for( int i = 0; i < adjacencySetList.size(); i++ ) {
    if( adjacencySetList[i].find( vertex ) != adjacencySetList[i].end() ) {
      vertices.push_back( i );
    }
  }
}
