
#include <iostream>
#include <opencv2/opencv.hpp>
 
using namespace std;
using namespace cv;
 
Mat AveragePooling(const Mat& srcImage, int G = 8)
{
    int cols = srcImage.cols;
    int rows = srcImage.rows;
    int channels = srcImage.channels();
    Mat destImage = Mat::zeros(rows, cols, CV_8UC3);

    int nH = rows / G;
    int nW = cols / G;

    for (int i = 0; i < nH; ++i)
    {
        for (int j = 0; j < nW; ++j)
        {
            for (int k = 0; k < channels; ++k)
            {
                int g_max = 0;
                for (int i_index = i * G; i_index < (i+1) * G; ++i_index)
                {
                    for (int j_index = j * G; j_index < (j+1) * G; ++j_index)
                    {
                        if (srcImage.ptr<cv::Vec3b>(i_index)[j_index][k] > g_max)
                        g_max = srcImage.ptr<cv::Vec3b>(i_index)[j_index][k];
                    }
                }
                for (int i_index = i * G; i_index < (i+1) * G; ++i_index)
                {
                    for (int j_index = j * G; j_index < (j+1) * G; ++j_index)
                    {
                        destImage.ptr<cv::Vec3b>(i_index)[j_index][k] = (int)g_max;
                    }
                }
            }
        }
    }

    return destImage;
}

int main()
{
    Mat srcImage = imread("../imori.jpg");
    imshow("Display Image window", srcImage);
    Mat destImage = AveragePooling(srcImage);
    imshow("destImage", destImage);

    waitKey(0);
    return 0;
}
