#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:
  //default constructor
  List();

  //copy constructor
  List(const List &other);

  //EFFECTS:  returns true if the list is empty
  bool empty() const;

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const;

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front();

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back();

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum);

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum);

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front();

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back();

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear();

  List & operator=(const List &rhs) {
    if (this == &rhs) { return *this; }
    clear();
    copy_all(rhs);
    return *this;
  }

  //destructor
  ~List();
  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other);

  int sizeT;
  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty

public:
  ////////////////////////////////////////
  class Iterator {
    friend class List;
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    Iterator() : node_ptr(nullptr) {}
    //Iterator(Node *node_ptr_in) : node_ptr(node_ptr_in) {}

    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    T & operator*() const;
    //dereference

    Iterator& operator++();


    bool operator==(Iterator rhs) const;

    bool operator!=(Iterator rhs) const;

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here
    
    // add any friend declarations here

    // construct an Iterator at a specific position
    Iterator(Node *p);
    //Iterator() : node_ptr(nullptr) {}

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    return Iterator();
    //call the default constructor
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i);
  //remove the node from the list 
  //same idea as erase from vector 

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum);

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

//default ctor
template<typename T>
List<T>::List()
: sizeT(0), first(nullptr), last(nullptr) { }

//copy ctor
template<typename T>
List<T>::List(const List<T> &other)
: sizeT(0), first(nullptr), last(nullptr) { 
  copy_all(other);
}

//EFFECTS:  returns true if the list is empty
template<typename T>
bool List<T>::empty() const {
  //set size to 0?
  return first == nullptr;
}

//EFFECTS: returns the number of elements in this List
//HINT:    Traversing a list is really slow.  Instead, keep track of the size
//         with a private member variable.  That's how std::list does it.
template<typename T>
int List<T>::size() const {
  return sizeT;
}

//REQUIRES: list is not empty
//EFFECTS: Returns the first element in the list by reference
template<typename T>
T & List<T>::front() {
  assert(!empty());
  return first->datum;
}

//REQUIRES: list is not empty
//EFFECTS: Returns the last element in the list by reference
template<typename T>
T & List<T>::back() {
  assert(!empty());
  return last->datum;
}

//EFFECTS:  inserts datum into the front of the list
template<typename T>
void List<T>::push_front(const T &datum) {
  Node *p = new Node;
  p->datum = datum;
  //when it is empty, the next would be nullptr
  //p->next = first;
  p->prev = nullptr;
  if (empty()) {
    p->next = nullptr;
    first = p;
    last = p;
  }
  else {
    p->next = first;
    first->prev = p;
    first = p;
  }
  ++sizeT;
}

//EFFECTS:  inserts datum into the back of the list
template<typename T>
void List<T>::push_back(const T &datum) {
  Node *p = new Node;
  p->datum = datum;
  p->next = nullptr;
  p->prev = last;
  if(empty()) { first = last = p; }
  else {
    last->next = p;
    last = p;
  }
  ++sizeT;
}

//REQUIRES: list is not empty
//MODIFIES: may invalidate list iterators
//EFFECTS:  removes the item at the front of the list
template<typename T>
void List<T>::pop_front() {
  assert(!empty());
  Node *victim = first;
  first = first->next;
  if (first != nullptr) {
    first -> prev = nullptr;
  }
  else {
    last = nullptr;
  }
  delete victim;
  --sizeT;
}
//only has 1 element 

//REQUIRES: list is not empty
//MODIFIES: may invalidate list iterators
//EFFECTS:  removes the item at the back of the list
template<typename T>
void List<T>::pop_back() {
  assert(!empty());
  if (first->next == nullptr) {
    first = nullptr;
    delete last;
  }
  else {
    Node *victim = last;
    last = last->prev;
    last -> next = nullptr;
    delete victim;
  }
  --sizeT;
}

//MODIFIES: may invalidate list iterators
//EFFECTS:  removes all items from the list
template<typename T>
void List<T>::clear() {
  while (!empty()) {
    pop_front();
  }
  sizeT = 0;
}

//destructor
template<typename T>
List<T>::~List() {
  clear();
}


//REQUIRES: list is empty
//EFFECTS:  copies all nodes from other to this
template<typename T>
void List<T>::copy_all(const List<T> &other) {
  for (Node *np = other.first; np; np = np->next) {
    push_back(np->datum);
  }
}

//Iterator
    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  template<typename T>
  T & List<T>::Iterator::operator*() const {
    assert(node_ptr);
    return node_ptr->datum;
  }

  template<typename T> 
  typename List<T>::Iterator &List<T>::Iterator::operator++() {
    assert(node_ptr);
    node_ptr = node_ptr->next;
    return *this;
  }

  template<typename T> 
  bool List<T>::Iterator::operator==(Iterator rhs) const{
    return node_ptr == rhs.node_ptr;
  }

  template<typename T> 
  bool List<T>::Iterator::operator!=(Iterator rhs) const{
    return node_ptr != rhs.node_ptr;
  }

    // add any additional necessary member variables here

    // add any friend declarations here

  //List::Iterator
  ////////////////////////////////////////
  template<typename T> 
  List<T>::Iterator::Iterator(Node *p) 
  : node_ptr(p) { }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  template<typename T> 
  void List<T>::erase(Iterator i) {
    assert(!empty());
    if (i.node_ptr == first) {
      pop_front();
    }
    else if (i.node_ptr == last) {
      pop_back();
    }
    else {
      Node *victim = i.node_ptr;
      victim->prev->next = i.node_ptr->next;
      victim->next->prev = i.node_ptr->prev;
      delete victim;
      --sizeT;
    }
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  template<typename T> 
  void List<T>::insert(Iterator i, const T &datum) {
    //when theres one element
    if (i.node_ptr == first) {
      push_front(datum);
    }
    else if (i.node_ptr == nullptr) {
      push_back(datum);
    }
    else {
      //fix this! decrementing pointers moves them  
      Node *p = new Node;
      p->datum = datum;
      p->next = i.node_ptr;
      p->prev = i.node_ptr->prev;
      i.node_ptr->prev->next = p;
      i.node_ptr->prev = p;
      ++sizeT;
    }
  }

#endif // Do not remove this. Write all your code above this line.

