#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <iostream>
#include <cassert>

template <typename T>
struct Node {
  T info;
  Node<T> *link;
  Node(T e): info(e), link(nullptr) {};
};

template <typename T>
class LinkedListIterator {
public:
  LinkedListIterator() : current(nullptr) {}
  LinkedListIterator(Node<T> *ptr) : current(ptr) {}

  T operator*() { return current->info; }
  LinkedListIterator<T> operator++(){
    current = current->link;
    return *this;
  } 
  bool operator==(const LinkedListIterator<T> &right) const {
    return (current == right.current);
  }
  bool operator!=(const LinkedListIterator<T> &right) const {
    return (current != right.current);
  }

private:
  Node<T> *current; 
};


template <typename T>
class LinkedList {
public:
  LinkedList(): first(nullptr), last(nullptr), count(0) {}
  LinkedList(const LinkedList<T> &otherList): first(nullptr) { copy(otherList); }
  ~LinkedList(){ destroy();  } 

  const LinkedList<T> &operator=(const LinkedList<T> &otherList) {
    if (this != &otherList) {
      copy(otherList);
    } 

    return *this;
  }

  bool empty() const { return (first == nullptr); }

  void print() const {
    Node<T> *current; 

    current = first;  
    while (current != nullptr) {
      std::cout << current->info << " ";
      current = current->link;
    }
  } 

  int length() const { return count; } 

  T front() const {
    assert(first != nullptr);
    return first->info; 
  }

  T back() const {
    assert(last != nullptr);
    return last->info; 
  }

  LinkedListIterator<T> begin() {
    LinkedListIterator<T> temp(first);
    return temp;
  }

  LinkedListIterator<T> end() {
    LinkedListIterator<T> temp(nullptr);
    return temp;
  }


  bool search(const T& searchItem) const {
    Node<T> *current; 
    bool found = false;
      
    current = first; 
    while (current != nullptr && !found) {  
      if (current->info == searchItem) {
        found = true;
      } else {
        current = current->link; 
      }
    }
    return found; 
  }

  void insertFirst(const T& newItem) {
    Node<T> *newNode= new Node<T>(newItem); 
    newNode->link = first; 
    first = newNode; 
    count++; 

    if (last == nullptr) last = newNode;
  }

  void insertLast(const T& newItem) {
    Node<T> *newNode = new Node<T>(newItem); 

    if (first == nullptr) {
      first = newNode;
      last = newNode;
      count++; 
    } else {
      last->link = newNode; 
      last = newNode; 
      count++; 
    }
  }

  void remove(const T& deleteItem){
    Node<T> *current; 
    Node<T> *trailCurrent; 
    bool found;

    if (first == nullptr) { 
        std::cout << "Cannot delete from an empty list." << std::endl;
    } else {
      if (first->info == deleteItem) {
        current = first;
        first = first->link;
        count--;
        if (first == nullptr) last = nullptr;
        delete current;
      } else {
        found = false;
        trailCurrent = first; 
        current = first->link; 

        while (current != nullptr && !found) {
          if (current->info != deleteItem) {
              trailCurrent = current;
              current = current-> link;
          } else {
              found = true;
          }
        }

        if (found) {
          trailCurrent->link = current->link;
          count--;

          if (last == current) last = trailCurrent; 
          delete current; 
        } else {
            std::cout << "The item to be deleted is not in the list." << std::endl;
        }
      }
    }
  }

  void destroy() {
    Node<T> *temp; 
    while (first != nullptr) {
      temp = first;    
      first = first->link; 
      delete temp;        
    }

    last = nullptr;
    count = 0;
  }

private:
  int count;
  Node<T> *first; 
  Node<T> *last;  

  void initialize() { destroy(); }

  void copy(const LinkedList<T> &otherList) {
    Node<T> *newNode;
    Node<T> *current;

    if (first != nullptr) destroy();

    if (otherList.first == nullptr) {
      first = nullptr;
      last = nullptr;
      count = 0;
    } else {
      current = otherList.first; 
      count = otherList.count;

      first = new Node<T>; 

      first->info = current->info; 
      first->link = nullptr;    
      last = first; 
      current = current->link; 

      while (current != nullptr) {
        newNode = new Node<T>; 
        newNode->info = current->info; 
        newNode->link = nullptr; 
        last->link = newNode; 
        last = newNode;  
        current = current->link;  
      } 
    } 
  }
};

#endif
