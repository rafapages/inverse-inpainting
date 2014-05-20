#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/photo/photo.hpp>


using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{

    Mat inputImage = imread("inputImage.png", CV_LOAD_IMAGE_COLOR);
    Mat inputSil   = imread("inputSil.png", CV_LOAD_IMAGE_GRAYSCALE);

    Mat eroder  = getStructuringElement(MORPH_RECT, Size(7,7));
    erode(inputSil, inputSil, eroder);
    erode(inputSil, inputSil, eroder);

    Mat invSil =  Scalar::all(255) - inputSil;

    Mat outputImage;

    inpaint(inputImage, invSil, outputImage, 7, INPAINT_TELEA);

    namedWindow( "Display window1", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window1", inputImage );                   // Show our image inside it.

    namedWindow( "Display window2", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window2", invSil );                   // Show our image inside it.

    namedWindow( "Display window3", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window3", outputImage );

    waitKey(0);


    return 0;
}

