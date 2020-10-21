#include <iostream>
#include <list>

#include "pid_utils.hpp"

#include <opencv4/opencv2/opencv.hpp>

typedef cv::Vec<uint8_t,3> Vec3b;

int main(int argc, char** argv )
{
    if ( argc != 2 )
	{
        std::cout << "usage: DisplayImage.out <Image_Path>" << std::endl;
        return -1;
    }
    
	cv::Mat image;
    image = cv::imread( argv[1], 1 );
    std::list<uint8_t> lDate;
    
	if ( !image.data )
	{
        printf("No image data \n");
        return -1;
    }
    
	//cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE );
    //cv::imshow("Display Image", image);
    //cv::waitKey(0);

    int i=0;
    int j=0;
    int matRows = image.rows;
    int matCols = image.cols;
    uint8_t iGetIndex;
    for( i = 0; i < matRows; i++)
    {
         for( j = 0; j < matCols; j++)
         {
             iGetIndex = pid::getColorIndex(image.at<cv::Vec3b>(i,j)[2],image.at<cv::Vec3b>(i,j)[1],image.at<cv::Vec3b>(i,j)[0]);
             //iGetIndex=pid::getColorIndex(static_cast<uint8_t>(image.at<cv::Vec3b>(i,j)[2]),static_cast<uint8_t>(image.at<cv::Vec3b>(i,j)[1]),static_cast<uint8_t>(image.at<cv::Vec3b>(i,j)[0]));
             lDate.push_back(iGetIndex);
         }
         /*std::cout<<std::endl<<"-------------"<<std::endl;
         std::list<int8_t>::iterator it=lDate.begin();
         for (; it!=lDate.end(); ++it)
             std::cout<<*it;
         getchar();*/
    }
    
	return 0;
}
