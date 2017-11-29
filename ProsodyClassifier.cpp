#include <iostream>

#include "ProsodyClassifier.h"

/**
 * Takes a 2D vector of doubles for positives
 * Takes a 2D vector of double for negatives
 */
ProsodyClassifier::ProsodyClassifier(
    std::vector<std::vector<double> > positives,
    std::vector<std::vector<double> > negatives) {

  int length = positives.size() + negatives.size();
  // 1 or -1, maps to trainingdata to determine whether data is pos or neg
  int labels[length];

  /** label positive data */
  for (int i = 0; i < positives.size(); i++) {
    labels[i] = 1;
  }

  /** label negative data */
  for (int i = positives.size(); i < length; i++) {
    labels[i] = -1;
  }

  // turn positive/negative vectors into a 2d double array
  float trainingDataArray[length][positives[0].size()];

  for (int i = 0; i < positives.size(); i++) {
    for (int j = 0; j < positives[0].size(); j++) {
      trainingDataArray[i][j] = (float)positives[i][j];
    }
  }

  int negativeIndex = 0;
  for (int i = positives.size(); i < length; i++) {
    for (int j = 0; j < negatives[0].size(); j++) {
      trainingDataArray[i][j] = (float)negatives[negativeIndex][j];
    }
    negativeIndex++;
  }

  // Mat for labels
  Mat labelsMat(length, 1, CV_32SC1, labels);

  // create mat for training data. Iterate through vectors to create Mat
  Mat trainingDataMat(length, positives[0].size(), CV_32FC1, trainingDataArray);

  this->svm = SVM::create();
  svm->setType(SVM::C_SVC);
  svm->setKernel(SVM::LINEAR);
  svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
  svm->train(trainingDataMat, ROW_SAMPLE, labelsMat);
}

// this function is untested. Use query(mat) instead
bool ProsodyClassifier::query(std::vector<double> a) {
  float input[a.size()];
  for (int i = 0; i < a.size(); i++) {
    input[i] = (float)a[i];
  }
  Mat queryMat(1, a.size(), CV_32FC1, input);
  float response = svm->predict(queryMat);
  return response == 1;
}

/**
 * Returns true if the classifier trained returns 1
 * Returns false otherwise
 */
bool ProsodyClassifier::query(Mat a) {
  return (svm->predict(a) == 1);
}

/**
 * Takes in a vector of test data (vector<vector<double> >)
 * Returns a vector of the results, either -1 or 1
 */
std::vector<int> ProsodyClassifier::query(std::vector<std::vector<double> > data) {
  std::vector<int> output;
  for (int i = 0; i < data.size(); i++) {
    output.push_back(query(data[i]));
  }

  return output;
}
