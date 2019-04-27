#ifndef CListGraph_h
#define CListGraph_h

#include "IGraph.h"

class CListGraph : public IGraph {
public:
  CListGraph( int count );
  CListGraph( const IGraph& graph );
  
  void AddEdge( int from, int to ) override;
  
  int VerticesCount() const override;
  void GetNextVertices(int vertex, std::vector<int>& vertices) const override;
  void GetPrevVertices(int vertex, std::vector<int>& vertices) const override;
  
private:
  std::vector<std::vector<int>> adjacencyLists;
};

#endif /* CListGraph_hpp */
