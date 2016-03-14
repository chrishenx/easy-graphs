/**
 
 -- This code is an usage example of the easy-graph library --
 
 Create the dfs and bfs of a simple graph
  
 */

#include <iostream>
#include "graph.h"
#include "dot_extencion.h"

using namespace std;
using namespace easy_graphs;

int main()
{
  // A weighted and not directed graph
  Graph<int> graph(true, false, {1, 2, 3, 4});
  graph.newEdge(1,2,4);
  graph.newEdge(1,3,1);
  graph.newEdge(2,3,6);
  graph.newEdge(4,2,1);
  
  cout << "Creating DFS tree" << endl;
  Graph<int> dfs_tree = graph.dfs(1);
  cout << "Creating BFS tree" << endl;
  Graph<int> bfs_tree = graph.bfs(2);
  
  dotRepr2PNG(dfs_tree.dotRepr(), "dfs");
  dotRepr2PNG(bfs_tree.dotRepr(), "bfs");
  
  cout << endl;
  return 0;

}
