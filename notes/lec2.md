# Lec2 - Types, Control Structures, and Procedural Abstraction
## 1. C++ Standard Library Types
### 1.1 std::string
A std::string represents text, a sequence of chars.
### 1.2 std::pair
A std::pair represents an ordered pair of values. A template parameter specifies the element type.
```cpp
std::pair<int, bool> p1;
p1.first = 5;
p1.second = false;
```
### 1.3 std::vector
A std::vector is a homogenous, sequential container. A template parameter specifies the element type.
#### Several ways to initialize a vector
```cpp
vector<int> v; // empty
vector<int> v(5); // 0, 0, 0, 0, 0
vector<int> v(3, 42); // 42, 42, 42
vector<int> v = {3, 5, 42, 28};
```
#### Vector Indexing - Difference between [] & .at()
```cpp
vector<int> v = {3, 5, 42, 28};
v[3] = 7;
v[4] = 100; // Out of bounds... undefined behavior!
v.at(3) = 7;
v.at(4) = 100; // Out of bounds.. throws an exception
```
- The [] operator is slightly faster since it doesn’t check the provided index.

#### Vector Functions
##### `.size()`
Returns the number of elements.
##### `.front()`
Returns a reference to the first element.
##### `.back()`
Returns a reference to the last element.
##### `.at()`
Works like indexing, but does bounds checking.
##### `.empty()`
Returns whether the vector is empty (as a bool).
##### `.clear()`
Removes all elements from the vector.
##### `.push_back()`
Adds a new element to the back of the vector.
##### `.pop_back()`
Removes the last element in the vector.
```cpp
vector<int> v; // v contains {}
v.push_back(1);
v.push_back(2);
v.push_back(3); // v contains {1, 2, 3}
v.pop_back(); // v contains {1, 2}
v.clear(); // v contains {}
```
## 2. Control Structures
### Short-Circuit Evaluation for && and ||
1. Evaluate the left operand first.
2. Evaluate the right operand ONLY if needed.
Common Pattern: Use the left operand to establish the safety of the right.
```cpp
if (i < v.size()) && (v[i] != 0)
```
## 3. Procedural Abstraction
### 3.1 Interfaces vs. Implementations
- an interface specifies what something does.
- an implementation specifies how it works.
### 3.2 Specification Comments (RMEs)
#### Requires
Prerequisites for the function to make sense.
The function implementation only needs to cover cases allowed by the interface’s REQUIRES clause.
- A function with no requirements is called complete.
- A function with requirements is called partial.
##### Checking the REQUIRES Clause
```cpp
// REQUIRES: v is not empty
// EFFECTS: returns the median of the numbers in v
double median(std::vector<double> v) {
  assert(!v.empty()); 
}
```
#### Modifies
MODIFIES indicate which things are potentially changed as a result of side effects.
- e.g. A reference parameter, cout, global variables, etc.
#### Effects
EFFECTS specifies what the function actually does.


