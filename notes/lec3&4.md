# Lec3&4 - Machine Model
## 1. Variables and Memory
A variable is a name in the program’s source code that refers to an object in memory.  
Data is stored in bytes, composed of 8 bits - binary digits of 0 or 1.
- int = 4 bytes, double = 8 bytes
### Default Initialization
- Atomic types like int, double, bool, char, etc. “Do nothing” – the value is undefined. (Memory Junk)
- Class types like vector/string, a default constructor. Ensures the object has a meaningful default value.
## 2. Floating Point Precision
There are infinitely many real numbers, but only a finite number (e.g. 264) of representable double values.
```cpp
int main() {
cout.precision(20); // print up to 20 decimal places
cout << 0.1 << endl; // 0.10000000000000000555
cout << 0.2 << endl; // 0.2000000000000000111
cout << 0.3 << endl; // 0.2999999999999999889
cout << (0.1 + 0.2) << endl; // 0.30000000000000004441
}
```
If you perform arithmetic on floating-point numbers, don’t use == or != to check the result. Instead, check if the numbers are close. 
## 3. Relational Operations
“Chained comparisons” in C++ will not work as expected.
```cpp
int x = 10;
3 < x && x < 7; // return false
```
## 4. Memory Diagrams
### Addresses
The `&` operator yields the address of an object.
```cpp
// Declare some variables
int x = 10 + 5;
int y = x;
double z = 3.14159;
int A;
cout << &x; // prints 0x1000
cout << &y; // prints 0x1004
cout << &z; // prints 0x1008
cout << &A; // prints 0x1010
```
### Value Semantics
```cpp
// Declare variables
int x = 10 + 5;
int y = 0;
cout << &x; // 0x1000
cout << &y; // 0x1004
// Assignments
y = x;
x = 20;
cout << &x; // still 0x1000
cout << &y; // still 0x1004
```
### References
A reference declaration binds a variable to an already existing object.  
`int &` = “reference to int”
```cpp
// Declare variables
int x = 10 + 5;
int y = x;
int &r = x;
cout << &x; // 0x1000
cout << &y; // 0x1004
cout << &r; // 0x1000
```
### Pointers
We can use addresses as pointers to indirectly access objects.  
`int *` = “pointer to int”  
- Use the & operator to get a pointer to an object. Gives you the address of an object(A reference).
- Use the * operator to dereference a pointer. Gives you the object at some address(A pointer).
```cpp
int x = 3; // &x = 0x1000
int y = 5; // &y = 0x1004
int *ptr = &x; // &ptr = 0x1008
cout << ptr; // prints 0x1000
cout << *ptr; // prints 3
cout << &ptr; // prints 0x1008
*ptr = 100; // set x to 100 via ptr
ptr = &y; // re-point ptr at y
*ptr = -42; // set y to -42 via ptr
```
## 5. Expression Value Categories
### lvalue
an object at some address in memory. (`&`: only apply to lvalue) 
lvalue – “left value”, could appear on left (or right) side.
`x`,  `*ptr`,  `v[2]`
### rvalue
a value with no meaningful address.  
rvalue – “right value”, only allowed on the right side.
`5`,  `x + 2`,  `sqrt(2)`, `&x`
## 6. Call Stack
```cpp
int min(int x, int y) {
  if (x < y) { return x; }
  else { return y; }
}
int minOf3(int x, int y, int z) {
  int a = min(x, y);
  int b = min(y, z);
  return min(a, b);
}
int main() {
  int a = 3;
  int b = 4;
  int c = 5;
  // prints 3
  cout << minOf3(a, b, c);
}
```
- Which function has the largest stack frame? Ans: min0f3
- What is the max amount of memory used by the program at any one time (assume ints are 4 bytes). Ans: 40 bytes
- How many different stack frames are created for the min() function throughout the program’s execution? Ans: 3
## 7. Pass & Return
### 7.1 Pass By Value
Regular parameter passing is done by value. We don’t pass objects, just their values.
```cpp
void swap(int x, int y) {
  int temp = x;
  x = y;
  y = temp;
}
int main() {
  int a = 3;
  int b = 7;
  cout << a << ", " << b; // 3, 7
  swap(a, b);
  cout << a << ", " << b; // 3, 7
}
```
### 7.2 Pass By Reference
The parameter is an alias for the original object.
```cpp
void swap(int &x, int &y) {
  int temp = x;
  x = y;
  y = temp;
}
int main() {
  int a = 3;
  int b = 7;
  cout << a << ", " << b; // 3, 7
  swap(a, b);
  cout << a << ", " << b; // 7, 3
}
```
### 7.3 Return By Reference
Return an object rather than its value.
```cpp
int & selectLargest(int &x, int &y) {
  if (x > y) {
  return x;
}
else {
  return y;
}
}
int main() {
  int a = 3; int b = 7;
  // set largest of a or b to 10
  selectLargest(a, b) = 10; // Returns an lvalue (y/b) instead of just an rvalue (7).
}
```
### 7.4 Pass-by-Pointer
Pass-by-pointer is really just pass-by-value, which makes a copy. But a copy of the address still lets you get back to the original object.
```cpp
void addOne(int *x) {
  *x += 1;
  // adds 1 to whatever x points to, which is z in this example, even though the name z is not in scope here.
  // We used the address of z to get to it.
}
int main() {
  int z = 1;
  int *ptr = &z; // ptr "points to" z
  *ptr += 1; // adds 1 to z, without using the name z
  addOne(&z); // adds one to z
  addOne(ptr); // same thing
}
```
```cpp
void swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}
int main() {
  int a = 3;
  int b = 5;
  swap(&a, &b);
  // a and b now swapped
}
```
### 7.5 Return-by-Pointer
```cpp
int * selectLargest(int *x, int *y) {
  if (*x > *y) { return x; }
  else { return y; }
}

int main() {
  int a = 10;
  int b = 5;
  // Set the largest of a or b to 100
  *selectLargest(a, b) = 100; // return a/x
}
```
```cpp
string * find_by_length(vector<string> &vec, int length) {
  for (size_t i = 0; i < vec.size(); ++i) {
    if (vec[i].size() == length) {
      return &vec[i];
    }
  }
  return nullptr; // no string of given length
}
int main() {
  vector<string> v = { "hello", "world", "from", "EECS", "280" };
  string *found = find_by_length(v, 3); // point to "280"
  if (found) {
    cout << "found string: " << *found << endl; // found string: "280"
  } else {
    cout << "no such string" << endl;
  }
}
```
## 8. Null and Uninitialized Pointers
### Uninitialized pointers
Just like with any other (primitive) variable, if you don't initialize a pointer, it's value is determined by memory junk. That means it's pointing randomly off into space.
- Dereference an uninitialized pointer → undefined behavior.
### Null pointers
Sometimes we want to definitively say "this pointer isn't pointing to anything right now", and the way to do that is point it at address 0. 
- Dereference a null pointer - runtime error (usually).
- Declare a null pointer like this: `int *ptr = nullptr`;
## 9. Dangling Pointer
A dangling pointer is a pointer to a “dead” object.
```cpp
int * selectLargest(int x, int y) {
  if (x > y) { return &x; }
  else { return &y; }
} // pass the address of x/y instead of the reference object
int main() {
  int a = 10; int b = 5;
  int *ptr = selectLargest(a, b); // ptr points to x which has been erased
  cout << *ptr << endl; // Uninitialized pointers - undefined behavior
}
```
