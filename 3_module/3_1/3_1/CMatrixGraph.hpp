#ifndef CMatrixGraph_hpp
#define CMatrixGraph_hpp

#include "IGraph.h"

class CMatrixGraph : public IGraph {
public:
  CMatrixGraph( int count );
  CMatrixGraph( const IGraph &graph );
  
  void AddEdge( int from, int to ) override;
  
  int VerticesCount() const override;
  void GetNextVertices( int vertex, std::vector<int>& vertices ) const override;
  void GetPrevVertices( int vertex, std::vector<int>& vertices ) const override;
private:
  std::vector<std::vector<bool>> adjacencyMatrix;
};

#endif /* CMatrixGraph_hpp */
