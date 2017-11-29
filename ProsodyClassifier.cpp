#include <iostream>

#include "ProsodyClassifier.h"

ProsodyClassifier::ProsodyClassifier(std::vector<std::vector<double> > positives, std::vector<std::vector<double> > negatives) {
  int length = positives.size() + negatives.size();
  int labels[length];

  /** label positive data */
  for (int i = 0; i < positives.size(); i++) {
    labels[i] = 1;
  }

  /** label negative data */
  for (int i = positives.size(); i < length; i++) {
    labels[i] = -1;
  }

  // add negatives into positives vector, to create one vector
  std::vector<std::vector<double> > trainingDataVector;

  for (int i = 0; i < positives.size(); i++) {
    trainingDataVector.push_back(positives[i]);
  }
  for (int i = 0; i < negatives.size(); i++) {
    trainingDataVector.push_back(negatives[i]);
  }

  // Mat for labels
  Mat labelsMat(length, 1, CV_32SC1, labels);

  // create mat for training data. Iterate through vectors to create Mat
  Mat trainingDataMat(trainingDataVector.size(), trainingDataVector[0].size(), CV_32FC1);

  for (int i = 0; i < trainingDataVector.size(); i++) {
    for (int j = 0; j < trainingDataVector[0].size(); j++) {
      trainingDataMat.at<double>(i,j) = trainingDataVector[i][j];
      std::cout << trainingDataVector[i][j];
    }
    std::cout << "\n";
  }

  std::cout << trainingDataMat << std::endl;

  this->svm = SVM::create();
  svm->setType(SVM::C_SVC);
  svm->setKernel(SVM::LINEAR);
  svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
  svm->train(trainingDataMat, ROW_SAMPLE, labelsMat);
}

bool ProsodyClassifier::query(std::vector<double> a) {
  Mat queryMat(a.size(), 1, CV_32FC1, &a[0]);
  float response = svm->predict(queryMat);
  return response == 1;
}

bool ProsodyClassifier::query(Mat a) {
  return (svm->predict(a) == 1);
}
