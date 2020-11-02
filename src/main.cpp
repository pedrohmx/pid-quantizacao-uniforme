#include <iostream>
#include <fstream>
#include <vector>
#include <array>

#include "pid_utils.hpp"
#include "bmp.hpp"

#include <opencv4/opencv2/opencv.hpp>

typedef cv::Vec<uint8_t,3> Vec3b;

int main(int argc, char** argv )
{
    if ( argc != 2 )
	{
        std::cout << "usage: " << argv[0] << " <Image_Path>" << std::endl;
        return 0;
    }
    
	cv::Mat image;
    image = cv::imread( argv[1], 1 );

    std::list<uint8_t> lDate;
    
	if ( !image.data )
	{
        printf("No image data \n");
        return -1;
    }

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
            lDate.push_back(iGetIndex);
        }
    }

	pid::BMP8b mapc(matCols, matRows);
	for (size_t i = 0; i < mapc.data.size(); i++)
    {
        mapc.data[i] = lDate.front();
        lDate.pop_front();
    }

	mapc.write("teste_out.bmp");

	return 0;
}