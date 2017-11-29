/**
 * ProsodyClassifier.h
 */

#ifndef PROSODYCLASSIFIER_H_
#define PROSODYCLASSIFIER_H_

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>
#include <iostream>

using namespace cv;
using namespace cv::ml;

class ProsodyClassifier {
  public:
    ProsodyClassifier(std::vector<std::vector<double> > positives, std::vector<std::vector<double> > negatives);
    bool query(std::vector<double> a);
    bool query(Mat a);
  private:
    Ptr<SVM> svm;
};

#endif
