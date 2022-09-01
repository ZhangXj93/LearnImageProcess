
#include <iostream>
#include <opencv2/opencv.hpp>
 
using namespace std;
using namespace cv;
 
Mat GaussFiltering(const Mat& srcImage, double sigma, int kSize = 3)
{
    int cols = srcImage.cols;
    int rows = srcImage.rows;
    int channels = srcImage.channels();
    Mat destImage = Mat::zeros(rows, cols, CV_8UC3);

    // prepare kernel
    int pad = floor(kSize / 2);
    int x = 0, y = 0;
    double kernel_sum = 0;

    // get guass kernel
    float gaussKernel[kSize][kSize];
    for (int i = 0; i < kSize; i++)
    {
        for (int j = 0; j < kSize; j++)
        {
            int pos_x = j - pad;
            int pos_y = i - pad;
            gaussKernel[i][j] = 1 / (2 * M_PI * sigma * sigma) * exp(-(pos_x * pos_x + pos_y * pos_y) / (2 * sigma * sigma));
            kernel_sum += gaussKernel[i][j]; 
        }
    }

    for (int i = 0; i < kSize; i++)
    {
        for (int j = 0; j < kSize; j++)
        {
            gaussKernel[i][j] /= kernel_sum;
        }
    }

    //filtering
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            for (int k = 0; k < channels; k++)
            {
                double sum = 0;
                for (int di = -pad; di <= pad; di++)
                {
                    for (int dj = -pad; dj <= pad; dj++)
                    {
                        if ((i + di >=0) && (j + dj >= 0))
                        {
                            sum += (double)srcImage.ptr<Vec3b>(i + di)[j + dj][k] * gaussKernel[di + pad][dj + pad];
                        }
                    }
                }
                destImage.ptr<Vec3b>(i)[j][k] = sum;   
            }
        }
    }

    return destImage;
}

int main()
{
    Mat srcImage = imread("../imori_noise.jpg");
    imshow("Display Image window", srcImage);
    Mat destImage = GaussFiltering(srcImage, 1.3, 3);
    imshow("destImage", destImage);

    waitKey(0);
    return 0;
}
