#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

char path[100] = "/Users/aliaksandrzankevich/Education/University/ComputerVision/Projects/OpenCV_5/sample4.jpg";

void fillArea( Mat& img, int x, int y)
{
    
    Point seed = Point(x, y);
    
    int b = (unsigned)theRNG() & 255;
    int g = (unsigned)theRNG() & 255;
    int r = (unsigned)theRNG() & 255;
    
    Rect ccomp;
    
    floodFill(img, seed, Scalar(b, g, r), &ccomp, Scalar(0, 0, 0),
                     Scalar(0, 0, 0), 8);
}

void colorDots(Mat& img) {
    for (int i = 0; i < img.rows - 1; i++) {
        for (int j = 0; j < img.cols - 1; j++) {
            if (img.at<Vec3b>(i, j)[0] == 255 && img.at<Vec3b>(i, j)[1] == 255 && img.at<Vec3b>(i, j)[1] == 255) {
                fillArea(img, j, i);
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    Mat img = imread(path, CV_LOAD_IMAGE_COLOR);
    Mat newImg;
    
    if (img.empty()) {
        cout << "Image cannot be loaded..!!" << endl;
        return -1;
    }
    
    namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
    
    threshold(img, img, 150, 255, 1);
    
    erode(img, img, getStructuringElement(2, Size(20, 20)));
    
    colorDots(img);
    
    dilate(img, img, getStructuringElement(2, Size(20, 20)));
    
    imshow("Original Image", img);
    
    waitKey(0);
    
    destroyAllWindows();
    
    return 0;
}
