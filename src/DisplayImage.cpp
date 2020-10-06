#include <iostream>

#include <opencv4/opencv2/opencv.hpp>

//using namespace cv;

int main(int argc, char** argv )
{
    if ( argc != 2 )
	{
        std::cout << "usage: DisplayImage.out <Image_Path>" << std::endl;
        return -1;
    }
    
	cv::Mat image;
    image = cv::imread( argv[1], 1 );
    
	if ( !image.data )
	{
        printf("No image data \n");
        return -1;
    }
    
	cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE );
    cv::imshow("Display Image", image);
    cv::waitKey(0);
    
	return 0;
}
