//************** rgb2y.cpp ***************//
// Read a RGB image, convert it to YUV and Y,U,V, and GARY.
//
// $ g++ rgb2y.cpp -o rgb2y `pkg-config --cflags --libs opencv`
// Usage: $ ./rgb2y cat.jpg 
//     

#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

int main(int argc, char const *argv[])
{
    IplImage* rgb = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
    IplImage* ycrcb = cvCreateImage(cvSize(rgb->width, rgb->height), IPL_DEPTH_8U, 3);
    IplImage* y = cvCreateImage(cvSize(rgb->width, rgb->height), IPL_DEPTH_8U, 1);
    IplImage* cr = cvCreateImage(cvSize(rgb->width, rgb->height), IPL_DEPTH_8U, 1);
    IplImage* cb = cvCreateImage(cvSize(rgb->width, rgb->height), IPL_DEPTH_8U, 1);
    IplImage* gray = cvCreateImage(cvSize(rgb->width, rgb->height), IPL_DEPTH_8U, 1);

    cvNamedWindow("RGB image", WINDOW_AUTOSIZE);
    cvNamedWindow("YCRCB image", WINDOW_AUTOSIZE);
    cvNamedWindow("Y image", WINDOW_AUTOSIZE);
    cvNamedWindow("CR image", WINDOW_AUTOSIZE);
    cvNamedWindow("CB image", WINDOW_AUTOSIZE);
    cvNamedWindow("GRAY image", WINDOW_AUTOSIZE);

    cvCvtColor(rgb, ycrcb, CV_BGR2YCrCb);
    cvCvtColor(rgb, gray, CV_BGR2GRAY);
    cvSplit(ycrcb, y, cr, cb, NULL);

    cvShowImage("RGB image", rgb);
    cvShowImage("YCRCB image", ycrcb);
    cvShowImage("Y image", y);
    cvShowImage("CR image", cr);
    cvShowImage("CB image", cb);
    cvShowImage("GRAY image", gray);

    cvWaitKey(0);

    return 0;
}
