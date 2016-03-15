/**
 
 -- This code is an usage example of the easy-graph library --
 
 Produce three animations corresponding to dfs, bfs and dijkstra.
 I recomend you to have three directories created before runnig the program:
    bfs_animation
    dfs_animation
    dijkstra_animation
  
 */

#include <iostream>
#include "../include/graph.h"
#include "../include/tools/dot_extension.h"

using namespace std;
using namespace easy_graphs;

string dot_extension::dotPath = "/usr/local/bin/dot"; // In case the dot binary is not in your system path  

int main()
{
  // A weighted and not directed graph
  auto graph = Graph<char>(true, false, 
    {'a', 'b', 'c', 'd', 'e', 'f','g', 'h', 'i', 'j', 'k', 's'});

  graph.newEdge('a', 'b', 2);
  graph.newEdge('a', 'c', 3);
  graph.newEdge('a', 's', 3);
  graph.newEdge('a', 'g', 3);
  graph.newEdge('b', 'd', 3);
  graph.newEdge('d', 'c', 5);
  graph.newEdge('d', 'f', 2);
  graph.newEdge('c', 'e', 3);
  graph.newEdge('c', 'h', 4);
  graph.newEdge('h', 'g', 8);
  graph.newEdge('f', 'e', 3);
  graph.newEdge('s', 'g', 6);
  graph.newEdge('e', 'j', 3);
  graph.newEdge('j', 'i', 10);
  graph.newEdge('j', 'k', 5);
  graph.newEdge('h', 'i', 7);
  
  cout << "Creating BFS animation" << endl;
  List<string> bfs_animation = graph.bfs_animation('s'); 

  int i = 0;
  for (const string& dot_repr : bfs_animation) {
    cout << "Rendering:" << endl;
    cout << dot_repr << endl;
    dot_extension::dotRepr2JPEG(dot_repr, "bfs_animation" + to_string(i), "bfs_animation");
    cout << "Done!" << endl;
    i++;
  }
  
  cout << "\nCreating DFS animation" << endl;
  List<string> dfs_animation = graph.dfs_animation('s'); 

  i = 0;
  for (const string& dot_repr : dfs_animation) {
    cout << "Rendering:" << endl;
    cout << dot_repr << endl;
    dot_extension::dotRepr2JPEG(dot_repr, "dfs_animation" + to_string(i), "dfs_animation");
    cout << "Done!" << endl;
    i++;
  }

  cout << "\nCreating Dijkstra animation" << endl;
  List<string> dijkstra_animation = graph.dijkstra_animation('s'); 

  i = 0;
  for (const string& dot_repr : dijkstra_animation) {
    cout << "Rendering:" << endl;
    cout << dot_repr << endl;
    dot_extension::dotRepr2JPEG(dot_repr, "dijkstra_animation" + to_string(i), "dijkstra_animation");
    cout << "Done!" << endl;
    i++;
  }

  cout << endl;
  return 0;

}
