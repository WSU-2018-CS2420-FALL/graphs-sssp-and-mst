#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cfloat>
#include "linked_list.h"
#include "linked_queue.h"
#include "priority_queue.h"

struct Edge {
  int from, to;
  double weight;

  Edge() = default;
  Edge(int v, int u, double w = 0.0): from(v), to(u), weight(w){}
  friend std::ostream& operator<<(std::ostream& out, const Edge& e){
    return out << e.to;
  }
};

template <typename T>
class Graph{
public:
  Graph(int sz): size(sz), adjLists(new LinkedList<Edge>[sz]()), vertices(new T[sz]()){}

  bool empty() const {
    return size == 0;
  }

  void setVertex(int v, T data){
    vertices[v] = data;
  }

  void addEdge(Edge e){
    adjLists[e.from].insertFirst(e);
  }

  void addEdge(int v, int u, double w = 0.0){
    Edge e(v, u, w);
    adjLists[v].insertFirst(e);
  }

  void print() const {
    std::cout << size << std::endl;
    for(int i = 0; i < size; i++){
      std::cout << i << ": " ;
      adjLists[i].print();
      std::cout << std::endl;
    }
  }

  LinkedList<Edge>* getAdjLists() const{
    return adjLists;
  }

  T* getVertices() const {
    return vertices;
  }

  void minimumSpanningTree(Graph<T>* &mst){
    //TODO
  }

  void shortestPath(int s, int d, Graph<T>* &path){
    //TODO
  }

  void shortestPath(int s, double* &distTo, int* & pred){
    //TODO
  }

  void depthFirstTraversal(){
    bool* visited = new bool[size]();

    for(int i = 0; i < size; i++){
      if(!visited[i]){
        depthFirstTraversal(i, visited);
      }
    }

    delete[] visited;
  }

  void breadthFirstTraversal(){
    LinkedQueue<int> queue;
    bool* visited = new bool[size]();

    for(int i = 0; i < size; i++){
      if(!visited[i]){
        queue.enqueue(i);
        visited[i] = true;
        std::cout << vertices[i] << " ";

        while(!queue.empty()){
          int u = queue.peekFront();
          queue.dequeue();
          
          for(LinkedListIterator<Edge> it = adjLists[u].begin(); it != adjLists[u].end(); ++it){
            int w = (*it).to;
            if(!visited[w]){
              queue.enqueue(w);
              visited[w] = true;
              std::cout << vertices[w] << " ";
            }
          }
        }
      }
    }

    delete[] visited;
  }

private:
  int size;
  LinkedList<Edge>* adjLists;
  T* vertices;

  void depthFirstTraversal(int v, bool* visited){
    visited[v] = true;
    std::cout << vertices[v] << " ";

    for(LinkedListIterator<Edge> it = adjLists[v].begin(); it != adjLists[v].end(); ++it){
      int u = (*it).to;
      if(!visited[u]){
        depthFirstTraversal(u, visited);
      }
    }
  }
};


#endif