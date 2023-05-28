//main.cpp
// Project UID db1f506d06d84ab787baf250c265e24e

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include "csvstream.h"
using namespace std;

class Classifier { 
//keep track of the classifier parameters learned from the training data
private:
  //The total number of posts in the entire training set.
  int total_posts = 0;

  //The number of unique words in the entire training set. (The vocabulary size.)
  double vocab_size = 0;

  //For each word w, the number of posts in the entire training set that contain w
  //maybe make this a vector so we can store amounts of all words 
  std::map<string, double> specific_words;

  //For each label C, the number of posts with that label.
  std::map<string, double> label_frequency;

  //For each label C and word w, the number of posts with label C that contain w
  std::map<string, map<string, double>> double_map;

  //storing the label and the int
  std::map<string, double> log_prior;

  //each label with, worse and likelihood
  std::map<string, map<string, double>> log_likelihood;

  //number of correctly predicted scores 


//interface that allows you to train the classifier and make predictions for 
//new piazza posts
public:
    void train (csvstream &input, bool debug) {
    std::map<string, string> row;
    //call the function that prints this out 
    //call a function the does the number of training posts - print
    //call the function does the unique vocab - print
    string bigString = "";
    if (debug) {
        cout << "training data:" << "\n";
    }
    while (input >> row) {
      const string &label = row["tag"];
      const string &content = row["content"];
      bigString += content;
      bigString += " ";
      if (debug) {
        cout << "  label = " << label << ", content = " << content << "\n";
      }
      total_posts++;
      //4th bullet
      label_frequency[label]++;
      set<string> words = unique_words(content);
      for (auto currentWord : words) {
        //3rd bullet
        specific_words[currentWord]++;
        //5th bullet
        double_map[label][currentWord]++;
      }
    }
    cout << "trained on " << total_posts << " examples" << "\n";
    vocab_size = unique_words(bigString).size();
    if (debug == true) {
      cout << "vocabulary size = " << vocab_size << "\n" << "\n";
    }
    else {
      cout << "\n";
    }
  }

void log(bool debug) {
      //log-prior
      if (debug) {
        cout << "classes:"<< "\n";
      }
      for (auto &currentLabel : label_frequency) {
        const auto &word = currentLabel.first; //key string
        auto number = currentLabel.second; //value int
        double logPrior = number / total_posts;
        logPrior = std::log (logPrior);
        log_prior[word] = logPrior;
        if (debug) {
          cout << "  " << word << ", " << number << " examples, log-prior = " << 
          logPrior << "\n"; //log print at end 
        }
      }

      if (debug) {
        cout << "classifier parameters:" << "\n";
      }
      for (auto &currentLabel : double_map) {
        const auto &label = currentLabel.first;
        for (auto &currentWord : currentLabel.second) {
          const auto &word = currentWord.first;
          auto count = currentWord.second; //value int
          logLikelihood(debug, count, word, label);
        }
      }
      if (debug) {
        cout << "\n";
      }
}

void logLikelihood(bool debug, double count, string word, string label) {
  double logLikeLiHood = 0;
  //first
  if (count != 0) {
    logLikeLiHood = std::log (count/label_frequency[label]);
    log_likelihood[label][word] = logLikeLiHood;
  }
  //log when w does not occur anywhere at all in the training set
  else if (specific_words[word] == 0) {
    logLikeLiHood = 1.0 / total_posts;
    logLikeLiHood = std::log(logLikeLiHood);
    log_likelihood[label][word] = logLikeLiHood;
  }
  //log when w does not occur in posts labeled C but does occur in the 
  //training data overall.
  else {
    logLikeLiHood = std::log(specific_words[word] / total_posts);
    log_likelihood[label][word] = logLikeLiHood;
  }
  if (debug) {
    cout << "  " << label << ":" << word << ", count = " << count 
    << ", log-likelihood = " << logLikeLiHood << "\n";
  }
}

//log-probability score
  void score(csvstream &input, bool debug) {
    int correct = 0;
    debug = false;
    std::map<string, string> row;
    cout << "test data:" << "\n";
    string prediction = "";
    int totalTestingPosts = 0;
    while(input >> row) {
      const string &correctLabel = row["tag"];
      const string &content = row["content"];
      totalTestingPosts++;
      double probability_score = 0;
      double highest = -10000000;
      //prediction work
      set<string> words = unique_words(content);
      for (auto &currentLabel : log_prior) {
        const auto &label = currentLabel.first;
        probability_score = log_prior[label];
        for (auto currentWord : words) {
          logLikelihood(debug, double_map[label][currentWord], currentWord, label);
          probability_score += log_likelihood[label][currentWord];
        }
        if (probability_score > highest) {
          highest = probability_score;
          prediction = label;
        }
      }
      cout << "  correct = " << correctLabel << ", predicted = " << 
      prediction << ", log-probability score = " << highest << "\n";
      cout << "  content = " << content << "\n" << "\n";
      if (correctLabel == prediction) {
        correct++;
      }
    }
    cout << "performance: " << correct << " / " << totalTestingPosts 
    << " posts predicted correctly" << "\n";
  }

  // EFFECTS: Return a set of unique whitespace delimited words.x
  set<string> unique_words(const string &str) {
    istringstream source(str);
    set<string> words;
    string word;
    while (source >> word) {
      words.insert(word);
    }
    return words;
  }
};

int main (int argc, char **argv) {
    cout.precision(3);
    string debugging;
    if (argc == 4) {
      debugging = argv[3];
    }
    //error 1: there are 3 or 4 arguments
    if (argc != 3 && argc != 4) {
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return 1;
    }
    //error 2: fourth argument
    if (argc == 4 && debugging != "--debug") {
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return 1;
    }
    //error 3: opening file
    std::ifstream input(argv[1]);
    if (!input) {
        cout << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    std::ifstream other_input(argv[2]);
    if (!input) {
      cout << "Error opening file: " << argv[2] << endl;
        return 1;
    }

    Classifier read;
    csvstream cvsin(argv[1]);
    bool debug = false;
    
    if (argc == 4) {
      debug = true;
    }

    read.train(cvsin, debug);

    read.log(debug);

    csvstream test_file(argv[2]);

    read.score(test_file, debug); 
    return 1;
}