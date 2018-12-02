#ifndef _COLLECTION_H_
#define _COLLECTION_H_

#include <iostream>
#include <stdexcept>
#include <cmath>

template<typename T, typename P>
struct Cell {
  T info;
  P priority;

  bool operator<(const Cell<T,P>& rhs) const { return priority < rhs.priority; }
  bool operator>(const Cell<T,P>& rhs) const { return priority > rhs.priority; }

  friend std::ostream& operator<<(std::ostream& out, const Cell<T,P>& c){
    return out << c.info << " (" << c.priority << ")"; 
  }
};

template<typename T, typename P>
class PriorityQueue {
public:
  PriorityQueue(): sz(0), capacity(8), elements(new Cell<T,P>[capacity]){}
  PriorityQueue(bool min): sz(0), capacity(8), reversed(min), elements(new Cell<T,P>[capacity]){}
  PriorityQueue(const PriorityQueue<T,P>& c): sz(c.sz), capacity(c.capacity) {
    elements = new Cell<T,P>[capacity];
    reversed = c.reversed;
    for(int i = 0; i < c.sz; i++){
      elements[i] = c.elements[i];
    }
  }

  PriorityQueue<T,P>& operator=(const PriorityQueue<T,P>& c){
    Cell<T,P>* newElements = new Cell<T,P>[c.capacity];
    for(int i = 0; i < sz; i++){
          newElements[i] = c.elements[i];
    }
    
    delete[] elements;
    elements = newElements;
    sz = c.sz;
    capacity = c.capacity;
    reversed = c.reversed;

    return *this;
  }

  bool full() const{ return sz == capacity; }
  bool empty() const{ return sz == 0; }
  int size() const{ return sz; }

  void enqueue(T e, P priority){
    if(sz == capacity){
      Cell<T,P>* newElements = new Cell<T,P>[capacity * 2];
      for(int i = 0; i < sz; i++){
          newElements[i] = elements[i];
      }

      delete[] elements;
      elements = newElements;
      capacity *= 2;
    }

    elements[sz].info = e;
    elements[sz++].priority = priority;

    buildHeap();
  }

  T dequeue(){
    if(empty()) throw std::runtime_error("Empty queue!");

    T minOrMax = elements[0].info;
    elements[0] = elements[sz - 1];
    sz--;
    heapify(0, sz);

    return minOrMax;
  }

  T peek() const { 
    if(empty()) throw std::runtime_error("Empty queue!");

    return elements[0].info; 
  }  

  bool contains(T e){
    for(int i = 0; i < sz; i++) {
      if(elements[i].info == e) {
        return true;
      }
    }

    return false;
  }

  void changePriority(T e, P priority){
    for(int i = 0; i < sz; i++) {
      if(elements[i].info == e) {
        elements[i].priority = priority;
        buildHeap();
        return;
      }
    }
  }

  friend std::ostream& operator<<(std::ostream& out, const PriorityQueue<T,P>& c){
    for(int i = 0; i < c.sz; i++){
      out << c.elements[i].info << " ";
    }

    return out;
  }

  ~PriorityQueue(){
    delete[] elements;
  }
protected:
    int  sz, capacity;
    bool reversed = false;
    Cell<T,P> *elements;

    void swap(int i, int j){
      Cell<T,P> temp = elements[i];
      elements[i] = elements[j];
      elements[j] = temp;
    }

    bool lessOrGreaterThan(int i, int j){
      return (!reversed && elements[i] < elements[j]) || 
             (reversed && elements[i] > elements[j]);
    }

    void buildHeap(){
      for(int i = sz / 2 - 1; i >= 0; i--){
        heapify(i, sz);
      }
    }

    void heapify(int p, int hsz){
      int left = 2 * p + 1;
      int right = left + 1;
      int largest = p;
      if(left < hsz && lessOrGreaterThan(p , left)) {
        largest = left;
      }

      if(right < hsz && lessOrGreaterThan(largest , right)) {
        largest = right;
      }

      if(largest != p){
        swap(p, largest);
        heapify(largest, hsz);
      }
    }
};
#endif