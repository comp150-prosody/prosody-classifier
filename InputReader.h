/**
 * InputReader.h
 */

#ifndef INPUTREADER_H_
#define INPUTREADER_H_

using namespace std;

class InputReader {
  public:
    static vector<vector<double> > parseFile(std::string filepath);
    static vector<string> generateCSV(std::string filepath);
    static std::vector<std::vector<double> > parseCSV(vector<string> csv);
};

#endif
