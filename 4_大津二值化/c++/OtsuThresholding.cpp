
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

Mat Thresholding(const Mat& srcImage, int threshold = 128)
{
    int cols = srcImage.cols;
    int rows = srcImage.rows;

    Mat destImage = Mat::zeros(rows, cols, CV_8UC1);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (srcImage.ptr<unsigned char>(i)[j] >= 128)
            {
                destImage.ptr<unsigned char>(i)[j] = 255;
            }
            else
            {
                destImage.ptr<unsigned char>(i)[j] = 0;
            }
        }
    }

    return destImage;
}

int OtsuThresholdingValue(const Mat& srcImage)
{
    int th = 0;
    int max_sigma = 0;
    for (int i = 1; i <= 255; ++i)
    {
        int nCountUp = 0;
        int nCountDown = 0;
        int nSumUp = 0;
        int nSumDown = 0;
        for (int j = 0; j < srcImage.rows; ++j)
        {
            for (int k = 0; k < srcImage.cols; ++k)
            {
                int nValue = srcImage.ptr<unsigned char>(j)[k];
                if (nValue <= i)
                {
                    nCountDown++;
                    nSumDown += nValue;
                }
                else
                {
                    nCountUp++;
                    nSumUp += nValue;
                }
            }
        }

        float fMeanDown = nCountDown == 0 ? 0 : (float)nSumDown / (float)nCountDown;
        float fMeanUp = nCountUp == 0 ? 0 : (float)nSumUp / (float)nCountUp;
        float w0 = (float)nCountDown / (srcImage.cols * srcImage.rows);
        float w1 = (float)nCountUp / (srcImage.rows * srcImage.cols);

        float sigma = w0 * w1 * pow((fMeanDown - fMeanUp), 2);
        if (sigma > max_sigma)
        {
            max_sigma = sigma;
            th = i;
        }    
    }

    std::cout << "th: " << th << std::endl;
    return th;
}

int main()
{
    Mat srcImage = imread("../imori.jpg");
    imshow("Display Image window", srcImage);
    Mat destImage = RGB2Gray(srcImage);
    imshow("destImage", destImage);
    int th = OtsuThresholdingValue(destImage);
    destImage = Thresholding(destImage, th);
    imshow("threshold image", destImage);
    waitKey(0);
    return 0;
}
