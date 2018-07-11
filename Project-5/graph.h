ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include<list>
using namespace std;

class Graph
{
 private:
  int numRoutes;
  int numVertices;
  double weight;
  vector<string> conversionTable;
  int stringToIndex(string );
  string indexToString(int);
  int indexedCities;
  list<pair<int, double>> * adjList;
  list<int> *adj;
  void connectedComponents();
  void DFSHelper(int v, bool visited[]);
  int connected;
  vector<pair<int,int>> separationEdgesList;
  void bridge();
  void bridgeUtil(int u, bool visited[], int disc[], int low[], int parent[]);
  int separationEdges;
  vector<pair<double, int>> Dijkstra(int src, int destination);
  vector<int> primMST();
  void DFSUtil(int v, bool visited[]);
  bool isConnected();
  int isEulerian();
  void EulerDFS(int source);
  void EulerDFSHelper(int source, bool visitedNodes[]);
  int checkPossible(int source, int dest);


 public:

  int getNumCities();
  int getNumRoutes();

  Graph(int, int);
  // Create the graph                                                                                                                                                                                                                                                                                                                                                       
  void addRoute(string, string, double);

  //part 1: Find the connected components and the bridges                                                                                                                                                                                                                                                                                                                   
  void analyseGraph();


  // Part 2: Find a ticket using Dijkstra                                                                                                                                                                                                                                                                                                                                   
  void findCost(const string &source, const string &destination);

  // Part 3: Try to do a tour of all cities                                                                                                                                                                                                                                                                                                                                 
  void eulerianTour(string);  // NOTE : If necessary, you can change the parameters to this function.                                                                                                                                                                                                                                                                       

};

#endif
