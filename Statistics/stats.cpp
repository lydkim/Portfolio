// stats.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5
#include "stats.h"
#include "p1_library.h"
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;
vector<vector<double> > summarize(vector<double> v) {
  sort(v); 
  double count = 0;
  vector<vector<double>> y;
  for (size_t i = 0; i < v.size(); ++i) {
    for (size_t j = 0; j < v.size(); ++j) {
      if (v[i] == v[j]) {
        count++;
      }

    }
    vector<double> small = {v[i], count};
    y.push_back(small);
    count = 0;
  }
return y;
}

int count(vector<double> v) {
    //the size of the array
  int count = 0;
  for (size_t i = 0; i < v.size(); ++i) {
    count ++;
  }
  return count;
}

double sum(vector<double> v) {
  //for loop to go through every number in the array and then having a total sum
  double total = 0;
  for (size_t i = 0; i < v.size(); ++i) {
    total += v[i] ;
  }
  return total;
}

double mean(vector<double> v) {
  double count = 0;
  double total = 0;
  double mean = 0;
  //for loop is the same as sum
  //count is the number of elements in the array
  for (size_t i = 0; i <v.size(); ++i) {
    total += v[i];
    count++;
  }
  mean = (total/count);


  return mean;
}

double median(vector<double> v) {
   double median;
   double median_index;
   double first_median_index;
   double second_median_index;
  
   sort(v);
  //even number of elements 
   if (v.size() % 2 == 0) {
    first_median_index = v.size()/2;
    second_median_index = ((v.size()/2) - 1);
    median = ((v[first_median_index] + v[second_median_index]) / 2);
   }
   //odd number of elements
   else {
    median_index = v.size()/2;
    median = v[median_index];
   }
  
   return median;
}
double mode(vector<double> v) {
  sort(v);
  double count = 0;
  double number = 0;
  double mode;
  for (size_t i = 0; i < v.size(); ++i) {
    for (size_t j = 0; j < v.size(); ++j) {
      if (v[i] == v[j]) {
        count++;
      }
    }
    if (count > number) {
      number = count;
      mode = v[i];

    }
    count = 0;
  }
  return mode;
}
double min(vector<double> v) {
  double min = v[0];
  for (size_t i = 0; i < v.size(); ++i) {
    if (v[i] < v[0]) {
      min = v[i];
    }
    else {
      min = v[0];
    }
  }
  return min;
}
double max(vector<double> v) {
  double max = v[0];
  for (size_t i = 0; i < v.size(); ++i) {
    if (v[i] > v[0]) {
      max = v[i];
    }
    else {
      max = v[0];
    }
  }
  return max;

}
double stdev(vector<double> v) {
  double count = 0;
  double stdev = 0;
  for (size_t i = 0; i < v.size(); ++i) {
    count ++;
  }
  
  double sum = 0;
  for (size_t i = 0; i < v.size(); ++i) {
    sum += v[i];
  }

  double mean = 0;
  mean = (sum/count);

  if (count == 1) {
    stdev = sum;
    return stdev;
  }

  double n = 0;
  n = 1 / (count - 1);

  double total = 0;
  for (size_t i = 0; i < v.size(); ++i) {
    total += ((v[i] - mean) * (v[i] - mean));
  }

  stdev = (sqrt(n * total));
  return stdev;


}
double percentile(vector<double> v, double p) {
  sort(v);
  double amount = 0;
  double n = 0;
  amount = count(v) - 1;
  n = ((p * amount) + 1);

  //for the 100th percentile
  

  double intpart = 0;
  double decimal = 0;
  decimal = modf(n, &intpart);

  double percentile = 0;

  if (p == 1) {
    percentile = v[amount];
    return percentile;
  }

  percentile = ((v[intpart-1]) + (decimal * (v[intpart] - v[intpart-1])));


  return percentile;
  
}