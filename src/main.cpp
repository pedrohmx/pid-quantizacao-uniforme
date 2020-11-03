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
    
	cv::Mat input_image, flipped_image;
    input_image = cv::imread( argv[1], 1 );

	if ( !input_image.data )
	{
        printf("No image data \n");
        return -1;
    }

    cv::flip(input_image, flipped_image, 0);//flips image 

    std::list<uint8_t> lDate;

    int i = 0;
    int j = 0;
    int matRows = flipped_image.rows;
    int matCols = flipped_image.cols;
    uint8_t iGetIndex;

    for( i = 0; i < matRows; i++)
    {
        for( j = 0; j < matCols; j++)
    	{
            iGetIndex = pid::getColorIndex(// OpenCV stores the image color information in memory as (BGR)
                flipped_image.at<cv::Vec3b>(i,j)[2],  //R
                flipped_image.at<cv::Vec3b>(i,j)[1],  //G
                flipped_image.at<cv::Vec3b>(i,j)[0]); //B
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