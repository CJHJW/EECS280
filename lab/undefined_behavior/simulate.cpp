#include <iostream>

#include "Dataset.hpp"
#include <cassert>

using namespace std;

void simulate_random_data(int n, int max_value) {
  Dataset ds;
  Dataset_init_random(&ds, n, max_value);
  Dataset_print(&ds, cout);
  cout << "Size: " << Dataset_size(&ds) << endl;
  cout << "First: " << *Dataset_at(&ds, 0) << endl;
  cout << "Last: " << *Dataset_at(&ds, Dataset_size(&ds)-1) << endl;
  cout << "Mean: " << Dataset_mean(&ds) << endl;
  cout << "Min: " << Dataset_min(&ds) << endl;
  
}

int main() {

  int num_elements = 5;
  cout << "How many elements? ";
  cin >> num_elements;
  
  int max_value = 10;
  cout << "What's the maximum value? ";
  cin >> max_value;

  Dataset ds;
  Dataset_init_random(&ds, num_elements, max_value);


}
