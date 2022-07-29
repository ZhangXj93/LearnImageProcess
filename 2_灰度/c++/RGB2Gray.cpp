
#include <iostream>
#include <opencv2/opencv.hpp>
 
using namespace std;
using namespace cv;
 
Mat RGB2Gray(const Mat& srcImage)
{
    int cols = srcImage.cols;
    int rows = srcImage.rows;
    Mat destImage = Mat::zeros(rows, cols, CV_8UC1);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            // 0.2126\ R + 0.7152\ G + 0.0722\ B
            destImage.ptr<unsigned char>(i)[j] = 0.2126 * srcImage.ptr<Vec3b>(i)[j][0] \
                + 0.7152 * srcImage.ptr<Vec3b>(i)[j][1] \
                + 0.0722 * srcImage.ptr<Vec3b>(i)[j][2];
        }
    }

    return destImage;
}

int main()
{
    Mat srcImage = imread("../imori.jpg");
    imshow("Display Image window", srcImage);
    Mat destImage = RGB2Gray(srcImage);
    imshow("destImage", destImage);
    waitKey(0);
    return 0;
}
