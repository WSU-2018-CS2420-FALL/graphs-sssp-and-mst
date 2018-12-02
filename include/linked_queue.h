#ifndef _LINKED_QUEUE_H_
#define _LINKED_QUEUE_H_
 
#include <iostream>
#include <cassert>
#include "linked_list.h"

template <typename T>
class LinkedQueue {
public:
  LinkedQueue(): front(nullptr), rear(nullptr){}
  LinkedQueue(const LinkedQueue<T>& q){ copy(q); }
  ~LinkedQueue() { destroy(); }

  const LinkedQueue<T>& operator=(const LinkedQueue<T>& q){
    destroy();
    return copy(q);
  }

  bool empty() const { return(front == nullptr); } 
  bool full() const { return false; }

  LinkedListIterator<T> begin() {
    LinkedListIterator<T> temp(front);
    return temp;
  }

  LinkedListIterator<T> end() {
    LinkedListIterator<T> temp(nullptr);
    return temp;
  }

  friend std::ostream& operator<<(std::ostream& out, LinkedQueue& q){
    for(T e : q){
      std::cout << e << std::endl;
    }

    return out;
  }

  void enqueue(const T& newElement) {
    Node<T> *newNode  = new Node<T>(newElement); 

    if (front == nullptr) {
      front = newNode;
      rear = newNode;
    } else {
      rear->link = newNode;
      rear = rear->link;
    }
  }

  T peekFront() const {
    assert(front != nullptr);
    return front->info; 
  }

  T peekRear() const {
    assert(rear!= nullptr);
    return rear->info;
  }

  void dequeue() {
    Node<T> *temp;
   
    if (!empty()) {
      temp = front; 
      front = front->link; 

      delete temp; 

      if (front == nullptr) rear = nullptr; 
    } else {
      std::cout << "Cannot remove from an empty queue" << std::endl;
    }
  }

private:
  Node<T> *front;
  Node<T> *rear; 

  LinkedQueue<T>& copy(const LinkedQueue<T>& q){
    front = nullptr;
    rear = nullptr;
    auto current = q.front;
    while(current){
      auto newNode = new Node<T>(current->info);
      if(front == nullptr) { // empty list
        front = newNode;
      } else {
        rear->link = newNode;
      }
      rear = newNode;
      current = current->link;
    }

    return *this;
  }

  void destroy() {
    auto current = front;
    while(current) {
      auto temp = current;
      current = current->link;
      delete temp;
    }
  }
};

#endif
