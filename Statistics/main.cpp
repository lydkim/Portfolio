// main.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5
#include "stats.h"
#include "p1_library.h"
#include <iostream>
#include <fstream>
using namespace std;
int main() {

  cout << "enter a filename" << endl;
  string filename;
  cin >> filename;
  cout << "enter a column name" << endl;
  string column;
  cin >> column;
  cout << "reading column " << column << " from " << filename << endl;

  cout << "Summary (value: frequency)" << endl;
  vector<double> b = extract_column(filename, column);
  vector<vector<double>> answer = summarize(b);

  for (size_t i = 0; i < b.size(); ++i) {
    cout << answer[i][0] << ": " << answer[i][1] << endl;

  }

  cout << endl;

  cout << "count = " << count(b) <<endl;
  cout << "sum = " << sum(b) << endl;
  cout << "mean = " << mean(b) <<endl;
  cout << "stdev = " << stdev(b) << endl;
  cout << "median = " << median(b) << endl;
  cout << "mode = " << mode(b) << endl;
  cout << "min = " << min(b) << endl;
  cout << "max = " << max(b) << endl;
  
  cout << "  0th percentile = " << percentile(b, 0) << endl;
  cout << " 25th percentile = " << percentile(b, .25) << endl;
  cout << " 50th percentile = " << percentile(b, .50) << endl;
  cout << " 75th percentile = " << percentile(b, .75) << endl;
  cout << "100th percentile = " << percentile(b, 1) << endl;


}

