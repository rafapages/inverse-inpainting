#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/photo/photo.hpp>

using namespace cv;

int main(int argc, char *argv[]){

    if( argc != 4){
        std::cerr << "Wrong number of arguments!" << std::endl;
        std::cerr << "Usage: " << argv[0] << " <inputImageName> <inputSilhouetteName> <outputImageName>" << std::endl;
        return -1;
    }

    std::cerr << "Reading " << argv[1] << std::endl;
    Mat inputImage = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    std::cerr << "Reading " << argv[2] << std::endl;
    Mat inputSil   = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);

    threshold(inputSil, inputSil, 1, 255, THRESH_BINARY);
    
    namedWindow( "Original segmentation image", WINDOW_AUTOSIZE );
    imshow( "Original segmentation image", inputSil );

    Mat eroder  = getStructuringElement(MORPH_RECT, Size(5,5));
//    Mat dilater = getStructuringElement(MORPH_RECT, Size(5,5));

    erode(inputSil, inputSil, eroder);
    erode(inputSil, inputSil, eroder);

    Mat invSil =  Scalar::all(255) - inputSil;

    Mat outputImage;

    inpaint(inputImage, invSil, outputImage, 7, INPAINT_TELEA);

    namedWindow( "Input image", WINDOW_AUTOSIZE );
    imshow( "Input image", inputImage );

    namedWindow( "Eroded segmented image", WINDOW_AUTOSIZE );
    imshow( "Eroded segmented image", invSil );

    namedWindow( "Extended output image", WINDOW_AUTOSIZE );
    imshow( "Extended output image", outputImage );
    waitKey(0);

    std::cerr << "Writing " << argv[3] << std::endl;
    imwrite(argv[3], outputImage);


    return 0;
}

