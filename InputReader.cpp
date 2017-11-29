#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "InputReader.h"

using namespace std;

vector<vector<double> > InputReader::parseFile(std::string filepath) {
  return InputReader::parseCSV(InputReader::generateCSV(filepath));
}

vector<string> InputReader::generateCSV(string filepath) {
  string line;
  ifstream infile(filepath);
  vector<string> csv;
  while (getline(infile, line)) {
    if (line.size() != 0) {
      line.erase(0,1);
      line.erase(line.size() -1);
      csv.push_back(line);
    }
  }

  return csv;
}

std::vector<std::vector<double> > InputReader::parseCSV(vector<string> csv) {
  std::vector<std::vector<double> > output;

  for (int i = 0; i < csv.size(); i++) {
    string line = csv[i];
    stringstream ss(line);
    vector<double> data;
    double d;
    while (ss >> d) {
      data.push_back(d);
      ss.ignore(1);
    }
    output.push_back(data);
  }

  return output;
}
