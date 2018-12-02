#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "graph.h"

using namespace std;

void createGraph(Graph<int>* &g) {
  ifstream file("../graph.txt");
  int size;
  file >> size;
  file.ignore();
  g = new Graph<int>(size);

  string line;
  while(getline(file, line)){
    stringstream ss;
    ss << line;
    int v, u;
    double w;
    char trash;

    ss >> v >> trash;
    while( ss >> u >> trash >> w >> trash){
      g->setVertex(v, v);
      g->addEdge(v, u, w);
    }

  }
  file.close();
}

int main(){
  Graph<int>* g;
  createGraph(g);
  g->print();

  Graph<int>* sp;
  g->shortestPath(0, 2, sp);
  sp->print();

  Graph<int>* mst;
  g->minimumSpanningTree(mst);
  mst->print();

  delete g;

  return 0;
}