#include <iostream>
#include <string>
#include "graph.h"
#include <list>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <bits/stdc++.h>
#define INFI 1000000

using namespace std;
typedef pair<double, double> dPair;

/*Graph class for use in Project 5.                                                                                                                                                                                                                                                                                                                                         
                                                                                                                                                                                                                                                                                                                                                                            
  This provided code does not include any specific data structure                                                                                                                                                                                                                                                                                                           
  for storing a graph, only a list of methods that will be called                                                                                                                                                                                                                                                                                                           
  from main. Based on the project handout and the lecture slides,                                                                                                                                                                                                                                                                                                           
  select a method for storing the graph and implement it here.                                                                                                                                                                                                                                                                                                              
*/


Graph::Graph(int Vertices, int routes) {
  separationEdges = 0;
  indexedCities = 0;
  numVertices = Vertices;
  numRoutes = routes;
  conversionTable.resize(numVertices);
  connected = 0;
  adjList = new list<pair<int, double>>[numVertices];
  adj = new list<int>[numVertices];

}

void Graph::analyseGraph(){
  connectedComponents();
  cout << connected << endl;
  bridge();
  cout << separationEdges << endl;;
  sort(separationEdgesList.begin(), separationEdgesList.end());
  for(int x = 0; x < separationEdgesList.size(); x++){
    if (indexToString(separationEdgesList[x].first) < (indexToString(separationEdgesList[x].second))){
      cout << indexToString(separationEdgesList[x].first) << " " << indexToString(separationEdgesList[x].second) << endl;
    } else {
      cout << indexToString(separationEdgesList[x].second) << " " << indexToString(separationEdgesList[x].first) << endl;
    }
  }
}

void Graph::addRoute(string u, string v, double weight){
  int x = stringToIndex(u);
  int y = stringToIndex(v);
  adjList[x].push_back(make_pair(y, weight));
  adjList[y].push_back(make_pair(x, weight));
}


void Graph::bridge() {
  bool *visited = new bool[numVertices];
  int *disc = new int[numVertices];
  int *low = new int[numVertices];
  int *parent = new int[numVertices];
  for (int i = 0; i < numVertices; i++) {
    parent[i] = -1;
    visited[i] = false;
  }
  for (int i = 0; i < numVertices; i++){
    if (visited[i] == false){
      bridgeUtil(i, visited, disc, low, parent);
    }
  }
}

void Graph::bridgeUtil(int u, bool visited[], int disc[], int low[], int parent[]){
  static int time = 0;
  visited[u] = true;
  disc[u] = low[u] = ++time;
  list<pair<int, double>>::iterator i;
  for (i = adjList[u].begin(); i != adjList[u].end(); ++i) {
    int v = (*i).first;
    if (!visited[v]) {
      parent[v] = u;
      bridgeUtil(v, visited, disc, low, parent);
      low[u]  = min(low[u], low[v]);
      if (low[v] > disc[u]){
        separationEdgesList.push_back(make_pair(u,v));
        separationEdges++;
      }


    } else if (v != parent[u]) {
      low[u]  = min(low[u], disc[v]);
    }
  }
}
void Graph::DFSHelper(int v, bool visited[]){
  visited[v] = true;
  list<pair<int, double>>::iterator i;
  for (i = adjList[v].begin(); i != adjList[v].end(); ++i){
    int a = (*i).first;
    if (!visited[a]){
      DFSHelper(a, visited);
    }
  }
}

void Graph::connectedComponents(){
  bool * visited = new bool[numVertices];
  for(int i = 0; i < numVertices; i++){
    visited[i] = false;
  }
  for (int i = 0; i < numVertices; i++){
    if (visited[i] == false){
      connected++;
      DFSHelper(i, visited);
    }
  }
}


int Graph::stringToIndex(string city){
  int y;
  for(int i = 0; i < indexedCities; i++){
    if(conversionTable[i].compare(city) == 0){
      return i;
    }
  }
  conversionTable[indexedCities] = city;
  y = indexedCities;
  indexedCities++;
  return y;
}

string Graph::indexToString(int num){
  return conversionTable[num];
}

int Graph::getNumCities(){
  return numVertices;
}

int Graph::getNumRoutes(){
  return numRoutes;
}
int Graph::checkPossible(int src, int dest){
  bool * visit = new bool[numVertices];
  for (int i = 0; i < numVertices; i++){
    visit[i] = false;
  }
  DFSHelper(src, visit);
  if (visit[dest] == false){
    return 0;
  }
  return 1;
}

