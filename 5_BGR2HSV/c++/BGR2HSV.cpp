
#include <iostream>
#include <opencv2/opencv.hpp>
 
using namespace std;
using namespace cv;
 
Mat BGR2HSV(const Mat& srcImage)
{
    int cols = srcImage.cols;
    int rows = srcImage.rows;
    Mat destImage = Mat::zeros(rows, cols, CV_32FC3);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            float r = srcImage.ptr<cv::Vec3b>(i)[j][2] / 255.0;
            float g = srcImage.ptr<cv::Vec3b>(i)[j][1] / 255.0;
            float b = srcImage.ptr<cv::Vec3b>(i)[j][0] / 255.0;

            float max_v = fmax(r, fmax(g, b));
            float min_v = fmin(r, fmin(g, b));

            float s = max_v - min_v;
            float v = max_v;
            float h = 0.0;
            if (max_v == min_v)
            {
                h = 0.0;
            }
            else if (min_v == r)
            {
                h = 60 * (b - g) / s + 180;
            }
            else if (min_v == g)
            {
                h = 60 * (r - b) / s + 300;
            }
            else if (min_v == b)
            {
                h = 60 * (g - r) / s + 60;
            }

            destImage.ptr<cv::Vec3f>(i)[j][0] = h;
            destImage.ptr<cv::Vec3f>(i)[j][1] = s;
            destImage.ptr<cv::Vec3f>(i)[j][2] = v;
        }
    }

    return destImage;
}

// inverse Hue
cv::Mat inverseHue(cv::Mat hsv)
{
    int height = hsv.rows;
    int width = hsv.cols;

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            hsv.at<cv::Vec3f>(y, x)[0] = fmod(hsv.at<cv::Vec3f>(y, x)[0] + 180, 360);
        }
    }

    return hsv;
}



int main()
{
    Mat srcImage = imread("../imori.jpg");
    imshow("Display Image window", srcImage);
    Mat destImage = BGR2HSV(srcImage);
    imshow("destImage", destImage);

    // Inverse Hue
    destImage = inverseHue(destImage);
    imshow("threshold image", destImage);

    waitKey(0);
    return 0;
}
