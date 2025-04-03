#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 List/Editor Project
 */

#include <iostream>
#include <iterator> //std::bidirectional_iterator_tag
#include <cassert>  //assert


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //EFFECTS:  returns true if the list is empty
  bool empty() const;

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow. Instead, keep track of the size
  //         with a private member variable. That's how std::list does it.
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
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS:  removes the item at the front of the list
  void pop_front();

  //REQUIRES: list is not empty
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS:  removes the item at the back of the list
  void pop_back();

  //MODIFIES: invalidates all iterators to the removed elements
  //EFFECTS:  removes all items from the list
  void clear();

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you should omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists.

  // Default constructor
  List();

  // Destructor
  ~List();

  // Copy constructor
  List(const List<T>& other_list);

  // Assignment operator
  List<T>& operator=(const List<T>& other_list);

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

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  int current_size; // track current size

public:
  ////////////////////////////////////////
  class Iterator {
  public:
    //OVERVIEW: Iterator interface to List

    // Add a default constructor here. The default constructor must set both
    // pointer members to null pointers.
    Iterator() : list_ptr(nullptr), node_ptr(nullptr) {}


    // Add custom implementations of the destructor, copy constructor, and
    // overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you should omit them. A user
    // of the class must be able to copy, assign, and destroy Iterators.



    // Your iterator should implement the following public operators:
    // *, ++ (both prefix and postfix), == and !=.
    // Equality comparisons must satisfy the following rules:
    // - two default-constructed iterators must compare equal
    // - a default-constructed iterator must compare unequal to an
    //   iterator obtained from a list, even if it is the end iterator
    // - two iterators to the same location in the same list must
    //   compare equal
    // - two iterators to different locations in the same list must
    //   compare unequal
    // - comparing iterators obtained from different lists results in
    //   undefined behavior
    //   - Your implementation can handle this however you like, but
    //     don't assume any particular behavior in your test cases --
    //     comparing iterators from different lists essentially
    //     violates the REQURES clause.
    // Note: comparing both the list and node pointers should be
    // sufficient to meet these requirements.
    T& operator*() const {
      assert(node_ptr);
      return node_ptr->datum;
    }

    Iterator& operator++() {
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }
    
    Iterator operator++(int) {
      Iterator copy = *this;
      ++(*this);
      return copy;
    }

    bool operator==(const Iterator& other) const {
      return list_ptr == other.list_ptr && node_ptr == other.node_ptr;
    }

    bool operator!=(const Iterator& other) const {
      return !(*this == other);
    }


    // Type aliases required to work with STL algorithms. Do not modify these.
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a reference to this Iterator
    Iterator& operator--() { // prefix -- (e.g. --it)
      assert(list_ptr);
      assert(*this != list_ptr->begin());
      if (node_ptr) {
        node_ptr = node_ptr->prev;
      } else { // decrementing an end Iterator moves it to the last element
        node_ptr = list_ptr->last;
      }
      return *this;
    }

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a copy of the original Iterator
    Iterator operator--(int /*dummy*/) { // postfix -- (e.g. it--)
      Iterator copy = *this;
      operator--();
      return copy;
    }

    // REQUIRES: Iterator is dereferenceable
    // EFFECTS: returns the underlying element by pointer
    // NOTE: T must be a class type to use the syntax it->. If T has a
    //       member variable f, then it->f accesses f on the
    //       underlying T element.
    T* operator->() const {
      return &operator*();
    }

  private:
    const List *list_ptr; //pointer to the List associated with this Iterator
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here


    // add any friend declarations here
    friend class List<T>;  

    // construct an Iterator at a specific position in the given List
    Iterator(const List *lp, Node *np);

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const;

  // return an Iterator pointing to "past the end"
  Iterator end() const;

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS: Removes a single element from the list container.
  //         Returns An iterator pointing to the element that followed the
  //         element erased by the function call
  Iterator erase(Iterator i);

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: Inserts datum before the element at the specified position.
  //         Returns an iterator to the the newly inserted element.
  Iterator insert(Iterator i, const T &datum);

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

// Default constructor
template <typename T>
List<T>::List() : first(nullptr), last(nullptr), current_size(0) {}

// Destructor
template <typename T>
List<T>::~List() {
  clear();
}

// Copy constructor
template <typename T>
List<T>::List(const List<T>& other_list) : first(nullptr), last(nullptr), current_size(0) {
  copy_all(other_list);
}

// Assignment operator
template <typename T>
List<T>& List<T>::operator=(const List<T>& other_list) {
  if (this != &other_list) {
    clear();
    copy_all(other_list);
  }
  return *this;
}

template <typename T>
bool List<T>::empty() const {
  return first == nullptr;
}

//EFFECTS: returns the number of elements in this List
//HINT:    Traversing a list is really slow. Instead, keep track of the size
//         with a private member variable. That's how std::list does it.
template <typename T>
int List<T>::size() const {
  return current_size;
}

//REQUIRES: list is not empty
//EFFECTS: Returns the first element in the list by reference
template <typename T>
T & List<T>::front() {
  assert(!empty());
  return first->datum;
}

//REQUIRES: list is not empty
//EFFECTS: Returns the last element in the list by reference
template <typename T>
T & List<T>::back() {
  assert(!empty());
  return last->datum;
}

//EFFECTS:  inserts datum into the front of the list
template <typename T>
void List<T>::push_front(const T &datum) {
  Node* new_node = new Node{first, nullptr, datum};
  if (first) {
    first->prev = new_node;
  }
  first = new_node;
  if (!last) {
    last = new_node;
  }
  ++current_size;
}

//EFFECTS:  inserts datum into the back of the list
template <typename T>
void List<T>::push_back(const T &datum) {
  Node* new_node = new Node{nullptr, last, datum};
  if (!first) {
    first = new_node;
  }
  if (last) {
    last->next = new_node;
  }
  last = new_node;
  ++current_size;
}

//REQUIRES: list is not empty
//MODIFIES: invalidates all iterators to the removed element
//EFFECTS:  removes the item at the front of the list
template <typename T>
void List<T>::pop_front() {
  assert(!empty());
  Node* temp = first;
  first = first->next;
  if (first) {
    first->prev = nullptr;
  }
  else {
    last = nullptr;
  }
  delete temp;
  --current_size;
}

//REQUIRES: list is not empty
//MODIFIES: invalidates all iterators to the removed element
//EFFECTS:  removes the item at the back of the list
template <typename T>
void List<T>::pop_back() {
  assert(!empty());
  Node* temp = last;
  last = last->prev;
  if (last) {
    last->next = nullptr;
  }
  else {
    first = nullptr;
  }
  delete temp;
  --current_size;
}

//MODIFIES: invalidates all iterators to the removed elements
//EFFECTS:  removes all items from the list
template <typename T>
void List<T>::clear() {
  while (!empty()) {
    pop_front();
  }
}

//REQUIRES: list is empty
//EFFECTS:  copies all nodes from other to this
template <typename T>
void List<T>::copy_all(const List<T> &other) {
  Node* current = other.first;
  while (current) {
    push_back(current->datum);
    current = current->next;
  }
}

 // construct an Iterator at a specific position in the given List
template <typename T>
List<T>::Iterator::Iterator(const List *lp, Node *np) : list_ptr(lp), node_ptr(np) {

}

// return an Iterator pointing to the first element
template <typename T>
typename List<T>::Iterator List<T>::begin() const {
  return Iterator(this, first);
}

// return an Iterator pointing to "past the end"
template <typename T>
typename List<T>::Iterator List<T>::end() const {
  return Iterator(this, nullptr);
}

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS: Removes a single element from the list container.
  //         Returns An iterator pointing to the element that followed the
  //         element erased by the function call
template <typename T>
typename List<T>::Iterator List<T>::erase(Iterator i) {
  assert(i.list_ptr == this);
  assert(i.node_ptr != nullptr);

  Node* n = i.node_ptr;
  Node* before = n->prev;
  Node* after = n->next;

  if (before) {
    before->next = after;
  }
  else {
    first = after;
  }

  if (after) {
    after->prev = before;
  }
  else {
    last = before;
  }

  delete n;
  --current_size;

  return Iterator(this, after);
}

//REQUIRES: i is a valid iterator associated with this list
//EFFECTS: Inserts datum before the element at the specified position.
//         Returns an iterator to the the newly inserted element.
template <typename T>
typename List<T>::Iterator List<T>::insert(Iterator i, const T &datum) {
  assert(i.list_ptr == this);

  Node* after = i.node_ptr;
  Node* before;
  if (after) {
    before = after->prev;
  }
  else {
    before = last;
  }

  Node* new_node = new Node{after, before, datum};

  if (before) {
    before->next = new_node;
  }
  else {
    first = new_node;
  }

  if (after) {
    after->prev = new_node;
  }
  else {
    last = new_node;
  }

  ++current_size;
  return Iterator(this, new_node);
}


#endif // Do not remove this. Write all your code above this line.
