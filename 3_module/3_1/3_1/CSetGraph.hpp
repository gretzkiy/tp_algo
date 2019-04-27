#ifndef CSetGraph_hpp
#define CSetGraph_hpp

#include "IGraph.h"
#include <unordered_set>

class CSetGraph : public IGraph {
public:
  CSetGraph( int count );
  CSetGraph( const IGraph &graph );
  
  void AddEdge( int from, int to ) override;
  
  int VerticesCount() const override;
  
  void GetNextVertices( int vertex, std::vector<int>& vertices ) const override;
  void GetPrevVertices( int vertex, std::vector<int>& vertices ) const override;
private:
  std::vector<std::unordered_set<int>> adjacencySetList;
};

#endif /* CSetGraph_hpp */
