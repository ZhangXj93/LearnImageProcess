
#include <iostream>
#include <opencv2/opencv.hpp>
 
using namespace std;
using namespace cv;
 
Mat DecreaseColor(const Mat& srcImage)
{
    int cols = srcImage.cols;
    int rows = srcImage.rows;
    int channels = srcImage.channels();
    Mat destImage = Mat::zeros(rows, cols, CV_8UC3);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            for (int k = 0; k < channels; ++k)
            {
                destImage.ptr<cv::Vec3b>(i)[j][k] = srcImage.ptr<cv::Vec3b>(i)[j][k] / 64 * 64 + 32;
            }
        }
    }

    return destImage;
}

int main()
{
    Mat srcImage = imread("../imori.jpg");
    imshow("Display Image window", srcImage);
    Mat destImage = DecreaseColor(srcImage);
    imshow("destImage", destImage);

    waitKey(0);
    return 0;
}
