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

