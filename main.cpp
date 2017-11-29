#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>
#include "ProsodyClassifier.h"
#include "InputReader.h"
using namespace cv;
using namespace cv::ml;

void testInputReader() {
  vector<vector<double> > pos_data = InputReader::parseFile("./data/pos_mean.txt");

  for (int r = 0; r < pos_data.size(); r++) {
    for (int c = 0; c < pos_data[0].size(); c++) {
      cout << pos_data[r][c];
    }
    cout << "\n";
  }
}

void run(int argc, char *argv[]) {
  if (argc != 4) {
    cout << "./main positive_training negative_training test_data" << endl;
  } else {
    vector<vector<double> > pos_data = InputReader::parseFile(argv[1]);
    vector<vector<double> > neg_data = InputReader::parseFile(argv[2]);
    vector<vector<double> > test_data = InputReader::parseFile(argv[3]);

    ProsodyClassifier pc(pos_data, neg_data);

    vector<int> out = pc.query(test_data);

    for (int i = 0; i < out.size(); i++) {
      std::cout << out[i] << ", ";
    }
    std::cout << endl;

    std::cout << "positive data size: " << pos_data.size() << endl;
    std::cout << "negative data size: " << neg_data.size() << endl;
    std::cout << "test_data size: " << test_data.size() << endl;
    std::cout << "output size: " << out.size() << endl;
    std::cout << endl;
  }
}

int main(int argc, char *argv[])
{
    run(argc, argv);
    /*
    std::vector<std::vector<double> > positives;
    std::vector<std::vector<double> > negatives;

    std::vector<double> row1;
    row1.push_back(200);
    row1.push_back(10);

    std::vector<double> row2;
    row2.push_back(255);
    row2.push_back(10);

    std::vector<double> row3;
    row3.push_back(200);
    row3.push_back(255);

    std::vector<double> row4;
    row4.push_back(10);
    row4.push_back(501);

    positives.push_back(row1);
    positives.push_back(row2);
    positives.push_back(row3);
    negatives.push_back(row4);

    ProsodyClassifier pc(positives, negatives);

    // Data for visual representation
    int width = 512, height = 512;
    Mat image = Mat::zeros(height, width, CV_8UC3);
    // Set up training data
    int labels[4] = {1, 1, 1, -1};
    float trainingData[4][2] = { {200, 10}, {255, 10}, {200, 255}, {10, 501} };
    Mat trainingDataMat(4, 2, CV_32FC1, trainingData);
    Mat labelsMat(4, 1, CV_32SC1, labels);

    // Train the SVM
    Ptr<SVM> svm = SVM::create();
    svm->setType(SVM::C_SVC);
    svm->setKernel(SVM::LINEAR);
    svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
    svm->train(trainingDataMat, ROW_SAMPLE, labelsMat);
    // Show the decision regions given by the SVM
    Vec3b green(0,255,0), blue (255,0,0);
    for (int i = 0; i < image.rows; ++i)
        for (int j = 0; j < image.cols; ++j)
        {
            Mat sampleMat = (Mat_<float>(1,2) << j,i);
            bool result = pc.query(sampleMat);
            float response = svm->predict(sampleMat);
            if (result)
                image.at<Vec3b>(i,j)  = green;
            else if (response == -1)
                image.at<Vec3b>(i,j)  = blue;
        }
    // Show the training data
    int thickness = -1;
    int lineType = 8;
    circle( image, Point(501,  10), 5, Scalar(  0,   0,   0), thickness, lineType );
    circle( image, Point(255,  10), 5, Scalar(255, 255, 255), thickness, lineType );
    circle( image, Point(501, 255), 5, Scalar(255, 255, 255), thickness, lineType );
    circle( image, Point( 10, 501), 5, Scalar(255, 255, 255), thickness, lineType );
    // Show support vectors
    thickness = 2;
    lineType  = 8;
    Mat sv = svm->getUncompressedSupportVectors();
    for (int i = 0; i < sv.rows; ++i)
    {
        const float* v = sv.ptr<float>(i);
        circle( image,  Point( (int) v[0], (int) v[1]),   6,  Scalar(128, 128, 128), thickness, lineType);
    }
    imwrite("result.png", image);        // save the image
    imshow("SVM Simple Example", image); // show it to the user
    waitKey(0);
    */
}
