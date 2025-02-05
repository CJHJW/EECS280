#include <cmath>
#include <iostream>
#include <cassert>
#include "Dataset.hpp"

using namespace std;

// REQUIRES: ds points to a Dataset
// MODIFIES: the Dataset pointed to by ds
// EFFECTS: Initializes an empty dataset with size 0
void Dataset_init_empty(Dataset *ds) {
  ds->data.clear(); // clear out any existing data
  ds->size = 0;
}

// REQUIRES: ds points to a Dataset
//           n >= 0
// MODIFIES: the Dataset pointed to by ds
// EFFECTS: Initializes a dataset with n random values
//          between 0 and max_value.
void Dataset_init_random(Dataset *ds, int n, int max_value) {
  ds->data.clear(); // clear out any existing data
  for (int i = 0; i < n; i++) {
    ds->data.push_back(rand() % max_value);
  }
  ds->size = n;
}

int Dataset_size(const Dataset *ds) {
  return ds->size;
}

// REQUIRES: ds points to a valid Dataset
//           0 <= i < ds->size
// MODIFIES: nothing
// EFFECTS: returns a pointer to the address of the element at index i
int * Dataset_at(Dataset *ds, int i) {
  int val = ds->data[i];
  int *ptr = &val;
  return ptr;
}

// REQUIRES: ds points to a valid Dataset
//           0 <= i < ds->size
// MODIFIES: nothing
// EFFECTS: returns a pointer to the address of the element at index i
const int * Dataset_at(const Dataset *ds, int i) {
  int val = ds->data[i];
  int *ptr = &val;
  return ptr;
}

// REQUIRES: ds points to a valid Dataset
// EFFECTS: returns the minimum value in the dataset
int Dataset_min(const Dataset *ds) {
  int min = ds->data[0];
  for (int i = 1; min < ds->size; i++) {
    if (*Dataset_at(ds, i) < min) {
      min = *Dataset_at(ds, i);
    }
  }
  return min;
}

// REQUIRES: ds points to a valid Dataset
// EFFECTS: returns the mean of the dataset
double Dataset_mean(const Dataset *ds) {
  double sum = 0.0;
  for(int i = 0; i < ds->size; i++) {
    sum += *Dataset_at(ds, i);
  }
  return sum / ds->size;
}

// REQUIRES: ds points to a valid Dataset
// EFFECTS: prints the dataset to os
void Dataset_print(const Dataset *ds, ostream &os) {
  for(int i = 0; i < ds->size; i++) {
    os << *Dataset_at(ds, i) << " ";
  }
  os << endl;
}
