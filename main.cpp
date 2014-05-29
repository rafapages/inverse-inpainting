#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/photo/photo.hpp>


using namespace std;
using namespace cv;

int main(int argc, char *argv[]){

    if( argc != 4){
        cout << "Wrong number of arguments!" << endl;
        return -1;
    }

    Mat inputImage = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    Mat inputSil   = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);

    threshold(inputSil, inputSil, 1, 255, THRESH_BINARY);

    namedWindow( "Original segmentation image", WINDOW_AUTOSIZE );
    imshow( "Original segmentation image", inputSil );

    Mat eroder  = getStructuringElement(MORPH_RECT, Size(5,5));
//    Mat dilater = getStructuringElement(MORPH_RECT, Size(5,5));

    erode(inputSil, inputSil, eroder);
//    erode(inputSil, inputSil, eroder);

    Mat invSil =  Scalar::all(255) - inputSil;

    Mat outputImage;

    inpaint(inputImage, invSil, outputImage, 7, INPAINT_TELEA);

    namedWindow( "Input image", WINDOW_AUTOSIZE );
    imshow( "Input image", inputImage );

    namedWindow( "Eroded segmented image", WINDOW_AUTOSIZE );
    imshow( "Eroded segmented image", invSil );

    namedWindow( "Extended output image", WINDOW_AUTOSIZE );
    imshow( "Extended output image", outputImage );

    imwrite(argv[3], outputImage);
    waitKey(0);

    return 0;
}

