#include <iostream>
#include <list>
#include <fstream>

#include <opencv4/opencv2/opencv.hpp>

int main(int argc, char** argv )
{
    if ( argc != 2 )
	{
        std::cout << "usage: DisplayImage.out <Image_Path>" << std::endl;
        return -1;
    }
    
	cv::Mat image;
    image = cv::imread( argv[1], 1 );
    std::list<char> lDate;
    //std::ofstream aTest;
    //aTest.open("texto.txt");
    
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
    /*for(i=0;j<;i++)
    {
        for(j=0;j<;j++)
        {
            cout << image.at<int8_t>(i,j)
        }
    }*/
    cv::MatIterator_<char> _it = image.begin<char>();
    for(;_it!=image.end<char>(); _it++){
        //std::cout << *_it << std::endl;
        //aTest<<*_it;
        lDate.push_back(*_it);
    }
    //aTest.close();
    
	return 0;
}
