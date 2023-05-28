/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 * Project UID 5366c7e2b77742d5b2142097e51561a5
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <limits>
#include <cmath>
using namespace std;



// Add prototypes for you test functions here.


const std::vector<double> TWICE = {1,1,2,2,3};
const std::vector<double> EVEN = {1,2,3,4};
const std::vector<double> DOS = {1,2,2,3};
const std::vector<double> REGULAR = {0, 100, 150, 151};
const std::vector<double> NEGATIVE = {-1, 0, 1};
const std::vector<double> DECIMAL = {-0.1, 1.0, 1.1};
const std::vector<double> ZERO = {0};
const std::vector<double> BACKWARD = {3,2,1};
const std::vector<double> EDGE = {100.123, 200.123, 300.123};

const double EPSILON = 0.00001;

void test_sum_small_data_set();
void test_count();
void test_sum();
void test_mean();
void test_median();
void test_mode();
void test_min();
void test_max();
void test_stdev();
void test_percentile();

int main() {
  cout.precision(std::numeric_limits<double>::max_digits10);
  test_sum_small_data_set();
  test_count();
  test_sum();
  test_mean();
  test_median();
  test_mode();
  test_min();
  test_max();
  test_stdev();
  test_percentile();
  return 0;
}

//summarize test
//[value]
//[frequency]

void test_sum_small_data_set() {
  cout << "test_sum_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(sum(data) == 6);

  cout << "PASS!" << endl;
}

//summarize
void test_summarize() {
  cout << "test_summarize" << endl;
  //1,1,2,2,3
  assert(abs(summarize(TWICE)[0][0] - (1)) <= EPSILON);
  assert(abs(summarize(TWICE)[0][1] - (2)) <= EPSILON);

  assert(abs(summarize(TWICE)[2][0] - (2)) <= EPSILON);
  assert(abs(summarize(TWICE)[2][1] - (2)) <= EPSILON);

  assert(abs(summarize(TWICE)[4][0] - (3)) <= EPSILON);
  assert(abs(summarize(TWICE)[4][1] - (1)) <= EPSILON);

  //even: 1,2,3,4
  assert(abs(summarize(EVEN)[0][0] - (1)) <= EPSILON);
  assert(abs(summarize(EVEN)[0][1] - (1)) <= EPSILON);

  assert(abs(summarize(EVEN)[1][0] - (2)) <= EPSILON);
  assert(abs(summarize(EVEN)[1][1] - (1)) <= EPSILON);

  assert(abs(summarize(EVEN)[2][0] - (3)) <= EPSILON);
  assert(abs(summarize(EVEN)[2][1] - (1)) <= EPSILON);

  assert(abs(summarize(EVEN)[3][0] - (1)) <= EPSILON);
  assert(abs(summarize(EVEN)[3][1] - (1)) <= EPSILON);

  //dos: 1,2,2,3
  assert(abs(summarize(DOS)[0][0] - (1)) <= EPSILON);
  assert(abs(summarize(DOS)[0][1] - (1)) <= EPSILON);

  assert(abs(summarize(DOS)[1][0] - (2)) <= EPSILON);
  assert(abs(summarize(DOS)[1][1] - (2)) <= EPSILON);

  assert(abs(summarize(DOS)[3][0] - (3)) <= EPSILON);
  assert(abs(summarize(DOS)[3][1] - (1)) <= EPSILON);

  //regular: 0,100,150,151
  assert(abs(summarize(REGULAR)[0][0] - (0)) <= EPSILON);
  assert(abs(summarize(REGULAR)[0][1] - (1)) <= EPSILON);

  assert(abs(summarize(REGULAR)[1][0] - (100)) <= EPSILON);
  assert(abs(summarize(REGULAR)[1][1] - (1)) <= EPSILON);

  assert(abs(summarize(REGULAR)[2][0] - (150)) <= EPSILON);
  assert(abs(summarize(REGULAR)[2][1] - (1)) <= EPSILON);

  assert(abs(summarize(REGULAR)[3][0] - (151)) <= EPSILON);
  assert(abs(summarize(REGULAR)[3][1] - (1)) <= EPSILON);

  //negative: -1,0,1
  assert(abs(summarize(NEGATIVE)[0][0] - (-1)) <= EPSILON);
  assert(abs(summarize(NEGATIVE)[0][1] - (1)) <= EPSILON);

  assert(abs(summarize(NEGATIVE)[1][0] - (0)) <= EPSILON);
  assert(abs(summarize(NEGATIVE)[1][1] - (1)) <= EPSILON);

  assert(abs(summarize(NEGATIVE)[2][0] - (1)) <= EPSILON);
  assert(abs(summarize(NEGATIVE)[2][1] - (1)) <= EPSILON);

  //decimal: -0.1, 1.0, 1.1
  assert(abs(summarize(DECIMAL)[0][0] - (-0.1)) <= EPSILON);
  assert(abs(summarize(DECIMAL)[0][1] - (1)) <= EPSILON);

  assert(abs(summarize(DECIMAL)[1][0] - (1.0)) <= EPSILON);
  assert(abs(summarize(DECIMAL)[1][1] - (1)) <= EPSILON);

  assert(abs(summarize(DECIMAL)[2][0] - (1.1)) <= EPSILON);
  assert(abs(summarize(DECIMAL)[0][1] - (1)) <= EPSILON);

  //zero: 0
  assert(abs(summarize(ZERO)[0][0] - (0)) <= EPSILON);
  assert(abs(summarize(ZERO)[0][1] - (1)) <= EPSILON);

  //backward: 3,2,1
  //assert(abs(summarize(BACKWARD)[0][0] - (3)) <= EPSILON);

  //assert(abs(summarize(REGULAR)[0][0] - (0)) <= EPSILON);

  //edge: 100.123, 200.123, 300.123
  assert(abs(summarize(EDGE)[0][0] - (100.123)) <= EPSILON);
  assert(abs(summarize(EDGE)[0][1] - (1)) <= EPSILON);

  assert(abs(summarize(EDGE)[1][0] - (200.123)) <= EPSILON);
  assert(abs(summarize(EDGE)[1][1] - (1)) <= EPSILON);

  assert(abs(summarize(EDGE)[2][0] - (300.123)) <= EPSILON);
  assert(abs(summarize(EDGE)[2][1] - (1)) <= EPSILON);
  cout << "PASS!" << endl;

}
//count
void test_count() {
  cout << "test_count" << endl;
  //assert(abs(function(vector name) - (value is) ) <= epsilon);
  assert(abs(count(TWICE) - (5)) <= EPSILON);
  assert(abs(count(EVEN) - (4)) <= EPSILON);
  assert(abs(count(DOS) - (4)) <= EPSILON);
  assert(abs(count(REGULAR) - (4)) <= EPSILON);
  assert(abs(count(NEGATIVE) - (3)) <= EPSILON);
  assert(abs(count(DECIMAL) - (3)) <= EPSILON);
  assert(abs(count(ZERO) - (1)) <= EPSILON);
  assert(abs(count(BACKWARD) - (3)) <= EPSILON);
  assert(abs(count(EDGE) - (3)) <= EPSILON);

  cout << "PASS!" << endl;

}

