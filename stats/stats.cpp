// stats.cpp
#include "stats.hpp"
#include <cassert>
#include <vector>
#include <algorithm> // sort
#include <cmath> // sqrt, modf

using namespace std;

int count(vector<double> v) {
  return v.size();
}

double sum(vector<double> v) {
  double total = 0;
  for (int i = 0; i < v.size(); i++)
  {
    total += v[i];
  }
  return total;
}

double mean(vector<double> v) {
  return static_cast<double>(sum(v)) / count(v);
}

double median(vector<double> v) {
  sort(v.begin(), v.end());
  if (count(v) % 2 == 1)
  {
    int index0 = (count(v)+1)/2 - 1;
    return v[index0];
  }
  else{
    int index1 = count(v) / 2;
    int index2 = count(v) / 2 - 1;
    return (v[index1] + v[index2]) / 2;
  }
}

double min(vector<double> v) {
  sort(v.begin(), v.end());
  return v[0];
}

double max(vector<double> v) {
  sort(v.begin(), v.end());
  return v[count(v)-1];
}

double stdev(vector<double> v) {
  double total = 0;
  for (int i = 0; i < count(v); i++) {
    total += pow(v[i] - mean(v), 2);
  }
  return sqrt(total / (count(v) - 1));
}

double percentile(vector<double> v, double p) {
  sort(v.begin(), v.end());
  double rank = p * (count(v) - 1) + 1;
  double intpart = 0;
  double fractpart = 0;
  fractpart = modf(rank, &intpart);
  if (p == 1) {
    return v[intpart-1];
  }
  else {
    return v[intpart-1] + fractpart * (v[intpart] - v[intpart-1]);
  }
}

vector<double> filter(vector<double> v,
                      vector<double> criteria,
                      double target) {
  vector<double> temp_1 = {};
  for (int i = 0; i < criteria.size(); i++) {
    if (criteria[i] == target) {
      temp_1.push_back(v[i]);
    }
  }
  return temp_1;
}
