include <iostream>
#include <string>
#include "graph.h"

using namespace std;
Graph * graph;

// Part 1 : Find the connected components and the bridge                                                                                                                                                                                                                                                                                                                    

void part1() {
  int vertices = -1, routes = -1;
  cin >> vertices;
  cin >> routes;
  if (vertices != -1 && routes != -1){
  graph = new Graph(vertices,routes);
  string first;
  string second;
  double weight;
  for(int i = 0; i  < graph->getNumRoutes(); i++ ){
    cin >> first>>second >> weight;
    graph->addRoute(first,second,weight);
  }
  graph->analyseGraph();
  }
}

// Part 2 :  Find a ticket using Dijkstra                                                                                                                                                                                                                                                                                                                                   
void part2() {
  int vertices, routes;
  cin >> vertices;
  cin >> routes;
  graph = new Graph(vertices,routes);
  string first;
  string second;
  double weight;
  for(int x = 0; x  < graph->getNumRoutes(); x++ ){
    cin >> first >> second >> weight;
    graph->addRoute(first,second,weight);
  }
  string src, dest;
  while(true){
    cin >> src;
    if(src.compare("END")==0){
      return;
    }
    cin >> dest;
    graph->findCost(src, dest);
  }

}

// Part 3 :Try to do a tour of all cities                                                                                                                                                                                                                                                                                                                                   
void part3() {
  int vertices, routes;
  cin >> vertices;
  cin >> routes;
  graph = new Graph(vertices,routes);
  string first;
  string second;
  double weight;
  for(int i = 0; i  < graph->getNumRoutes(); i++ ){
    cin >> first >> second  >> weight;
    graph->addRoute(first,second,weight);
  }
  string root;
  cin >> root;
  graph->eulerianTour(root);
}

int main()
{
  double cmd;
  cin >> cmd;
  if(cmd == 1){
    part1();
  }
  else if(cmd == 2){
    part2();
  }
  else if(cmd == 3){
    part3();
  }
  return 0;
}
