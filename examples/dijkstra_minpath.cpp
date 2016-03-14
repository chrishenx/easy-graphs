/**
 
 -- This code is an usage example of the easy-graph library --
 
 Compute the minimun path from one vertex to another on a simple net. 
 
 */

#include <iostream>
#include "../include/graph.h"
#include "../include/tools/dot_extencion.h"

using namespace std;
using namespace easy_graphs;

int main() {
  auto grafo = Graph<char>(true, false, 
    {'a', 'b', 'c', 'd', 'e', 'f','g', 'h', 'i', 'j', 'k', 's'});

  grafo.newEdge('a', 'b', 2);
  grafo.newEdge('a', 'c', 3);
  grafo.newEdge('a', 's', 3);
  grafo.newEdge('a', 'g', 3);
  grafo.newEdge('s', 'g', 6);
  grafo.newEdge('b', 'd', 3);
  grafo.newEdge('d', 'c', 5);
  grafo.newEdge('d', 'f', 2);
  grafo.newEdge('c', 'e', 3);
  grafo.newEdge('c', 'h', 4);
  grafo.newEdge('h', 'g', 8);
  grafo.newEdge('f', 'e', 3);
  grafo.newEdge('e', 'j', 3);
  grafo.newEdge('j', 'i', 10);
  grafo.newEdge('j', 'k', 5);
  grafo.newEdge('h', 'i', 7);

  grafo.dijkstra('s');
  dotRepr2PNG(grafo.dotRepr(GraphDrawingMode::SHOW_DISTANCES), "grafo1_dijkstra");

  char source = 's';
  char target = 'f';

  int distance = 0;
  auto path = grafo.dijkstra(source, target, distance);

  if (distance > 0) {
    cout << "Path from " << source << " to " << target << ": " << endl;
    cout << path << endl;
    cout << "Distance between vertices: " << distance << endl;
  } else if (distance == -1){
    cout << "There is no path between " << source << " and " << target << endl;
  } else {
    cout << "Someone of the vertices does not exist" << endl;
  }

  return 0;
}