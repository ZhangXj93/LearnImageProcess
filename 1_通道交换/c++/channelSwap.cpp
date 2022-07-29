
#include <iostream>
#include <opencv2/opencv.hpp>
 
using namespace std;
using namespace cv;
 
Mat channelSwap(const Mat& srcImage)
{
    int cols = srcImage.cols;
    int rows = srcImage.rows;
    Mat destImage = Mat::zeros(rows, cols, CV_8UC3);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            destImage.at<Vec3b>(i, j)[0] = srcImage.at<Vec3b>(i, j)[2];
            destImage.at<Vec3b>(i, j)[1] = srcImage.at<Vec3b>(i, j)[1];
            destImage.at<Vec3b>(i, j)[2] = srcImage.at<Vec3b>(i, j)[0];
        }
    }

    return destImage;
}

int main()
{
    Mat srcImage = imread("../imori.jpg");
    imshow("Display Image window", srcImage);
    Mat destImage = channelSwap(srcImage);
    imshow("destImage", destImage);
    waitKey(0);
    return 0;
}
