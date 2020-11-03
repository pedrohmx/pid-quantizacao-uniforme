#include <iostream>
#include <fstream>
#include <vector>
#include <array>

#include "pid_utils.hpp"
#include "bmp.hpp"

#include "argparse/argparse.hpp"

#include <opencv4/opencv2/opencv.hpp>

typedef cv::Vec<uint8_t,3> Vec3b;

int main(int argc, char** argv ){

    argparse::ArgumentParser parser("quantizacao-uniforme");

	parser.add_argument("input")
		.help("Path to input image.");
	
	parser.add_argument("output")
		.help("Path to output value (default unnamed.bmp)")
		.default_value("unnamed.bmp");

	try {
		parser.parse_args(argc,argv);
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
		std::cerr << parser << std::endl;
		exit(0);
	}
    
	cv::Mat input_image, flipped_image;
    input_image = cv::imread( parser.get<std::string>("input").c_str(), 1 );

	if ( !input_image.data )
	{
        printf("Error: could not open image\n");
        return -1;
    }

    cv::flip(input_image, flipped_image, 0);//flips image 

    std::list<uint8_t> data_list;

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
            data_list.push_back(iGetIndex);
        }
    }

	pid::BMP8b out_bitmap(matCols, matRows);

	for (size_t i = 0; i < out_bitmap.data.size(); i++)
    {
        out_bitmap.data[i] = data_list.front();
        data_list.pop_front();
    }

	out_bitmap.write(parser.get<std::string>("output").c_str());

	return 0;
}