/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 *
 * EECS 280 Statistics Project
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.hpp"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

void test_sum_small_data_set();
void test_count_small_data_set();
void test_mean_small_data_set();
void test_median_small_data_set();
void test_min_small_data_set();
void test_max_small_data_set();
void test_stdev_small_data_set();
void test_percentile_small_data_set();
void test_filter_small_data_set();

// Add prototypes for you test functions here.

int main() {
  test_sum_small_data_set();
  // Call your test functions here
  test_count_small_data_set();
  test_mean_small_data_set();
  test_median_small_data_set();
  test_min_small_data_set();
  test_max_small_data_set();
  test_stdev_small_data_set();
  test_percentile_small_data_set();
  test_filter_small_data_set();
  return 0;
}

void test_sum_small_data_set() {
  cout << "test_sum_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(sum(data) == 6);

  cout << "PASS!" << endl;
}

// Add the test function implementations here.
void test_count_small_data_set() {
  cout << "test_count_small_data_set" << endl;

  vector<double> data;
  data.push_back(-1);

  assert(count(data) == 1);

  cout << "PASS!" << endl;
}

// Precision for floating point comparison
const double epsilon = 0.00001;

static bool almost_equal(double x, double y) {
  return abs(x - y) < epsilon;
}

void test_mean_small_data_set() {
  cout << "test_mean_small_data_set" << endl;

  vector<double> data;
  data.push_back(1.5);
  data.push_back(0.5);
  data.push_back(0);
  data.push_back(0);
  data.push_back(-0.5);

  assert(almost_equal(mean(data), 0.3));

  cout << "PASS1!" << endl;

  vector<double> data1;
  data1.push_back(1);

  assert(almost_equal(mean(data1), 1));

  cout << "PASS2!" << endl;

}

void test_median_small_data_set() {
  cout << "test_median_small_data_set" << endl;

  vector<double> data1;
  data1.push_back(1);
  data1.push_back(2);
  data1.push_back(3);
  data1.push_back(4);
  data1.push_back(5);

  assert(almost_equal(median(data1), 3));

  cout << "PASS1!" << endl;

  vector<double> data2;
  data2.push_back(1);
  data2.push_back(2);
  data2.push_back(3);
  data2.push_back(4);
  data2.push_back(5);
  data2.push_back(6);

  assert(almost_equal(median(data2), 3.5));

  cout << "PASS2!" << endl;

  vector<double> data3;
  data3.push_back(1);

  assert(almost_equal(median(data3), 1));

  cout << "PASS3!" << endl;

}

void test_min_small_data_set() {
  cout << "test_min_small_data_set" << endl;

  vector<double> data;
  data.push_back(0.5);
  data.push_back(0);
  data.push_back(-0.5);

  assert(almost_equal(min(data), -0.5));

  cout << "PASS!" << endl;
}

void test_max_small_data_set() {
  cout << "test_max_small_data_set" << endl;

  vector<double> data;
  data.push_back(0.5);
  data.push_back(0);
  data.push_back(-0.5);

  assert(almost_equal(max(data), 0.5));

  cout << "PASS!" << endl;
}

void test_stdev_small_data_set() {
  cout << "test_stdev_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(0);
  data.push_back(-1);

  assert(almost_equal(stdev(data), 1));

  cout << "PASS!" << endl;
}

void test_percentile_small_data_set() {
  cout << "test_percentile_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(0);
  data.push_back(-1);

  assert(almost_equal(percentile(data, 1.0), 1));

  cout << "PASS1!" << endl;

  assert(almost_equal(percentile(data, 0), -1));

  cout << "PASS2!" << endl;
}

void test_filter_small_data_set() {
  cout << "test_filter_small_data_set" << endl;

  vector<double> data;
  vector<double> criteria;
  double target = 1;
  data.push_back(1);
  data.push_back(0);
  data.push_back(-1);
  criteria.push_back(1);
  criteria.push_back(0);
  criteria.push_back(1);

  assert(filter(data, criteria, target) == vector<double>({1, -1}));

  cout << "PASS!" << endl;
}