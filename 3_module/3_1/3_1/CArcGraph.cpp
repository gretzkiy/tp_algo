#include "CArcGraph.hpp"

CArcGraph::CArcGraph( int count ) {
  verticesCount = count;
}

CArcGraph::CArcGraph( const IGraph &graph ) {
  verticesCount = graph.VerticesCount();
  
  for( int from = 0; from < verticesCount; from++ ) {
    std::vector<int> tempVertices;
    graph.GetNextVertices( from, tempVertices );
    
    for ( auto to : tempVertices) {
      arcList.push_back( std::make_pair( from, to ) );
    }
  }
}

void CArcGraph::AddEdge( int from, int to ) {
  assert( from >= 0 && from < verticesCount );
  assert( to >= 0 && to < verticesCount );
  
  arcList.push_back( std::make_pair( from, to ) );
}

int CArcGraph::VerticesCount() const {
  return verticesCount;
}

void CArcGraph::GetNextVertices( int vertex, std::vector<int> &vertices ) const {
  assert( vertex >= 0 && vertex < verticesCount );
  vertices.clear();
  
  for( auto arc : arcList ) {
    if( vertex == arc.first ) {
      vertices.push_back( arc.second );
    }
  }
}

void CArcGraph::GetPrevVertices( int vertex, std::vector<int> &vertices ) const {
  assert( vertex >= 0 && vertex < verticesCount );
  vertices.clear();
  
  for( auto arc : arcList ) {
    if( vertex == arc.second ) {
      vertices.push_back( arc.first );
    }
  }
}