//sum
void test_sum() {
  cout << "test_sum" << endl;

  assert(abs(sum(TWICE) - (9)) <= EPSILON);
  assert(abs(sum(EVEN) - (10)) <= EPSILON);
  assert(abs(sum(DOS) - (8)) <= EPSILON);
  assert(abs(sum(REGULAR) - (401)) <= EPSILON);
  assert(abs(sum(NEGATIVE) - (0)) <= EPSILON);
  assert(abs(sum(DECIMAL) - (2)) <= EPSILON);
  assert(abs(sum(ZERO) - (0)) <= EPSILON);
  assert(abs(sum(BACKWARD) - (6)) <= EPSILON);
  assert(abs(sum(EDGE) - (600.369)) <= EPSILON);

  cout << "PASS!" << endl;

}

//mean 
void test_mean() {
  cout << "test_mean" << endl;

  assert(abs(mean(TWICE) - (1.8)) <= EPSILON);
  assert(abs(mean(EVEN) - (2.5)) <= EPSILON);
  assert(abs(mean(DOS) - (2)) <= EPSILON);
  assert(abs(mean(REGULAR) - (100.25)) <= EPSILON);
  assert(abs(mean(NEGATIVE) - (0)) <= EPSILON);
  assert(abs(mean(DECIMAL) - (0.66666667)) <= EPSILON);
  assert(abs(mean(ZERO) - (0)) <= EPSILON);
  assert(abs(mean(BACKWARD) - (2)) <= EPSILON);
  assert(abs(mean(EDGE) - (200.123)) <= EPSILON);

  cout << "PASS!" << endl;

}
//median
void test_median() {
  cout << "test_median" << endl;

  assert(abs(median(TWICE) - (2)) <= EPSILON);
  assert(abs(median(EVEN) - (2.5)) <= EPSILON);
  assert(abs(median(DOS) - (2)) <= EPSILON);
  assert(abs(median(REGULAR) - (125)) <= EPSILON);
  assert(abs(median(DECIMAL) - (1.0)) <= EPSILON);
  assert(abs(median(ZERO) - (0)) <= EPSILON);
  assert(abs(median(BACKWARD) - (2)) <= EPSILON);
  assert(abs(median(EDGE) - (200.123)) <= EPSILON);

  //assert(abs(median(NEGATIVE) - (0)) <= EPSILON);

  cout << "PASS!" << endl;

}

//mode
void test_mode() {
  cout << "test_mode" << endl;

  assert(abs(mode(TWICE) - (1)) <= EPSILON);
  assert(abs(mode(EVEN) - (1)) <= EPSILON);
  assert(abs(mode(DOS) - (2)) <= EPSILON);
  assert(abs(mode(REGULAR) - (0)) <= EPSILON);
  assert(abs(mode(NEGATIVE) - (-1)) <= EPSILON);
  assert(abs(mode(DECIMAL) - (-0.1)) <= EPSILON);
  assert(abs(mode(ZERO) - (0)) <= EPSILON);
  assert(abs(mode(BACKWARD) - (1)) <= EPSILON);
  assert(abs(mode(EDGE) - (100.123)) <= EPSILON);

  cout << "PASS!" << endl;

}

