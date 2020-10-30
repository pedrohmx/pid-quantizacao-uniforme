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
    
	cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE );
    cv::imshow("Display Image", image);
    cv::waitKey(0);

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
    int w,h;
    int aux = 0;
	std::cout << "Entre com o tamanho da imagem (width/comprimento/x) (height/altura/y):" << std::endl;
	std::cin >>	w >> h;
	pid::BMP8b mapc(w,h);
	for (size_t i = 0; i < mapc.data.size(); i++)
    {
        mapc.data[i] = lDate.front();
        lDate.pop_front();
    }
    //std::cout<<lDate.size()<<std::endl;
	std::string strout = "teste_" + std::to_string(w) + "x" + std::to_string(h) + ".bmp";
	mapc.write(strout.c_str());
	return 0;
}