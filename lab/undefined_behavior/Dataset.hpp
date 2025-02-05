#ifndef DATASET_HPP
#define DATASET_HPP

#include <iostream>
#include <vector>

struct Dataset {
  std::vector<int> data;
  int size; // the number of elements in the dataset
};

// REQUIRES: ds points to a Dataset
// MODIFIES: the Dataset pointed to by ds
// EFFECTS: Initializes an empty dataset with size 0
void Dataset_init_empty(Dataset *ds);

// REQUIRES: ds points to a Dataset
//           0 <= n
// MODIFIES: the Dataset pointed to by ds
// EFFECTS: Initializes a dataset with n random values
//          between 0 and max_value.
void Dataset_init_random(Dataset *ds, int n, int max_value);

int Dataset_size(const Dataset *ds);

// REQUIRES: ds points to a valid Dataset
//           0 <= i < ds->size
// EFFECTS: returns a pointer to the address of the element at index i
int * Dataset_at(Dataset *ds, int i);

// REQUIRES: ds points to a valid Dataset
//           0 <= i < ds->size
// EFFECTS: returns a pointer to the address of the element at index i
const int * Dataset_at(const Dataset *ds, int i);

// REQUIRES: ds points to a valid Dataset
// EFFECTS: returns the minimum value in the dataset
int Dataset_min(const Dataset *ds);

// REQUIRES: ds points to a valid Dataset
// EFFECTS: returns the mean of the dataset
double Dataset_mean(const Dataset *ds);

// REQUIRES: ds points to a valid Dataset
// EFFECTS: prints the dataset to os
void Dataset_print(const Dataset *ds, std::ostream &os);

#endif // DATASET_HPP
