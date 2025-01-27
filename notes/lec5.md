# Lec5 - `const`, `structs`, and C-Style ADTs
## 1. `const`
### The `const` Keyword
- `const` is a type qualifier that prohibits assignment.
#### 'const' and Pointers
```cpp
int x = 3;
const int y = 5;

int *ptr0 = &x; // Regular pointer to int.

// These declarations are equivalent
// Pointer to const int. It’s a read-only pointer – you can’t change the int through it.
const int * ptr1 = &x;
int const * ptr1 = &x;

int * const ptr2 = &x; // const pointer. It’s a fixed pointer that always points to the same place.
```
#### 'const' and References
```cpp
int x = 3;
const int y = 5;
// Bind references to the original objects, creating a new variable/alias for them.
int &ref_x = x;
int &ref_y = y; // ERROR! Not allowed. Because y is a const while ref_y is not a const.

// Reference to const int. Not allowed to modify data through these aliases.
const int &cref_x = x; // OK. cref_x could be a const while x is not a const.
const int &cref_y = y; // cref_y must be a const.
```
#### Which of the assignments are legal?
```cpp
int x = 3;
const int y = 3;
const int * ptr1 = &x;
int * const ptr2 = &x;
const int &ref = x;

y = 5; // Not legal
*ptr1 = 5; // Not legal
ptr1 = &y; // Legal
*ptr2 = 5; // Legal
ptr2 = &x; // Not legal
ref = 5; // Not legal
x = 5; // Legal
```
### `const` conversions
```cpp
const int data = 3;
const int *cptr = &data;
int *ptr = cptr; // Not legal. ptr is not a const pointer, can potentially change the value of data.
```
```cpp
const int x = 3;
int y = x; // Legal. Passing by value is allowed.
```
### Benifits of `const`
#### Catch mistakes in implementation code.
```cpp
void append(vector<int> &target, const vector<int> &src) {
  for (size_t i = 0; i < src.size(); ++i) {
    src.push_back(target[i]); // Not legal
  }
}
```
#### Catch misuse of interfaces.
```cpp
void append(vector<int> &target, const vector<int> &src);
const string & get_secret_passphrase();

int main() {
  vector<int> v1 = {1, 2, 3};
  const vector<int> v2 = {4, 5};
  append(v1, v2); // v1 now holds 1,2,3,4,5
  append(v2, v1); // error - shouldn't be appending to const v2!

  get_secret_passphrase() += "lol"; // error – only allowed "read only" access to the passphrase
}
```
## 2. `struct`
### Intro to `struct`
We can use both `struct` and `class` to create class-type objects in C++.
#### Initializing `structs`
```cpp
struct Person {
  int age;
  string name;
  bool isNinja;
};

int main() {
  Person alex;
  Person jon = { 25, "jon", true };
  alex = { 75, "granny", false };
}
```
#### Member Access
The . operator accesses individual members.
```cpp
int main() {
  Person p = { 48, "Shweta", true };
  p.isNinja = true;
}
```
#### Copying `structs`
`structs` can be copied with `=`. This copies each member individually.
```cpp
int main() {
  Person alex;
  Person jon = { 25, "jon", true };
  alex = jon;
}
```
#### `structs` and `const`
A `struct` can be declared const. Neither it nor its members may be assigned to.
```cpp
int main() {
  const Person p1 = { 17, "Kim", true };
  Person p2 = { 17, "Ron", true };
  
  p1.isNinja = false; // not possible
  p1 = p2; // not possible
}
```
#### `structs` and Pointers
A pointer can point to a struct.  
Use the . to get members. Alternatively, use the -> operator as a shortcut!
```cpp
int main() {
  Person p = { 31, "Aliyah", true };  
  Person * ptr = &p;
  p.age = 32;
  *ptr.age = 33;
  ptr->age = 34;
}
```
#### Parameter Passing Rules
Do you need to modify the original object? -> `void func(Person *p);`, `void func(Person &p);`  
Is it a potentially large type? -> `void func(const Person *p);`, `void func(const Person &p);`  
No big deal to copy, then? -> `void func(int p);`, `void func(Pixel p);`
## 3. C-Style ADTs
### ADT Initialization and Representation Invariants
Check invariants using assert.
```cpp
struct Triangle {
  double a, b, c;
};

void Triangle_init(Triangle *tri, double a_in, 
                   double b_in, double c_in) {
  assert(0 < a_in && 0 < b_in && 0 < c_in);
  assert(a_in + b_in > c_in  && a_in + c_in > b_in && b_in + c_in > a_in);
  tri->a = a_in;
  tri->b = b_in;
  tri->c = c_in;
}

int main() {
  Triangle t1;
  Triangle_init(&t1, 3, 4, 11); // This will now cause a failed assertion. It is impossible to create an invalid Triangle.
}
```
### Composing ADTs
One ADT might be a member of another.
```cpp
struct Professor {
  int age;
  Triangle favTriangle;
};

// Always remember to initialize member ADTs, either by using an _init function or as a copy of a pre-existing ADT.
void Professor_init(Professor *prof, int age, int side) {
  prof->age = age;
  Triangle_init(&prof->favTriangle, side, side, side);
}

void Professor_init(Professor *prof, int age,
                    const Triangle &favTriangle) {
  prof->age = age;
  prof->favTriangle = favTriangle;
}
```
### Function Overloading
Multiple functions with the same name but different signatures (name + param types) are allowed.
```cpp
struct Matrix {
  int width;
  int height;
  std::vector<int> data;
};

// Get a pointer to an element in a const Matrix
int * Matrix_at(Matrix *mat, int row, int col) {
}

// Get a pointer to an element in a const Matrix
const int * Matrix_at(const Matrix *mat, int row, int col) {
}
```
### Unit Testing C-Style ADTs
```cpp
// Fills a 3x5 Matrix with a value and checks that
// Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(&mat, width, height);  
  Matrix_fill(&mat, value);  
  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) { 
      ASSERT_EQUAL(*Matrix_at(&mat, row, col), value);
    }
  }
}
```