//min
void test_min() {
  cout << "test_min" << endl;

  assert(abs(min(TWICE) - (1)) <= EPSILON);
  assert(abs(min(EVEN) - (1)) <= EPSILON);
  assert(abs(min(DOS) - (1)) <= EPSILON);
  assert(abs(min(REGULAR) - (0)) <= EPSILON);
  assert(abs(min(NEGATIVE) - (-1)) <= EPSILON);
  assert(abs(min(DECIMAL) - (-0.1)) <= EPSILON);
  assert(abs(min(ZERO) - (0)) <= EPSILON);
  assert(abs(min(BACKWARD) - (1)) <= EPSILON);
  assert(abs(min(EDGE) - (100.123)) <= EPSILON);

  cout << "PASS!" << endl;

}

//max
void test_max() {
  cout << "test_max" << endl;

  assert(abs(max(TWICE) - (3)) <= EPSILON);
  assert(abs(max(EVEN) - (4)) <= EPSILON);
  assert(abs(max(DOS) - (3)) <= EPSILON);
  assert(abs(max(REGULAR) - (151)) <= EPSILON);
  assert(abs(max(NEGATIVE) - (1)) <= EPSILON);
  assert(abs(max(DECIMAL) - (1.1)) <= EPSILON);
  assert(abs(max(ZERO) - (0)) <= EPSILON);
  assert(abs(max(BACKWARD) - (3)) <= EPSILON);
  assert(abs(max(EDGE) - (300.123)) <= EPSILON);

  cout << "PASS!" << endl;

}

//stdev
void test_stdev() {
  cout << "test_stdev" << endl;

  assert(abs(stdev(TWICE) - (0.8366600265340)) <= EPSILON);
  assert(abs(stdev(EVEN) - (1.290994448735)) <= EPSILON);
  assert(abs(stdev(DOS) - (0.81649658092773)) <= EPSILON);
  assert(abs(stdev(REGULAR) - (70.947750727795)) <= EPSILON);
  assert(abs(stdev(NEGATIVE) - (1)) <= EPSILON);
  assert(abs(stdev(DECIMAL) - (0.66583281184794)) <= EPSILON);
  assert(abs(stdev(ZERO) - (0)) <= EPSILON);
  assert(abs(stdev(BACKWARD) - (1)) <= EPSILON);
  assert(abs(stdev(EDGE) - (100)) <= EPSILON);

  cout << "PASS!" << endl;

}

//percentile
void test_percentile() {
  cout << "test_percentile" << endl;

  assert(abs(percentile(TWICE, .25) - (1)) <= EPSILON);
  assert(abs(percentile(TWICE, .50) - (2)) <= EPSILON);
  assert(abs(percentile(TWICE, .75) - (2)) <= EPSILON);
  assert(abs(percentile(TWICE, 1) - (3)) <= EPSILON);

  assert(abs(percentile(EVEN, .25) - (1.75)) <= EPSILON);
  assert(abs(percentile(EVEN, .50) - (2.5)) <= EPSILON);
  assert(abs(percentile(EVEN, .66) - (2.98)) <= EPSILON);

  assert(abs(percentile(DOS, .20) - (1.6)) <= EPSILON);
  assert(abs(percentile(DOS, .40) - (2)) <= EPSILON);
  assert(abs(percentile(DOS, .88) - (2.64)) <= EPSILON);

  assert(abs(percentile(REGULAR, .20) - (60)) <= EPSILON);
  assert(abs(percentile(REGULAR, .88) - (150.64)) <= EPSILON);

  assert(abs(percentile(NEGATIVE, .20) - (-0.6)) <= EPSILON);
  assert(abs(percentile(NEGATIVE, 0) - (-1)) <= EPSILON);
  assert(abs(percentile(NEGATIVE, .99) - (0.98)) <= EPSILON);

  assert(abs(percentile(DECIMAL, .20) - (0.34)) <= EPSILON);
  assert(abs(percentile(DECIMAL, .33) - (0.626)) <= EPSILON);

  assert(abs(percentile(ZERO,0) - (0)) <= EPSILON);
  assert(abs(percentile(ZERO,.90) - (0)) <= EPSILON);
  assert(abs(percentile(ZERO,1) - (0)) <= EPSILON);

  assert(abs(percentile(BACKWARD, 0) - (1)) <= EPSILON);
  assert(abs(percentile(BACKWARD, .02) - (1.04)) <= EPSILON);

  assert(abs(percentile(EDGE, .02) - (104.123)) <= EPSILON);
  assert(abs(percentile(EDGE, .20) - (140.123)) <= EPSILON);

  cout << "PASS!" << endl;

}

//assert(abs(function(vector name) - (value is) ) <= epsilon);