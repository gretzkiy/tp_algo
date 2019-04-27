#ifndef CArcGraph_hpp
#define CArcGraph_hpp

#include "IGraph.h"
#include <utility>

class CArcGraph : public IGraph {
public:
  CArcGraph( int count );
  CArcGraph( const IGraph &graph );
  
  void AddEdge( int from, int to ) override;
  
  int VerticesCount() const override;
  
  void GetNextVertices( int vertex, std::vector<int>& vertices ) const override;
  void GetPrevVertices( int vertex, std::vector<int>& vertices ) const override;
private:
  int verticesCount;
  std::vector<std::pair<int, int>> arcList;
};

#endif /* CArcGraph_hpp */