void Graph::findCost(const string &src, const string &dest){
  int x = stringToIndex(src);
  int y = stringToIndex(dest);
  if (checkPossible(x, y) == 0){
    cout << "not possible" << endl;
    return;
  }
  vector<pair<double, int>> temp = Dijkstra(x, y);
  double path = temp[y].first;
  string output = dest;
  int vertex = y;
  while(temp[vertex].second != x){
    output = indexToString(temp[vertex].second) +  " " + output;
    vertex = temp[vertex].second;
  }
  output = src + " " + output;
  cout << output << " ";
  printf("%.2f\n", path);
}

vector<pair<double, int>> Graph::Dijkstra(int src, int dest){
  set<pair<int, int>> setFren;
  vector<pair<double, int>> dist;
  dist.resize(numVertices);
  for (int i = 0; i < numVertices; i++){
    dist[i].first = INFI;
    dist[i].second = -1;
  }
  setFren.insert(make_pair(0, src));
  dist[src].first = 0;
  dist[src].second = src;

  while (!setFren.empty()){
    pair <int, int> temp = *(setFren.begin());
    setFren.erase(setFren.begin());
    int u = temp.second;
    list<pair<int, double>>::iterator i;
    for (i = adjList[u].begin(); i != adjList[u].end(); ++i){
      int v = (*i).first;
      double weight = (*i).second;
      if (dist[v].first > dist[u].first + weight){
        if (dist[v].first != INFI){
          setFren.erase(setFren.find(make_pair(dist[v].first, v)));
        }
        dist[v].first = dist[u].first + weight;
        dist[v].second = u;
        setFren.insert(make_pair(dist[v].first, v));
      }
    }

  }
  return dist;
}

vector<int> Graph::primMST(){
  priority_queue< pair<double,double>, vector <pair<double,double>> , greater<pair<double,double>> > pq;
  int src = 0;
  vector<int> key(numVertices, INFI);
  vector<int> parent(numVertices, -1);
  vector<bool> inMST(numVertices, false);
  pq.push(make_pair(0,src));
  key[src] = 0;
  while (!pq.empty()){
    int u = pq.top().second;
    pq.pop();
    inMST[u] = true;
    list< pair<int, double> >::iterator i;
    for (i = adjList[u].begin(); i != adjList[u].end(); i++){
      int v = (*i).first;
      double weight = (*i).second;
      if (inMST[v] == false && key[v] > weight){
        key[v] = weight;
        pq.push(make_pair(key[v], v));
        parent[v] = u;
      }
    }
  }
  return parent;
}
void Graph::eulerianTour(string city){
  if (isEulerian() == 0){
    cout << "not possible" << endl;
    return;
  }
  vector<int> edges = primMST();
  for (int i = 1; i < numVertices; i++){
    adj[i].push_back(edges[i]);
    adj[edges[i]].push_back(i);
  }
  int in = stringToIndex(city);
  EulerDFS(in);
}
void Graph::DFSUtil(int v, bool visited[]){
  visited[v] = true;
  list<pair<int, double>>::iterator i;
  for (i = adjList[v].begin(); i != adjList[v].end(); ++i){
    if (!visited[(*i).first]){
      DFSUtil((*i).first, visited);
    }
  }
}
void Graph::EulerDFS(int src){
  bool *visitedNodes = new bool[numVertices];
  for (int i = 0; i < numVertices; i++){
    visitedNodes[i] = false;
  }
  EulerDFSHelper(src, visitedNodes);
}
void Graph::EulerDFSHelper(int src, bool nodes[]) {
  nodes[src] = true;
  cout << indexToString(src) << endl;
  vector<int> temp;
  list<int>::iterator i;
  for (i = adj[src].begin(); i != adj[src].end(); i++){
    temp.push_back(*i);
  }
  for (int i = 0; i < temp.size()-1; i++){
    for (int j = 0; j < temp.size()-i-1; j++){
      if (indexToString(temp[j]).compare(indexToString(temp[j+1])) > 0){
        int num = temp[j];
        temp[j] = temp[j+1];
        temp[j+1] = num;
      }
    }
  }
  for(int i = 0; i < temp.size(); i++){
    if (!nodes[temp[i]]){
      EulerDFSHelper(temp[i], nodes);
    }
  }
}
int Graph::isEulerian(){
  bool *visited = new bool[numVertices];
  int i;
  for (i = 0; i < numVertices; i++){
    visited[i] = false;
  }
  for (i = 0; i < numVertices; i++){
    if (adjList[i].size() != 0){
      break;
    }
  }
  if (i == numVertices){
    return 1;
  }
  DFSUtil(i, visited);
  for (i = 0; i < numVertices; i++){
    if (visited[i] == false && adjList[i].size() > 0){
      return 0;
    }
  }
  return 1;
}
